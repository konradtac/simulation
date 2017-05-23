#ifndef RECEIVEACK_H_
#define  RECEIVEACK_H_
#include "event.h"
#include "simulation.h"
#include "receiver.h"
#include "system.h"
#include "package.h"
#include "agenda.h"
#include<list>
#include<iostream>
#include<fstream>
#include<math.h>
class Simulation;
class ReceiveACK:public Event
{
public:
	ReceiveACK(double, System*, Agenda*, Transmitter*);
	~ReceiveACK();

	void execute();
	void start();
	string getClassName() { return "ReceiveACK"; }

	ReceiveACK *getTypeOfEvent() { return this; }
private:
	System *ptrToSystem_;
	Agenda *ptrToAgenda_;
	Channel *ptrToChannel_;
	Transmitter *ptrToTransmitter_;
	ofstream file_;
};
#endif // RECEIVEACK_H_
