#include<iostream>
#include<cmath>


int strange(int n)
{
        int result;
        if (n == 1)
        {
     result = 0;
        }
        else
        {
     result = 1  +  strange(n / 2);
        }
        return result;
} 

int Pascal(int n, int r)
{
	//conditions for breaking
	if(r > n) return 0;
	if((r == 0) || (r == n)) return 1;
	return Pascal(n - 1, r - 1) + Pascal(n-1, r);
}

int main()
{
	int n;
	int r;
	std::cout << "\nEnter n:" << std::endl;
	std::cin >> n;
	std::cout << "\nEnter r:" << std::endl;
	std::cin >> r;
	std::cout << "\nCalculating...";
	std::cout << "\nResult of Pascal is: " << Pascal(n,r);
	return 0;
}
