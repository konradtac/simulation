#include "statistics.h"



Statistics::Statistics(double ip_, double tos_):initialPhase_(ip_), timeOfSimulation_(tos_)
{
	sumOfAllPackage_=0;
	waitingInBufforTimesSum_=0.0;
	avgWaitingToSendTime_=0.0;
	//inicjalizacja wektora 0 wartościami
	for (int i = 0; i < 8; ++i) {
		sendErrorRate_[i] = 0;
		losePackages_[i] = 0;
	}

}


Statistics::~Statistics()
{
}
