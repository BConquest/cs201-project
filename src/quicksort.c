#include "../include/quicksort.h"

void swap(int *i, int *j)
{
    int t = *i;
    *i = *j;
    *j = t;
}

int partition(int *array,int *positions, int low, int high)
{
    int pivot = array[high];
    int i = (low - 1);

    for(int j = low; j <= high -1; j++)
    {
        if(array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
            swap(&positions[i], &positions[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    swap(&positions[i + 1], &positions[high]);
    return i + 1;
}

void quickSort(int *sort, int *positions, int low, int high)
{
    if (low < high) 
    { 
        int index = partition(sort, positions, low, high); 

        quickSort(sort, positions, low, index - 1); 
        quickSort(sort, positions, index + 1, high); 
    } 
}