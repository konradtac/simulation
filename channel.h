#ifndef CHANNEL_H_
#define CHANNEL_H_
#include <iostream>
#include "package.h"
#include "ack.h"
#include <list>
using namespace std;
class Channel
{
public:
	Channel();
	~Channel();

	bool isBussy();
	bool isCollision();
	int getIdRecipient();
	void setPackage(Package*);
	void setAck(Ack*);
	void setBusy(bool);//ustaw zajêtoœæ kana³u
	void setCollision(bool a_) {
		collision_ = a_;
	}
	void removePackage() {
		package_ = nullptr;
	}
	void removeAck() {
		ack_=nullptr;
	}
	Package* getPackage();
	Ack* getAck();
	list<Package*>& getChannelBuffor() { return channelBuffor_; }
private:
	list<Package*> channelBuffor_;
	bool bussy_; // flaga informuj¹ca, czy kana³ jest zajêty (0- wolny 1-zajêty)
	bool collision_; // flaga informuj¹ca, czy w kanale wystêpuje kolizja (0- nie wystêpuje 1-wystêpuje)
	int id_recipient; //numer odbiornika, do którego ma dotrzeæ pakiet 
	Package* package_; //przechowywanie pakietu podczas transportu do odbiornika
	Ack* ack_; //przechowywanie ACK podczas transportu do nadajnika

};

#endif // CHANNEL_H_
