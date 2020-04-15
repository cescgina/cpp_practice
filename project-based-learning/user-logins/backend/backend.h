#include <random>
#include <string>

class UserManager{
    public:
        UserManager(const std::string& existing_db);
        UserManager();
        UserManager(const UserManager& um);
        void getUserInformation();
        void handleUser();
    private:
        std::string database;
        std::string username;
        std::string password;
        std::string action;
        std::string salt;
        static const std::string salt_chars;
        std::mt19937 gen;
        std::uniform_int_distribution<int> ascii_char;
        void addUser();
        void loginUser();
        void encryptPassword();
        void initRNG();
        void generateSalt();
        void writeUser();
        bool userExists();
        void initDB();
};
