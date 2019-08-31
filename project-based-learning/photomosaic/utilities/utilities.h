#include <list>
#include <vector>
#include <string>
#include <unordered_map>

typedef std::vector<std::vector<std::string>> files_array;
typedef std::vector<std::vector<std::vector<float>>> pixels_array;
typedef std::unordered_map<std::string, std::vector<float>> sources_map;

std::pair<int, int> calculate_resolutions(int original_res, int rows, int cols);
void create_folder(std::string& path);
std::list<std::string> get_list_photos(std::string& path);
std::string get_filename(std::string path);
files_array match_sources_files(pixels_array& pixels, sources_map& source_colors);
