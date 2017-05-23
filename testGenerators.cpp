#include <iostream>
#include "simulation.h"
#include "uniformGenerator.h"
#include <string>
#in

using namespace std;







int main() {

	UniformGenerator *gen = new UniformGenerator(123);
	for (int i = 0; i < 100; ++i) {
		cout << gen->rand01_() << endl;
		//cout << gen->getKernel_() << endl;
	}

	int k;

	//Simulation *simulate_ = new Simulation();
	//simulate_->start();

	//delete simulate_;
	cin >> k;
	return 0;

}