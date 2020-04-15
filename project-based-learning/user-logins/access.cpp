#include <string>
#include <iostream>
#include <unistd.h>
#include "backend.h"

void printHelp(){
    std::cerr << "Usage is: ./access.o [-r -n user-number -h]" << std::endl;
    std::cerr << "Input parameters description:" << std::endl;
    std::cerr << "\t-f: Path to existing database to use " << std::endl;
    std::cerr << "\t-n: Number of users that will interact" << std::endl;
    std::cerr << "\t-h: Show help " << std::endl;
}

UserManager initDatabase(const std::string& db_path){
    if (db_path != ""){
        return UserManager(db_path);
    }
    else{
        return UserManager();
    }
}

int main(int argc, char** argv){
    int c, users=1;
    std::string database="";
    while ((c = getopt(argc, argv, "hf:n:")) != -1){
        switch (c){
            case 'h':
                printHelp();
                return 0;
            case 'f':
                database = std::string(optarg);
                break;
            case 'n':
                users = std::stoi(std::string(optarg));
        }
    }
    UserManager users_information = initDatabase(database);
    for (int i=0; i<users; ++i){
       users_information.getUserInformation();
       users_information.handleUser();
    }

}
