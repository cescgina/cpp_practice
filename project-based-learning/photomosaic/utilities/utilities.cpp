#include <list>
#include <cmath>
#include <string>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <experimental/filesystem>
#include "utilities.h"

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
    files_array image_to_file(rows, std::vector<std::string>(cols));
    vector_sources similiar_bucket;
    for (size_t i=0; i < rows; i++){
        for (size_t j=0; j < cols; j++){
            float r=pixels[i][j][0], g=pixels[i][j][1], b=pixels[i][j][2];
            std::vector<float> rounded_averages = round_averages(pixels[i][j]);
            int key = encode_averages(rounded_averages);
            if (source_colors.find(key) == source_colors.end()){
                similiar_bucket = find_similar_bucket(source_colors, key);
            }
            else{
                similiar_bucket = source_colors[key];
            }
            float dist = 10000.0;
            float local_dist = 0.0, local_r, local_g, local_b;
            std::string similar_file = "";
            for (vector_sources::iterator el=similiar_bucket.begin(); el != similiar_bucket.end(); el++){
                local_r = r-el->second[0];
                local_g = g-el->second[1];
                local_b = b-el->second[2];
                local_dist = std::sqrt(local_r*local_r+local_g*local_g+local_b*local_b);
                if (local_dist < dist){
                    dist = local_dist;
                    similar_file = el->first;
                }
            }
            image_to_file[i][j] = similar_file;
        }
    }
    return image_to_file;
}


std::vector<float> round_averages(std::vector<float> averages){
    std::vector<float> rounded_averages(3, 0);
    for (int i=0; i<3; i++){
        rounded_averages[i] = ((float)((int)(averages[i] * 10))) / 10;
    }
    return rounded_averages;
}

vector_sources find_similar_bucket(sources_map& source_colors, const int key){
    vector_sources similar_bucket;
    std::vector<float> decoded = decode_averages(key);
    float r = decoded[0], g = decoded[1], b = decoded[2], dist=1000.0;
    float local_dist = 0.0, local_r, local_g, local_b;
    std::vector<float> local_decoded = {0.0, 0.0, 0.0};
    for (int el=0; el<1331; el++){
        if (source_colors.find(el) == source_colors.end()){
            continue;
        }
        local_decoded = decode_averages(el);
        local_r = r-local_decoded[0];
        local_g = g-local_decoded[1];
        local_b = b-local_decoded[2];
        local_dist = std::sqrt(local_r*local_r+local_g*local_g+local_b*local_b);
        if (local_dist < dist){
            dist = local_dist;
            similar_bucket = source_colors[el];
        }
        
    }
    return similar_bucket;
}

int encode_averages(std::vector<float>& rounded_avg){
    // the encoding is based on the fact that be used buckets of resolution
    // 0.1, so we have 11 possibilities per position => 1331 possibilities
    return (int)(rounded_avg[2]*10)+11*(int)(10*rounded_avg[1])+121*(int)(10*rounded_avg[0]);
}

std::vector<float> decode_averages(int code){
    auto div_result = std::div(code, 121);
    float d1 = (float)(div_result.quot/10.0);
    int k = div_result.rem;
    div_result = std::div(k, 11);
    float d2 = (float)(div_result.quot/10.0);
    float d3 = (float)(div_result.rem/10.0);
    std::vector<float> decoded = {d1, d2, d3};
    return decoded;
}
