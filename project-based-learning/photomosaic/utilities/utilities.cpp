#include <list>
#include <cmath>
#include <string>
#include <utility>
#include <experimental/filesystem>
#include <utilities.h>

std::pair<int, int> calculate_resolutions(int original_res, int rows, int cols){
    int res_x = original_res, res_y = original_res;
    while (rows % res_y != 0){
        res_y--;
    }
    while (cols % res_x != 0){
        res_x--;
    }
    return std::pair<int, int>(res_x, res_y);
}

void create_folder(std::string& path){
    std::experimental::filesystem::create_directory(path);
}

std::list<std::string> get_list_photos(std::string& path){
    std::list<std::string> list_photos;
    for (auto & file: std::experimental::filesystem::directory_iterator(path)){
        list_photos.push_back(file.path());
    }
    return list_photos;
}

std::string get_filename(std::string path){
    const size_t pos = path.find_last_of("\\/");
    return path.substr(pos+1);
}

files_array match_sources_files(pixels_array& pixels, sources_map& source_colors){
    size_t rows = pixels.size(), cols = pixels[0].size();
    files_array image_to_file(rows, std::vector<std::string>(cols, ""));
    for (size_t i=0; i < rows; i++){
        for (size_t j=0; j < cols; j++){
            float r=pixels[i][j][0], g=pixels[i][j][1], b=pixels[i][j][2];
            float dist = 10000.0;
            float local_dist = 0.0, local_r, local_g, local_b;
            std::string similar_file = "";
            for (sources_map::iterator el=source_colors.begin(); el!=source_colors.end(); el++){
                local_r = r-el.second[0];
                local_g = g-el.second[1];
                local_b = b-el.second[2];
                local_dist = std::sqrt(local_r*local_r+local_g*local_g+local_b*local_b);
                if (local_dist < dist){
                    dist = local_dist;
                    similar_file = el.first;
                }
            }
            image_to_file[i][j] = similar_file;
        }
    }
    return image_to_file;
}
