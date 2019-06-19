/*
 * Comms.c
 *
 * Created: 4/28/2018 7:18:48 PM
 *  Author: reed
 */ 
#include "CANFastTransfer.h"
#include "CommsDefenition.h"
#include <stdbool.h>

#define statusIndex 1

void checkCommsReceived()
 {
	 return ReceivedData; 
 }

bool checkEnabled() 
{
	if(ReceiveCAN[EnableDisable] == 1) 
	{
		return true;
	}
	return false; 
}

int checkRequestStatus() 
{
	if(ReceiveCAN[RequestStatus] >= 1) {
		int temp = ReceiveCAN[RequestStatus];
		ReceiveCAN[RequestStatus] = 0;
		return temp;	
	}
	return 0; 
}

void sendStatus(unsigned int adrs) {
	ToSendCAN( statusIndex, getFaultStatus());
	sendDataCAN( adrs);
}