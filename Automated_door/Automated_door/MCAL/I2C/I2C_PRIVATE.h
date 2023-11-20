/*
 * I2C_PRIVATE.h
 *
 * Created: 10/31/2023 10:54:25 AM
 *  Author: MERNA
 */ 


#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_


#define TWI_STATUS_VALUE						(TWSR & 0xF8)

#define TWI_START_COND_ACK						0x08
#define TWI_REP_START_COND_ACK					0x10
#define TWI_SLA_WRITE_ACK						0x18
#define TWI_SLA_READ_ACK						0x40
#define TWI_MASTER_DATA_TX_ACK					0x28
#define TWI_MASTER_DATA_RX_ACK					0x50
#define TWI_MASTER_DATA_RX_NACK					0x58



#endif /* I2C_PRIVATE_H_ */