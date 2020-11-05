#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>
//UNCOMMENT THE FOLLOWING LINE TO DISABLE MULTITHREADING
#define USE_THREADING //If this is defined, then threading options will be enabled

#ifdef USE_THREADING
#include <pthread.h>
#endif
#define NUM_TESTS_PER_ALGO 10
#define NUM_ALGOS 4
#define USE_WORST_CASE false //Useful for calculating Big O notation


class AssortedSorter{
	public:
		AssortedSorter(){
			if(myArray)
				free(myArray);
			myArray = nullptr;
			myArraySize = 20001;
			myArray = new int[myArraySize];
			max_out();
		}
		AssortedSorter(unsigned int size){
			if(myArray)
				free(myArray);
			myArray = nullptr;
			myArraySize = size;
			myArray = new int[myArraySize];
			max_out();
		}
		~AssortedSorter(){
			if(myArray != nullptr)
				free(myArray);
		}
		//Sort algos
		void bubbleSort(long int& loop_counter, long int& swap_counter){
			loop_counter = 0;
			swap_counter = 0;
			bool haveswapped = false;
			do{
				
				haveswapped = false;
				for(int i = 0; i < myArraySize - 1; i++){
					loop_counter++; //Exactly what the assignment says
					if(myArray[i] > myArray[i+1])
						{swap_counter++;haveswapped = true;swap(i, i+1);}
				}
			}while(haveswapped);
		}
		void selectionSort(long int& loop_counter, long int& swap_counter){
			loop_counter = 0;
			swap_counter = 0;
			for(int i = 0; i < myArraySize - 1; i++) //The target
			{
				unsigned int smallest_value_index = i;
				int smallest_value = myArray[smallest_value_index];
				for(int j = i + 1; j < myArraySize; j++) //The source
				{
					loop_counter++; //Exactly where the assignment says to put it
					if(myArray[j] < smallest_value){
						smallest_value = myArray[j];
						smallest_value_index = j;
					}
				}
				//Perform the swap for this position
				swap_counter++;
				swap(i, smallest_value_index);
			}
		}
		void shellSort(long int& loop_counter, long int& swap_counter){
			loop_counter = 0;
			swap_counter = 0;
			for (unsigned int gap = myArraySize/2; gap > 0; gap /= 2){ //Gaps
				for(unsigned int end = gap; end < myArraySize; end++){ //End
					//Perform insertion sort on elements up to end, with gap gap
					int temp = myArray[end]; //This is the value we are considering
					long int high_comp = end;
					for(high_comp = end; high_comp >= gap && myArray[high_comp - gap] > temp; high_comp -= gap)
					{
						myArray[high_comp] = myArray[high_comp - gap]; loop_counter++;
					}
					swap_counter++;
					myArray[high_comp] = temp;
				}
			}
		}
		int partition(unsigned int start, unsigned int stop, long int& loop_counter, long int& swap_counter){ //exact copy, pretty much
			long int up = start, down = stop - 1, part = myArray[stop];
			if(stop <= start)
				return start;
			while(1){
				while(myArray[up] < part)
					{up++;loop_counter++;}
				while ((part < myArray[down]) && (up < down))
					{down--;loop_counter++;}
				if(up >= down)
					break;
				swap_counter++;
				swap(up, down);
				up++;
				down--;
			}
			swap_counter++;
			swap(up, stop);
			return up;
		}
		void quickSort(long int& loop_counter, long int& swap_counter){ //exact copy, pretty much
			loop_counter = 0;
			swap_counter = 0;
			int start = 0;
			int stop = myArraySize - 1;
			int i, s = 0, stack[myArraySize];
			stack[s++] = start;
			stack[s++] = stop;
			while(s > 0){
				stop = stack[--s];
				start = stack[--s];
				if(start >= stop)
					continue;
				i = partition(start, stop, loop_counter, swap_counter);
				if(i - start > stop - i){
					stack[s++] = start;
					stack[s++] = i - 1;
					stack[s++] = i + 1;
					stack[s++] = stop;
				} else {
					stack[s++] = i + 1;
					stack[s++] = stop;
					stack[s++] = start;
					stack[s++] = i - 1;
				}
			}
		}
		
