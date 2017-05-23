#include "receiver.h"



Receiver::Receiver()
{
}

Receiver::Receiver(int k) :receiver_id_(k)
{
}

Receiver::~Receiver()
{
}

int Receiver::getReceiverId() {
	return receiver_id_;
}
Ack* Receiver::getAck() {
	return ack_;
}


