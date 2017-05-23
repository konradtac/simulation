#include "receivePackage.h"



ReceivePackage::ReceivePackage(double clk_, System* sys_, Agenda* agenda_)
{
	ptrToSystem_ = sys_;//zapisanie wska�nika do Simulation
	ptrToAgenda_ = agenda_;
	time_ = clk_;//Ustawienie czasu wyst�pienia
	//ptrToAgenda_->setAgenda(this);//dodanie do agendy

	if (ptrToSystem_->isLog_()) {
		file_.open("dane", ios_base::app);
		cout << endl << endl;
		file_ << endl << endl;
		cout << "ZDARZENIE- ODBIOR PAKIETU" << endl;
		file_ << "ZDARZENIE- ODBIOR PAKIETU" << endl;
		
		cout << "Czas wyst�pienia zdarzenia " << time_ << " [ms]" << endl;
		file_ << "Czas wyst�pienia zdarzenia " << time_ << " [ms]" << endl;
		cout << "Dodatnie do kalendarza zdarze�" << endl;
		file_ << "Dodatnie do kalendarza zdarze�" << endl;

		file_.close();
	}
	
	
	
	
}


ReceivePackage::~ReceivePackage()
{
}


void ReceivePackage::execute() {
	action();
}
void ReceivePackage::action() {
	if (ptrToSystem_->isLog_()) {
		file_.open("dane", ios_base::app);
		cout << endl << endl;
		file_ << endl << endl;
		cout << endl << endl;
		cout << "###################################" << endl;
		cout << "OBS�UGA ZDARZENIA: ODBI�R PAKIETU: " << endl;
		cout << "###################################" << endl;
		file_ << "###################################" << endl;
		file_ << "OBS�UGA ZDARZENIA: ODBI�R PAKIETU: " << endl;
		file_ << "###################################" << endl;
	}
	if (ptrToSystem_->getChannel()->getChannelBuffor().size() == 0) {
		if (ptrToSystem_->isLog_()) {
			cout << "Kana� jest pusty" << endl;
			file_ << "Kana� jest pusty" << endl;
		}
		ptrToSystem_->getChannel()->setCollision(false);
		return;
	}
	//Je�eli w buforze kana�u znajduje si� wi�cej pakiet�w ni� jeden, ustawiamy kolizj� na true
	if (ptrToSystem_->getChannel()->getChannelBuffor().size() > 1) {
		if (ptrToSystem_->isLog_()) {
			cout << "W kanale znajduje si� wi�cej ni� jeden pakiet" << endl;
			file_ << "W kanale znajduje si� wi�cej ni� jeden pakiet" << endl;
		}
		ptrToSystem_->getChannel()->setCollision(true);
		if (ptrToSystem_->isLog_()) {
			cout << "Ustawiamy kolizj� w kanale" << endl;
			file_ << "Ustawiamy kolizj� w kanale" << endl;
		}
		ptrToSystem_->getChannel()->getChannelBuffor().pop_back();
		if (ptrToSystem_->isLog_()) {
			cout << "Czy�cimy bufor" << endl;
			file_ << "Czy�cimy bufor" << endl;
		}
		return;
		
	}
	//Utworzenie pakietu
	Package *temp_Package_= ptrToSystem_->getChannel()->getChannelBuffor().back();
	//usuwamy pakiet z bufora kana�u
	ptrToSystem_->getChannel()->getChannelBuffor().pop_back();
	if (ptrToSystem_->isLog_()) {
		cout << "Usuwamy pakiet z bufora kana�u" << endl;
		file_ << "Usuwamy pakiet z bufora kana�u" << endl;
	}
	if (ptrToSystem_->getChannel()->isCollision()) {
		if (ptrToSystem_->getChannel()->getChannelBuffor().size() ==0) {
			ptrToSystem_->getChannel()->setCollision(false);
		}
	}
	else {
		//Orientujemy si� od kt�rego odbiornika ma dosta� si� pakiet
		int receiver_id_ = temp_Package_->getId();
		if (ptrToSystem_->isLog_()) {
			cout << "Odbiornik: " << receiver_id_ << " odebra� pakiet " << endl;
			file_ << "Odbiornik: " << receiver_id_ << " odebra� pakiet " << endl;
		}

		//##########STATYSTYKI#################################################################
		double differential_time_ = time_ - temp_Package_->getCreateTime_();

		ptrToSystem_->getPtrToStatistics_()->addDelayOfPackageSum(differential_time_);
		ptrToSystem_->getPtrToStatistics_()->addSumOfDelayPackage_();

		
		//#####################################################################################

		//Utworzenie dla k-tego odbiornika wiadomo�ci ACK
		Ack *ptrToAck_ = new Ack(receiver_id_);
		ptrToSystem_->getReceiver_(receiver_id_)->setAck_(ptrToAck_);
		if (ptrToSystem_->isLog_()) {
			cout << "Utworzenie pakietu ACK" << endl;
			file_ << "Utworzenie pakietu ACK" << endl;
		}
		//Wprowadzenie wiadomo�ci ACK do kana�u

		ptrToSystem_->getChannel()->setAck(ptrToAck_);
		if (ptrToSystem_->isLog_()) {
			cout << "Wprowadzenie pakietu ACK do kana�u" << endl;
			file_ << "Wprowadzenie pakietu ACK do kana�u" << endl;
			file_.close();
		}
		//int CTIZ_ = Ack::getCtiz();
		//ptrToAgenda_->setAgenda(new ReceiveACK(time_+ CTIZ_, ptrToSystem_, ptrToAgenda_));
	}
	
}