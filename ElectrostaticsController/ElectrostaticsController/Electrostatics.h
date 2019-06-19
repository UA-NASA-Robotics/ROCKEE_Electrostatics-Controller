/*
 * Electrostatics.h
 *
 * Created: 4/21/2018 2:15:29 PM
 *  Author: reed
 */ 


#ifndef ELECTROSTATICS_H_
#define ELECTROSTATICS_H_

char getState();
//initialization functions
void initializeHBridge();
void enableHV(); 
void disableHV(); 

//error checking functions
void faultReset();
void restartHbridge(); 
int checkFault(); 
char getFaultStatus(); 

//active use functions
void toggleHBridge(); 

//passive use function;
void beginHBridgeToggle(); 
void stopBridgeToggle(); 


#endif /* ELECTROSTATICS_H_ */