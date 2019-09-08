#include <list>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <Magick++.h>

typedef std::vector<std::vector<std::string>> files_array;
typedef std::vector<std::vector<std::vector<float>>> pixels_array;
typedef std::vector<std::pair<std::string, std::vector<float>>> vector_sources;
typedef std::unordered_map<int, vector_sources> sources_map;
typedef std::unordered_map<std::string, Magick::Image> image_map;

std::pair<int, int> calculate_resolutions(int original_res, int rows, int cols);
void create_folder(std::string& path);
std::list<std::string> get_list_photos(std::string& path);
std::string get_filename(std::string path);
files_array match_sources_files(pixels_array& pixels, sources_map& source_colors);
std::vector<float> round_averages(std::vector<float> averages);
vector_sources find_similar_bucket(sources_map& source_colors, int key);
int encode_averages(std::vector<float>& rounded_average);
std::vector<float> decode_averages(int code);
std::vector<float> average_quarters(std::vector<float>& averages);
float calculate_distance(std::vector<float>& arr1, std::vector<float>& arr2);
