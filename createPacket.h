#ifndef CREATEPACKET_H_
#define CREATEPACKET_H_
#include "event.h"
#include "simulation.h"
#include "transmitter.h"
#include "system.h"
#include "package.h"
#include "agenda.h"
#include<list>
#include<iostream>
#include<fstream>

class Simulation;
class CreatePacket: public Event
{
public:
	CreatePacket(double clk_, Transmitter* transmiter_, Agenda* agenda_, System*);
	~CreatePacket();
	void execute();
	void action();
	CreatePacket* getTypeOfEvent() { return this; }
	string getClassName() { return "CreatePacket"; }

private:
	Transmitter *ptrToTransmitter_;
	Package *ptrToPackage_;
	Agenda *ptrToAgenda_;
	System *ptrToSystem_;
	ofstream file_;
};
#endif // CREATEPACKET_H_