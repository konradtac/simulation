#ifndef GENERATOR_H_
#define GENERATOR_H_
class Generator
{

public:
	Generator();
	~Generator();

private:
	int kernel_;
	double M = 2147483647.0;
	int A = 16807;
	int Q = 127773;
	int R = 2836;
	int h;
};
#endif // GENERATOR_H_