		//Util funcs
		void swap(unsigned int index1, unsigned int index2){
			if(!(index1 < myArraySize && index2 < myArraySize))
				return;
			int temp = myArray[index1];
			myArray[index1] = myArray[index2];
			myArray[index2] = temp;
		}
		void randomize(unsigned int num_values = 10000){
			srand(time(NULL));
			for(int i = 0; i < myArraySize && i < num_values; i++)
				myArray[i] = rand();
		}
		void max_out(){ //Everything will always end up at the end
			for(int i = 0; i < myArraySize; i++)
				myArray[i] = INT_MAX;
		}
		void GenerateReversed(){
			for(int i = 0; i < myArraySize; i++){
				myArray[i] = (int)myArraySize - i; //Doesn't work for values of myArraySize which are above the limit of a signed int
			}
		}
		void printArray(bool commas_or_newlines = true){
			std::cout << "\nARRAY SIZE: " << myArraySize << std::endl;
			std::cout << "ARRAY CONTENTS:" << std::endl << std::endl;
			for(int i = 0; i < myArraySize; i++){
				std::cout << myArray[i];
				if(commas_or_newlines && i != myArraySize - 1)
					std::cout << ",";
				else
					std::cout << std::endl;
			}
		}
		int* getMyArray(){return myArray;}
		unsigned int getSize(){return myArraySize;}
	private:
		int* myArray = nullptr;
		unsigned int myArraySize = 0;
};

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
AssortedSorter* mySorter = nullptr;

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
	std::cout << "\n" << (char*)screen << std::endl; //should work
}

void* threaded_function(void* arg); //For threading
//Threading variables~~~~~~~~~~~~~~~~~~~
std::string Status = "";
#ifdef USE_THREADING
	pthread_mutex_t CriticalSection = PTHREAD_MUTEX_INITIALIZER;
#endif
bool done = false; //Bools are always either true or false so they can be used sort of like atomic variables... Level 100 Jankiness but it works

int main(){
	//Clear out arrays
	for(int i = 0; i < NUM_TESTS_PER_ALGO * NUM_ALGOS; i++){time_seconds_array[i] = 0; swap_counter_array[i] = 0; loop_counter_array[i] = 0;} //make sure there's no junk in there
	//Initialize sorter
	mySorter = new AssortedSorter(20001);
	//Thread variable
	#ifdef USE_THREADING
		pthread_t tid;
	#endif
	//The part of the assignment where things are a bit vague
	std::cout << "\nEnter how many numbers you wish to generate. Less than zero means I choose a number for you." << std::endl;
	std::cin >> UserNumOfNumbers;
	if(!(UserNumOfNumbers > 9 && UserNumOfNumbers < 20001)) //it's what the assignment says. I assume it meant inclusive
		{UserNumOfNumbers = 10000;std::cout << "\nWe chose: " << UserNumOfNumbers << std::endl;}
		
		
	//Set up the worst case, where all elements are in exactly the wrong order
	if(USE_WORST_CASE){
		mySorter->GenerateReversed();
	}
	
	system("clear");
	//If we don't use threading, just straight up call it
	#ifndef USE_THREADING
		threaded_function(nullptr);
	#endif
	#ifdef USE_THREADING
	pthread_create(&tid, NULL, threaded_function, NULL);
		//Display the thread status and draw something pretty ;)
		
		while(!done){
			//wait for 16.666666 milliseconds
			clock_t begin_frame = clock();
			while((double)(clock() - begin_frame)/CLOCKS_PER_SEC < 0.016666666) //Wait for a frame, it's ridiculous to be locking and unlocking a mutex faster than refresh
			{/**Dont do anything!**/}
			
			//START CRITICAL SECTION
			pthread_mutex_lock(&CriticalSection);
				std::string criticaltext = Status;
			pthread_mutex_unlock(&CriticalSection);
			//END CRITICAL SECTION
			
			system("clear");
			std::cout << "STATUS: " << criticaltext << "\n";
			renderMandelBrot(32, 32, 128, imaginary_number(0,0), imaginary_number(2, 2), angle_iter);
			angle_iter += angle_iter_amt;
			if(angle_iter > 2 * 3.14159)
				angle_iter = 0;
		}
		
	pthread_join(tid, NULL); //pull out
	#endif
	std::cout << std::endl;
	renderMandelBrot(96, 96, 128, imaginary_number(0,0), imaginary_number(2, 2), 0.2 * 3.14159);
	//~ //Print statistics
	for(int algo = 0; algo < NUM_ALGOS; algo++){
		std::cout << "\nAlgorithm: ";
		switch(algo){
			case 0:
				std::cout << "\nBubble sort" <<std::endl;
			break;
			case 1:
				std::cout << "\nSelection sort" <<std::endl;
			break;
			case 2:
				std::cout << "\nShell sort" <<std::endl;
			break;
			case 3:
				std::cout << "\nQuick sort" <<std::endl;
			break;
		};
		for(int test = 0; test < NUM_TESTS_PER_ALGO; test++){
			std::cout << "TEST # " << test + 1 << std::endl;
			std::cout << "Swaps: "  << swap_counter_array[algo * NUM_TESTS_PER_ALGO + test];
			std::cout << "\nLoops: "<< loop_counter_array[algo * NUM_TESTS_PER_ALGO + test];
			std::cout << "\nTime: " << time_seconds_array[algo * NUM_TESTS_PER_ALGO + test] << std::endl;
		}
	}
	if(mySorter)
		delete mySorter;
	//Display a few seconds of mandelbrot
	std::cout << "\nEnter 42 to watch the mandelbrot set rotate for 20 seconds, or any other integer to quit" << std::endl;
	std::cin >> inputter;
	if(inputter != 42)
		return 0;
	start_time = clock();
	while((double)(clock() - start_time)/CLOCKS_PER_SEC < 20){
			clock_t begin_frame = clock();
			while((double)(clock() - begin_frame)/CLOCKS_PER_SEC < 0.032) //Wait for a frame, it's ridiculous to be locking and unlocking a mutex faster than refresh
			{/**Dont do anything!**/}
			
			
			system("clear");
			renderMandelBrot(64, 64, 128, imaginary_number(0,0), imaginary_number(2, 2), angle_iter);
			angle_iter += angle_iter_amt;
			if(angle_iter > 2 * 3.14159)
				angle_iter = 0;
	}
	return 0;
} //Eof main















