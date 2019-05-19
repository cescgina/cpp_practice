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
        int x;
        int y;
        // is radioactive_mutant_vampire_bunny
        bool rmvb; 
        Bunny(std::string name_in, std::string color_in, int x_coor, int y_coor){
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
            x = x_coor;
            y = y_coor;
        }
        void print_bunny();
        void die();
        bool check_death();
        bool check_breed();
        void turn_vampire();
        std::string gridCharacter();

};
void Bunny::print_bunny(){ 
    std::cout << "======================================= " << std::endl;
    std::cout << "Printing info for bunny named " << name << std::endl;
    std::cout << "Age is " << age << ", color is " << color  << ", sex is " << sex << " and is located at position " << x << "," << y << std::endl;
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
    return ((!rmvb) && (sex == "female") && (age > 2));
}

void Bunny::turn_vampire(){
    std::cout << "Bunny " << name << " at position " << x << "," << y << " turned into a radioactive mutant vampire bunny" << std::endl;
    rmvb = true;
}

std::string Bunny::gridCharacter(){
    if (rmvb) return "X";
    if (sex == "male"){
        if (age > 2) return "M";    
        else return "m";
    }
    else{
        if (age > 2) return "F";
        else return "f";
    }
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

std::pair<int, int> findEmptyPosition(int x, int y, std::vector<std::vector<Bunny*>> & grid_el){
    std::pair<int, int> coords;
    int x_coord, y_coord;
    std::vector<int> directions(8);
    std::iota(directions.begin(), directions.end(), 0);
    std::random_shuffle(directions.begin(), directions.end());
    for (std::vector<int>::iterator it = directions.begin(); it != directions.end(); it++){
        switch(*it){
            case 0:
                // up and left
                x_coord = x-1;
                y_coord = y-1;
                if (x_coord >= 0 && y_coord >= 0 && !grid_el[x_coord][y_coord]){
                    coords = std::make_pair(x_coord, y_coord);
                    return coords;
                }
            case 1:
                // left 
                x_coord = x;
                y_coord = y-1;
                if (y_coord >= 0 && !grid_el[x_coord][y_coord]){
                    coords = std::make_pair(x_coord, y_coord);
                    return coords;
                }
            case 2:
                // down and left
                x_coord = x+1;
                y_coord = y-1;
                if (x_coord < 80 && y_coord >= 0 && !grid_el[x_coord][y_coord]){
                    coords = std::make_pair(x_coord, y_coord);
                    return coords;
                }
            case 3:
                // up
                x_coord = x-1;
                y_coord = y;
                if (x_coord >= 0 && !grid_el[x_coord][y_coord]){
                    coords = std::make_pair(x_coord, y_coord);
                    return coords;
                }
            case 4:
                // down
                x_coord = x+1;
                y_coord = y;
                if (x_coord < 80 && !grid_el[x_coord][y_coord]){
                    coords = std::make_pair(x_coord, y_coord);
                    return coords;
                }
            case 5:
                // up and right
                x_coord = x-1;
                y_coord = y+1;
                if (x_coord >= 0 && y_coord < 80 && !grid_el[x_coord][y_coord]){
                    coords = std::make_pair(x_coord, y_coord);
                    return coords;
                }
            case 6:
                // right
                x_coord = x;
                y_coord = y+1;
                if (y_coord < 80 && !grid_el[x_coord][y_coord]){
                    coords = std::make_pair(x_coord, y_coord);
                    return coords;
                }
            case 7:
                // down and right
                x_coord = x+1;
                y_coord = y+1;
                if (x_coord < 80 && y_coord < 80 && !grid_el[x_coord][y_coord]){
                    coords = std::make_pair(x_coord, y_coord);
                    return coords;
                }
        }
    }
    coords = std::make_pair(x, y);
    return coords;
}

std::pair<int, int> findNeighbourBunny(int x, int y, std::vector<std::vector<Bunny*>> & grid_el){
    std::pair<int, int> coords;
    int x_coord, y_coord;
    std::vector<int> directions(8);
    std::iota(directions.begin(), directions.end(), 0);
    std::random_shuffle(directions.begin(), directions.end());
    for (std::vector<int>::iterator it = directions.begin(); it != directions.end(); it++){
        switch(*it){
            case 0:
                // up and left
                x_coord = x-1;
                y_coord = y-1;
                if (x_coord >= 0 && y_coord >= 0 && grid_el[x_coord][y_coord]){
                    if (!grid_el[x_coord][y_coord]->rmvb){
                        coords = std::make_pair(x_coord, y_coord);
                        return coords;
                    }
                }
            case 1:
                // left 
                x_coord = x;
                y_coord = y-1;
                if (y_coord >= 0 && grid_el[x_coord][y_coord]){
                    if (!grid_el[x_coord][y_coord]->rmvb){
                        coords = std::make_pair(x_coord, y_coord);
                        return coords;
                    }
                }
            case 2:
                // down and left
                x_coord = x+1;
                y_coord = y-1;
                if (x_coord < 80 && y_coord >= 0 && grid_el[x_coord][y_coord]){
                    if (!grid_el[x_coord][y_coord]->rmvb){
                        coords = std::make_pair(x_coord, y_coord);
                        return coords;
                    }
                }
            case 3:
                // up
                x_coord = x-1;
                y_coord = y;
                if (x_coord >= 0 && grid_el[x_coord][y_coord]){
                    if (!grid_el[x_coord][y_coord]->rmvb){
                        coords = std::make_pair(x_coord, y_coord);
                        return coords;
                    }
                }
            case 4:
                // down
                x_coord = x+1;
                y_coord = y;
                if (x_coord < 80 && grid_el[x_coord][y_coord]){
                    if (!grid_el[x_coord][y_coord]->rmvb){
                        coords = std::make_pair(x_coord, y_coord);
                        return coords;
                    }
                }
            case 5:
                // up and right
                x_coord = x-1;
                y_coord = y+1;
                if (x_coord >= 0 && y_coord < 80 && grid_el[x_coord][y_coord]){
                    if (!grid_el[x_coord][y_coord]->rmvb){
                        coords = std::make_pair(x_coord, y_coord);
                        return coords;
                    }
                }
            case 6:
                // right
                x_coord = x;
                y_coord = y+1;
                if (y_coord < 80 && grid_el[x_coord][y_coord]){
                    if (!grid_el[x_coord][y_coord]->rmvb){
                        coords = std::make_pair(x_coord, y_coord);
                        return coords;
                    }
                }
            case 7:
                // down and right
                x_coord = x+1;
                y_coord = y+1;
                if (x_coord < 80 && y_coord < 80 && grid_el[x_coord][y_coord]){
                    if (!grid_el[x_coord][y_coord]->rmvb){
                        coords = std::make_pair(x_coord, y_coord);
                        return coords;
                    }
                }
        }
    }
    coords = std::make_pair(x, y);
    return coords;
}

void print_grid(std::vector<std::vector<Bunny*>> & grid_el){
    std::cout << "  ";
    for (int k=0; k < 80; k++){
        std::cout << k << " ";
    }
    std::cout << std::endl;
    for (int i=0; i < 80; i++){
        std::cout << i << " ";
        for (int j=0; j < 80; j++){
            if (grid_el[i][j]){
                std::cout << grid_el[i][j]->gridCharacter() << " ";
            }
            else{
                std::cout << "#" << " ";
            }
        }
        std::cout << std::endl;
    }    
}

int main(int argc, char** argv){
    std::vector<std::string> NAMES = {"NAME1", "NAME2", "NAME3", "NAME4", "NAME5", "NAME6", "NAME7", "NAME8", "NAME9", "NAME10", "NAME11", "NAME12", "NAME13", "NAME14", "NAME15", "NAME16", "NAME17", "NAME18", "NAME19", "NAME20", "NAME21", "NAME22", "NAME23", "NAME24", "NAME25", "NAME26", "NAME27", "NAME28", "NAME29", "NAME30"};
    std::vector<std::string> COLORS = {"white", "black", "brown", "spotted"};
    std::vector<std::vector<Bunny*>> grid(80, std::vector<Bunny*>(80));
    std::list<Bunny> bunnies;
    std::vector<std::vector<Bunny*>>& grid_ref=grid;
    bool adults, death, breed; 
    int turns = 1500, i=0, vampires=0, born_rmvb=0, x_coord, y_coord;
    std::pair<int, int> coords;
    std::streambuf* coutbuf = std::cout.rdbuf(); 
    std::ofstream out("logfile.txt");
    std::cout.rdbuf(out.rdbuf());
    std::cout << "STARTING SIMULATION" << std::endl;
    for (int i=0; i<5; i++){
        while (true){
            x_coord = std::rand() % 80;
            y_coord = std::rand() % 80;
            if (!grid[x_coord][y_coord]) break;
        }
        bunnies.push_front(Bunny(NAMES[std::rand() % NAMES.size()], COLORS[std::rand() % COLORS.size()], x_coord, y_coord));
        grid[x_coord][y_coord] = &bunnies.front();
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
                grid[it->x][it->y] = NULL;
                it = bunnies.erase(it);
                continue;
            }
            // check if there are adults for breeding
            else if (it->age >= 2 && !it->rmvb && it->sex == "male") adults=true;
            coords = findEmptyPosition(it->x, it->y, grid_ref);
            if (coords.first != it->x || coords.second != it->y){
                // move bunny
                std::cout << "Moving ";
                if (it->rmvb) std::cout << "Radioactive mutant vampire ";
                std::cout << "bunny " << it->name << " from " << it->x << "," << it->y << " to " << coords.first << "," << coords.second << std::endl; 
                std::swap(grid[it->x][it->y], grid[coords.first][coords.second]);
                it->x = coords.first;
                it->y = coords.second;
            }
            it++;
        }
        if (adults){
            for (std::list<Bunny>::iterator it=bunnies.begin(); it != bunnies.end(); it++){
                // breeding
                breed = it->check_breed();
                if (breed) {
                    coords = findEmptyPosition(it->x, it->y, grid_ref);
                    if (coords.first != it->x || coords.second != it->y){
                        // new bunny is born
                        bunnies.push_front(Bunny(NAMES[std::rand() % 5], it->color, coords.first, coords.second));
                        grid[coords.first][coords.second] = &bunnies.front();
                        if (bunnies.front().rmvb) born_rmvb++;
                    }
                }
            }
        }
        if (vampires > 0){
            int turned_vamp=0;
            for (std::list<Bunny>::iterator it=bunnies.begin(); it != bunnies.end(); it++){
                // vampire breeding
                if (it->rmvb && (it->age > 0)) {
                    coords = findNeighbourBunny(it->x, it->y, grid_ref);
                    if (coords.first != it->x || coords.second != it->y){
                        grid[coords.first][coords.second]->turn_vampire();
                        turned_vamp++;
                    }
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
        std::cout << "Update of the bunnies at the end of turn " << i << "! Total population " << bunnies.size() << ", number of vampires " << vampires << std::endl;
        for (std::list<Bunny>::iterator it=bunnies.begin(); it != bunnies.end(); it++){
            it->print_bunny();
        }
        print_grid(grid_ref);
        if (i >= turns || bunnies.empty()) break;
        i++;
    }
    std::cout.rdbuf(coutbuf);
}
