/*
 * Comms.h
 *
 * Created: 4/28/2018 7:19:02 PM
 *  Author: reed
 */ 


#ifndef COMMS_H_
#define COMMS_H_

bool checkCommsReceived(); 
bool checkEnabled();
int checkRequestStatus(); 

void sendStatus(unsigned int adrs); 


#endif /* COMMS_H_ */