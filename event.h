#ifndef EVENT_H_
#define EVENT_H_
#include<iostream>
#include<string>
using namespace std;

class Event
{
public:
	Event();
	~Event();
	virtual void execute() = 0;
	virtual Event* getTypeOfEvent()=0;
	virtual string getClassName() = 0;
	double getTime() { return time_; }
protected:
	double time_;
};

#endif // EVENT_H_
