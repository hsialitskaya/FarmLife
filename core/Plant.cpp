#include "Plant.h"

Plant::Plant(int power, Position position, int initiative, int liveLength, int powerToReproduce) 
: Organism(power, position, initiative, liveLength, powerToReproduce)
{
setSpecies("Plant");
setType('P');
}

Plant::Plant(Position position) : Organism(position)
{
	setSpecies("Plant");
	setType('P');
}

Plant::Plant() : Organism()
{
	setSpecies("Plant");
	setType('P');
}

Plant::~Plant() = default;


std::string Plant::toString() const
{
    return std::string("{ species: Plant") + 
           ", power: " + std::to_string(getPower()) + 
           ", initiative: " + std::to_string(getInitiative()) +
           ", liveLength: " + std::to_string(getLiveLength()) +
           ", powerToReproduce: " + std::to_string(getPowerToReproduce()) +
           ", birthTurn: " + std::to_string(getBirth()) +
           ", deathTurn: " + std::to_string(getDeath()) +
           ", position: " + getPosition().toString() +
           " }";
}

// Nie poruszają się
void Plant::move(int dx, int dy) {
}




