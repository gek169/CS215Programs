#include <iostream>
#include <string>
using namespace std; //Oh, for shame!
double getDouble(std::string text){
	double return_val = -1.0;
	while(return_val < 0.0)
	{
		std::cout << text;
		std::cin >> return_val;
		if(return_val < 0.0)
			std::cout << "invalid data (negative rainfall) -- retry"; //literally exactly what it says to print
	}
	return return_val;
}
int main() {
	double months[12];
	std::string month_names[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	double sum = 0;
	double average = 0;
	int least_rain = 0;
	double least_rain_value = 1000000000000000.0; //Unlikely to be higher than this. I could include the numeric_limits library to make sure, but revel has errored when I did that before
	int most_rain = 0;
	double most_rain_value = 0.0;
	
	for(int i = 0; i < 12; i++)
		{
			months[i] = getDouble( ((i==0)?std::string("\tEnter rainfall for "):std::string("\t Enter rainfall for ")) + month_names[i] + ":"); //Carefully crafted to reproduce the EXACT output shown in revel
			sum += months[i];
			if(months[i] > most_rain_value){
				most_rain = i;
				most_rain_value = months[i];
			}
			
			if(months[i] < least_rain_value){
				least_rain = i;
				least_rain_value = months[i];
			}
		}
	std::cout << "\t Total rainfall: " << sum << std::endl;//4-space tab plus one space
	std::cout << "\tAverage rainfall: " << sum / 12.0 << std::endl;//4-space tab and no space
	std::cout << "\tLeast rainfall in: " << month_names[least_rain] << std::endl;
	std::cout << "\tMost rainfall in: " << month_names[most_rain] << std::endl;
	std::cout << "\t\n   "; //This is what it shows on revel, but I don't know how to make a 3 space tab that isn't made of spaces so I made it out of spaces 
	
	return 0;
}
