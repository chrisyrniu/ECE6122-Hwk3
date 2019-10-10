/*
Author: <Yaru Niu>
Class: ECE6122
Last Date Modified: <2019-10-06>
Description: Solution to Problem 3 of Homework 3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <omp.h>
#include <time.h>

using namespace std;

// Main
int main(int argc, char* argv[]){
    fstream input;
    int number;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    int rows;
    int **triangle;
    int *maxSum;
    // Read the file, and store the data of the triangle into a dynamic 2D array
    const char* filepath = argv[1];
    input.open(filepath, ios::in);
    if (!input){
        cout << "Unable to open file";
    }
    while(input >> number){
        if (flag1 == 0){
            rows = number;
            triangle = new int*[rows];
            for (int i = 0; i < rows; ++i){
                triangle[i] = new int[i + 1];
            }
            flag1 = flag1 + 1;
        }
        else{
            triangle[flag2][flag3] = number;
            if (flag2 == flag3){
                flag3 = 0;
                flag2 = flag2 + 1;
            }
            else{
                flag3 = flag3 + 1;
            }
        }
    }
    input.close();
    //Muti-thread (one)
    #pragma omp parallel num_threads(1)
    {
        // Dynamic programming: get the maximum sum from the bottom to top
        // Initialize the maxSum array with the bottom number of the triangle
        maxSum = triangle[rows - 1];
        for (int m = rows - 2; m >= 0; --m){
            for (int n = 0; n <= m; ++n)
                maxSum[n] = max(maxSum[n], maxSum[n + 1]) + triangle[m][n];
        }
        cout << maxSum[0] << endl;
        ofstream output;
        output.open("output3.txt");
        output << maxSum[0];
    }
}
