#ifndef UNIFORMGENERATOR_H_
#define UNIFORMGENERATOR_H_
class UniformGenerator
{

public:
	UniformGenerator(int);
	~UniformGenerator();


	void rand_() {
		h = kernel_ / Q;
		kernel_ = A*(kernel_ - Q*h) - R*h;
		if (kernel_ < 0)
			kernel_ = kernel_ + static_cast<int>(M);
	}
	//generate kernel_ from 0 to 1
	double rand01_() {
		h = kernel_ / Q;
		kernel_ = A*(kernel_ - Q*h) - R*h;
		if (kernel_ < 0)
			kernel_ = kernel_ + static_cast<int>(M);
		return kernel_ / M;
	}
	int getKernel_() { return kernel_; }

	 double rand(int start_, int end_)
	{
		return rand01_()*(end_ - start_) + start_;
	}


private:
	int kernel_;
	double M = 2147483647.0;
	int A = 16807;
	int Q = 127773;
	int R = 2836;
	int h;
};
#endif // UNIFORMGENERATOR_H_
