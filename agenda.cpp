#include "agenda.h"


Agenda::Agenda()
{
}

void Agenda::setAgenda(Event* ev_) {

	agenda.push_back(ev_);
	sortByTime();
}
void Agenda::sortByTime() {
	agenda.sort(CompareEventTime());
}
list<Event*> &Agenda::getAgenda(){
	return agenda;
}


Agenda::~Agenda()
{
}
