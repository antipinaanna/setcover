#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

struct Set {
    std::set<int> elements;
    int index;
    int cost;
};

struct Result {
    int totalCost;
    std::vector<bool> includedSets;
};

Result minimumSetCover(std::vector<Set>& sets, const std::set<int>& universe) {
    Result result;
    result.totalCost = 0;


    result.includedSets.resize(sets.size(), false);
    std::set<int> tmpUniverse = universe;


    std::sort(sets.begin(), sets.end(), [](const Set& a, const Set& b) {
        return a.cost < b.cost;
    });


    for (const Set& s : sets) {
        bool containsUncoveredElement = false;
        for (const int& element : s.elements) {
            if (tmpUniverse.count(element) > 0) {
                containsUncoveredElement = true;
                break;
            }
        }

        if (containsUncoveredElement) {
            result.includedSets[s.index] = true;
            result.totalCost += s.cost;


            for (const int& element : s.elements) {
                tmpUniverse.erase(element);
            }
        }
    }

    return result;
}

int main() {
    std::string folderPath = "./data";
    std::ofstream file_out("output_dataframe");
	if (file_out.is_open())
	{
		for (const auto &entry : fs::directory_iterator(folderPath)) 
		{
			if (entry.is_regular_file())
			{
                std::string filePath = entry.path().string();
				std::ifstream file(filePath);
				if (file.is_open())
				{
                    int universeSize;
                    file >> universeSize;
                    int numSets;
                    file >> numSets;
                    // Ввод элементов и их стоимостей для каждого множества
                    std::vector<Set> sets(numSets);
                    for (int i = 0; i < numSets; ++i) {
                        int cost;
                        file >> cost;
                        std::string input;
                        std::getline(file, input);
                        std::istringstream ss(input);
                        int element;
                        while (ss >> element) {
                            sets[i].elements.insert(element);
                        }
                        sets[i].cost = cost;
                        sets[i].index = i;
                    }
                    std::set<int> universe;
                    for (int i = 0; i < universeSize; i++) {
                        universe.insert(i);
                    }
                    Result result = minimumSetCover(sets, universe);

                    std::cout << "Total Cost: " << result.totalCost << std::endl;
                    std::cout << "Included Sets: ";
                    for (bool included : result.includedSets) {
                        std::cout << (included ? 1 : 0);
                    }
                    std::cout << std::endl;
                    file_out << filePath << ", "<< result.totalCost << std::endl;
                        file.close();
				}
				else
					std::cout << "Не удалось открыть файл" << std::endl;
			}
		}
		file_out.close();
    }    
}
