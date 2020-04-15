#include <fstream>
#include <iostream>
#include <crypt.h>
#include "backend.h"

const std::string UserManager::salt_chars = "abcdefghijklmnopqrstvwxyz./ABCDEFGHIJKLMNOPQRSTVWXYZ0123456789";
UserManager::UserManager(){
    database = "database.txt";
    action = "";
    initRNG();
    initDB();
}

UserManager::UserManager(const std::string& existing_db){
    database = existing_db;
    action = "";
    initRNG();
    initDB();
}

UserManager::UserManager(const UserManager& um){
    std::cout << "Using copy constructor" << std::endl;
    database = um.database;
    action = um.action;
    initRNG();
    initDB();
}

void UserManager::initDB(){
    std::ifstream db_connection(database);
    if (db_connection.is_open()) {
        // database already exists, do nothing
        db_connection.close();
    }
    else{
        db_connection.close();
        std::ofstream db_connection(database);
        db_connection << "Database" << std::endl;
        db_connection.close();
    }
}

void UserManager::getUserInformation(){
    action = "";
    while (action != "r" and action != "l"){
        std::cout << "Want to login or register a new user?[l/r]" << std::endl;
        std::cin >> action;
    }
    std::cout << "Enter username:" << std::endl;   
    std::cin >> username;
    std::cout << "Enter password:" << std::endl;   
    std::cin >> password;
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
    if (userExists()){
        std::cout << "Username " << username << " already exists!" << std::endl;
        return;
    }
    writeUser();
}

void UserManager::loginUser(){
    std::ifstream db_connection(database); 
    std::string line, stored_password = "";
    size_t pos=0;
    if (!db_connection.is_open()) {
        std::cout << "Failed to open " << database << '\n';
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

void UserManager::writeUser(){
    std::ofstream db_connection(database, std::ios_base::app); 
    db_connection << "- " << username << ":" << std::endl;
    db_connection << "\tpassword: " << password << std::endl;
    db_connection << "\tsalt: " << salt << std::endl;
}

bool UserManager::userExists(){
    std::ifstream db_connection(database); 
    std::string line;
    if (!db_connection.is_open()) {
        std::cout << "Failed to open " << database << '\n';
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
