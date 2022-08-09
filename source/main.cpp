#include <iostream>
#include <string>
#include <curses.h>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;
using file_str_list = std::vector<std::string>; 

inline void usage() {
	std::cout <<
	"Usage: to_do_tool [path_to_directory_with_project]" <<
	std::endl;
}

bool check_file(std::string file_name)
{
	const std::vector<std::string> file_extension = {".cpp", ".hpp", ".c", ".h"};
	for(const auto& ext : file_extension) {
		if(file_name.find(ext) != std::string::npos) {
			return true;
		}
	}
	return false;
}

uint32_t find_files(fs::path& dir, file_str_list& file_list) {
	uint32_t loaded_files = 0; 
	for(const auto &file : fs::recursive_directory_iterator(dir)) {
		if(file.is_regular_file() == true) {
			auto cur_file = file.path();			
			if(check_file(cur_file.filename().string()) == true) {
				file_list.push_back(cur_file.string());
				loaded_files++;
			}
		}
	}
	return loaded_files;
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		usage();
		return EXIT_FAILURE;
	}

	fs::path path_to_director;

	if(std::string(".").compare(argv[1]) != 0) {
		path_to_director = fs::current_path();
	}
	else {
		path_to_director = fs::path(argv[1]); 
	}

	if(fs::exists(path_to_director) == false)
	{
		std::cerr << "Directory doesn't exists" << std::endl;
		return EXIT_FAILURE;
	}

	file_str_list file_list;
	if(find_files(path_to_director, file_list) == 0) {
		std::cout << "Cannot find files" << std::endl;
	}
	for(auto x : file_list) {
		std::cout << x << std::endl;
	}

	

	//initscr();
	//cbreak();
	//noecho();
	//endwin();
	return 0;
}
