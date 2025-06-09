#pragma once

#include "Dandelion.h"
#include "Sheep.h"
#include "Grass.h"
#include "Wolf.h"
#include "Amanita.h"
#include "Bear.h"
#include "Cow.h"
#include "Goat.h"
#include "Hare.h"
#include "Pig.h"
#include "Clover.h"
#include "Berries.h"
#include <functional>
#include <map>
#include <memory> 

class OrganismCreator {
public:
    static std::shared_ptr<Organism> createOrganism(const std::string &type, const Position &pos);
    static std::map<std::string, std::function<std::shared_ptr<Organism>(const Position &)>>
        creator;
};