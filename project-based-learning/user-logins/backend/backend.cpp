#include <fstream>
#include <iostream>
#include <crypt.h>
#include "backend.h"

Interface::Interface(const std::string& path_db, bool use_db){
    db_path = path_db;
    db_use = use_db;
    if (db_use){

    }
    else{
        std::ifstream db_connection(db_path);
        if (db_connection.is_open()) {
            // database already exists, do nothing
            db_connection.close();
        }
        else{
            db_connection.close();
            std::ofstream db_connection(db_path);
            db_connection << "Database" << std::endl;
            db_connection.close();
        }
    }
}

/*
Interface::Interface(const Interface& interface) {
    db_path = interface.db_path;
    db_use = interface.db_use;
    std::ifstream db_connection(db_path);
    if (db_use){

    }
    else{
        std::ifstream db_connection(db_path);
        if (db_connection.is_open()) {
            // database already exists, do nothing
            db_connection.close();
        }
        else{
            db_connection.close();
            std::ofstream db_connection(db_path);
            db_connection << "Database" << std::endl;
            db_connection.close();
        }
    }
}
*/

std::pair<std::string, std::string> Interface::readUser(const std::string& username){
    std::string stored_password = "", salt;
    if (db_use){
        
    }
    else{
        std::ifstream db_connection(db_path); 
        std::string line;
        size_t pos=0;
        if (!db_connection.is_open()) {
            std::cout << "Failed to open " << db_path << '\n';
        } 
        else {
            while(std::getline(db_connection, line)){
                if (line[0] == '-' and line.substr(2, line.size()-3) == username){
                    // read password
                    std::getline(db_connection, line);
                    pos = line.find(":");
                    stored_password = line.substr(pos+2);
                    //read salt
                    std::getline(db_connection, line);
                    pos = line.find(":");
                    salt = line.substr(pos+2);
                    break;
                }
            }    
        }
        db_connection.close();
    }
    return std::make_pair(stored_password, salt);
}

void Interface::writeUser(const std::string& username, const std::string& password, const std::string& salt){
    if (db_use){
        
    }
    else{
        std::ofstream db_connection(db_path, std::ios_base::app); 
        db_connection << "- " << username << ":" << std::endl;
        db_connection << "\tpassword: " << password << std::endl;
        db_connection << "\tsalt: " << salt << std::endl;
        db_connection.close();
    }
}

bool Interface::userExists(const std::string& username){
    if (db_use){
        return false;
    }
    else{
        std::ifstream db_connection(db_path); 
        std::string line;
        if (!db_connection.is_open()) {
            std::cout << "Failed to open " << db_path << '\n';
        } 
        else {
            while(std::getline(db_connection, line)){
                if (line[0] == '-' and line.substr(2, line.size()-3) == username){
                    return true;
                }
            }    
        }
        return false;
    }
}


const std::string UserManager::salt_chars = "abcdefghijklmnopqrstvwxyz./ABCDEFGHIJKLMNOPQRSTVWXYZ0123456789";

UserManager::UserManager(const std::string& path_db, bool use_db) : database(path_db, use_db) {
    action = "";
    initRNG();
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
}

UserManager::UserManager(const UserManager& um) : database("", false){
    std::cout << "Using copy constructor" << std::endl;
    database = um.database;
    action = um.action;
    initRNG();
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
}

void UserManager::getUserInformation(){
    action = "";
    while (action != "r" and action != "l"){
        std::cout << "Want to login or register a new user?[l/r]" << std::endl;
        std::cin >> action;
    }
    std::cout << "Enter username:" << std::endl;   
    std::cin >> username;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::cout << "Enter password:" << std::endl;   
    std::cin >> password;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void UserManager::handleUser(){
    if (action == "r"){
       addUser(); 
    }
    else {
       loginUser(); 
    }
}

void UserManager::initRNG(){
    gen = std::mt19937(std::random_device{}()); 
    // 62 valid chars for crypt 
    ascii_char = std::uniform_int_distribution<int>(0, 61);
}

void UserManager::generateSalt(){
    salt = "aa";
    salt[0] = salt_chars[ascii_char(gen)];
    salt[1] = salt_chars[ascii_char(gen)];
}

void UserManager::encryptPassword(){
    char* encrypted = crypt(password.c_str(), salt.c_str());
    if (!encrypted){
        std::cout << "Something went wrong while encrypting" << std::endl;
    }
    else{
        password = encrypted;
    }
}

void UserManager::addUser(){
    generateSalt();
    encryptPassword();
    if (database.userExists(username)){
        std::cout << "Username " << username << " already exists!" << std::endl;
        return;
    }
    database.writeUser(username, password, salt);
}

void UserManager::loginUser(){
    std::pair<std::string, std::string > user_info = database.readUser(username);
    std::string stored_password = user_info.first;
    salt = user_info.second;
    if (stored_password != ""){
       encryptPassword();
       if (password == stored_password){
           std::cout << "You have discovered the greatest secret:" << std::endl;
           std::cout << "[REDACTED]" << std::endl;
       }
       else{
           std::cout << "Incorrect user/password!!!" << std::endl;
       }
    }
    else{
        std::cout << "Incorrect user/password!!!" << std::endl;
    }
}
