#include "FoodChainLoader.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <map>

class FoodChainConfig {
private:
    static std::string findFoodChainPath() {
        std::vector<std::string> possiblePaths = {
            "resources/files/food_chain.json",
            "../resources/files/food_chain.json",
            "../../resources/files/food_chain.json"
        };

        for (const auto& path : possiblePaths) {
            if (std::filesystem::exists(path)) {
                return path;
            }
        }

        throw std::runtime_error("Nie znaleziono pliku food_chain.json w żadnej ze znanych lokalizacji.");
    }

public:
    static std::map<std::string, std::vector<std::string>> getFoodChain() {
        try {
            std::string path = findFoodChainPath();
            return FoodChainLoader::loadFromFile(path);
        } catch (const std::exception& e) {
            std::cerr << "Błąd podczas ładowania pliku food_chain.json: " << e.what() << "\n";
            return {}; // Zwróć pustą mapę w przypadku błędu
        }
    }
};
