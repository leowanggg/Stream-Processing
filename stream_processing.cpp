/***********************************************************************/
/*                   algorithms for stream processing                  */
/***********************************************************************/
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include <math.h>
#include <map>
#include <list>
#include <sys/resource.h>

// the function of the first algorithm
void findFrequentElement(double theta){
	std::cout << "##### First alogrithm(finding frequent elements) #####" << std::endl;
	std::cout << std::endl;
	// K (a set of symbols)
	std::map<std::string, int> K;
	// count length of the input stream
	int m = 0;
	// define the input line
	std::string line;
	// for mesuring the elapsed time
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::duration<double> duration;
	// first pass
	do{ 
		std::cin >> line;
		// std::cout << line << " ";
		if(line != "*"){
			start = std::chrono::steady_clock::now();
			// count the length of the input stream
			++m;
			// if x[i] is in K
			if(K.find(line) != K.end()){
				// then count[x[i]] := count[x[i]] + 1
				K[line] ++;
			}
			// else insert x[i] in K, set count[x[i]] := 1
			else{
				K[line] = 1;
			}
			// if |K| > 1/theta
			if (K.size() > 1/theta){
				// for all a in K do
				for (auto itK = K.begin(); itK != K.end();){
					// count[a] = count[a] - 1
					itK -> second --;
					// if count[a] = 0
					if(itK -> second == 0){
						// delete a from K
						K.erase(itK++);
					}
					else{
						++itK;
					}
				}
			}
			end = std::chrono::steady_clock::now();
			duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		}
	}while(line != "*");
	// find the tallies of all symbols in K
	for (auto itK = K.begin(); itK != K.end(); ++itK){
		itK -> second = 0;
	}
	// second pass
	do{ 
		std::cin >> line;
		if(line != "*"){
			start = std::chrono::steady_clock::now();
			// if x[i] is in K
			if(K.find(line) != K.end()){
				// then count[x[i]] := count[x[i]] + 1
				++K[line];
			}
			end = std::chrono::steady_clock::now();	
			duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		}
	}while(line != "*");
	// delete from K the symbols with tally less than θN
	start = std::chrono::steady_clock::now();
	for (auto itK = K.begin(); itK != K.end();){
		if(itK -> second <= theta*m){
			K.erase(itK++);
		}
		else{
			++itK;
		}
	}
	end = std::chrono::steady_clock::now();
	duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	//output K
	// check if K is empty
	if(K.empty()){
		std::cout << "There exist not symbol with frequency more than "<< theta << std::endl;
	}
	else{
		std::cout << "The symbol(s) with frequency more than "<< theta << " is(are): ";
		for (auto itK = K.begin(); itK != K.end(); ++itK){
			std::cout << itK -> first << " ";
		}
	}
	std::cout << std::endl;
	std::cout << "The algorithm took: " << duration.count() << " s." << std::endl;
	std::cout << std::endl;
	std::cout << "######################################################" << std::endl;
}
// define the function of the brute-force algorithm compared to the first algorithm
void findFrequentElementBF(double theta){
	std::cout << "##### Brute-force algorithm(finding frequent elements) #####" << std::endl;
	std::cout << std::endl;
	// define K (a set of symbols)
	std::map<std::string, int> K;
	// define the input line
	std::string line;
	// count length of the input stream
	int m = 0;
	// for mesuring the elapsed time
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::duration<double> duration;
	do{ 
		std::cin >> line;
		if(line != "*"){
			start = std::chrono::steady_clock::now();
			++m;
			if(K.find(line) != K.end()){
					// then count[x[i]] := count[x[i]] + 1
				K[line] ++;
			}
				// else insert x[i] in K, set count[x[i]] := 1
			else{
				K[line] = 1;
			}
			end = std::chrono::steady_clock::now();
			duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		}
	}while(line != "*");
	int threshold = m*theta;
	start = std::chrono::steady_clock::now();
	for (auto itK = K.begin(); itK != K.end();){
		if(itK -> second > threshold){
			++itK;
		}
		else{
			K.erase(itK++);
		}
	}
	end = std::chrono::steady_clock::now();
	duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	//output K
	// check if K is empty
	if(K.empty()){
		std::cout << "There exist not symbol with frequency more than "<< theta << std::endl;
	}
	else{
		std::cout << "The symbol(s) with frequency more than "<< theta << " is(are): ";
		for (auto itK = K.begin(); itK != K.end(); ++itK){
			std::cout << itK -> first << " ";
		}
	}
	std::cout << std::endl;
	std::cout << "The algorithm took: " << duration.count() << " s." << std::endl;
	std::cout << std::endl;
	std::cout << "######################################################" << std::endl;
}

