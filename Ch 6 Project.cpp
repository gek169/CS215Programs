#include <iostream>
using namespace std;
bool isPrime(int x){
	if (x < 2)
		return false;
	else if (x < 4) //No reason to test 2 or 3 which are both prime
		return true;
	else {
		int i = x - 1;
		bool Divisor_Found = false;
		while (i > 1 && Divisor_Found == false){
			if (x%i == 0)
				Divisor_Found = true;
			i--;	
		}
		return !Divisor_Found;
	}
}
int main() {
	int input = 2;
		std::cout << "Enter a number and I'll tell you whether it is prime: ";
		std::cin >> input;
		if(isPrime(input))
			std::cout << input <<" is prime \n";
		else
			std::cout << input <<" is NOT prime \n";
	return 0;
}
