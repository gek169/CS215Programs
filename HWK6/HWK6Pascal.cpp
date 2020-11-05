#include<iostream>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>

typedef unsigned int uint; //makes this so much easier to type
typedef long int lint; //ditto

long int factorial(lint n){ //Converting from uint to int has an issue, this solves it
	if(n <= 1)
		return 1;
	else
		return n * factorial(n-1);
} //this is recursive, so it counts

double Pascal_Identity(uint n, uint r){
	double result;
	result = (double)(factorial((lint)n)) / (double)(factorial((lint)n - (lint)r) * factorial(r));
	return result;
}

int main(){
	//for(lint i = 0; i < 10; i++)
	//	printf("\nfactorial(%i) is %i", i, factorial(i));
	//printf("\n");
	//Proof of the pudding
	for(lint n = 0; n < 10; n++)
		for(lint r = 0; r < 10; r++)
			printf("\nn = %ld and r = %ld, and Pascal_Identity(n, r) is %f", n, r, Pascal_Identity(n, r));


	return 0;
}
