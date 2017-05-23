#ifndef SIMULATION_H_
#define SIMULATION_H_
#include "system.h"
#include "transmitter.h"
#include "event.h"
#include "createPacket.h"
#include "checkChannel.h"
#include "receivePackage.h"
#include "receiveACK.h"
#include "agenda.h"

#include "uniformGenerator.h"
#include "exponentialGenerator.h"

#include<iostream>
#include<fstream>

#include "kernels.h"
#include "statistics.h"
using namespace std;

class Simulation
{
public:
	Simulation();
	~Simulation();
	//rozpoczêcie symulacji, zawiera g³ówn¹ pêtlê symulacji
	void start();
	System* getPtrToSystem() { return ptrToSystem_; }
	int getNumberOfSimulatons_();
	double getTimeOfSimulation_();
private:
	list<Event*> agenda;
	double clock_=0.0;
	System *ptrToSystem_;
	Event *ptrToEvent_;
	//Simulation *ptrToSimulation_;
	double timeOfSimulation_;
	Agenda *ptrToAgenda_;
	int numberOfSimulations_;
	
};

#endif // SIMULATION_H_
