#include <iostream>

int main(){
    struct Month{const char* name; int days;};
    const char* months[12] ={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Month mont_struct[12]={{"January", 31}, {"February", 28}, {"March", 31}, {"April", 30}, {"May", 31}, {"June", 30}, {"July", 31}, {"August", 31}, {"September", 30}, {"October", 31}, {"Nobember", 30}, {"December", 31}};
    for (int i=0; i<12; i++){
        std::cout << "Month " << months[i] << " has " << days[i] << " days" << std::endl;
    }
    for (int i=0; i<12; i++){
        std::cout << "Month " << mont_struct[i].name << " has " << mont_struct[i].days << " days but with a struct" << std::endl;
    }
}
