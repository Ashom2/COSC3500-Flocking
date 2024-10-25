#include <stdio.h>
#include <chrono>

#include "flockingCPU.h"

//Must be compiled with flockingCPU.cpp
//To run do:
//g++ -o flockingProfiler flockingProfiler.cpp flockingCPU.cpp

const char *profilingFilepath = "ProfilingData.csv";

/*
Saves 
*/
void save(FILE *fptr, int number, double time1) {
    // Write row to file
    fprintf(fptr, "%d, %g\n", number, time1);
}

//TODO check that the parameters are the same - especially numCells (or automate)
//TODO add error between comparisons
//TODO don't overwrite file, just add new line

//performance-affecting variables:
//number of boids
//Cell dimensions


//TODO these should be retrieved, or set the same
const int numCells_x = 16;
const int numCells_y = 16;


int main()
{
    // Create a file and open it for writing
    FILE *fptr;
    fptr = fopen(profilingFilepath, "w");
    if (fptr == NULL) {
        printf("%s", "Error opening file");
        return 1;
    }

    //Column headings
    fprintf(fptr, "N, Time (ms)\n");



    for (int N = 1; N < 100001; N *= 10) {
        //Initialize arrays
        Boid* boidsArray = initBoids(N);
        Cell cellsArray[numCells_x * numCells_y];
        initCells(N, boidsArray, cellsArray);    

        // Begin timing
        auto start = std::chrono::high_resolution_clock::now();

        // Do function
        updateFrame(cellsArray);

        // End timing
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> duration_us = end - start;

        printf("Time taken: %g us\n", duration_us.count());

        save(fptr, N, duration_us.count());
    }

    // Close the file
    fclose(fptr);

    return 0;
}