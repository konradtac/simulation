#include "system.h"




System::System(Kernels* ptrToKernels_, Statistics* stats_)
{
	//Stworzenie i umieszczenie w wektorze 8 nadajników i 8 odbiorników
	for (int i = 0; i < kK_; ++i) {
		//Tworzenie nadajników
		Transmitter *transmitter_ = new Transmitter(i, ptrToKernels_);
		transmitters_.push_back(transmitter_);
		//Tworzenie odbiorników
		Receiver *receiver_ = new Receiver(i);
		receivers_.push_back(receiver_);
	}
	//Stworzenie wskaŸnika do kana³u
	ptrToChannel_ = new Channel();

	//Utworzenie Generatora CTPK
	ptrToGenerator_CTPK_ = new UniformGenerator(ptrToKernels_->getKernelsList_().front());
	ptrToKernels_->getKernelsList_().pop_front();

	ptrToGenerator_R_ = new UniformGenerator(ptrToKernels_->getKernelsList_().front());
	ptrToKernels_->getKernelsList_().pop_front();
	//GEnerator Transmitter ID
	ptrToGenerator_TID_ = new UniformGenerator(ptrToKernels_->getKernelsList_().front());
	ptrToKernels_->getKernelsList_().pop_front();

	ptrToStatistics_ = stats_;
}


System::~System()
{
}
void System::displayTransmitters() {
	file_.open("dane", ios_base::app);
	file_ << endl << endl;
	cout << "TRANSMITTERS:" << endl;
	file_ << "TRANSMITTERS:" << endl;
	for (int i = 0; i < kK_; ++i) {
		cout << " Transmitter id: " << transmitters_[i]->getTransmitterId() << " ,address: " << transmitters_[i] << endl;
		file_ << " Transmitter id: " << transmitters_[i]->getTransmitterId() << " ,address: " << transmitters_[i] << endl;
	}
	cout << endl;
	file_.close();
}
void System::displayReceivers() {
	file_.open("dane", ios_base::app);
	file_ << endl << endl;
	cout << "RECEIVERS:" << endl;
	file_ << "RECEIVERS:" << endl;
	for (int i = 0; i < kK_; ++i) {
		cout << " Receiver id: " << receivers_[i]->getReceiverId() << " ,address: " << receivers_[i] << endl;
		file_ << " Receiver id: " << receivers_[i]->getReceiverId() << " ,address: " << receivers_[i] << endl;
	}
	cout << endl;
	file_.close();
}
vector<Transmitter*> System::getTransmitters_() { 
	return transmitters_;
}
vector<Receiver*> System::getReceivers_() { 
	return receivers_; 
}
Transmitter* System::getTransmitter_(int k_) {
	return transmitters_[k_]; 
}
Receiver* System::getReceiver_(int k_) { 
	return receivers_[k_]; 
}
int System::getNumberOfReceiversOrTransmitters() {
	return kK_; 
}
Channel* System::getChannel() {
	return ptrToChannel_; 
}
UniformGenerator* System::getPtrToGenerator_CTPK_() { 
	return ptrToGenerator_CTPK_; 
}
UniformGenerator* System::getPtrToGenerator_R_() {
	return ptrToGenerator_R_;
}
UniformGenerator* System::getPtrToGenerator_TID_() {
	return ptrToGenerator_TID_;
}
Statistics * System::getPtrToStatistics_() {
	return ptrToStatistics_;
}