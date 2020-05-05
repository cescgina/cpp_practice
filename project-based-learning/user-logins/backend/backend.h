#include <random>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <sqlite3.h>

class Interface{
    public:
        Interface(const std::string& path_db, bool use_db);
        Interface(const Interface& interface);
        ~Interface();
        Interface operator=(const Interface& interface);
        std::pair<std::string, std::string> readUser(const std::string& username);
        void writeUser(const std::string& username, const std::string& password, const std::string& salt);
        bool userExists(const std::string& username);
        void initTable();
        void initDB();
    private:
        std::string db_path;
        bool db_use;
        sqlite3* db_sql;
};

class UserManager{
    public:
        UserManager(const std::string& path_db, bool use_db);
        UserManager(const UserManager& um);
        void getUserInformation();
        void handleUser();
    private:
        Interface database;
        std::string username;
        std::string password;
        std::string action;
        std::string salt;
        static const std::string salt_chars;
        std::mt19937 gen;
        std::uniform_int_distribution<int> ascii_char;
        termios oldt;
        termios newt;
        void addUser();
        void loginUser();
        void encryptPassword();
        void initRNG();
        void generateSalt();
        void writeUser();
        bool userExists();
};
