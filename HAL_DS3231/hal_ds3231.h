#ifndef HAL_DS3231_H
#define HAL_DS3231_H
#include <stdint.h>
#include <time.h>

// i2c slave address of the DS3231 chip
#define DS3231_SLA                  0x68

#define DS3231_12                   1<<6
#define DS3231_24                   0<<6
#define DS3231_CENTURY              1<<7

// timekeeping registers
#define DS3231_TIME_CAL_ADDR        0x00
#define DS3231_ALARM1_ADDR          0x07
#define DS3231_ALARM2_ADDR          0x0B
#define DS3231_CONTROL_ADDR         0x0E
#define DS3231_STATUS_ADDR          0x0F
#define DS3231_AGING_OFFSET_ADDR    0x10
#define DS3231_TEMPERATURE_ADDR     0x11

// control register bits
#define DS3231_CONTROL_A1IE     0x1		/* Alarm 2 Interrupt Enable */
#define DS3231_CONTROL_A2IE     0x2		/* Alarm 2 Interrupt Enable */
#define DS3231_CONTROL_INTCN    0x4		/* Interrupt Control */
#define DS3231_CONTROL_RS1	    0x8		/* square-wave rate select 2 */
#define DS3231_CONTROL_RS2    	0x10	/* square-wave rate select 2 */
#define DS3231_CONTROL_CONV    	0x20	/* Convert Temperature */
#define DS3231_CONTROL_BBSQW    0x40	/* Battery-Backed Square-Wave Enable */
#define DS3231_CONTROL_EOSC	    0x80	/* not Enable Oscillator, 0 equal on */


// status register bits
#define DS3231_STATUS_A1F      0x01		/* Alarm 1 Flag */
#define DS3231_STATUS_A2F      0x02		/* Alarm 2 Flag */
#define DS3231_STATUS_BUSY     0x04		/* device is busy executing TCXO */
#define DS3231_STATUS_EN32KHZ  0x08		/* Enable 32KHz Output  */
#define DS3231_STATUS_OSF      0x80		/* Oscillator Stop Flag */

typedef struct _DS3231 {
    void (*i2c_transmit)(uint8_t sla_address, uint8_t *send_data, uint8_t bytes);
    void (*i2c_receive)(uint8_t sla_address, uint8_t *rec_data, uint8_t bytes);
}DS3231_t;


typedef struct _RTC {
    struct tm time;     /* time.h tm sturct to store time data */
    void (*init)(void);
    void (*update_time)(void);
    void (*set_time)(struct tm *time);
    uint8_t (*decode)(uint8_t data);
    uint8_t (*encode)(uint8_t data);
}RTC_t;

#endif  /* HAL_DS3231_H */
