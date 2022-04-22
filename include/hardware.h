#define LED_SPEED_MODE LEDC_LOW_SPEED_MODE
#define LED_FREQUENCY 5000

#define BUZZER_FREQ 3000

#define TIMER_LED_R LEDC_TIMER_0
#define TIMER_LED_G LEDC_TIMER_1
#define TIMER_LED_B LEDC_TIMER_2
#define TIMER_BUZZER LEDC_TIMER_3

#define CHANNEL_LED_R LEDC_CHANNEL_0
#define CHANNEL_LED_G LEDC_CHANNEL_1
#define CHANNEL_LED_B LEDC_CHANNEL_2
#define CHANNEL_BUZZER LEDC_CHANNEL_3


#define PIN_LED_R GPIO_NUM_4
#define PIN_LED_G GPIO_NUM_5
#define PIN_LED_B GPIO_NUM_18
#define PIN_BUZZER GPIO_NUM_27

#define PIN_TOF_SDA GPIO_NUM_33
#define PIN_TOF_SCL GPIO_NUM_25

#define PIN_IMU_SDA GPIO_NUM_23
#define PIN_IMU_SCL GPIO_NUM_21

#define I2C_IMU_HZ 40000
#define I2C_TOF_HZ 200000

#define I2C_NUM_TOF 0
#define I2C_NUM_IMU 1

#define UART_SERVO UART_NUM_2
#define UART_USER UART_NUM_0

#define PIN_UART_USER_TX GPIO_NUM_3
#define PIN_UART_USER_RX GPIO_NUM_1

#define PIN_UART_SERVO_TX GPIO_NUM_17
#define PIN_UART_SERVO_RX GPIO_NUM_16

#define UART_USER_BAUD 2000000
#define UART_SERVO_BAUD 1000000

#define PIN_SPI_UWB_SCK GPIO_NUM_14
#define PIN_SPI_UWB_MISO GPIO_NUM_12
#define PIN_SPI_UWB_MOSI GPIO_NUM_13
#define PIN_SPI_UWB_CS GPIO_NUM_15

#define SPI_UWB_HZ 1000000
#define SPI_UWB_NUM 2

#define PIN_VBAT_SENSE_GND GPIO_NUM_32

#define PIN_BAT_SENSE GPIO_NUM_34
#define CHANNEL_BAT_SENSE ADC1_CHANNEL_0

#define PIN_3V3_EN GPIO_NUM_26
#define PIN_BUTTON_IN GPIO_NUM_35


#define TOF_RESET_START 0
#define TOF_RESET_END 7

#define EX_PIN_UWB_RST (2 + 8)
#define EX_PIN_3V3_PG (3 + 8)
#define EX_PIN_USER_PG (4 + 8)
#define EX_PIN_USER_EN (5 + 8)
#define EX_PIN_SERVO_PG (6 + 8)
#define EX_PIN_SERVO_EN (7 + 8)

#define EX_PIN_TOF_0 0
#define EX_PIN_TOF_1 1
#define EX_PIN_TOF_2 2
#define EX_PIN_TOF_3 3
#define EX_PIN_TOF_4 4
#define EX_PIN_TOF_5 5
#define EX_PIN_TOF_6 6
#define EX_PIN_TOF_7 7