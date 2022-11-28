#include <avr/io.h>

#define I2C_DIRECTION_BIT_WRITE                         0
#define I2C_DIRECTION_BIT_READ                          1
#define I2C_SET_ADDR_POSITION(address)                  (address << 1)           
#define I2C_SLAVE_RESPONSE_ACKED                        (!(TWI_RXACK_bm & TWI0.MSTATUS))
#define I2C_DATA_RECEIVED                               (TWI_RIF_bm & TWI0.MSTATUS)
#define I2C_DATA_SEND                               (TWI_WIF_bm & TWI0.MSTATUS)


static void I2C_0_transmittingAddrPacket(uint8_t slaveAddres, uint8_t directionBit);
static uint8_t I2C_0_receivingDataPacket(void);
static void I2C_0_sendMasterCommand(uint8_t newCommand);
static void I2C_0_setACKAction(void);
static void I2C_0_setNACKAction(void);
static void write_EEPROM(uint16_t memory_address, uint8_t data_to_write);
static uint8_t read_random_EEPROM(uint16_t memory_address);
