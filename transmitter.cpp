#include "transmitter.h"


Transmitter::Transmitter():send_Package_(nullptr)
{
	//inicjalizacja generatora
	generator_ = new UniformGenerator(123);
	
}

Transmitter::Transmitter(int id, Kernels *ptrToKernels_):transmitter_id_(id),send_Package_(nullptr)
{
	int seed_ = ptrToKernels_->getKernelsList_().front();
	//inicjalizacja generatora
	cout << "UTWORZENIE GENERATORA O ZIARNIE " << seed_ << " DLA " << id << "-TEGO NADAJNIKA" << endl;
	generator_ = new UniformGenerator(seed_);
	ptrToKernels_->getKernelsList_().pop_front();
	//Utworzenie generatora wyk³adniczego na podstawie generatora równomiernego
	exp_gen_=new ExponentialGenerator(generator_, ptrToKernels_->getLambda_());
}


Transmitter::~Transmitter()
{
}

int Transmitter::getTransmitterId() {
	return transmitter_id_;
}
int Transmitter::getTimeCGP() {
	return time_CGP_;
}

void Transmitter::pushPacketToBuffor(Package* pack_){
	buffor_.push(pack_); 
}
void Transmitter::removePacketFromBuffor(){
	//send_Package_ = buffor_.front();
	buffor_.pop(); 
}
Package* Transmitter::getPacketFromBuffor(){ 
	return buffor_.front(); 
}
bool Transmitter::isEmpty(){
	return buffor_.empty(); 
}
UniformGenerator* Transmitter::getGenerator_() {
	return generator_;
}

