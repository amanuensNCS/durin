#include "vl53l5cx_api.h"
#include "vl53l5cx_plugin_async.h"

#include "durin.h"
#include "hardware.h"
#include "tof_and_expander.h"
#include "pt.h"

#define EXPANDER_ADDRESS (0x20)

#define NUM_VL53L5CX 8
#define VL53L5CX_ADDRESS_CHAIN_START 0x41
VL53L5CX_Configuration tof_sensors[NUM_VL53L5CX];

#define TOF_I2C_WAIT() do { PT_YIELD(pt); } while (nbe_i2c_is_busy(&durin.hw.i2c_tof))
#define TOF_I2C_WAIT_BLOCK() do {} while (nbe_i2c_is_busy(&durin.hw.i2c_tof))

void expander_write(uint16_t output);
void expander_read(uint8_t *buf);
uint16_t expander_parse(uint8_t *buf);

void init_tof_and_expander() {
    durin.hw.port_expander_ouput = ~0; // everything defaults to 1
    expander_write(durin.hw.port_expander_ouput);
    TOF_I2C_WAIT_BLOCK();
    
    //reset all
    /* already 1 
    for (uint8_t i = 0; i < NUM_VL53L5CX; i++) {
        durin.hw.port_expander_ouput |= 1 << (TOF_RESET_START + i);
    }
    expander_write(durin.hw.port_expander_ouput);
    TOF_I2C_WAIT_BLOCK();
    */

    for (uint8_t i = 0 ; i < NUM_VL53L5CX; i++) {
        //unreset sensor
        durin.hw.port_expander_ouput &= ~(1 << (TOF_RESET_START + i));
        expander_write(durin.hw.port_expander_ouput);
        TOF_I2C_WAIT_BLOCK();

        VL53L5CX_Platform platform;
        platform.address = VL53L5CX_DEFAULT_I2C_ADDRESS;
        platform.nbe_i2c = &durin.hw.i2c_tof;
        tof_sensors[i].platform = platform;
        uint8_t alive;
        vl53l5cx_is_alive(&tof_sensors[i], &alive);
        if (!alive) {
            printf("dead tof sensor with index %d\n", i);
            continue;
        }

        vl53l5cx_init(&tof_sensors[i]);
        vl53l5cx_set_i2c_address(&tof_sensors[i], VL53L5CX_ADDRESS_CHAIN_START + i);
    }
}

void update_tof_and_expander(struct pt *pt) {
    PT_BEGIN(pt);

    static uint32_t current_port_output = 1 << 16; // only 16 outputs so this value is "invalid"
    static uint8_t tof_index;
    
    while (1) {
        if (current_port_output != durin.hw.port_expander_ouput) {
            expander_write(durin.hw.port_expander_ouput);
            TOF_I2C_WAIT();
            current_port_output = durin.hw.port_expander_ouput;
        }
        static uint8_t buf[2];
        expander_read(buf);
        TOF_I2C_WAIT();
        durin.hw.port_expander_input = expander_parse(buf);

        for (tof_index = 0; tof_index < NUM_VL53L5CX; tof_index++) {
            vl53l5cx_get_ranging_data_async_start(&tof_sensors[tof_index]);
            TOF_I2C_WAIT();
            VL53L5CX_ResultsData result;
            //vl53l5cx_get_ranging_data_async_finish(&tof_sensors[tof_index], &result);
            for (uint8_t i = 0; i < 64; i++) {
                //durin.telemetry.ranging_data[tof_index][i] = result.distance_mm[i] / 1000.0;
            }

            PT_YIELD(pt);
        }
    }
    PT_END(pt);
}

void expander_write(uint16_t output) {
    uint8_t buf[2];
    buf[0] = output & 0x00ff;
    buf[1] = (output >> 8) & 0x00ff;
    nbe_i2c_start_write(&durin.hw.i2c_tof, EXPANDER_ADDRESS, NULL, NULL);
    nbe_i2c_write_preamble(&durin.hw.i2c_tof, buf, 2);
    nbe_i2c_stop(&durin.hw.i2c_tof);
    nbe_i2c_commit(&durin.hw.i2c_tof);
}

void expander_read(uint8_t *buf) {
    nbe_i2c_start_read(&durin.hw.i2c_tof, EXPANDER_ADDRESS, NULL, buf);
    nbe_i2c_read(&durin.hw.i2c_tof, 2);
    nbe_i2c_stop(&durin.hw.i2c_tof);
    nbe_i2c_commit(&durin.hw.i2c_tof);
}

uint16_t expander_parse(uint8_t *buf) {
    return buf[0] + (buf[1] << 8);
}