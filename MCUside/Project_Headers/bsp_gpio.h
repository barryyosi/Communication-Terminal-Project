#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_

#include "TFC.h"



void enableClkToPorts();

void setDirection(Port port, bit_t value);
bit_t getDirection(Port port);
//-----------
bit_t getInputData(Port port);
//--------
void setOutputData(Port port, bit_t value);
void togglePin(Port port);
bit_t getOutputData(Port port);
//--------
void clearIRQFlag(Port port);
bit_t getIRQFlag(Port port);
//--------
void setPortRole(Port port, PortRole role);
PortRole getPortRole(Port port);
//--------
void setIRQType(Port port, IRQType irqType);
IRQType getIRQType(Port port);
//--------
void setHighDriveStrength(Port port);
bit_t getDriveStrength(Port port);
//--------
void setSlowSlewRate(Port port);
//--------
void setPullEnable(Port port);
bit_t getPullEnable(Port port);
void setPullSelect(Port port);
bit_t getPullSelect(Port port);
//--------
void setPassiveFilter(Port port);
bit_t getPassiveFilter(Port port);
//--------

void initOutput(Port port);
void InitInput(Port port);

#endif
