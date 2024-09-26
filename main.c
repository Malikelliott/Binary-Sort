/*
Assignment 3
Filename: main.c
Author: Malik Elliott 991610598
Sorting stuff
Date: March 23 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define ARRLEN 10 //No more than 100 because of test_dat file

void selectionSort(int arr[], int n);
void swap (int *x, int *y);
void bubbleSort(int arr[], int n);
void siftDown(int arr[], int size, int root);
void heapSort(int arr[], int size);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void printSorted(int arr[]);
void printTime(double t);

int main() {
    
    int arr [ARRLEN];   int arr2 [ARRLEN];  int arr3 [ARRLEN];  int arr4 [ARRLEN];
    int arr5 [ARRLEN];  int arr6 [ARRLEN];  int arr7 [ARRLEN];  int arr8 [ARRLEN];
    
    printf("The list: [ ");
    for (int i = 0; i < ARRLEN; i++){
        arr[i] = rand() % ARRLEN;
        arr2[i] = arr[i];    arr3[i] = arr2[i];     arr4[i] = arr3[i];
        printf("%d ", arr[i]);
    } printf("]\n\n");
    
    clock_t start = clock();
    printf("BUBBLE SORT"); bubbleSort(arr, ARRLEN); printSorted(arr);
    double timeElapsed = (1000*(double)clock() - start) / CLOCKS_PER_SEC;
    printTime(timeElapsed);
    
    clock_t start2 = clock();
    printf("SELECTION SORT"); selectionSort(arr2, ARRLEN); printSorted(arr2);
    double timeElapsed2 = (1000*(double)clock() - start2) / CLOCKS_PER_SEC;
    printTime(timeElapsed2);
    
    clock_t start3 = clock();
    printf("HEAP SORT"); heapSort(arr3, ARRLEN); printSorted(arr3);
    double timeElapsed3 = (1000*(double)clock() - start3) / CLOCKS_PER_SEC;
    printTime(timeElapsed3);
    
    /**/clock_t start4 = clock();
    printf("QUICK SORT"); quickSort(arr4, 0, arr[ARRLEN-1]); printSorted(arr4);
    double timeElapsed4 = (1000*(double)clock() - start4) / CLOCKS_PER_SEC;
    printTime(timeElapsed4);
    
    
    FILE *fp, *g1, *g2, *g3, *g4;//
    int x = 0;
    int y = 0;
    fp=fopen("test_dat.txt", "r");      g1=fopen("g1.txt", "w");    g2=fopen("g2.txt", "w");
    g3=fopen("g3.txt", "w");    g4=fopen("g4.txt", "w");
    if(fp == NULL)
        printf("File not exist");
    else{
        fprintf(g1, "Unsorted (Bubble)\n");      fprintf(g2, "Unsorted (Selection)\n");
        fprintf(g3, "Unsorted (Heap)\n");      fprintf(g4, "Unsorted (Quick)\n");
        do{
            fscanf(fp, "%d", &arr5[x]);     fprintf(g1, "%d\n", arr5[x]);   fprintf(g2, "%d\n", arr5[x]);
            fprintf(g3, "%d\n", arr5[x]);   fprintf(g4, "%d\n", arr5[x]);
            arr6[x] = arr5[x];      arr7[x] = arr6[x];      arr8[x] = arr7[x];
            x++;
        } while (x < ARRLEN);
        
        printf("G1:"); bubbleSort(arr5, ARRLEN); printf("G2:"); selectionSort(arr6, ARRLEN);
        printf("G3:"); heapSort(arr7, ARRLEN);   printf("G4:"); quickSort(arr8, 0, ARRLEN);
        fprintf(g1, "\nSorted\n"); fprintf(g2, "\nSorted\n");
        fprintf(g3, "\nSorted\n"); fprintf(g4, "\nSorted\n");
        
        do{
            fprintf(g1, "%d\n", arr5[y]); fprintf(g2, "%d\n", arr6[y]);
            fprintf(g3, "%d\n", arr7[y]); fprintf(g4, "%d\n", arr8[y]);
            y++;
        } while (y < ARRLEN);
    }
}

void bubbleSort(int arr[], int n) {
    bool swapped;
    int comp = 0;
    int swa = 0;
    for (int i = 0; i < n-1; i++) {
        swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
                swapped = true;
                swa++;
            }
            comp++;
        }
    if (swapped == false) break;
    }
    printf("\nNumber of comparisons: %d, Number of swaps: %d\n", comp, swa);
}

void swap (int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int arr[], int n) {// work on
    int comp = 0;
    int swa = 0;
    int min_idx;
    for (int i = 0; i < n-1; i++) {
        min_idx = i;
        for (int j = i+1; j < n; j++){
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
            comp++;  
        }
        swap(&arr[min_idx], &arr[i]);
        swa++;
    }
    printf("\nNumber of comparisons: %d, Number of swaps: %d\n", comp, swa);
}

void heapSort(int arr[], int size) {//work on
    int comp = 0;
    int swa = 0;
    // Build heap (rearrange array, i.e. heapify) 
    for (int i = size/2 - 1; i >= 0; i--)
        siftDown(arr, size, i);
        swa++;
       
        // One by one extract an element from heap 
    for (int i = size - 1; i > 0; i--) {
        swap(&arr[i], &arr[0]);
        comp++;
        siftDown(arr, i, 0); //heapify the root
    }
    printf("\nNumber of comparisons: %d, Number of swaps: %d\n", comp, swa);
}

void siftDown(int arr[], int size, int root) {
    int temp = arr[root];
    int child = 2*root + 1;
    while (child < size) {
        if (child < size-1 && arr[child] < arr[child+1])
            child++;   //choose root of right subtree
        if (temp >= arr[child]) break;  //root is good now
            arr[root] = arr[child];   //copy max child to root
            root = child;    //move down to continue
            child = 2*root + 1;   //left child
    } 
    arr[root] = temp;  //put “bad” root to proper place
}

void quickSort(int arr[], int low, int high) {
    
    if (low < high){
        /* pi is partitioning index, arr[pi] is now
           at right place */
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);  // Before pi
        quickSort(arr, pi + 1, high); // After pi
    }
    
}

int partition(int arr[], int low, int high) { 
    int comp = 0;
    int swa = 0;
    int pivot = arr[high];  // takes last element as pivot 
    int i = low;  // Index of the first greater element   
    for (int j = low; j <= high - 1; j++)  {
        if (arr[j] <= pivot) { 
            // swap with the first greater element
            swap(&arr[i], &arr[j]); 
            i++; 
            comp++;
        } 
    }  
    swap(&arr[i], &arr[high]); //put pivot to its place
    swa++;
    printf("\nNumber of comparisons: %d, Number of swaps: %d\n", comp, swa);
    return i; //return the new partitioning index
}

void printSorted(int arr[]){
    for (int i = 0; i < ARRLEN; i++){
        printf("%d ", arr[i]);
    }
}

void printTime(double t){
    printf("\nTime: %f seconds\n\n", t);
}





