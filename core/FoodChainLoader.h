#pragma once
#include <map>
#include <string>
#include <fstream>
#include "../include/json.hpp" 
#include <stdexcept>

using json = nlohmann::json; 

class FoodChainLoader {
public:
    static std::map<std::string, std::vector<std::string>> loadFromFile(const std::string& filePath) {
        std::map<std::string, std::vector<std::string>> foodChain;
        
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Nie udało się otworzyć pliku: " + filePath);
        }

        json root;
        file >> root; // Wczytaj plik JSON

        if (root.is_null()) {
            throw std::runtime_error("Plik JSON jest pusty lub ma niepoprawną zawartość.");
        }

        for (auto& [species, preyList] : root.items()) {
            for (auto& prey : preyList) {
                foodChain[species].push_back(prey.get<std::string>());
            }
        }

        return foodChain;
    }
};
