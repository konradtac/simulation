#include "createPacket.h"
#include <cstdlib>
#include<iostream>
#include<fstream>
using namespace std;




CreatePacket::CreatePacket(double clk_, Transmitter* transmiter_, Agenda* agenda_, System* system_)
{
	double random_ = transmiter_->getExpGenerator_()->rand_();
	//zaokr¹glenie do dwóch miejsc po przecinku
	random_ = round(random_ * 10) / 10;
	time_ = clk_ + random_;//wylosowanie czasu wyst¹pienia

	ptrToTransmitter_ = transmiter_;// pole, w którym przechowywany jest wskaŸnik na nadajnik, do któego ma trafiæ pakiet
	ptrToSystem_ = system_;
	ptrToAgenda_ = agenda_;

	if (ptrToSystem_->isLog_()) {
		file_.open("dane", ios_base::app);
		cout << endl << endl;
		file_ << endl << endl;
		cout << "Czas wyst¹pienia tego zdarzenia: " << time_ << " [ms]" << endl;
		file_ << "Czas wyst¹pienia tego zdarzenia: " << time_ << " [ms]" << endl;
		file_.close();
	}
	
	
	
	
	

}


CreatePacket::~CreatePacket()
{
	
}
void CreatePacket::execute() {
	action();
}
void CreatePacket::action() {

	if (ptrToSystem_->isLog_()) {
		file_.open("dane", ios_base::app);
		cout << endl << endl;
		file_ << endl << endl;
		cout << endl << endl;
		cout << "###################################" << endl;
		cout << "OBS£UGA ZDARZENIA: UTWÓRZ PAKIET: " << endl;
		cout << "###################################" << endl;
		file_ << "###################################" << endl;
		file_ << "OBS£UGA ZDARZENIA: UTWÓRZ PAKIET: " << endl;
		file_ << "###################################" << endl;
	}
	ptrToPackage_ = new Package(static_cast<int>(ptrToSystem_->getPtrToGenerator_CTPK_()->rand(1, 10)), ptrToTransmitter_->getTransmitterId(), time_);
	if (ptrToSystem_->isLog_()) {
		cout << "Utworzenie pakietu o ID= " << ptrToPackage_->getId() << " , czasie CTPK [ms]= " << ptrToPackage_->getCtpTime() << endl;
		file_ << "Utworzenie pakietu o ID= " << ptrToPackage_->getId() << " , czasie CTPK [ms]= " << ptrToPackage_->getCtpTime() << endl;
	}
	ptrToTransmitter_->pushPacketToBuffor(ptrToPackage_);

	if (ptrToSystem_->isLog_()) {
		cout << "Dodanie pakietu do " << ptrToTransmitter_->getTransmitterId() << "-tego bufora" << endl;
		file_ << "Dodanie pakietu do " << ptrToTransmitter_->getTransmitterId() << "-tego bufora" << endl;
	}
	if (ptrToTransmitter_->getSend_Package() == nullptr) {
		ptrToTransmitter_->setSend_Package(ptrToTransmitter_->getPacketFromBuffor());
		//ptrToTransmitter_->removePacketFromBuffor();
		ptrToAgenda_->setAgenda(new CheckChannel(time_, ptrToSystem_, ptrToAgenda_, ptrToTransmitter_->getTransmitterId(),false));
		if (ptrToSystem_->isLog_()) {
			cout << "Dodanie pakietu do " << ptrToTransmitter_->getTransmitterId() << "-przetwarzanego pola" << endl;
			file_ << "Dodanie pakietu do " << ptrToTransmitter_->getTransmitterId() << "-przetwarzanego pola" << endl;

			file_.close();
		}
	}

	ptrToAgenda_->setAgenda(new CreatePacket(time_, ptrToTransmitter_, ptrToAgenda_, ptrToSystem_));
	
	//ptrToAgenda_->setAgenda(new CheckChannel(time_, ptrToSystem_, ptrToAgenda_, ptrToTransmitter_->getTransmitterId()));
	
	
	
	
}