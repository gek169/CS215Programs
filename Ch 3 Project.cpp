#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    float rain_month_1;
    float rain_month_2;
    float rain_month_3;
    char    month1[20], month2[20], month3[20];
    
    cout << "Input month: "; cin >> month1;
    cout << "Input rainfall for " << month1 << ": "; cin >> rain_month_1;
    
    cout << "Input month: "; cin >> month2;
    cout << "Input rainfall for " << month2 << ": "; cin >> rain_month_2;
    
    cout << "Input month: "; cin >> month3;
    cout << "Input rainfall for " << month3 << ": "; cin >> rain_month_3;
    
    cout << "The average rainfall for "
    << month1 << ", "
    << month2 << ", and "
    << month3 << " is "
    << setprecision(2) << showpoint << fixed
    << (rain_month_1+rain_month_2+rain_month_3)/3.0
    << " inches." << endl;
    return -1;
}
