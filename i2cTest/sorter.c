#include "sorter.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int numSortedArr = 0;
int arrLength = 150;
int* globArray;


//function prototypes
// void permutation(int *arr, int arrSize);
// int randomizer(int arrSize);
// void swap(int* arr, int i, int j);
// void bubbleSort(int* arr, int arrSize);
// void* sorter_startSorting(void* arg);
// void printArr(int *arr, int arrLength, int space);


void createArray(int length)
{
int *arr = (int*)malloc(sizeof(int)*length);

	for(int i= 0; i < length; i++)
	{
		arr[i] = i;
	}
	permutation(arr, length);
	bubbleSort(arr, length);
	numSortedArr++;
}


void permutation(int *arr, int arrSize)
{
	for(int i = 0; i < arrSize; i++){

		swap(arr, i, randomizer(arrSize));
	}
}

int randomizer(int arrSize)
{

	int randNum = rand() % arrSize;
	return randNum;
}

void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void bubbleSort(int* arr, int arrSize)
{	
for(int i = 0; i < arrSize; i++)
	{
		for(int j=0; j < arrSize - 1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				swap(arr, j, j+1);
			}
			globArray = arr;
		}
	}
}

void* sorter_startSorting(void* arg)
{
	printf("Started Sorting\n");
	char stopSort = ' ';     //flag

	while(stopSort == ' ')
	{
		pthread_mutex_lock(&mutex);
		createArray(arrLength);
		free(globArray);
		pthread_mutex_unlock(&mutex);
	}
	printf("Exited sorter\n");
	pthread_exit(0);

}

void printArr(int *arr, int arrLength, int space)
{
	for(int i = 0; i < arrLength; i++)
	{
		if(((i % space) == 0) && (i != 0))
		{
			printf("\n");
		}
		if(i == arrLength - 1)
		{
			printf("%d\n", arr[i]);
		}
		else
		{
			printf("%d, \t", arr[i]);
		}
	}
}




