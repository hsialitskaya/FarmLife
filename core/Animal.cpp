#include "Animal.h"

Animal::Animal(int power, Position position, int initiative, int liveLength, int powerToReproduce) 
: Organism(power, position, initiative, liveLength, powerToReproduce)
{
setSpecies("Animal");
setType('A');
}

Animal::Animal(Position position) : Organism(position)
{
setSpecies("Animal");
setType('A');
}

Animal::Animal() : Organism()
{
	setSpecies("Animal");
	setType('A');
}

Animal::~Animal() = default;

std::string Animal::toString() const
{
    return std::string("{ species: Animal") + 
           ", power: " + std::to_string(getPower()) + 
           ", initiative: " + std::to_string(getInitiative()) +
           ", liveLength: " + std::to_string(getLiveLength()) +
           ", powerToReproduce: " + std::to_string(getPowerToReproduce()) +
           ", position: " + getPosition().toString() +
           ", lastPosition: " + getLastPosition().toString() +
           ", birthTurn: " + std::to_string(getBirth()) +
           ", deathTurn: " + std::to_string(getDeath()) +
           ", ancestors: " + ancestorsToString() +
           " }";
}

void Animal::move(int dx, int dy) {
    Position currentPos = getPosition(); 
    setLastPosition(currentPos);
    currentPos.move(dx, dy);            
    setPosition(currentPos);             
}





