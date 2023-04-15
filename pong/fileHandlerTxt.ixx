module;
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
export module fileHandlerTxt;
import IfileHandler;

export struct fileHandlerTxt : IfileHandler {
	std::string fileName = "score.txt";


	void saveToFile(int leftPlayerScore, int rightPlayerScore, std::string username) {
		std::filesystem::path filePath(fileName);

		std::ofstream file(filePath, std::ios::app);
		if (!file.is_open()) {
			std::cerr << "Could not open the file" << std::endl;
			return;
		}
		file << leftPlayerScore << ";" << rightPlayerScore << ";" << username << "\n";
		file.close();
	}

	std::vector<std::tuple<int, int, std::string>> readFromFile() {
		std::vector<std::tuple<int, int, std::string>> result;

		std::filesystem::path filePath(fileName);
		if (!std::filesystem::exists(filePath)) {
			std::cout << "File not found" << std::endl;
			return result;
		}

		std::ifstream file(filePath);
		if (!file.is_open()) {
			std::cerr << "Could not open the file" << std::endl;
			return result;
		}
		std::string line;
		while (file >> line) {
			std::tuple<int, int, std::string> t = splitString(line);

			result.push_back(t);
		}

		file.close();
		return result;

	}

	std::tuple<int, int, std::string> splitString(const std::string& input) {
		int firstInt = 0, secondInt = 0;
		std::string str;

		// find the first and second semicolons in the input string
		size_t firstSemicolon = input.find(';');
		size_t secondSemicolon = input.find(';', firstSemicolon + 1);

		// extract the first and second integers from the string
		firstInt = std::stoi(input.substr(0, firstSemicolon));
		secondInt = std::stoi(input.substr(firstSemicolon + 1, secondSemicolon - firstSemicolon - 1));

		// extract the string after the second semicolon
		str = input.substr(secondSemicolon + 1);

		// create and return the tuple
		return std::make_tuple(firstInt, secondInt, str);
	}
};