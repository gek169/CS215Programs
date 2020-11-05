
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<string>

#define nullptr 0
//if you are on Windows:
//#define CLEAR_COMMAND "cls"
//if you are running a good OS:
#define CLEAR_COMMAND "clear"

struct Customer_Datum{
	Customer_Datum(
		std::string _name = "\n\n",//The user physically cannot type 2 newlines
		std::string _address = "",
		std::string _city = "",
		std::string _state = "",
		std::string _ZIP_code = "",
		std::string _Telephone = "",
		double _AcctBal = 0,
		std::string _DateLastPayment = ""
	){ //genius
		name = _name;
		address = _address;
		city = _city;
		state = _state;
		ZIP_code = _ZIP_code;
		Telephone = _Telephone;
		AcctBal = _AcctBal;
		DateLastPayment = _DateLastPayment;
	}
	void reset(){
		name = "\n\n";
	}
	void printme(){
		if(name == "\n\n")
			return;
		std::cout << "\n\n\nCustomer name: " << name;
		std::cout << "\nCustomer address: " << address;
		std::cout << "\nCity: " << city;
		std::cout << "\nState: " << state;
		std::cout << "\nZIP code: " << ZIP_code;
		std::cout << "\nTelephone: " << Telephone;
		std::cout << "\nAccount balance: " << AcctBal;
		std::cout << "\nDate of last payment: " << DateLastPayment;
	}
	std::string name = "\n\n";//The user physically cannot type newline
	std::string address = "";
	std::string city = "";
	std::string state = "";
	std::string ZIP_code = "";
	std::string Telephone = ""; 
	double AcctBal = 0;
	std::string DateLastPayment = "";
};

Customer_Datum Data[256]; 
bool shouldQuit = false; //Quit the program
std::string option_text = "";

int get_first_empty(){
	int i = 0;
	while(i < 256 && Data[i].name != "\n\n") i++; //Elegant, isn't it?
	return i;
}

int main(){
	while(!shouldQuit){
		system(CLEAR_COMMAND);//Makes printing much prettier
		std::cout << "\n1. Enter new account information\n2. Change account information\n3. Display all account information\n4. Exit the program" << std::endl;
		std::getline(std::cin,option_text);
		int option = atoi(option_text.c_str());
		switch(option){
			case 1:
				option = get_first_empty();
				if(option >= 256)
				{
					std::cout << "\nError: Database full" << std::endl;
				} else {
					std::cout << "\nCustomer name: ";
					std::getline(std::cin, Data[option].name);
					std::cout << "\nCustomer address: ";
					std::getline(std::cin, Data[option].address);
					std::cout << "\nCity: ";
					std::getline(std::cin, Data[option].city);
					std::cout << "\nState: ";
					std::getline(std::cin, Data[option].state);
					std::cout << "\nZIP code: ";
					std::getline(std::cin, Data[option].ZIP_code);
					std::cout << "\nTelephone: ";
					std::getline(std::cin, Data[option].Telephone);
					//we need to do an atof (returns a double)
					std::cout << "\nAccount balance: ";
					std::getline(std::cin, option_text);
					Data[option].AcctBal = atof(option_text.c_str());
					
					std::cout << "\nDate of last payment: ";
					std::getline(std::cin, Data[option].DateLastPayment);
				}
			break;
			case 2:
				std::cout << "\n\nWhat number?" << std::endl;
				std::getline(std::cin, option_text); option = abs(atoi(option_text.c_str()))%256;
				Data[option].printme();
				std::cout << "\n\n" << std::endl;
					std::cout << "\nCustomer name: ";
					std::getline(std::cin, Data[option].name);
					std::cout << "\nCustomer address: ";
					std::getline(std::cin, Data[option].address);
					std::cout << "\nCity: ";
					std::getline(std::cin, Data[option].city);
					std::cout << "\nState: ";
					std::getline(std::cin, Data[option].state);
					std::cout << "\nZIP code: ";
					std::getline(std::cin, Data[option].ZIP_code);
					std::cout << "\nTelephone: ";
					std::getline(std::cin, Data[option].Telephone);
					//we need to do an atof (returns a double)
					std::cout << "\nAccount balance: ";
					std::getline(std::cin, option_text);
					Data[option].AcctBal = atof(option_text.c_str());
					
					std::cout << "\nDate of last payment: ";
					std::getline(std::cin, Data[option].DateLastPayment);
			break;
			case 3:
				for(int i = 0; i < 256; i++)
				{
					Data[i].printme();
					if(Data[i].name != "\n\n"){
						std::cout << "\nPress enter to continue..." << std::endl;
						std::getline(std::cin, option_text);
					}
				}
			break;
			case 4:
				shouldQuit = true;
			break;
			default:
			break;
		}
	}
	return 0;
}
