/*
 * I2C_PROGRAM.c
 *
 * Created: 10/31/2023 10:52:29 AM
 *  Author: MERNA
 */ 

#include "I2C_INTERFACE.h"
#include "I2C_REGISTER.h"
#include "I2C_PRIVATE.h"
/*********************************************************************************/

void TWI_vInitMaster(u8 Copy_u8Address)
{
	if((Copy_u8Address < 128) && (Copy_u8Address > 0)) // address for master is optional
	{
		TWAR = Copy_u8Address<<1 ;
	}
	//Choose SCL frequency= 400 kHz
	TWBR = 12;
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);
	
	//Enable ACK
	SET_BIT(TWCR,TWEA);
	
	//Enable TWI Peripheral
	SET_BIT(TWCR,TWEN);
}
/*********************************************************************************/

void TWI_vSendStartCondition(void)
{
	//Request a Start condition
	SET_BIT(TWCR,TWSTA);
	
	//Clear flag for start condition
	SET_BIT(TWCR,TWINT);
	
	//Busy Wait for the flag 
	while(GET_BIT(TWCR,TWINT) == 0);
	
	//Check Status Code == Start Cond. ACK
	while(TWI_STATUS_VALUE != TWI_START_COND_ACK);
}
/*********************************************************************************/

void TWI_vSendRepStartCondition(void)
{
	//Request a Start condition
	SET_BIT(TWCR,TWSTA);
	
	//Clear flag for start condition
	SET_BIT(TWCR,TWINT);
	
	//Busy Wait for the flag
	while(GET_BIT(TWCR,TWINT) == 0);
	
	//Check Status Code == Repeated Start Cond. ACK
	while(TWI_STATUS_VALUE != TWI_REP_START_COND_ACK);
}
/*********************************************************************************/

void TWI_vSendStopCondition(void)
{
	//Request a Stop Condition
	SET_BIT(TWCR,TWSTO);
	
	//Clear flag for Stop Condition
	SET_BIT(TWCR,TWINT);
}
/*********************************************************************************/

void TWI_vSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	if(Copy_u8SlaveAddress < 128) //validation 
	{
		TWDR = Copy_u8SlaveAddress<<1 ;
		CLR_BIT(TWDR,0); // Clear BIT0 For Write Operation
		
		//Clear Start Condition Bit
		CLR_BIT(TWCR,TWSTA);
		
		//Clear flag for Sending Address + R/W Bit
		SET_BIT(TWCR,TWINT);
		
		//Busy Wait for the flag
		while(GET_BIT(TWCR,TWINT) == 0);
		
		//Check Status Code == Start Cond. ACK
		while(TWI_STATUS_VALUE != TWI_SLA_WRITE_ACK);
	}
}
/*********************************************************************************/

void TWI_vSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	if(Copy_u8SlaveAddress < 128) //validation
	{
		TWDR = Copy_u8SlaveAddress<<1 ;
		SET_BIT(TWDR,0); // Set BIT0 For Read Operation
		
		//Clear Start Condition Bit
		CLR_BIT(TWCR,TWSTA);
		
		//Clear flag for Sending Address + R/W Bit
		SET_BIT(TWCR,TWINT);
		
		//Busy Wait for the flag
		while(GET_BIT(TWCR,TWINT) == 0);
		
		//Check Status Code == Slave Address+READ bit ACK
		while(TWI_STATUS_VALUE != TWI_SLA_READ_ACK);
	}
}
/*********************************************************************************/

void TWI_vWriteMasterDataByte(u8 Copy_u8TxData)
{
	TWDR = Copy_u8TxData;
	
	//Clear flag for Sending Data
	SET_BIT(TWCR,TWINT);
	
	//Busy Wait for the flag
	while(GET_BIT(TWCR,TWINT) == 0);
	
	//Check Status Code == Start Cond. ACK
	while(TWI_STATUS_VALUE != TWI_MASTER_DATA_TX_ACK);
	
}
/*********************************************************************************/

void TWI_vReadMasterDataByte(u8* Copy_pu8RxData,u8 Copy_u8AckNack)
{
	if(Copy_pu8RxData != NULL)
	{
		if(Copy_u8AckNack == TWI_DATA_RX_NACK)
		{
			CLR_BIT(TWCR,TWEA);
		}
		else
		{
			SET_BIT(TWCR,TWEA);
		}
		//Clear flag for Sending Data
		SET_BIT(TWCR,TWINT);
		
		//Busy Wait for the flag
		while(GET_BIT(TWCR,TWINT) == 0);
		
		if(Copy_u8AckNack == TWI_DATA_RX_NACK)
		{
			//Check Status Code == Start Cond. NACK
			while(TWI_STATUS_VALUE != TWI_MASTER_DATA_RX_NACK);
		}
		else
		{
			//Check Status Code == Start Cond. ACK
			while(TWI_STATUS_VALUE != TWI_MASTER_DATA_RX_ACK);
		}
		
		*Copy_pu8RxData = TWDR;
	}
}

/*********************************************************************************/
