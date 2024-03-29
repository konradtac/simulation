#ifndef SYSTEM_H_
#define SYSTEM_H_
#include <iostream>
#include "transmitter.h"
#include "receiver.h"
#include "channel.h"
#include "statistics.h"
#include <vector>
#include<fstream>
using namespace std;
class System
{
public:
	System();
	System(Kernels*, Statistics*);
	~System();

	void displayTransmitters();
	void displayReceivers();
	vector<Transmitter*> getTransmitters_();
	vector<Receiver*> getReceivers_();
	Transmitter* getTransmitter_(int k_);// zwraca wskaźnik na k-ty nadajnik
	Receiver* getReceiver_(int k_);// zwraca wskaźnik na k-ty odbiornik
	int getNumberOfReceiversOrTransmitters();
	Channel* getChannel();
	

	UniformGenerator* getPtrToGenerator_CTPK_();
	UniformGenerator* getPtrToGenerator_R_();
	UniformGenerator* getPtrToGenerator_TID_();

	Statistics* getPtrToStatistics_();

	void setLog_(bool b_) {
		log_ = b_;
	}
	bool isLog_(){
		return log_;
	}

private:
	int const kK_ = 8; //liczba nadajnikow, odbiorników
	vector<Transmitter*> transmitters_;// wektor przechowujący k transmiterów
	vector<Receiver*> receivers_;// wektor przechowujący k odbiorników
	Channel *ptrToChannel_;
	UniformGenerator *ptrToGenerator_CTPK_;
	UniformGenerator *ptrToGenerator_R_;
	UniformGenerator *ptrToGenerator_TID_;
	ofstream file_;
	bool log_;
	Statistics *ptrToStatistics_;
	
};
#endif // SYSTEM_H_
