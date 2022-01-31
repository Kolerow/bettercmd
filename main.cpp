#include "term.h"
#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>

namespace filesystem = std::filesystem;

int cd(int argc, const char *argv) {
	std::string path = filesystem::current_path().string();
	std::string argument(argv);
	if (argument.rfind("..", 0) == 0) {
		filesystem::current_path(argument);
	}
	else {
		filesystem::path location;
		location = filesystem::current_path() / ("C:" + argument);
		if (is_directory(location)) filesystem::current_path(location);
		else std::cout << "Location is not a folder" << std::endl;
	}
}

int main() {
	Terminal term;
	while (true) {
		term.prompt();
		std::string command = term.command();
		if (command == "exit") {
			exit(0);
		}
		if (command.rfind("cwd", 0) == 0) {
			int counter = 1;
			std::string delimiter = " ";

			size_t pos = 0;
			std::string token;
			while ((pos = command.find(delimiter)) != std::string::npos) {
				token = command.substr(0, pos);
				command.erase(0, pos + delimiter.length());
				counter++;
			}
			if (counter > 2) {
				std::cout << "Too many arguments" << std::endl;
			}
			else if (counter< 2) {
				std::cout << "Not enough arguments" << std::endl;
			}
			else {
				cd(1, command.c_str());
			}
		}
		else {
			system(command.c_str());
		}
	}
}
