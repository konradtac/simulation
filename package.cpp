#include "package.h"



Package::Package()
{
}
Package::Package(int time_, int id_, double ct_ ): time_Ctp_(time_), package_id_(id_), createTime_(ct_)
{
}

Package::~Package()
{
}
int Package::getId() {
	return package_id_;
}
double Package::getCtpTime() {
	return time_Ctp_;
}
double Package::getCreateTime_() {
	return createTime_;
}