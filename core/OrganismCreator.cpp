#include "OrganismCreator.h"
#include <memory> 

std::map<std::string, std::function<std::shared_ptr<Organism>(const Position &)>>
    OrganismCreator::creator = {
        {"D", [](const Position &pos) { return std::make_shared<Dandelion>(pos); }},
        {"G", [](const Position &pos) { return std::make_shared<Grass>(pos); }},
        {"S", [](const Position &pos) { return std::make_shared<Sheep>(pos); }},
        {"T", [](const Position &pos) { return std::make_shared<Amanita>(pos); }},
        {"W", [](const Position &pos) { return std::make_shared<Wolf>(pos); }},
        {"B", [](const Position &pos) { return std::make_shared<Bear>(pos); }},
        {"E", [](const Position &pos) { return std::make_shared<Berries>(pos); }},
        {"L", [](const Position &pos) { return std::make_shared<Clover>(pos); }},
        {"C", [](const Position &pos) { return std::make_shared<Cow>(pos); }},
        {"K", [](const Position &pos) { return std::make_shared<Goat>(pos); }},
        {"H", [](const Position &pos) { return std::make_shared<Hare>(pos); }},
        {"I", [](const Position &pos) { return std::make_shared<Pig>(pos); }}
};

std::shared_ptr<Organism> OrganismCreator::createOrganism(const std::string &type, const Position &pos) {
    auto it = creator.find(type);
    if (it != creator.end()) {
        return it->second(pos); 
    }
    return nullptr;
}