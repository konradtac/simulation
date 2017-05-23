#include <iostream>
#include "simulation.h"
#include "uniformGenerator.h"
#include "exponentialGenerator.h"
#include <string>
#include <fstream>

using namespace std;







int main() {
	


	int k;
	
	Simulation *simulate_ = new Simulation();
	simulate_->start();

	delete simulate_;
	cin >> k;
	
	return 0;

}