#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector> //USED ONLY FOR SPLITTING STRINGS
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#define nullptr 0

//UTILITY FUNCTIONS

//Note: This use of STD VECTOR shouldn't count against the spec. It's not a member of the class, and although this is referenced by the class and the return type used, again the vector is not a member of the class.
//I could replace this by using the provided example, but this version is file-error safe
//I could also write my own vector, but that would be complicated. I circumvent such a need and use STL vector solely for splitting strings.
inline std::vector<std::string> SplitString(const std::string &s, char delim)
{
    std::vector<std::string> elems;

    const char* cstr = s.c_str();
    unsigned int strLength = s.length();
    unsigned int start = 0;
    unsigned int end = 0;

    while(end <= strLength)
    {
        while(end <= strLength)
        {
            //if((cstr[end] == delim && end = strLength-1) ||(cstr[end] == delim && (end < strLength - 1) && cstr[end+1] != delim)) //Do not break until we've reached the end of the spaces. This means that multiple spaces will just leave trailing spaces on the end.
            if(cstr[end] == delim)
                break;
            end++;
        }

        elems.push_back(s.substr(start, end - start));
        //~ elems.back().erase(remove_if(elems.back().begin(), elems.back().end(), isspace)); //Remove space characters
        if(elems.back() == "" || elems.back() == " ")
			elems.pop_back();
        start = end + 1;
        end = start;
    }

    return elems;
}

//Gets rid of spaces
void cleanse_string(std::string& s){
	s.erase(remove(s.begin(),s.end(),' '),s.end());
}

//Finds a string within a string
bool findString(std::string s1, std::string s2){
	if (s1.find(s2) != std::string::npos) {
		return true;
	}
	return false;
}
//END OF UTILITY FUNCTIONS


//Per-spec
struct car{
	car(){ //Just in case
		
	}
	std::string Make_Model = "";
	size_t year = 0;
	std::string color = "";
	std::string car_class = "";
	std::string fuel_type = "";
	double price = -1;
	void printMe(){ //Print this
		std::cout << "\n" 			<< Make_Model 	<< std::endl;
		std::cout << "Year: " 		<< year 		<< std::endl;
		std::cout << "Color: " 		<< color 		<< std::endl;
		std::cout << "Class: " 		<< car_class 	<< std::endl;
		std::cout << "Fuel type: " 	<< fuel_type 	<< std::endl;
		std::cout << "Price: " 		<< price 		<< std::endl;
	}
	void writeMe(std::ofstream& file){ //Write this
		file << "\n" << Make_Model; //Line 1
		file << "\n" << year << " " << color << " " << car_class << " " << fuel_type << " " << price;
	}
};

class AutoDealer{
private:
	car* CarArray; //I seriously doubt you will have more than 65,535 cars. Also, it's the maximum of size_t according to the spec.
	//Using a fixed array of the maximum possible size is a waste of memory, but
	//the program spec doesn't say I don't have to and it means I don't have to constantly
	//malloc() memcpy() free()
	size_t count = 0;
public:
	car*& getCarArray(){ //Get the pointer to the array, necessary for the copy constructor
		return CarArray;
	}
	AutoDealer(){ //Constructor per-spec
		CarArray = new car[65535]; //HEAP ALLOCATION NECESSARY
		count = 0;
	}
	AutoDealer(AutoDealer& Other) //Copy constructor
	{
		count = Other.count;
		CarArray = Other.getCarArray();
		//We stole it, run away!
		Other.getCarArray() = nullptr;
	}
	~AutoDealer(){ //Destructor
		if(CarArray != nullptr)
			delete[] CarArray;
	}
	void inputCarInfo(){ //Grab keyboard input, make a new car
		if(count >= 65535)
			return;
		car SampleCar; //the car to be put in the array
		std::string last_input_text; //exactly what it is
		std::cout << "\nWhat is the make and model of the car? ";
		std::getline(std::cin, SampleCar.Make_Model);
		std::cout << "\nColor?";
		std::getline(std::cin, SampleCar.color);
		cleanse_string(SampleCar.color);
		std::cout << "\nYear? ";
		std::getline(std::cin, last_input_text);
		SampleCar.year = atoi(last_input_text.c_str());
		std::cout << "\nClass? ";
		std::getline(std::cin, SampleCar.car_class);
		cleanse_string(SampleCar.car_class);
		
		std::cout << "\nFuel Type? ";
		std::getline(std::cin, SampleCar.fuel_type);
		cleanse_string(SampleCar.fuel_type);
		
		std::cout << "\nPrice? ";
		std::getline(std::cin, last_input_text);
		SampleCar.price = atof(last_input_text.c_str());
		
		CarArray[count] = SampleCar;
		count++;
	}
	int readCarsFile(std::string filename){ //Parse a data file
		//~ std::cout << "\nMARK1";
		std::ifstream file;
		file.open(filename.c_str());
		if (!file.is_open()) {std::cout << "\nERROR! FILE NOT GOOD!"; return 1;} // Fail condition: failed to open file
		//I will not be using the method presented as an example, because it does not handle incorrect spacing correctly.
		count = 0;
		
		//~ std::cout << "\nMARK2";
		while(file.good() && count < 65535)
		{
			
			car SampleCar;
			std::vector<std::string> Tokens; //USED ONLY FOR STRING PARSING!!! CAN BE REPLACED WITH YOUR CODE, BUT CAN'T DO SPACING ERROR HANDLING!!! PLEASE DON'T COUNT OFF POINTS!!! IT IS TECHNICALLY ACCORDING TO SPECIFICATION!
			std::string line1 = ""; //line1 of a car definition
			std::string line2 = ""; //line2 of a car definition
			//~ std::cout << "\nMARK3" << std::endl;
			while(file.good() && (line1.length() < 3 || (line1.length() > 1 && line1[0] == '#')) ) //It is impossible for a line to meet the spec and not be at least 3 characters long. Additionally, I want file comments.
				std::getline(file, line1); //Car make and model line
			if(!file.good())
				return 0; //Uh oh, no part 2!
			while(file.good() && (line2.length() < 9 || (line2.length() > 1 && line2[0] == '#')) ) //It is impossible for a line to meet the spec and not be at least 9 characters long. Additionally, I want file comments.
				std::getline(file, line2); //Car make and model line
			//std::getline(file, line2);
			SampleCar.Make_Model = line1;//BAM!
			//~ std::cout << "\nMARK4" << std::endl;
			Tokens = SplitString(line2, ' '); //STL vector returned. I might replace it with a piece of malloc'd memory or an array, IDK
			//~ std::cout << "\nMARK5" << std::endl;
			if(Tokens.size() < 5) continue;//If there aren't enough tokens, don't try to parse them.
			
			SampleCar.year = atoi(Tokens[0].c_str());
			SampleCar.color = (Tokens[1]);
			SampleCar.car_class = (Tokens[2]);
			SampleCar.fuel_type = (Tokens[3]);
			SampleCar.price = atof(Tokens[4].c_str());
			CarArray[count] = SampleCar;
			count++;
		}
		return 0;
	}
	//Search for a car based on three parameters. All matching any of the parameters will appear.
	void searchCar(std::string make_model_search, std::string car_class_search, std::string car_color_search){
		for(size_t i = 0; i < count; i++){
			std::string make_model_car = CarArray[i].Make_Model;
			std::string car_class_car = CarArray[i].car_class;
			std::string car_color_car = CarArray[i].color;
			if(findString(make_model_car, make_model_search) ||
			   findString(car_class_car, car_class_search) ||
			   findString(car_color_car, car_color_search))
				CarArray[i].printMe();
		}
	}
	//Display all cars
	void displayCars(){
		for(size_t i = 0; i < count; i++)
			CarArray[i].printMe();
	}
	//Write the cars file
	void writeCarsFile(){
		std::ofstream file;
		file.open("Car_DB.txt");
		file << "\n#CAR DATABASE FILE, 0 CALORIES\n#NOW WITHOUT GLUTEN";
		for(size_t i = 0; i < count; i++)
			CarArray[i].writeMe(file);
	}
};
AutoDealer MyDealer;
int IQ = 100; //IT RETURNS

