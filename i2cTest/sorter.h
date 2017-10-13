// sorter.h
// Module to spawn a separate thread to sort random arrays 
// (permutations) on a background thread. It provides access to 
// contents of the current (potentially partially sorted) array, 
// and to the count of the total number of arrays sorted.

#ifndef _SORTER_H_
#define _SORTER_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Globally defined variables
pthread_mutex_t mutex;
int numSortedArr;
int arrLength;
int* globArray;

/******************************************************************/
//Array sorting-related functions

// Create array
void createArray(int length);

// Utilizes swap and randomizer functions to create permutation of array
void permutation(int *arr, int arrSize);

// For each element in array, choose a random number and then swap
int randomizer(int arrSize);

// Simple swap helper function
void swap(int* arr, int i, int j);

// Sorts array
void bubbleSort(int* arr, int arrSize);

// Begin/end the background thread which sorts random permutations.
void* sorter_startSorting(void* arg);

// Prints array 10 elements per line
void printArr(int *arr, int arrLength, int space);


#endif
