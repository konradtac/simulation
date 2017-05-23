#ifndef PACKAGE_H_
#define PACKAGE_H_
#include <iostream>
using namespace std;
class Package
{
public:
	Package();
	Package(int,int, double);
	~Package();

	int getId();
	double getCtpTime();
	double getCreateTime_();

private:
	double time_Ctp_; //czas transmisji wiadomoœci ze stacji nadawczej do odbiorczej
	int package_id_;//identyfikator pakietu
	//STATYSTYKI
	double createTime_;

};
#endif // CHANNEL_H_