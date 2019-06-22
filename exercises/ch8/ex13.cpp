#include <iostream>


void ind_iteration(const int* arr, const int size){
    for (int i=0; i<size; i++){
        std::cout << arr[i] << std::endl;
    }
}

void ptr_iteration(const int* arr, const int size){
    const int* end = arr+size;
    //while(arr != end){
    for (const int *ptr = arr; ptr != end; ptr++){
        std::cout << *ptr << std::endl;
        arr++;
    }
}

int main(){
    int a[5]={0, 1, 2, 3, 4}, b=5;
    ind_iteration(a, b);
    ptr_iteration(a, b);
}
