#include "ack.h"



Ack::Ack()
{
}
Ack::Ack(int id):ack_id_(id)
{
}

Ack::~Ack()
{
}

int Ack::getAckId() {

	return ack_id_;
}
