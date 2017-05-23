#include "checkChannel.h"
#include<fstream>
#include <typeinfo>

CheckChannel::CheckChannel(double clk_, System* sys_, Agenda* agenda_, int k_,bool ret_)
{
	time_ = clk_;
	transmitterId_ = k_;
	isRetransmission_ = ret_;
	ptrToAgenda_ = agenda_;//zapisanie wska�nika do Simulation
	ptrToSystem_ = sys_;
	ptrToChannel_ = ptrToSystem_->getChannel();

	if (ptrToSystem_->isLog_()) {
		file_.open("dane", ios_base::app);
		cout << endl << endl;
		file_ << endl << endl;
		cout << "ZDARZENIE- CZY KANA� JEST ZAJETY" << endl;
		file_ << "ZDARZENIE- CZY KANA� JEST ZAJETY" << endl;

		cout << "Czas wyst�pienia zdarzenia " << time_ << " [ms]" << endl;
		file_ << "Czas wyst�pienia zdarzenia " << time_ << " [ms]" << endl;

		//ptrToAgenda_->setAgenda(this);//dodanie do agendy
		cout << "Dodatnie do kalendarza zdarze�" << endl;
		file_ << "Dodatnie do kalendarza zdarze�" << endl;

		file_.close();
	}
	
}



CheckChannel::~CheckChannel()
{
}
void CheckChannel::execute() {
	action();
}
void CheckChannel::action() {

	if(ptrToSystem_->isLog_()) {
		file_.open("dane", ios_base::app);
		cout << endl << endl;
		file_ << endl << endl;
		cout << endl << endl;
		cout << "###################################" << endl;
		cout << "OBS�UGA ZDARZENIA: SPRAWD� KANA�: " << endl;
		cout << "###################################" << endl;
		file_ << "###################################" << endl;
		file_ << "OBS�UGA ZDARZENIA: SPRAWD� KANA�: " << endl;
		file_ << "###################################" << endl;
		cout << "Sprawdzamy zaj�to�� kana�u" << endl;
		file_ << "Sprawdzamy zaj�to�� kana�u" << endl;
	}
	
	//sprawdzamy zaj�to�� kana�u
	if ((ptrToSystem_->getChannel()->isBussy())) {
		if (ptrToSystem_->isLog_()) {
			cout << "kana� jest zaj�ty, czekamy 0.5 ms" << endl;
			file_ << "kana� jest zaj�ty, czekamy 0.5 ms" << endl;
		}
		ptrToAgenda_->setAgenda(new CheckChannel(time_ + 0.5, ptrToSystem_, ptrToAgenda_, transmitterId_,(isRetransmission_ ? true:false)));
		return;
	}
	if (ptrToSystem_->isLog_()) {
		cout << "Tworzymy wska�nik na pakiet, kt�ry chcemy transportowa� z bufora" << endl;
		file_ << "Tworzymy wska�nik na pakiet, kt�ry chcemy transportowa� z bufora" << endl;
	}
	//if (ptrToSystem_->getTransmitter_(transmitterId_)->isEmpty() == true) {
		//cout << "bufor nadajnika jest pusty" << endl;
		//return;
	//}
	Package* packageToTransport;
	if (isRetransmission_) {
		packageToTransport = ptrToSystem_->getTransmitter_(transmitterId_)->getSend_Package();
	}
	else {
		packageToTransport = ptrToSystem_->getTransmitter_(transmitterId_)->getPacketFromBuffor();
		if (ptrToSystem_->isLog_()) {
			cout << "usuwamy najstarszy pakiet z bufora nadajnika o numerze " << transmitterId_ << " , kt�rego id pakietu= " << packageToTransport->getId() << endl;
			file_ << "usuwamy najstarszy pakiet z bufora nadajnika o numerze " << transmitterId_ << " , kt�rego id pakietu= " << packageToTransport->getId() << endl;
		}
		

		//usu� najstarszy pakiet z k-tego bufora
		ptrToSystem_->getTransmitter_(transmitterId_)->removePacketFromBuffor();

		//##########STATYSTYKI#################################################################
		double differential_time_ = time_ - packageToTransport->getCreateTime_();
		cout << "DIFF TIME"<<differential_time_ << endl;
		ptrToSystem_->getPtrToStatistics_()->addWaitingInBufforTimesSum_(differential_time_);
		ptrToSystem_->getPtrToStatistics_()->addSumOfAllPackage_();

		ptrToSystem_->getPtrToStatistics_()->setSendErrorRate_(transmitterId_);
		//#####################################################################################
	}
	
	
	
	//Obs�uga zdarzenia, w kt�rym wyst�puj� te same w
	
	//Czy istnieje inny event typu checkChannel o tym samym czasie
	bool a_ = false;
	string typeOfEvent_ = typeid(dynamic_cast<CheckChannel&>(*(ptrToAgenda_->getAgenda().front()->getTypeOfEvent()))).name();

	for (list<Event*>::iterator it = ++(ptrToAgenda_->getAgenda().begin()); it != ptrToAgenda_->getAgenda().end(); it++){
		if ((*it)->getTime() == time_) {
			if ((*it)->getClassName() == "CheckChannel") {
				a_ = true;
				if (ptrToSystem_->isLog_()) {
					file_ << "Te same czasy" << endl;
					cout << "TE SAME CZASY" << endl;
				}
				break;
			}
		}
		else {
			break;
		}
		
		//cout << (*it)->getTime() << ' ';
		
	}
	//Event *tmp= ptrToAgenda_->getAgenda();
	//while(tmp->)
	//for (int i = 0; i < kK_; ++i) {
		//tmp->getAgenda()
		//if()
	//}
	//zajmij kana�
	
	if (!a_) {
		if (ptrToSystem_->isLog_()) {
			cout << "Zajmujemy kana�" << endl;
			file_ << "Zajmujemy kana�";
		}
		ptrToSystem_->getChannel()->setBusy(true);
	}
	
	if (ptrToSystem_->isLog_()) {
		cout << "Umieszczamy pakiet o id= " << packageToTransport->getId() << " w kanale " << endl;
		file_ << "Umieszczamy pakiet o id = " << packageToTransport->getId() << " w kanale " << endl;
		file_.close();
	}
	
	//umie�� pakiet w kanale
	ptrToSystem_->getChannel()->setPackage(packageToTransport);
	//Zaplanowanie odbioru pakietu
	ptrToAgenda_->setAgenda(new ReceivePackage(time_ + packageToTransport->getCtpTime(), ptrToSystem_, ptrToAgenda_));
	//zaplanowanie odbioru ACK
	int CTIZ_ = Ack::getCtiz();
	ptrToAgenda_->setAgenda(new ReceiveACK(time_ + packageToTransport->getCtpTime() + CTIZ_, ptrToSystem_, ptrToAgenda_, ptrToSystem_->getTransmitter_(transmitterId_)));
	//Zaplanowanie Sprawdzenia kana�u
	//ptrToAgenda_->setAgenda(new CheckChannel(time_, ptrToSystem_, ptrToAgenda_, transmitterId_));
	
	

	
		
	
	
	
}