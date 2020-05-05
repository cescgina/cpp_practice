#include <fstream>
#include <iostream>
#include <stdexcept>
#include <crypt.h>
#include "backend.h"

void Interface::initTable(){
    char *zErrMsg = 0;
    int rc, exists;
    std::string command = "SELECT count(type) from sqlite_master WHERE type='table' and name='users';";
    sqlite3_stmt *ppStmt = nullptr;
    //check if db had previoulsy the users table
    rc = sqlite3_prepare_v2(db_sql, command.c_str(), -1, &ppStmt, nullptr);
    if (rc != SQLITE_OK){
        throw std::string(sqlite3_errmsg(db_sql));
    }
    rc = sqlite3_step(ppStmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE){
        std::string errmsg(sqlite3_errmsg(db_sql));
        sqlite3_finalize(ppStmt);
        throw errmsg;
    }
    exists = sqlite3_column_int(ppStmt, 0);
    rc = sqlite3_finalize(ppStmt);
    if (!exists){
        command = "CREATE TABLE users(USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, SALT TEXT NOT NULL)";
        rc = sqlite3_exec(db_sql, command.c_str(), nullptr, nullptr, &zErrMsg);
    }
}

void Interface::initDB(){
    if (db_use){
        int rc = sqlite3_open(db_path.c_str(), &db_sql);
        if (rc){
            sqlite3_close(db_sql);
            throw std::invalid_argument("Can't open database "+ db_path + " error " + sqlite3_errmsg(db_sql));
        }
        // check if db already existed, else create table
        initTable();
    }
    else{
        std::ifstream db_text(db_path);
        if (db_text.is_open()) {
            // database already exists, do nothing
            db_text.close();
        }
        else{
            db_text.close();
            std::ofstream db_text(db_path);
            db_text << "Database" << std::endl;
            db_text.close();
        }
    }

}
Interface::Interface(const std::string& path_db, bool use_db){
    db_path = path_db;
    db_use = use_db;
    initDB();
}

Interface::Interface(const Interface& interface) {
    db_path = interface.db_path;
    db_use = interface.db_use;
    initDB();
}

// implement copy assignment operator to satisfy rule of three
Interface Interface::operator=(const Interface& interface){
    db_path = interface.db_path;
    db_use = interface.db_use;
    initDB();
    return *this;
}

Interface::~Interface(){
    sqlite3_close(db_sql);
}

std::pair<std::string, std::string> Interface::readUser(const std::string& username){
    std::string stored_password = "", salt;
    if (db_use){
        int rc;
        sqlite3_stmt *ppStmt = nullptr;
        std::string command = "SELECT PASSWORD, SALT FROM users WHERE USERNAME=?";
        rc = sqlite3_prepare_v2(db_sql, command.c_str(), -1, &ppStmt, nullptr);
        if (rc != SQLITE_OK){
            throw std::string(sqlite3_errmsg(db_sql));
        }
        rc = sqlite3_bind_text(ppStmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK){
            std::string errmsg(sqlite3_errmsg(db_sql));
            sqlite3_finalize(ppStmt);
            throw errmsg;
        }
        rc = sqlite3_step(ppStmt);
        if (rc != SQLITE_ROW && rc != SQLITE_DONE){
            std::string errmsg(sqlite3_errmsg(db_sql));
            sqlite3_finalize(ppStmt);
            throw errmsg;
        }
        if (rc == SQLITE_DONE){
            // user not found
            sqlite3_finalize(ppStmt);
            return std::make_pair(stored_password, salt);
        }
        stored_password = std::string(reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 0)));
        salt = std::string(reinterpret_cast<const char*>(sqlite3_column_text(ppStmt, 1)));
        sqlite3_finalize(ppStmt);
    }
    else{
        std::ifstream db_text(db_path); 
        std::string line;
        size_t pos=0;
        if (!db_text.is_open()) {
            std::cout << "Failed to open " << db_path << '\n';
        } 
        else {
            while(std::getline(db_text, line)){
                if (line[0] == '-' and line.substr(2, line.size()-3) == username){
                    // read password
                    std::getline(db_text, line);
                    pos = line.find(":");
                    stored_password = line.substr(pos+2);
                    //read salt
                    std::getline(db_text, line);
                    pos = line.find(":");
                    salt = line.substr(pos+2);
                    break;
                }
            }    
        }
        db_text.close();
    }
    return std::make_pair(stored_password, salt);
}

void Interface::writeUser(const std::string& username, const std::string& password, const std::string& salt){
    if (db_use){
        int rc;
        sqlite3_stmt *ppStmt = nullptr;
        std::string command = "INSERT INTO users (USERNAME, PASSWORD, SALT) VALUES (?, ?, ?)";
        rc = sqlite3_prepare_v2(db_sql, command.c_str(), -1, &ppStmt, nullptr);
        if (rc != SQLITE_OK){
            throw std::string(sqlite3_errmsg(db_sql));
        }
        rc = sqlite3_bind_text(ppStmt, 1, username.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_bind_text(ppStmt, 2, password.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_bind_text(ppStmt, 3, salt.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK){
            std::string errmsg(sqlite3_errmsg(db_sql));
            sqlite3_finalize(ppStmt);
            throw errmsg;
        }
        rc = sqlite3_step(ppStmt);
        if (rc != SQLITE_ROW && rc != SQLITE_DONE){
            std::string errmsg(sqlite3_errmsg(db_sql));
            sqlite3_finalize(ppStmt);
            throw errmsg;
        }
        sqlite3_finalize(ppStmt);
    }
    else{
        std::ofstream db_text(db_path, std::ios_base::app); 
        db_text << "- " << username << ":" << std::endl;
        db_text << "\tpassword: " << password << std::endl;
        db_text << "\tsalt: " << salt << std::endl;
        db_text.close();
    }
}

bool Interface::userExists(const std::string& username){
    if (db_use){
        int rc;
        sqlite3_stmt *ppStmt = nullptr;
        std::string command = "SELECT USERNAME FROM users WHERE USERNAME=?";
        rc = sqlite3_prepare_v2(db_sql, command.c_str(), -1, &ppStmt, nullptr);
        if (rc != SQLITE_OK){
            throw std::string(sqlite3_errmsg(db_sql));
        }
        rc = sqlite3_bind_text(ppStmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK){
            std::string errmsg(sqlite3_errmsg(db_sql));
            sqlite3_finalize(ppStmt);
            throw errmsg;
        }
        rc = sqlite3_step(ppStmt);
        if (rc != SQLITE_ROW && rc != SQLITE_DONE){
            std::string errmsg(sqlite3_errmsg(db_sql));
            sqlite3_finalize(ppStmt);
            throw errmsg;
        }
        sqlite3_finalize(ppStmt);
        return rc != SQLITE_DONE;
    }
    else{
        std::ifstream db_text(db_path); 
        std::string line;
        if (!db_text.is_open()) {
            std::cout << "Failed to open " << db_path << '\n';
        } 
        else {
            while(std::getline(db_text, line)){
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
    database = Interface(path_db, use_db);
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
