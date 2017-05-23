#ifndef EXPOTENTIALGENERATOR_H_
#define EXPOTENTIALGENERATOR_H_
#include "uniformGenerator.h"
#include <cmath>

class ExponentialGenerator
{
public:
	ExponentialGenerator(UniformGenerator*,double);
	~ExponentialGenerator();

	double rand_();
	double rand_(int);//losowanie dla retransmisji
private:
	double lambda_ = 0.0;
	UniformGenerator* uniform_generator_;
};
#endif // EXPOTENTIALGENERATOR_H_
