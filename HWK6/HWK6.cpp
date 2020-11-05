#include<iostream>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>

bool isPalinDrome(char* inword, int length){ //use strlen to calculate string length for length
	char test1, test2;
	if(length <= 1) //strings with length 1 are already palindromes
		return true;
	//The first and last characters
	test1 = inword[0]; test2 = inword[length -1];
	//printf("\n%c versus %c, hmmm....", test1, test2);
	if(test1 == test2)
		return true && isPalinDrome(inword + 1, length - 2);
	else
		return false;
	return true;

	//WORD: ABRACADABRA
	//Iteration 1: A VS A, call against [1] and [length-2]
	//Iteration 2: B VS R, return false
	//return is false
}
int main(){
	char* strings[] = {"Hello", "ABBA", "GODDOG", "ABRACADABRA", "YAGGAY", "GODADOG"};
	int strings_length = 6;
	for(int i = 0; i < strings_length; i++)
		printf("\nString %i is palindrome: %i", i, isPalinDrome(strings[i], strlen(strings[i]) ) ) ;
}