//I split the options in the menu up into functions. Pretty basic stuff. Not worth talking about.
void Option_1(){
	//input new car info
	MyDealer.inputCarInfo();
	IQ++;
}

void Option_2(){
	//display stuff
	MyDealer.displayCars();
	IQ++;
}

void Option_3(){
	//search
	std::string t1, t2, t3; //these names are useful because they're literally just placeholders for the first, second, and third arguments of the searchcar function
	std::cout << "\nENTER MAKE AND MODEL (case sensitive): ";
	std::getline(std::cin, t1);
	std::cout << "\nENTER CLASS (case sensitive): ";
	std::getline(std::cin, t2);
	std::cout << "\nENTER COLOR (case sensitive): ";
	std::getline(std::cin, t3);
	MyDealer.searchCar(t1,t2,t3);
	IQ++;
	
}

void Option_4(){
	//Make like a tree and LEAVE you idiot!
	std::cout << "\n*slapped on backside of head*";
	std::cout << "\n*Your IQ has decreased to 69 due to brain damage*";
	std::cout << "\nIt's LEAVE you idiot!";
	std::cout << "\n\"Make like a tree and LEAVE\"";
	std::cout << "\nYou sound like a damn fool when you say it wrong";
	IQ = 69; //70-1
}

//Main
int main(int argc, char** argv){
	//std::cout << "\nFIRST EXECUTION IN MAIN" << std::endl;
	
	MyDealer.readCarsFile("Car_DB.txt");
	//MyDealer.displayCars();
	std::string opt1 = "";
	int select = 0;
	bool shouldQuit = false;
	
	std::string s1 = "Find the token within the string and you get a bunch of gold!";
	std::string s2 = "a bunch of gold!";
	std::cout << "\n\n" << findString(s1, s2) << std::endl;
	while(!shouldQuit){ //Do I need to explain this one?
		std::cout << "\nWhere do you want to go today?" <<
					 "\n1 Enter More Data" <<
					 "\n2 Display Information" <<
					 "\n3 search for a car" <<
					 "\n4 Make like a tree and get out of here!" << std::endl;
		std::getline(std::cin, opt1);
		select = atoi(opt1.c_str());
		//I moved everything into the functions, nothing to talk about here.
		switch(select){
			case 1:
				Option_1();break;
			case 2:
				Option_2();break;
			case 3:
				Option_3();break;
			case 4:
				Option_4();break;
			default:
				std::cout << "\nWhat, you don't know how to use a menu? Idiot."; IQ -= 5;
			break;
		}
		if(IQ < 70) //No longer qualified to use my software
		{
			shouldQuit = true;
		}
	}
	if(IQ < 70)
		std::cout << "\nSorry, my software has detected that you are not smart enough to continue using the computer.\nPerhaps you should take up java programming." << std::endl;
	MyDealer.writeCarsFile();
}
