#ifndef CHECKCHANNEL_H_
#define CHECKCHANNEL_H_
#include "simulation.h"
#include "event.h"
#include "channel.h"
#include "system.h"
#include "package.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include "agenda.h"
#include<fstream>

class Simulation;
class CheckChannel : public Event
{
public:
	//CheckChannel(double, System*, Agenda*);
	CheckChannel(double, System*, Agenda*, int, bool);
	~CheckChannel();
	void execute();
	void action();
	CheckChannel* getTypeOfEvent() { return this; }
	string getClassName() { return "CheckChannel"; }
private:
	System *ptrToSystem_;
	Simulation *ptrToSimulation_;
	Agenda *ptrToAgenda_;
	Channel *ptrToChannel_;
	ofstream file_;
	int transmitterId_;
	bool isRetransmission_;
};

#endif // CHECKCHANNEL_H_