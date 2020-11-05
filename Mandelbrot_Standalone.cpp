#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>
//~ //UNCOMMENT THE FOLLOWING LINE TO DISABLE MULTITHREADING
//~ #define USE_THREADING //If this is defined, then threading options will be enabled

//~ #ifdef USE_THREADING
//~ #include <pthread.h>
//~ #endif
#define NUM_TESTS_PER_ALGO 10
#define NUM_ALGOS 4
#define USE_WORST_CASE false //Useful for calculating Big O notation

//Variables
long int swap_counter = 0, loop_counter = 0;
unsigned int inputter = 0;
long int UserNumOfNumbers = 10000;
long int swap_counter_array[NUM_TESTS_PER_ALGO * NUM_ALGOS];
long int loop_counter_array[NUM_TESTS_PER_ALGO * NUM_ALGOS];
clock_t start_time = 0;
clock_t end_time = 0;
double time_seconds;
double time_seconds_array[NUM_TESTS_PER_ALGO * NUM_ALGOS];
float angle_iter = 0;
float angle_iter_amt = 0.01;
//~ AssortedSorter* mySorter = nullptr;

///For the mandelbrot renderer. 32 x 32
struct imaginary_number{ //doubles as a vec2
	float real = 0;
	float imaginary = 0;
	imaginary_number(float x, float y){
		real = x;
		imaginary = y;
	}
	void Rotate(float pivot_x, float pivot_y, float angle){
		if (angle == 0)
            return;

        float s = sin(angle);
        float c = cos(angle);

        real      -= pivot_x;
        imaginary -= pivot_y;
		
		float nx = (real      * c) - (imaginary     * s);
		float ny = (real * s)      + (imaginary * c);
		
        real      = nx + pivot_x;
        imaginary = ny + pivot_y;
	}
};

int mandelbrot_test(imaginary_number c, int maxiter, float testvalsq) { //x component is real, y is imaginary
		float zr = 0;
		float zi = 0; //Factor of i
		float lastzr = 0;
		for (int i = 0; i < maxiter; i++)
		{
			zr = (zr * zr) - (zi * zi) + c.real;
			zi = 2 * lastzr * zi + c.imaginary;
			if(zr * zr + zi * zi > testvalsq){
				return i;
			}
			lastzr = zr;
		}
		return maxiter;
}

void renderMandelBrot(unsigned int width, unsigned int height, int maxiter, imaginary_number mandelcenter, imaginary_number scales, float angle){
	char screen[(width + 1) * height + 1];
	screen[(width + 1) * height] = '\0';//String terminator, so it can be printed
	for(int i = 0; i < (width + 1) * height; i++) //Clear the rest
		screen[i] = ' ';//Space
	for(int y = 0; y < height; y++)
		screen[width + (width + 1) * y] = '\n';
	for(int x = 0; x < width; x++)
		for(int y = 0; y < height; y++)
		{
			const char Gradient[5] = {' ', '.', '^', '@', '#'};
			//Determine the coordinates on the Z plane to sample from
			//First, get the explicit point in screenspace
			imaginary_number sampling_point = {(float)x / (width) - 0.5f, (float)y / (height) - 0.5f};
			//Second, scale 
			sampling_point.real *= scales.real;
			sampling_point.imaginary *= scales.imaginary;
			
			//Third, Shift
			sampling_point.real -= mandelcenter.real;
			sampling_point.imaginary -= mandelcenter.imaginary;
			
			//Fourth, Rotate
			sampling_point.Rotate(0, 0, angle);
			
			
			
			//finally, do the mandelbrot test for this point
			int result = mandelbrot_test(sampling_point, maxiter, 1000.0);
			char outchar = '#';
			outchar = Gradient[(int)(4.0f * (float)result / (float)maxiter)];
			screen[x + (y * (width + 1))] = outchar;
		}
	//~ std::cout << "\n" << (char*)screen << std::endl; //should work
    system("clear");
    printf("\n%s",(char*)screen);
    fflush(stdout);
}

void* threaded_function(void* arg); //For threading
//Threading variables~~~~~~~~~~~~~~~~~~~
std::string Status = "";
bool done = false; //Bools are always either true or false so they can be used sort of like atomic variables... Level 100 Jankiness but it works

int main(){
	
	system("clear");
	//If we don't use threading, just straight up call it
	//~ #ifndef USE_THREADING
		//~ threaded_function(nullptr);
	//~ #endif
	//~ #ifdef USE_THREADING
	//~ pthread_create(&tid, NULL, threaded_function, NULL);
		//Display the thread status and draw something pretty ;)
		
		while(!done){
			//wait for 16.666666 milliseconds
			clock_t begin_frame = clock();
			while((double)(clock() - begin_frame)/CLOCKS_PER_SEC < 0.016666666) //Wait for a frame, it's ridiculous to be locking and unlocking a mutex faster than refresh
			{/**Dont do anything!**/}
			
			//START CRITICAL SECTION
			//~ pthread_mutex_lock(&CriticalSection);
				//~ std::string criticaltext = Status;
			//~ pthread_mutex_unlock(&CriticalSection);
			//END CRITICAL SECTION
			
			system("clear");
			//~ std::cout << "STATUS: " << criticaltext << "\n";
			renderMandelBrot(64, 64, 128, imaginary_number(0,0.5), imaginary_number(2, 2), angle_iter);
			angle_iter += angle_iter_amt;
			if(angle_iter > 2 * 3.14159)
				angle_iter = 0;
		}
	return 0;
} //Eof main





