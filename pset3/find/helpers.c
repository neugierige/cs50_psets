/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int key, int values[], int size)
{
    int min = 0;
    int max = size-1;
    
    while (min <= max) {
        int midpoint = (min+max)/2;
        if (values[midpoint] < key) {
            min = midpoint + 1;
        } else if (values[midpoint] > key) {
            max = midpoint -1;
        } else {
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            if (values[j] > values[j+1]) {
                int holder = values[j+1];
                values[j+1] = values[j];
                values[j] = holder;
            }
        }
    }
    return;
}