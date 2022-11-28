#include "eepromAT24C.h"


void I2C_0_transmittingAddrPacket(uint8_t slaveAddres, uint8_t directionBit)
{
    TWI0.MADDR = I2C_SET_ADDR_POSITION(slaveAddres) + directionBit;
    while (!I2C_SLAVE_RESPONSE_ACKED){};  
}

uint8_t I2C_0_receivingDataPacket(void)
{
    while (!I2C_DATA_RECEIVED){};
    return TWI0.MDATA;    
}

void I2C_0_sendMasterCommand(uint8_t newCommand)
{    TWI0.MCTRLB |=  newCommand;
}

void I2C_0_setACKAction(void)
{
    TWI0.MCTRLB &= !TWI_ACKACT_bm;
}

void I2C_0_setNACKAction(void)
{
    TWI0.MCTRLB |= TWI_ACKACT_bm;
}

void write_EEPROM(uint16_t memory_address, uint8_t data_to_write){
        I2C_0_transmittingAddrPacket(0x50,I2C_DIRECTION_BIT_WRITE);
        I2C_0_setACKAction();
        I2C_0_sendMasterCommand(TWI_MCMD_RECVTRANS_gc); 
        while (!I2C_DATA_SEND){};
        TWI0.MDATA=memory_address>>8;
        while (!I2C_DATA_SEND){};
        TWI0.MDATA=(memory_address & 0b0000000011111111);
        while (!I2C_DATA_SEND){};
        TWI0.MDATA=data_to_write;
        while(!I2C_SLAVE_RESPONSE_ACKED){};
        I2C_0_sendMasterCommand(TWI_MCMD_STOP_gc);
}

uint8_t read_random_EEPROM(uint16_t memory_address){
    uint8_t data_return;
    I2C_0_transmittingAddrPacket(0x50,I2C_DIRECTION_BIT_WRITE);
    I2C_0_setACKAction();
    I2C_0_sendMasterCommand(TWI_MCMD_RECVTRANS_gc);
    while (!I2C_DATA_SEND){};
    TWI0.MDATA=memory_address>>8;
    while (!I2C_DATA_SEND){};
    TWI0.MDATA=(memory_address & 0b0000000011111111);
    I2C_0_transmittingAddrPacket(0x50,I2C_DIRECTION_BIT_READ);
    I2C_0_sendMasterCommand(TWI_MCMD_RECVTRANS_gc);
    data_return=I2C_0_receivingDataPacket();
    I2C_0_sendMasterCommand(TWI_MCMD_STOP_gc);
    return data_return;
}