module;
#include <vector>
export module IfileHandler;

export struct IfileHandler {
	virtual void saveToFile(int leftPlayerScore, int rightPlayerScore) = 0;
	virtual std::vector<std::pair<int, int>> readFromFile() = 0;
};