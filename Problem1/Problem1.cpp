/*
Author: <Yaru Niu> 
Class: ECE6122 
Last Date Modified: <2019-10-06>
Description: Solution to Problem 1 of Homework 3
*/

#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;

// Main
int main(int argc, char* argv[]) {
	// Obtain the height and the width
    int height = atoi(argv[2]);
    int width = atoi(argv[4]);
    unsigned long long *number;
    number = new unsigned long long[height];
    // Muti-thread (one)
    #pragma omp parallel num_threads(1)
    {
    	// Dynamic programming
	   	for (int i = 0; i < height; ++i)
	        number[i] = 1;
	    // Count the number of routes from the right to left
	    for (int j = width - 1; j >= 0; --j){
	    	// Count the number of routes from the bottom to top
	        for (int k = height - 1; k >= 0; --k){
	        	// The point at the bottom only has one route
	            if (k == height - 1)
	                number[k] = number[k] + 1;
	            else
	                number[k] = number[k] + number[k + 1];
	        }
	    }
	    cout << "Number of Routes: " << number[0] << endl;
    }
}