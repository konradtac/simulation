#include "kernels.h"



Kernels::Kernels(double l_)
{
	uni_gen_ = new UniformGenerator(123);
	exp_gen_ = new ExponentialGenerator(uni_gen_, l_);
	lambda_= l_;
}
void Kernels::generateKernels_(int nOSimulations_){
	ofstream file_;
	file_.open("kernels.txt", ofstream::out | ofstream::trunc);
	int number_of_simulations_ = nOSimulations_;
	int number_exp_generators_ = number_of_simulations_ * 8;
	int number_uni_generators_ = number_of_simulations_ * 3;//(CTPK+R+losowanie id transmittera)
	int kernel_ = 0;
	for (int i = 0; i < (number_exp_generators_+number_uni_generators_); ++i) {
		for (int j = 0; j < 100000; ++j) {
			uni_gen_->rand01_();
			kernel_ = uni_gen_->getKernel_();
		}
		//zapisanie ziaren:
		file_ << kernel_ << endl;
		kernelsList_.push_back(kernel_);
	}
	file_.close();
}
void Kernels::displayKernelsList_() {
	//Wyœwietlenie zawartoœci listy ziaren
	cout << "LISTA ZIAREN" << endl;
	for (list<int>::iterator it = kernelsList_.begin(); it != kernelsList_.end(); it++)
		cout << *it << endl;
}
list<int> &Kernels:: getKernelsList_() {
	return kernelsList_;
}
double Kernels::getLambda_() {
	return lambda_;
}


Kernels::~Kernels()
{
}
