#include "simulation.h"




Simulation::Simulation()
{
	//ptrToSimulation_ = this;
	//STWORZENIE AGENDY
	ptrToAgenda_ = new Agenda();
	numberOfSimulations_ = 1;
	
}


Simulation::~Simulation()
{
}
bool CompareEventTime::operator()(Event * lhs, Event * rhs) {
	return lhs->getTime() < rhs->getTime(); 
}
int Simulation::getNumberOfSimulatons_() {
	return numberOfSimulations_;
}
double Simulation::getTimeOfSimulation_() {
	return timeOfSimulation_;
}
void Simulation::start() {

	cout << "Ile chcesz przeprowadzić symulacji ?" << endl;
	cin >> numberOfSimulations_;
	for (int i = 0; i < numberOfSimulations_; ++i) {

		double lambda_;
		cout << "Podaj wartość Lambdy" << endl;
		cin >> lambda_;

		double initial_phase_;
		cout << "początek fazy" << endl;
		cin >> initial_phase_;

		double timeOfSimulation_;
		cout << "Podaj czas symulacji" << endl;
		cin >> timeOfSimulation_;

		//Tworzenie ziaren
		Kernels *kernels_ = new Kernels(lambda_);
		//inicjalizacja Statystyk
		Statistics *stats_ = new Statistics(initial_phase_, timeOfSimulation_);

		kernels_->generateKernels_(numberOfSimulations_);
		//wyswietlenie ziaren dla zadanej liczby symulacji
		kernels_->displayKernelsList_();
		//inicjalizacja systemu
		ptrToSystem_ = new System(kernels_, stats_);
		//inicjalizacja statystyk
		//Statistics *stats_ = new Statistics(this->ptrToSystem_->getNumberOfReceiversOrTransmitters(),this);

		ptrToSystem_->displayTransmitters();
		ptrToSystem_->displayReceivers();


		//Utworzenie po jednym zdarzeniu czasowym: "CreatePacket" dla każdego nadajnika
		for (int i = 0; i < ptrToSystem_->getNumberOfReceiversOrTransmitters(); ++i) {
			Event *ptrToPacket_ = new CreatePacket(clock_, ptrToSystem_->getTransmitter_(i), ptrToAgenda_, ptrToSystem_);
			ptrToAgenda_->setAgenda(ptrToPacket_);
			
		}
		int isLog_;
		int mode;// zmienna przechowywująca tryb uruchomieniowy symulacji
		cout << "0- uruchomienie symulacji w normalnym trybie" << endl;
		cout << "1- uruchomienie symulacji w trybie krokowym" << endl;
		cin >> mode;

		cout << "Czy wyświetlac logi" << endl;
		cout << "0- ukryj logi " << endl;
		cout << "1- wyświetlaj logi" << endl;
		cin >> isLog_;
		if (isLog_ == 1) {
			ptrToSystem_->setLog_(true);
		}
		else {
			ptrToSystem_->setLog_(false);
		}

		
		//GŁÓWNA PĘTLA SYMULACYJNA
		while (clock_ < timeOfSimulation_) {
			if (ptrToAgenda_->getAgenda().empty())break;
			if (isLog_) {
				cout << "#################" << endl;
				cout << "STAN AGENDY" << endl;
				//wyswietl agende
				this->ptrToAgenda_->displayAgenda_();
				cout << "#################" << endl;
			}
			//pobierz pierwszy komunikat
			Event *type = ptrToAgenda_->getAgenda().front();
			if (type == nullptr)break;
			//Ustaw zegar na następne zdarzenie
			clock_ = type->getTime();
			type->execute();
			if (isLog_) {
				cout << endl << endl;
				cout << "Czas aktualnie obsługiwanego zdarzenia" << endl;
				cout << type->getTime() << endl;
			}
			//usuwam pierwszy komunikat z listy
			ptrToAgenda_->getAgenda().pop_front();
			//delete type;
			if (mode == 1) {
				system("pause");
			}		
		}
		cout << "STATYSTYKI" << endl;
		ptrToSystem_->getPtrToStatistics_()->displayStatistics_();
	}

	

}
