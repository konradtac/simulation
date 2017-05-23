#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_
#include <queue>
#include <iostream>
#include "package.h"
#include "exponentialGenerator.h"
#include "kernels.h"
using namespace std;
class Kernels;
class Transmitter
{
public:
	Transmitter();
	Transmitter(int k, Kernels*);
	~Transmitter();

	int getTransmitterId();
	int getTimeCGP();
	void pushPacketToBuffor(Package* pack_);
	void removePacketFromBuffor();
	Package* getPacketFromBuffor();
	UniformGenerator *getGenerator_();
	ExponentialGenerator *getExpGenerator_() {
		return exp_gen_;
	}
	Package* getSend_Package() {
		return send_Package_;
	}
	void setSend_Package(Package* pack_) {
		send_Package_ = pack_;
	}
	bool isEmpty();
	void setR_(int sr_) {
		r_ = sr_;
	}
	void increment_r_() {
		r_++;
	}
	int get_r_() {
		return r_;
	}
	const int getKLR() {
		return kLR_;
	}
private:
	const int kLR_ = 2; //liczba mo¿liwych retransmisji
	int r_ = 0;
	queue<Package*> buffor_; //bufor, jako kolejka, w której przechowywane s¹ pakiety w nadajniku
	Package* send_Package_;//Pole, w którym transmiter przechowuje wys³any pakiet
	int transmitter_id_;//numer identyfikacyjny nadajnika
	int time_CGP_;//odstêp czasu, po którym nadajnik generuje pakiet
	//Przechowujemy generator danego transmitera:
	UniformGenerator *generator_;
	ExponentialGenerator *exp_gen_;

};

#endif // TRANSMITTER_H_