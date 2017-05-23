#include "exponentialGenerator.h"



ExponentialGenerator::ExponentialGenerator(UniformGenerator* uniform_gen_, double l_)
{
	uniform_generator_ = uniform_gen_;
	lambda_=l_;

}


ExponentialGenerator::~ExponentialGenerator()
{
}

double ExponentialGenerator::rand_() {
	double k = uniform_generator_->rand01_();
	return -(1.0 / lambda_) * log(k);
}
double ExponentialGenerator::rand_(int r_) {
	double k = uniform_generator_->rand01_();
	return -(1.0 / double(r_)) * log(k);
}