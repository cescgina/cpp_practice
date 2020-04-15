#include <string>
#include <iostream>
#include <unistd.h>
#include "backend.h"

void printHelp(){
    std::cerr << "Usage is: ./access.o [-r -n user-number -h]" << std::endl;
    std::cerr << "Input parameters description:" << std::endl;
    std::cerr << "\t-f: Path to existing database to use " << std::endl;
    std::cerr << "\t-n: Number of users that will interact" << std::endl;
    std::cerr << "\t-t: Whether to use a text file for the database" << std::endl;
    std::cerr << "\t-h: Show help " << std::endl;
}


int main(int argc, char** argv){
    int c, users=1;
    std::string database="database.txt";
    bool use_db = true;
    while ((c = getopt(argc, argv, "hf:n:t")) != -1){
        switch (c){
            case 'h':
                printHelp();
                return 0;
            case 'f':
                database = std::string(optarg);
                break;
            case 'n':
                users = std::stoi(std::string(optarg));
                break;
            case 't':
                use_db = false;
                break;
        }
    }
    UserManager users_information = UserManager(database, use_db);
    for (int i=0; i<users; ++i){
       users_information.getUserInformation();
       users_information.handleUser();
    }

}
