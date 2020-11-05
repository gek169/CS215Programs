#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>


int main(){
	//std::cout << "Welcome to Chapter 5 Project!\n";
	std::ifstream file;
	std::string line;
	int numcount = 0;
	float numsum = 0;
	float average = 0;
    file.open("Random.txt");
    if (file.is_open())
		while(file.good()){
				getline(file, line);
				if (line.length() > 0) //This might not do anything... I don't know
					numcount++;
				else
					continue;
				
				numsum += atof(line.c_str());
			}
	else
		std::cout << "UNABLE TO OPEN FILE!!! FRICK!!!\n";
		
	if(numcount > 0)
	{
		average = numsum / numcount;
		std::cout << "\nNumber of numbers:\n" << numcount << "\nSum the numbers:\n" << numsum << "\nAverage of the numbers:\n" << average << std::endl; 
	} else {
		std::cout << "\nMAJOR SCREW UP, CALL JOHNNY";
	}
	return 0;
}
