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

	

	
	//#################�redni czas oczekiwania na wys�anie:###################
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
	//#################�rednie op�nienie pakietu:###################
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

	//#################Przep�ywno�� systemu:###################
	double countBitRate_() {
		return sumOfDelayPackage_ / (timeOfSimulation_/1000);
	}
	//#########################################################################

	//#################�rednia liczba retransmisji:############################
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
	//#################�rednia pakietowa stopa b��d�w:############################
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
		cout << "�redni czas oczekiwania: " << countAvgWaitingToSendTime_() << "ms"<< endl;
		cout << "Srednie op�nienie pakietu: " << countAvgDelayPackageTime_() << "ms"<< endl;
		cout << "Przep�ywno�� systemu: " << countBitRate_() << "pak/s"<< endl;
		cout << "Liczba retransmisji: " << countNumberOfRetransmissions_() << endl;
		cout << "�rednia pakietowa stopa b��d�w: " << countPacketErrorRate() << endl;
		cout << "Maksymalna pakietowa stopa b��d�w: " << countMaxPacketErrorRate_() << endl;
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

	//�redni czas oczekiwania na wys�anie:
	int sumOfAllPackage_;
	double waitingInBufforTimesSum_;
	double avgWaitingToSendTime_;

	//�rednie op�nienie pakietu
	int sumOfDelayPackage_=0;//suma wszystkich pakiet�w, kt�re wysz�y z bufora
	double delayOfPackageSum=0.0;
	double avgDelayPackageTime_ =0.0;
	

	//przep�ywno�� systemu
	//korzystam z pola sumOfDelayPackage_

	//�rednia liczba retransmisji pakiet�w (dla dobrze odebranych)
	//suma wszystkich retransmisji/ilosc nadajnik�w
	int numberOfAllRetransmissions_=0 ;
	int numberOfRetransmissions_ = 0;

	//�rednia pakietowa stopa b��d�w
	int sendErrorRate_[8];//ilo�� pakiet�w wysy�anych dla ka�dego nadajnika
	int losePackages_[8];//ilo�� pakiet�w straconych
	//double packetErrorRate_;
};
#endif // STATISTICS_H_
