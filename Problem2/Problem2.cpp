/*
Author: <Yaru Niu>
Class: ECE6122
Last Date Modified: <2019-10-6>
Description: Solution to Problem 2 of Homework 3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <omp.h>
#include <time.h>

using namespace std;
// Main
int main(int argc, char* argv[]){
    fstream input;
    int number;
    int flag1 = 0;
    int flag2 = 0;
    int rows;
    int columns;
    long int **matrix;
   // Read the file, and store the data into a dynamic 2D array
   const char* filepath = argv[1];
    input.open(filepath, ios::in);
    if (!input){
        cout << "Unable to open file";
    }
    while(input >> number){
        if (flag1 == 0){
            rows = number;
            flag1 = flag1 + 1;
        }

        else if (flag1 == 1){
            columns = number;
            flag1 = flag1 + 1;
            matrix = new long int*[rows];
            for (int i = 0; i < rows; ++i){
                matrix[i] = new long int[columns];
            }
        }
        else{
            matrix[flag2/columns][flag2%columns] = number;
            flag2 = flag2 + 1;
        }

    }
    input.close();
    // Find the largest product
    long int maxValue = -9223372036854775807;
    double start, end, cost;
    start = clock();
    // Multi-threads
    #pragma omp parallel for num_threads(2)
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < columns; ++j){
            // Go through each number in the matrix
            long int down = -9223372036854775807;
            long int right = -9223372036854775807;
            long int diag1 = -9223372036854775807;
            long int diag2 = -9223372036854775807;
            if (i + 3 < rows){
                // The product in the downside dirction®
                down = matrix[i][j] * matrix[i+1][j] * matrix[i+2][j] *matrix[i+3][j];
                if (down > maxValue){
                    maxValue = down;
                }
            }
            if (j + 3 < columns){
                // The product in the rightside direction
                right = matrix[i][j] * matrix[i][j+1] * matrix[i][j+2] * matrix[i][j+3];
                if (right > maxValue){
                    maxValue = right;
                }
            }
            if ((i + 3 < rows) && (j + 3 < columns)){
                // The product in one of the diagonals
                diag1 = matrix[i][j] * matrix[i+1][j+1] * matrix[i+2][j+2] * matrix[i+3][j+3];
                if (diag1 > maxValue){
                    maxValue = diag1;
                }
            }
            if ((i + 3 < rows) && (j - 3 >= 0)){
                // The product in the other diagonal
                diag2 = matrix[i][j] * matrix[i+1][j-1] * matrix[i+2][j-2] * matrix[i+3][j-3];
                if (diag2 > maxValue){
                    maxValue = diag2;
                }
            }
        }
    }
    // Output the largest product in a txt file
    end = clock();
    cost = end - start;
    cout << cost/CLOCKS_PER_SEC << endl;
    // cout << CLOCKS_PER_SEC << endl;
    ofstream output;
    output.open("output2.txt");
    output << maxValue;
    cout << maxValue << endl;
}
