#include <iostream>
#include <string>
using namespace std; //Oh, for shame!
class Circle{
    public:
        Circle(){
            radius = 0.0;
        }
        void setRadius(double rad){radius = rad;}
        double getRadius(){return radius;}
        double getArea(){return pi * radius * radius;}
        double getDiameter(){return radius * 2.0;}
        double getCircumference(){return 2.0 * pi * radius;}
    private:
        double pi = 3.14159;
        double radius = 0;
};

Circle myCirc;
double inrad = 0.0;

int main() {
	std::cout << "Enter Radius: ";
	std::cin >> inrad;
	myCirc.setRadius(inrad);
	std::cout << "Area = " << myCirc.getArea() << "\nDiameter = " << myCirc.getDiameter() << "\nCircumference = " << myCirc.getCircumference() << std::endl;
	return 0;
}
