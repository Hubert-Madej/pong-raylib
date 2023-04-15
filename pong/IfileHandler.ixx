module;
#include <vector>
#include <string>
export module IfileHandler;

export struct IfileHandler {
	virtual void saveToFile(int leftPlayerScore, int rightPlayerScore, std::string username) = 0;
	virtual std::vector<std::tuple<int, int, std::string>> readFromFile() = 0;
};