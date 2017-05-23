#ifndef RECEIVER_H_
#define RECEIVER_H_
#include <queue>
#include <iostream>
#include "ack.h"
using namespace std;
class Receiver
{
public:
	Receiver();
	Receiver(int k);
	~Receiver();

	int getReceiverId();
	Ack* getAck();
	void setPackageRec_(Package *pack_) {
		package_rec_ = pack_;
	}
	void setAck_(Ack *ac_) {
		ack_ = ac_;
	}
private:
	int receiver_id_; //numer identyfikacyjny odbiornika
	Ack* ack_; //flaga ack, pozwalaj�ca na identyfikacj�, czy dany pakiet dotar� do odbiornika
	Package* package_rec_;// pole przechowywuj�ce pakiet, kt�ry dotar�
	


};

#endif // RECEIVER_H_