#include "uniformGenerator.h"



UniformGenerator::UniformGenerator(int krnl_)
{
	kernel_ = krnl_;
	h = kernel_ / Q;
}


UniformGenerator::~UniformGenerator()
{
}
