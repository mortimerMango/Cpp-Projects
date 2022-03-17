#include <iostream>
using namespace std;
/*
 * Implementation of a bitonic mergesort
 * IF asc is TRUE, then the output is in ascending order
 * IF asc is FALSE, then output is in descending order
 */

void merge(int* input, int size, int* output, bool output_asc) {

    if(output_asc){                     //TRUE == ASCENDING
        int i = 0, j = size-1, k = 0;
        while(i < size/2 && j >= 0){
            if(input[i] < input[j]){
                output[k++] = input[i++];
            }
            else
                output[k++] = input[j--];
        }
        while(i < size/2)
            output[k++] = input[i++];
        while(j >= 0)
            output[k++] = input[j--];
    }
    else{                               //FALSE == DESCENDING
        int i = size/2 -1, j = size/2, k = 0;
        while(i >= 0 && j < size){
            if(input[i] > input[j])
                output[k++] = input[i--];
            else
                output[k++] = input[j++];
        }
        while(i >= 0)
            output[k++] = input[i--];
        while(j < size)
            output[k++] = input[j++];
    }
}

void mergesort(int *input, int size, int* output, bool output_asc) {

    if(size == 0){}
    else if(size == 1){
        output[0] = input[0];
    }
    else{
        int* temp = new int[size];
        int mid = size/2;
        mergesort(input, mid, temp, 1);
        mergesort(input + mid, size - mid, temp + mid, 0);
        merge(temp, size, output, output_asc);
    }
}

int* mergesort(int* input, int size) {
    int* output = new int[size];
    mergesort(input, size, output, false);
    return output;
}