/*********************Second alogorithm******************************/
// define the function for computing the basic estimator X
double getX(const int r, const int m){
	// comput X
	double X = 0.0;
	if(r != 1){
		X = m*((double)r/(double)m*log2((double)m/(double)r)-((double)r-1.0)/(double)m*log2((double)m/((double)r-1.0)));
	}
	else{
		X = m*((double)r/(double)m*log2((double)m/(double)r));
	}
	return X;
}
// define the median function
double median(const std::list<double> &Y, int s2){
	double medium = 0.0;
	auto itY = Y.begin();
	if(s2%2 == 1){
		advance(itY, s2/2);
		medium = *itY;
	}
	else{
		advance(itY, (s2/2 - 1));
		double a = *itY;
		++itY;
		double b = *itY;
		medium = (a + b)/2.0;
	}
	return medium;
}
// define the function for computing the final estimator Z
double getZ(const std::vector<int> &r, const int s1, const int s2, const int m){
	// calculation
	// define the vector to contain Xij
	std::list<double> Y;
	auto itr = r.begin();
	// 1 <= j <= s2
	for (int j = 0; j < s2; ++j){
		double X = 0.0;
		for (int i = 0; i < s1; ++i){
			double temp = getX(*itr, m);
			X += temp;
			++itr;
		}
		X = X/(double)s1;
		Y.push_back(X);
	}
	Y.sort();
	// define the final estimator Z
	double Z = median(Y, s2);
	return Z;
}
// define the function of the second algorithm
void estimateEntropy(){
	std::cout << "##### Second algorithm(Estimating entropy) #####" << std::endl;
	std::cout << std::endl;
	// define the input line
	std::string line;
	// count length of the input stream
	int m = 0;
	// majority candidate
	std::string candidate;
	int count = 0, mx = 0;
	// final estimator Z
	// s1, s2
	int s1 = 10;
	int s2 = 1;
	int s1s2 = s1*s2;
	// r, al
	std::vector<int> r(s1s2);
	std::vector<std::string> al(s1s2);
	// for mesuring the elapsed time
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::duration<double> duration;
	// first pass
	do{ 
		std::cin >> line;
		if(line != "*"){
			start = std::chrono::steady_clock::now();
			// find a majority candidate x as in Boyer and Moore
			// if count == 0
			if(count == 0){
				candidate = line;
				count = 1;
			}else{
				if(line == candidate){
					++count;
				}
				else{
					--count;
				}
			}
				// calculate r
			++m;
			for (int j = 0; j < s1s2; ++j)
			{
				int p = rand()%m;
				if(p == (m - 1)){
					al[j] = line;
					r[j] = 1;
				}else{
					if(al[j] == line){
						++r[j];
					}
				}
			}
			end = std::chrono::steady_clock::now();
			duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		}
	}while(line != "*");
	// compute final estimator Z
	double Z = getZ(r, s1, s2, m);
	// second pass
	m = 0;
	do{ 
		std::cin >> line;
		// vector to contain all the symbols in a line of the input stream
		if(line != "*"){
			start = std::chrono::steady_clock::now();
			// frequncy mx of the majority candidate
			if(line == candidate){
				++mx;
			}else{
				// calculate r
				++m;
				for (int j = 0; j < s1s2; ++j)
				{	
					al[j] = "";
					r[j] = 1;
					int p = rand()%m;
					if(p == (m - 1)){
						al[j] = line;
						r[j] = 1;
					}else{
						if(al[j] == line){
							++r[j];
						}
					}
				}
			}	
			end = std::chrono::steady_clock::now();
			duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		}
	}while(line != "*");
	// compute the final estimator Y
	start = std::chrono::steady_clock::now();
	double Y = getZ(r, s1, s2, m);
	double H = 0.0;
	if(mx <= m/2){
		H = Z;
	}
	else{
		int k = m - mx;
		H = (double)k*Y/(double)m + (double)(m - k)/(double)m*log2((double)m/(double)(m - k));
	}
	end = std::chrono::steady_clock::now();
	duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	// output the entropy
	std::cout << "The empirical entropy is: " << H << std::endl; 
	std::cout << std::endl;
	std::cout << "The algorithm took: " << duration.count() << " s." << std::endl;
	std::cout << std::endl;
	std::cout << "######################################################" << std::endl;
}
void estimateEntropyBF(){
	std::cout << "##### Brute-force algorithm(estimating entropy) #####" << std::endl;
	std::cout << std::endl;
	// count
	std::map<std::string, int> K;
	// count length of the input stream
	int m = 0;
	// define the input line
	std::string line;
	// for mesuring the elapsed time
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::duration<double> duration;
	do{ 
		std::cin >> line;
		if(line != "*"){
			start = std::chrono::steady_clock::now();
			++m;
			if(K.find(line) != K.end()){
					// then count[A[i]] := count[A[i]] + 1
				K[line] ++;
			}
				// else insert A[i] in K, set count[A[i]] := 1
			else{
				K[line] = 1;
			}
			end = std::chrono::steady_clock::now();
			duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
		}
	}while(line != "*");
	double H = 0.0;
	start = std::chrono::steady_clock::now();
	for (auto itm = K.begin(); itm != K.end(); ++itm){
		H += ((double)(itm -> second)/(double)m*log2((double)m/(double)(itm -> second)));
	}
	end = std::chrono::steady_clock::now();
	duration += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	// output the entropy
	std::cout << "The empirical entropy is: " << H << std::endl; 
	std::cout << std::endl;
	std::cout << "The algorithm took: " << duration.count() << " s." << std::endl;
	std::cout << std::endl;
	std::cout << "######################################################" << std::endl;
}
int main(int argc, char const *argv[])
{	
	bool error = false;
	if(argc < 2){
		std::cout << "Please input arguments for ./stream_processing" << std::endl;
		std::cout << "./stream_processing <name of algorithm> <threshold>(needed when you choose [maj] or [majB])" << std::endl;
		std::cout << "<name of algorithm>: [maj] -> first algorithm,[majB] -> brute-force algorithm for finding frequent items,[ent] -> second algorithm,[entB] -> brute-force algorithm for estimating entropy" << std::endl;
		std::cout << "<threshold>: number between 0 - 1, needed when you choose [maj] or [majB]" << std::endl;
		std::cout << "i.e ./stream_processing maj 0.5" << std::endl;
		return 0;
	}
	std::string algoName = argv[1];
	double theta;
	if(algoName == "maj"||algoName == "majB"){
		if(argc < 3){
			std::cout << "Please add argument <threshold>" << std::endl;
			return 0;
		}
		theta = atof(argv[2]);
	}
	std::string line;
	do{
		std::cin >> line;
	}while(line != "********************************");
	if(algoName == "maj"){
		findFrequentElement(theta);
	}
	else if(algoName == "majB"){
		findFrequentElementBF(theta);
	}
	else if(algoName == "ent"){
		estimateEntropy();
	}
	else if(algoName == "entB"){
		estimateEntropyBF();
	}
	return 0;
}