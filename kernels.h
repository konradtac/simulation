#ifndef KERNELS_H_
#define KERNELS_H_
#include <iostream>
#include <fstream>
#include<list>
#include "uniformGenerator.h"
#include "exponentialGenerator.h"
using namespace std;
class Kernels
{
public:
	Kernels(double);
	~Kernels();
	
	
	void generateKernels_(int);
	void displayKernelsList_();
	list<int> &getKernelsList_();
	double getLambda_();
private:
	UniformGenerator *uni_gen_;
	ExponentialGenerator *exp_gen_;
	list<int> kernelsList_;
	double lambda_;
	
};


#endif // KERNELS_H_
