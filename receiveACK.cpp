#include "receiveACK.h"



ReceiveACK::ReceiveACK(double clk_, System* sys_, Agenda* agenda_, Transmitter* transmitter_)
{

	time_ = clk_;
	ptrToSystem_ = sys_;
	ptrToAgenda_ = agenda_;
	ptrToTransmitter_ = transmitter_;
	ptrToChannel_ = ptrToSystem_->getChannel();
	//ptrToAgenda_->setAgenda(this);
	if (ptrToSystem_->isLog_()) {
		file_.open("dane", ios_base::app);
		cout << endl << endl;
		file_ << endl << endl;
		cout << "ZDARZENIE- ODBIOR ACK" << endl;
		file_ << "ZDARZENIE- ODBIOR ACK" << endl;
		cout << "Czas wyst¹pienia zdarzenia " << time_ << " [ms]" << endl;
		file_ << "Czas wyst¹pienia zdarzenia " << time_ << " [ms]" << endl;
		cout << "Dodatnie do kalendarza zdarzeñ" << endl;
		file_ << "Dodatnie do kalendarza zdarzeñ" << endl;
		file_.close();
	}
	
}


ReceiveACK::~ReceiveACK()
{
}

void ReceiveACK::execute() {
	start();
}
void ReceiveACK::start() {
	if (ptrToSystem_->isLog_()) {
		file_.open("dane", ios_base::app);
		cout << endl << endl;
		cout << "###################################" << endl;
		cout << "OBS£UGA ZDARZENIA: ODBIÓR ACK: " << endl;
		cout << "###################################" << endl;
		file_ << "###################################" << endl;
		file_ << "OBS£UGA ZDARZENIA: ODBIÓR ACK: " << endl;
		file_ << "###################################" << endl;
	}
	//k-ty transmiter sprawdza, czy znajduje siê ACK
	//je¿eli k-ty transmiter nie dosta³ ACK, rozpoczyna retransmisjê
	//je¿eli dosta³ ACK, zwalnia kana³
	
	if (ptrToChannel_->getAck()!=nullptr){
		int ack_id_ = ptrToChannel_->getAck()->getAckId();
		if (ptrToSystem_->isLog_()) {
			cout << "Odbiornik: " << ack_id_ << " pomyœlnie przes³a³ pakiet!" << endl;
			file_ << "Odbiornik: " << ack_id_ << " pomyœlnie przes³a³ pakiet!" << endl;
		}
		ptrToChannel_->removeAck();
		if (ptrToSystem_->isLog_()) {
			cout << "Pakiet ACK zosta³ usuniêty z kana³u" << endl;
			file_ << "Pakiet ACK zosta³ usuniêty z kana³u" << endl;
		}
		ptrToTransmitter_->setSend_Package(nullptr);

		if (ptrToSystem_->isLog_()) {
			cout << "Pole, w którym przechowywany by³ pakiet ustawiamy na puste" << endl;
			file_ << "Pole, w którym przechowywany by³ pakiet ustawiamy na puste" << endl;
			//ptrToSystem_->getTransmitter_(ack_id_)->setSend_Package(nullptr);
		}
		ptrToChannel_->setBusy(false);
		if (ptrToSystem_->isLog_()) {
			cout << "Zwalniamy kana³" << endl;
			file_ << "Zwalniamy kana³" << endl;
		}

		//##########STATYSTYKI#################################################################
		ptrToSystem_->getPtrToStatistics_()->addToRetransmissions_(ptrToTransmitter_->get_r_());
		//#####################################################################################

		ptrToTransmitter_->setR_(0);
		
	}
	else {
		if (ptrToSystem_->isLog_()) {
			cout << "RETRANSMISJA PAKIETU" << endl;
			file_ << "RETRANSMISJA PAKIETU" << endl;
		}
		if(ptrToChannel_->getChannelBuffor().empty())
		ptrToChannel_->setBusy(false);
		
		//losowanie czasu CRP=R*CTPK R<0,2^(r-1)>
		//je¿eli liczba dostêpnych retransmisji jest >0
		const int lR_ = ptrToTransmitter_->getKLR();
		ptrToTransmitter_->increment_r_();
		int r_ = ptrToTransmitter_->get_r_();
		if ( r_ <= lR_ ){
			//##########STATYSTYKI#################################################################
			if (r_ == 1) {
				ptrToSystem_->getPtrToStatistics_()->addToCounterOfRetranmissions_();
			}
			//#####################################################################################
			if (ptrToSystem_->isLog_()) {
				cout << "Numer retransmisji: " << ptrToTransmitter_->get_r_() << endl;
				file_ << "Numer retransmisji: " << ptrToTransmitter_->get_r_() << endl;
			}
			//aktualizuje r
			double ret_time_=ptrToSystem_->getPtrToGenerator_R_()->rand(0, (pow(2, r_) - 1));
			ret_time_ = round(ret_time_ * 10) / 10;
			if (ptrToSystem_->isLog_()) {
				cout << "Wylosowany czas retransmisji, po którym nast¹pi próba retransmisji: " << ret_time_ << endl;
				file_ << "Wylosowany czas retransmisji, po którym nast¹pi próba retransmisji: " << ret_time_ << endl;

				cout << "Dodanie do Agendy zdarzenia sprawdŸ kana³ po up³ywie: " << ret_time_ << endl;
				file_ << "Dodanie do Agendy zdarzenia sprawdŸ kana³ po up³ywie: " << ret_time_ << endl;
			}
			
			ptrToAgenda_->setAgenda(new CheckChannel(time_ + ret_time_, ptrToSystem_, ptrToAgenda_, ptrToTransmitter_->getTransmitterId(),true));
		}
		else {
			
			//##########STATYSTYKI##########################################################################
			ptrToSystem_->getPtrToStatistics_()->setLosePackages_(ptrToTransmitter_->getTransmitterId());
			//##############################################################################################
			if (ptrToSystem_->isLog_()) {
				cout << "Transmisja pakietu z nadajnika o id= " << ptrToTransmitter_->getTransmitterId() << "nie powiod³a siê" << endl;
				file_ << "Transmisja pakietu z nadajnika o id= " << ptrToTransmitter_->getTransmitterId() << "nie powiod³a siê" << endl;
			}
			ptrToTransmitter_->setR_(0);
			ptrToTransmitter_->setSend_Package(nullptr);
			ptrToChannel_->setBusy(false);
			if (ptrToSystem_->isLog_()) {
				cout << "Zwalniamy kana³" << endl;
				file_ << "Zwalniamy kana³" << endl;

				file_.close();
			}
		}

		//ptrToSystem_->getPtrToGenerator_R_()->rand(0,2p)
	}
	
}