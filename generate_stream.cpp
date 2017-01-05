/******************************************************/
/*    generate pseudo random stream for testing       */
/******************************************************/
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <random>
#include <math.h>
//generate the library of symbols
std::vector<int> generateWeights(int numSymbols, std::string distributionType, double r){
	// weights
	std::vector<int> weights;
	// generate weights
	// uniform
	if(distributionType == "uni"){
		std::cout << "*****uniform_distribution*****" << std::endl;
		for (int i = 0; i < numSymbols; ++i){
			weights.push_back(1);
		}
	}
	// geometric
	if(distributionType == "geo"){
		std::cout << "*****geometric_distribution*****" << std::endl;
		// k
		double k = (1.0 - r)/(1 - pow(r, (double)numSymbols));
		int number;
		for (int i = 0; i < numSymbols; ++i){
			number = k * pow((double)r, (double)i) * numSymbols;
			weights.push_back(number);
		}
	}
	return weights;
}
int main(int argc, char const *argv[]){
	// input arguments
	// number of input arguments
	if(argc < 2){
		std::cout << "Please input arguments for ./generate_stream" << std::endl;
		std::cout << "./generate_tream <number of lines> <number of symbols> <type of distribution> <times> <r>(needed when you choose [geometric])" << std::endl;
		std::cout << "<number of lines>: the number of lines of the stream." << std::endl;
		std::cout << "<number of symbols>: all the different values in the stream, each value is a random number." << std::endl;
		std::cout << "<type of distribution>: the type of the distribution of the random number.[uni]-> uniform distribution [geo] -> geometric distribution." << std::endl;
		std::cout << "<times>: the times of the printing of the stream, the first(maj) and second(ent) algorithm needs 2 times." << std::endl;
		std::cout << "<seed>: the seed for random number generator." << std::endl;
		std::cout << "<r>: r for geometric law, needed when you choose [geometric]." << std::endl;
		std::cout << "i.e ./generate_stream 10 100 geo 2 1 0.5" << std::endl;
		std::cout << "********************************" << std::endl;
		return 0;
	}
	// number of lines
	int numLines = 0;
	if(argv[1]){
		numLines = atoi(argv[1]);
	}else{
		std::cout << "Please add argument <number of lines>" << std::endl;
		return 0;
	}
	// number of symbols
	int numSymbols = 0;
	if(argv[2]){
		numSymbols = atoi(argv[2]);
	}else{
		std::cout << "Please add argument <number of symbols> after <number of lines>" << std::endl;
		return 0;
	}
	// distribution type
	std::string distributionType = "";
	if(argv[3]){
		distributionType = argv[3];
	}else{
		std::cout << "Please add argument <type of distribution> [uni] or [geo] after <number of symbols>" << std::endl;
		return 0;
	}
	// number of passes
	int times = 0;
	if(argv[4]){
		times = atoi(argv[4]);
	}else{
		std::cout << "Please add argument <times> after <type of distribution>" << std::endl;
		return 0;
	}
	// seed
	int seed = 0;
	if(argv[5]){
		seed = atoi(argv[5]);
	}else{
		std::cout << "Please add argument <seed> after <times>" << std::endl;
		return 0;
	}
	// r 
	double r = 0.0;
	if(distributionType == "geo"){
		if(argv[6]){
			r = atof(argv[6]);
			
		}else{
			std::cout << "Please add argument <r> after <seed>" << std::endl;
			return 0;
		}
	}
	// weigths
	std::vector<int> weights = generateWeights(numSymbols, distributionType, r);
	std::cout << "********************************" << std::endl;
	// random number generator
	for (int i = 0; i < times; ++i){
		std::default_random_engine generator(seed);

		std::discrete_distribution<int> distribution(weights.begin(), weights.end());
		// generate stream
		for (int i = 0; i < numLines; ++i){
			// define the symbol
			int symbol = distribution(generator);
			// output line
			std::cout << symbol << std::endl;
		}
		std::cout << "*" << std::endl;
	}
	return 0;
}