#include "merge_sort.hpp"
#include "bubble_sort.h"
#include <chrono>
#include <raylib.h>
#include <thread>
#include <vector>
#include "main.h"
#include <stack>
extern std::stack<screen> screenStack;
extern screen currentscreen;
extern int bar_width;
extern int comparision_count;
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        comparision_count++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
		DrawState(arr,left,right);
        merge(arr, left, mid, right);
		DrawState(arr,left,right);
    

       
    }
}


void RunMergeSortVisualizer(){

    SetTargetFPS(30); // Change This Value To Increase Animation Time 

    
    const int max_barHeight = GetScreenHeight()-100;
    const int min_barHeight = 20; 
    const int bar_count = GetScreenWidth()/(bar_width+1);
    

    std::vector<int> dataset; 
    for(int i =0;i<bar_count;i++){
        dataset.push_back(GetRandomValue(min_barHeight, max_barHeight));
    }
    bool isSorted = false;
  

    while(!WindowShouldClose()){
   
        ClearBackground(RAYWHITE);
        if(IsKeyPressed(KEY_B)){
            currentscreen = screenStack.top();
            break; 
       }
        if(!isSorted){
            mergeSort(dataset,0,dataset.size()-1);
            isSorted = true;
        }
        DrawState(dataset,-1,-1);
  

    }
    



}
