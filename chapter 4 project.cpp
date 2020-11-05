#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    int num = -1;
    while(num < 1 || num > 10)
	{
		std::cout << "\nEnter a number (1 - 10):";std::cin >> num;
	}
	std::cout << "\n The Roman numeral version of " << num << " is ";
	switch(num){
		case 1:
			std::cout << "I.\n";
			break;
		case 2:
			std::cout << "II.\n";
			break;
		case 3:
			std::cout << "III.\n";
			break;
		case 4:
			std::cout << "IV.\n";
			break;
		case 5:
			std::cout << "V.\n";
			break;
		case 6:
			std::cout << "VI.\n";
			break;
		case 7:
			std::cout << "VII.\n";
			break;
		case 8:
			std::cout << "VIII.\n";
			break;
		case 9:
			std::cout << "IX.\n";
			break;
		case 10:
			std::cout << "X.\n";
			break;
	}
    return -1;
}
