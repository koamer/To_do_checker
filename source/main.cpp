#include <iostream>
#include <memory>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <thread>

#include <curses.h>

namespace fs = std::filesystem;
using file_str_list = std::vector<std::string>;

inline void usage()
{
	std::cout << "Usage: to_do_tool [path_to_directory_with_project]" << std::endl;
}

// void split_and_run(file_str_list &file_list)
// {
// }
bool check_file(std::string file_name)
{
	const std::vector<std::string> file_extension = {".cpp", ".hpp", ".c", ".h", ".py", ".sh"};
	for (const auto &ext : file_extension)
	{
		if (file_name.find(ext) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

uint32_t find_files(fs::path &dir, file_str_list &file_list)
{
	uint32_t loaded_files = 0;
	for (const auto &file : fs::recursive_directory_iterator(dir))
	{
		if (file.is_regular_file() == true)
		{
			auto cur_file = file.path();
			if (check_file(cur_file.filename().string()) == true)
			{
				file_list.push_back(cur_file.string());
				loaded_files++;
			}
		}
	}
	return loaded_files;
}

std::string find_todos(file_str_list &file_list)
{
	// std::string
	std::map<std::string, uintmax_t> file_sizes;
	for (auto file : file_list)
	{
		file_sizes.insert(std::make_pair(file, fs::file_size(fs::path(file))));
	}

	const uint32_t threads_number = std::thread::hardware_concurrency();

	std::vector<std::thread> threads(threads_number);
	for (auto &thread : threads)
	{
	}

	return "";
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		usage();
		return EXIT_FAILURE;
	}

	fs::path path_to_director;

	if (std::string(".").compare(argv[1]) != 0)
	{
		path_to_director = fs::current_path();
	}
	else
	{
		path_to_director = fs::path(argv[1]);
	}

	if (fs::exists(path_to_director) == false)
	{
		std::cerr << "Directory doesn't exists" << std::endl;
		return EXIT_FAILURE;
	}

	file_str_list file_list;
	if (find_files(path_to_director, file_list) == 0)
	{
		std::cerr << "Cannot find any file with source code."
							<< "Supported lanugange: C++, C, Python, Shell Script" << std::endl;
		return EXIT_FAILURE;
	}

	std::string to_dos = find_todos(file_list);

	// initscr();
	// cbreak();
	// noecho();
	// endwin();
	return 0;
}
