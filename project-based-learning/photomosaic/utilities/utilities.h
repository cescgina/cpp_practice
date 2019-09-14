#include <map>
#include <list>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <Magick++.h>

typedef std::vector<std::vector<std::string>> files_array;
typedef std::vector<std::vector<std::vector<float>>> pixels_array;
typedef std::vector<std::pair<std::string, std::vector<float>>> vector_sources;
typedef std::map<std::vector<float>, vector_sources> sources_map;
typedef std::unordered_map<std::string, Magick::Image> image_map;

std::pair<int, int> calculate_resolutions(const int original_res, const int rows, const int cols);
void create_folder(const std::string& path);
std::list<std::string> get_list_photos(const std::string& path);
std::string get_filename(const std::string& path);
files_array match_sources_files(const pixels_array& pixels, sources_map& source_colors, const int image_fractions);
std::vector<float> round_averages(const std::vector<float> averages);
vector_sources find_similar_bucket(const sources_map& source_colors, const std::vector<float>& rounded_averages);
int encode_averages(const std::vector<float>& rounded_average);
std::vector<float> decode_averages(const int code);
std::vector<float> average_quarters(const std::vector<float>& averages);
float calculate_distance(const std::vector<float>& arr1, const std::vector<float>& arr2);
