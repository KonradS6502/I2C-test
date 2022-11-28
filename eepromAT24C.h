#include <avr/io.h>

#define I2C_DIRECTION_BIT_WRITE                         0
#define I2C_DIRECTION_BIT_READ                          1
#define I2C_SET_ADDR_POSITION(address)                  (address << 1)           
#define I2C_SLAVE_RESPONSE_ACKED                        (!(TWI_RXACK_bm & TWI0.MSTATUS))
#define I2C_DATA_RECEIVED                               (TWI_RIF_bm & TWI0.MSTATUS)
#define I2C_DATA_SEND                               (TWI_WIF_bm & TWI0.MSTATUS)

/* 
 * Initialization of I2C is obligatory before use.
 * Example of initialization:
 * 
 * void I2C_init(void){
    TWI0.MBAUD=0xFF;
    TWI0.MCTRLA|=_BV(0);
    TWI0.MSTATUS|=_BV(0);
}
 */
void I2C_0_transmittingAddrPacket(uint8_t slaveAddres, uint8_t directionBit);
uint8_t I2C_0_receivingDataPacket(void);
void I2C_0_sendMasterCommand(uint8_t newCommand);
void I2C_0_setACKAction(void);
void I2C_0_setNACKAction(void);
void write_EEPROM(uint16_t memory_address, uint8_t data_to_write);
uint8_t read_random_EEPROM(uint16_t memory_address);
