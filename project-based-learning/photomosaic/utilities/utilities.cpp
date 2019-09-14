#include <list>
#include <cmath>
#include <string>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <experimental/filesystem>
#include "utilities.h"

std::pair<int, int> calculate_resolutions(const int original_res, const int rows, const int cols){
    int res_x = original_res, res_y = original_res;
    while (rows % res_y != 0){
        res_y--;
    }
    while (cols % res_x != 0){
        res_x--;
    }
    return std::pair<int, int>(res_x, res_y);
}

void create_folder(const std::string& path){
    std::experimental::filesystem::create_directory(path);
}

std::list<std::string> get_list_photos(const std::string& path){
    std::list<std::string> list_photos;
    for (auto & file: std::experimental::filesystem::directory_iterator(path)){
        list_photos.push_back(file.path());
    }
    return list_photos;
}

std::string get_filename(const std::string& path){
    const size_t pos = path.find_last_of("\\/");
    return path.substr(pos+1);
}

files_array match_sources_files(const pixels_array& pixels, sources_map& source_colors, const int image_fractions){
    size_t rows = pixels.size(), cols = pixels[0].size();
    files_array image_to_file(rows, std::vector<std::string>(cols));
    vector_sources similiar_bucket;
    std::vector<float> averages(3*image_fractions, 0), rounded_averages(3*image_fractions, 0);
    for (size_t i=0; i < rows; i++){
        for (size_t j=0; j < cols; j++){
            averages = pixels[i][j];
            rounded_averages = round_averages(averages);
            if (source_colors.find(rounded_averages) == source_colors.end()){
                similiar_bucket = find_similar_bucket(source_colors, rounded_averages);
            }
            else{
                similiar_bucket = source_colors[rounded_averages];
            }
            float dist = 10000.0;
            float local_dist = 0.0;
            std::string similar_file = "";
            for (vector_sources::iterator el=similiar_bucket.begin(); el != similiar_bucket.end(); el++){
                local_dist = calculate_distance(pixels[i][j], el->second);
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


std::vector<float> round_averages(const std::vector<float> averages){
    std::vector<float> rounded_averages(3, 0);
    for (int i=0; i<3; i++){
        rounded_averages[i] = ((float)((int)(averages[i] * 10))) / 10;
    }
    return rounded_averages;
}

vector_sources find_similar_bucket(const sources_map& source_colors, const std::vector<float>& rounded_averages){
    vector_sources similar_bucket;
    float local_dist = 0.0, dist=100000.0;
    for (sources_map::const_iterator el=source_colors.begin(); el != source_colors.end(); el++){
        local_dist = calculate_distance(el->first, rounded_averages);
        if (local_dist < dist){
            dist = local_dist;
            similar_bucket = el->second;
        }
    }
    return similar_bucket;
}

int encode_averages(const std::vector<float>& rounded_avg){
    // the encoding is based on the fact that be used buckets of resolution
    // 0.1, so we have 11 possibilities per position => 1331 possibilities
    return (int)(rounded_avg[2]*10)+11*(int)(10*rounded_avg[1])+121*(int)(10*rounded_avg[0]);
}

std::vector<float> decode_averages(const int code){
    auto div_result = std::div(code, 121);
    float d1 = (float)(div_result.quot/10.0);
    int k = div_result.rem;
    div_result = std::div(k, 11);
    float d2 = (float)(div_result.quot/10.0);
    float d3 = (float)(div_result.rem/10.0);
    std::vector<float> decoded = {d1, d2, d3};
    return decoded;
}

std::vector<float> average_quarters(const std::vector<float>& averages){
    std::vector<float> final_average(3, 0);
    size_t averages_size = averages.size(), n_bins = averages_size/3;
    for (size_t k=0; k<averages.size(); k++){
        final_average[k % 3] += averages[k];
    }
    for (int k=0; k<3; k++){
        final_average[k] /= n_bins;
    }
    return final_average;
}

float calculate_distance(const std::vector<float>& arr1, const std::vector<float>& arr2){
    float dist = 0.0, diff;
    for (size_t i=0; i<arr1.size(); i++){
        diff = arr1[1]-arr2[i];
        dist += diff*diff;
    }
    return std::sqrt(dist);
}
