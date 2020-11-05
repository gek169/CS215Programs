#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <fstream>

int* Function(int* in_array, int array_size){
	int* return_val = new int[array_size * 2];
	for(int i = 0; i < array_size * 2; i++){
		if(i < array_size)
			return_val[i] = in_array[i];
		else
			return_val[i] = 0;
	}
	return return_val;
}

int main(){
	int N;
	int N_Failsafe = 0;
	int* in_array = nullptr;
	int* out_array = nullptr;
	std::ifstream file;
	std::string line;
	int num_lines = 0;
	//std::cout << "\n Enter number of ints in file: " << std::endl;
	std::cin >> N;
	if(N > 50 || N < 0) return 1; // Fail condition: greater than 50
	file.open("data"); // it doesn't say .txt
    if (!file.is_open()) return 1; // Fail condition: failed to open file
    in_array = new int[N];
    //take in all the things in the file
    while(file.good() && num_lines < N){
				getline(file, line);
				if (line.length() > 0) 
					{num_lines++;N_Failsafe++;}
				else
					continue;
				
				in_array[num_lines-1] = atoi(line.c_str());
	}
	out_array = Function(in_array, N);
	for(int i = 0; i < N * 2; i++){
		std::cout << out_array[i] << std::endl;
	}
	return 0;
}


//Exact contents of "data" file I used:
/*
13
1556
-89
23
4
9
10
11
12
3
5
9
12



145810
14
4
* EOF
 * */
//Worked for multiple versions
