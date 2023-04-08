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


	void saveToFile(int leftPlayerScore, int rightPlayerScore) {
		std::filesystem::path filePath(fileName);

		std::ofstream file(filePath, std::ios::app);
		if (!file.is_open()) {
			std::cerr << "Could not open the file" << std::endl;
			return;
		}
		file << leftPlayerScore << "." << rightPlayerScore << "\n";
		file.close();
	}

	std::vector<std::pair<int, int>> readFromFile() {
		std::vector<std::pair<int, int>> result;

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
			std::pair<int, int> p;
			p.first = std::stoi(line.substr(0, line.find(".")));
			p.second = std::stoi(line.substr(line.find(".")));
			result.push_back(p);
		}

		file.close();
		return result;

	}
};