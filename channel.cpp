#include "channel.h"



Channel::Channel():collision_(false),bussy_(false),channelBuffor_(), ack_(nullptr)
{
}


Channel::~Channel()
{
}


bool Channel::isBussy() {
	return bussy_;
}
bool Channel::isCollision() {
	return collision_;
}
int Channel::getIdRecipient() {
	return id_recipient;
}
Package* Channel::getPackage() {
	return package_;
}
Ack* Channel::getAck() {
	return ack_;
}
void Channel::setPackage(Package* p_) {
	channelBuffor_.push_back(p_);
	package_ = p_;
}
void Channel::setAck(Ack* p_) {
	ack_ = p_;
}
void Channel::setBusy(bool b_) {
	bussy_ = b_;
}