void* threaded_function(void* arg){
	
	//BUBBLE SORT~~~
	for(int i = 0; i < NUM_TESTS_PER_ALGO; i++){
		
		#ifdef USE_THREADING
		//START CRITICAL SECTION
			pthread_mutex_lock(&CriticalSection);
				Status = "BUBBLE SORT | TEST # " + std::to_string(i + 1);
			pthread_mutex_unlock(&CriticalSection);
		//END CRITICAL SECTION
		#endif
		
		if(!USE_WORST_CASE)
			mySorter->randomize(UserNumOfNumbers); //this is exactly what the assignment says to do
		else
			mySorter->GenerateReversed();
		//std::cout << "\nSORTING VIA BUBBLESORT TEST #" << i + 1 << std::endl;
		start_time = clock();
			mySorter->bubbleSort(loop_counter, swap_counter);
		end_time = clock(); 
		//Note the time
		time_seconds = (double)(end_time - start_time)/CLOCKS_PER_SEC; time_seconds_array[i] = time_seconds; //Guh!
		
		//std::cout << "\nResults:\nLOOP COUNTER:" << loop_counter << "\nSWAP COUNTER:" << swap_counter << std::endl;
		//std::cout << "\nTIME TAKEN: " << time_seconds << std::endl; 
		swap_counter_array[i] = swap_counter;
		loop_counter_array[i] = loop_counter;
		//mySorter->printArray(false);
		start_time = 0;
		end_time = 0;
	}
	
	//SELECTION SORT~~~
	for(int i = 0; i < NUM_TESTS_PER_ALGO; i++){
		
		#ifdef USE_THREADING
		//START CRITICAL SECTION
			pthread_mutex_lock(&CriticalSection);
				Status = "SELECTION SORT | TEST # " + std::to_string(i + 1);
			pthread_mutex_unlock(&CriticalSection);
		//END CRITICAL SECTION
		#endif
		if(!USE_WORST_CASE)
			mySorter->randomize(UserNumOfNumbers); //this is exactly what the assignment says to do
		else
			mySorter->GenerateReversed();
		//std::cout << "\nSORTING VIA SELECTION SORT TEST #" << i + 1 << std::endl;
		start_time = clock();
			mySorter->selectionSort(loop_counter, swap_counter);
		end_time = clock(); 
		//Note the time
		time_seconds = (double)(end_time - start_time)/CLOCKS_PER_SEC; time_seconds_array[NUM_TESTS_PER_ALGO * 1 + i] = time_seconds; //Guh!
		
		//std::cout << "\nResults:\nLOOP COUNTER:" << loop_counter << "\nSWAP COUNTER:" << swap_counter << std::endl;
		//std::cout << "\nTIME TAKEN: " << time_seconds << std::endl; 
		swap_counter_array[NUM_TESTS_PER_ALGO * 1 + i] = swap_counter;
		loop_counter_array[NUM_TESTS_PER_ALGO * 1 + i] = loop_counter;
		//mySorter->printArray(false);
		start_time = 0;
		end_time = 0;
	}
	
	for(int i = 0; i < NUM_TESTS_PER_ALGO; i++){
		
		#ifdef USE_THREADING
		//START CRITICAL SECTION
			pthread_mutex_lock(&CriticalSection);
				Status = "SELECTION SORT | TEST # " + std::to_string(i + 1);
			pthread_mutex_unlock(&CriticalSection);
		//END CRITICAL SECTION
		#endif
		if(!USE_WORST_CASE)
			mySorter->randomize(UserNumOfNumbers); //this is exactly what the assignment says to do
		else
			mySorter->GenerateReversed();
		//std::cout << "\nSORTING VIA SELECTION SORT TEST #" << i + 1 << std::endl;
		start_time = clock();
			mySorter->shellSort(loop_counter, swap_counter);
		end_time = clock(); 
		//Note the time
		time_seconds = (double)(end_time - start_time)/CLOCKS_PER_SEC; time_seconds_array[NUM_TESTS_PER_ALGO * 2 + i] = time_seconds; //Guh!
		
		//std::cout << "\nResults:\nLOOP COUNTER:" << loop_counter << "\nSWAP COUNTER:" << swap_counter << std::endl;
		//std::cout << "\nTIME TAKEN: " << time_seconds << std::endl; 
		swap_counter_array[NUM_TESTS_PER_ALGO * 2 + i] = swap_counter;
		loop_counter_array[NUM_TESTS_PER_ALGO * 2 + i] = loop_counter;
		//mySorter->printArray(false);
		start_time = 0;
		end_time = 0;
	}
	
	for(int i = 0; i < NUM_TESTS_PER_ALGO; i++){
		
		#ifdef USE_THREADING
		//START CRITICAL SECTION
			pthread_mutex_lock(&CriticalSection);
				Status = "SELECTION SORT | TEST # " + std::to_string(i + 1);
			pthread_mutex_unlock(&CriticalSection);
		//END CRITICAL SECTION
		#endif
		if(!USE_WORST_CASE)
			mySorter->randomize(UserNumOfNumbers); //this is exactly what the assignment says to do
		else
			mySorter->GenerateReversed();
		//std::cout << "\nSORTING VIA SELECTION SORT TEST #" << i + 1 << std::endl;
		start_time = clock();
			mySorter->quickSort(loop_counter, swap_counter);
		end_time = clock(); 
		//Note the time
		time_seconds = (double)(end_time - start_time)/CLOCKS_PER_SEC; time_seconds_array[NUM_TESTS_PER_ALGO * 3 + i] = time_seconds; //Guh!
		
		//std::cout << "\nResults:\nLOOP COUNTER:" << loop_counter << "\nSWAP COUNTER:" << swap_counter << std::endl;
		//std::cout << "\nTIME TAKEN: " << time_seconds << std::endl; 
		swap_counter_array[NUM_TESTS_PER_ALGO * 3 + i] = swap_counter;
		loop_counter_array[NUM_TESTS_PER_ALGO * 3 + i] = loop_counter;
		//mySorter->printArray(false);
		start_time = 0;
		end_time = 0;
	}
	done = true;
	
	#ifndef USE_THREADING
		return nullptr;
	#endif
	#ifdef USE_THREADING
		pthread_exit(nullptr);
	#endif
}
