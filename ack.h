#ifndef ACK_H_
#define ACK_H_
#include "package.h"
class Ack
{
public:
	Ack();
	Ack(int);
	~Ack();
	int getAckId();
	static const int getCtiz() {
		return kCtiz_;
	}
private:
	static const int kCtiz_ =1; //czas transmisji wiadomoœci ACK
	int ack_id_;//identyfikator pakietu
};
#endif // ACK_H_
