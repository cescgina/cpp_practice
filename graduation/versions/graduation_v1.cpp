#include <list>
#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <streambuf>


class Bunny{
    public:
        std::string sex;
        std::string color;
        std::string name;
        int age;
        // is radioactive_mutant_vampire_bunny
        bool rmvb; 
        Bunny(std::string name_in, std::string color_in){
            age = 0;
            color = color_in;
            name = name_in;
            int r = rand() % 2, r2 = rand() % 100;
            if (r) sex = "male";
            else sex = "female";
            rmvb = false;
            if (r2 < 2) rmvb = true;
            if (rmvb) std::cout << "Radioactive Muntant Vampire ";
            std::cout << "Bunny named " << name << " born!" << std::endl;
        }
        void print_bunny();
        void die();
        bool check_death();
        bool check_breed();
        void turn_vampire();

};
void Bunny::print_bunny(){ 
    std::cout << "======================================= " << std::endl;
    std::cout << "Printing info for bunny named " << name << std::endl;
    std::cout << "Age is " << age << ", color is " << color  << " and sex is " << sex << std::endl;
    if (rmvb) std::cout << "Is a radioactive mutant vampire bunny!!" << std::endl;
}
void Bunny::die(){
    if (rmvb) std::cout << "Radioactive mutant vampire ";
    std::cout << "Bunny " << name << " died!" << std::endl;
}
bool Bunny::check_death(){
    if ((rmvb && age > 50) || (!rmvb && age > 10)){
        die();
        return true;
    }
    return false;
}
bool Bunny::check_breed(){
    return ((sex == "female") && (age > 2));
}

void Bunny::turn_vampire(){
    std::cout << "Bunny " << name << " turned into a radioactive mutant vampire bunny" << std::endl;
    rmvb = true;
}

int randomize(const int &i) {
    return rand() % i;
}

bool age_sort(const Bunny& first, const Bunny& second){
    return first.age < second.age;
}

void bunny_massacre(std::list<Bunny>& bunny_list){
    std::cout << "I'm inevitable" << std::endl;
    int n = bunny_list.size(), i = 0, offset;
    std::list<Bunny>::iterator it_b;
    std::vector<int> sample(n/2);
    // generate numbers 0 .. n-1
    std::iota(sample.begin(), sample.end(), 0);
    // shuffle elements
    std::random_shuffle(sample.begin(), sample.end(), randomize);
    // grab the first five elements after shuffling
    std::vector<int> chosen(sample.begin(), sample.begin() + n/2);
    std::sort(chosen.begin(), chosen.end());
    for (std::vector<int>::iterator it=chosen.begin(); it != chosen.end(); it++){
        offset = *it - i;
        it_b = bunny_list.begin();
        std::advance(it_b, offset);
        bunny_list.erase(it_b);
        i++;
    }
}

int main(int argc, char** argv){
    std::vector<std::string> NAMES = {"NAME1", "NAME2", "NAME3", "NAME4", "NAME5", "NAME6", "NAME7", "NAME8", "NAME9", "NAME10", "NAME11", "NAME12", "NAME13", "NAME14", "NAME15", "NAME16", "NAME17", "NAME18", "NAME19", "NAME20", "NAME21", "NAME22", "NAME23", "NAME24", "NAME25", "NAME26", "NAME27", "NAME28", "NAME29", "NAME30"};
    std::vector<std::string> COLORS = {"white", "black", "brown", "spotted"};
    std::list<Bunny> bunnies;
    bool adults, death, breed; 
    int turns = 1500, i=0, vampires=0, born_rmvb=0;
    std::streambuf* coutbuf = std::cout.rdbuf(); 
    std::ofstream out("logfile.txt");
    std::cout.rdbuf(out.rdbuf());
    std::cout << "STARTING SIMULATION" << std::endl;
    for (int i=0; i<5; i++){
        bunnies.push_back(Bunny(NAMES[std::rand() % NAMES.size()], COLORS[std::rand() % COLORS.size()]));
    }

    for (std::list<Bunny>::iterator it=bunnies.begin(); it != bunnies.end(); it++){
        it->print_bunny();
        if (it->rmvb) vampires++;
    }
    while (true){
        std::cout << "STARTING TURN " << i << std::endl;
        std::list<Bunny>::iterator it=bunnies.begin();
        born_rmvb = 0;
        adults = false;
        while (it != bunnies.end()){
            it->age++;
            // handle death of old bunnies
            death = it->check_death();
            if (death) {
                //update number of vampires in case of death
                if (it->rmvb) vampires--;
                it = bunnies.erase(it);
                continue;
            }
            // check if there are adults for breeding
            else if (it->age >= 2 && !it->rmvb) adults=true;
            it++;
        }
        if (adults){
            for (std::list<Bunny>::iterator it=bunnies.begin(); it != bunnies.end(); it++){
                // breeding
                breed = it->check_breed();
                if (breed) {
                    Bunny newborn = Bunny(NAMES[std::rand() % 5], it->color);
                    bunnies.push_back(newborn);
                    if (newborn.rmvb) born_rmvb++;
                }
            }
        }
        if (vampires > 0){
            int turned_vamp=0;
            for (std::list<Bunny>::iterator it=bunnies.begin(); it != bunnies.end(); it++){
                // vampire breeding
                if (turned_vamp == vampires) break;
                if (!it->rmvb) {
                    it->turn_vampire();
                    turned_vamp++;
                }
            }
            vampires += turned_vamp;
        }
        vampires += born_rmvb;
        if (bunnies.size() > 1000){
            std::list<Bunny>& bunnies_ref=bunnies;
            // Thanos time!!
            bunny_massacre(bunnies_ref);
            vampires = 0;
            for (std::list<Bunny>::iterator it=bunnies.begin(); it != bunnies.end(); it++){
                if (it->rmvb) vampires++;
            }
        }
        bunnies.sort(age_sort);
        std::cout << "Update of the bunnies at the end of turn " << i << "! Total population " << bunnies.size() << ", number of vampires " << vampires << std::endl;
        for (std::list<Bunny>::iterator it=bunnies.begin(); it != bunnies.end(); it++){
            it->print_bunny();
        }
        if (i >= turns || bunnies.empty()) break;
        i++;
    }
    std::cout.rdbuf(coutbuf);
}
