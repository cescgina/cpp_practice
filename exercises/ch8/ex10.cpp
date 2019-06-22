#include <string>
#include <iostream>

void print_array(std::string str_arr[], int size){
    for (int i=0; i<size; i++){
        std::cout << str_arr[i] << std::endl;
    }
}

int main(){
    std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    for (int i=0; i<12; i++){
        std::cout << months[i] << std::endl;
    }
    print_array(months, sizeof(months)/sizeof(months[0]));
}
