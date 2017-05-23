#ifndef RECEIVEPACKAGE_H_
#define  RECEIVEPACKAGE_H_
#include "event.h"
#include "simulation.h"
#include "receiver.h"
#include "system.h"
#include "package.h"
#include "ack.h"
#include<list>
#include<iostream>
#include<fstream>
class Simulation;
class ReceivePackage:public Event
{
public:
	ReceivePackage(double, System*, Agenda*);
	~ReceivePackage();

	void execute();
	void action();

	ReceivePackage *getTypeOfEvent() { return this; }
	string getClassName() { return "ReceivePackage"; }
private:
	System *ptrToSystem_;
	Agenda *ptrToAgenda_;
	ofstream file_;
};

#endif // RECEIVEPACKAGE_H_