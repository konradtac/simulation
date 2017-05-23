#ifndef AGENDA_H_
#define AGENDA_H_
#include "event.h"
#include<iostream>
#include<list>

using namespace std;


struct CompareEventTime {
	bool operator()(Event * lhs, Event * rhs);
};
class Agenda
{
public:
	Agenda();
	~Agenda();

	void setAgenda(Event* ev_);
	void sortByTime();
	list<Event*> &getAgenda();
	void displayAgenda_() {
		for (list<Event*>::iterator it = agenda.begin(); it != agenda.end(); it++) {
			cout << (*it)->getTime() << ' '<<" Zdarzenie: "<<(*it)->getClassName()<<" ";
			cout << endl;
		}
	}
private:
	list<Event*> agenda;
};
#endif // AGENDA_H_
