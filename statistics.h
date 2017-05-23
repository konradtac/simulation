#ifndef STATISTICS_H_
#define STATISTICS_H_
#include <iostream>
#include<vector>
using namespace std;
class Statistics
{
public:
	Statistics(double, double);
	~Statistics();

	

	
	//#################Œredni czas oczekiwania na wys³anie:###################
	//ADD
	void addSumOfAllPackage_() {
		
		sumOfAllPackage_++;
	}
	void addWaitingInBufforTimesSum_(double arg_) {
		waitingInBufforTimesSum_ = waitingInBufforTimesSum_ + arg_;
	}
	
	//LICZ
	double countAvgWaitingToSendTime_() {
		return (waitingInBufforTimesSum_ / static_cast<double>(sumOfAllPackage_));
	}
	//#########################################################################
	//#################œrednie opóŸnienie pakietu:###################
	//ADD
	void addSumOfDelayPackage_() {
		sumOfDelayPackage_++;
	}
	void addDelayOfPackageSum(double arg_) {
		delayOfPackageSum = delayOfPackageSum + arg_;
	}

	//LICZ
	double countAvgDelayPackageTime_() {
		return (delayOfPackageSum / static_cast<double>(sumOfDelayPackage_));
	}
	//#########################################################################

	//#################Przep³ywnoœæ systemu:###################
	double countBitRate_() {
		return sumOfDelayPackage_ / (timeOfSimulation_/1000);
	}
	//#########################################################################

	//#################Œrednia liczba retransmisji:############################
	void addToCounterOfRetranmissions_() {
		numberOfRetransmissions_++;
	}
	void addToRetransmissions_(int nORetransmissions_) {
		numberOfAllRetransmissions_ = numberOfAllRetransmissions_ + nORetransmissions_;
	}

	double countNumberOfRetransmissions_() {
		return numberOfAllRetransmissions_ / static_cast<double>(numberOfRetransmissions_);
	}
	//#########################################################################
	//#################Œrednia pakietowa stopa b³êdów:############################
	void setSendErrorRate_(int k_) {
		sendErrorRate_[k_]++;
	}
	void setLosePackages_(int k_) {
		losePackages_[k_]++;
	}
	double countPacketErrorRate(){
		double sumOfSendPacket=0.0;
		double sumOfLosePacket = 0.0;
		for(int i = 0; i < 8; ++i) {
			sumOfSendPacket = sumOfSendPacket + sendErrorRate_[i];
			sumOfLosePacket = sumOfLosePacket + losePackages_[i];
		}
		return sumOfLosePacket / sumOfSendPacket;
	}
	double countMaxPacketErrorRate_() {
		double max_=0;
		for (int i = 0; i < 8; ++i) {
			if ((losePackages_[i] / sendErrorRate_[i])>max_) {
				max_= losePackages_[i] / sendErrorRate_[i];
			}
		}
		return max_;
	}

	//#########################################################################


	void displayStatistics_() {
		cout << "Œredni czas oczekiwania: " << countAvgWaitingToSendTime_() << "ms"<< endl;
		cout << "Srednie opóŸnienie pakietu: " << countAvgDelayPackageTime_() << "ms"<< endl;
		cout << "Przep³ywnoœæ systemu: " << countBitRate_() << "pak/s"<< endl;
		cout << "Liczba retransmisji: " << countNumberOfRetransmissions_() << endl;
		cout << "Œrednia pakietowa stopa b³êdów: " << countPacketErrorRate() << endl;
		cout << "Maksymalna pakietowa stopa b³êdów: " << countMaxPacketErrorRate_() << endl;
		for (int i = 0; i < 8; ++i) {
			cout<< sendErrorRate_[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < 8; ++i) {
			cout << losePackages_[i] << " ";
		}
		cout << endl;
		
		cout << endl;
	}
private:
	int numberOfTransmitters_ = 8;
	double initialPhase_ = 0.0;
	double timeOfSimulation_;

	//Œredni czas oczekiwania na wys³anie:
	int sumOfAllPackage_;
	double waitingInBufforTimesSum_;
	double avgWaitingToSendTime_;

	//œrednie opóŸnienie pakietu
	int sumOfDelayPackage_=0;//suma wszystkich pakietów, które wysz³y z bufora
	double delayOfPackageSum=0.0;
	double avgDelayPackageTime_ =0.0;
	

	//przep³ywnoœæ systemu
	//korzystam z pola sumOfDelayPackage_

	//œrednia liczba retransmisji pakietów (dla dobrze odebranych)
	//suma wszystkich retransmisji/ilosc nadajników
	int numberOfAllRetransmissions_=0 ;
	int numberOfRetransmissions_ = 0;

	//œrednia pakietowa stopa b³êdów
	int sendErrorRate_[8];//iloœæ pakietów wysy³anych dla ka¿dego nadajnika
	int losePackages_[8];//iloœæ pakietów straconych
	//double packetErrorRate_;
};
#endif // STATISTICS_H_
