#include "Wolf.h"

Wolf::Wolf(Position position) : Animal(position) {
    setSpecies("Wolf");
    setType('W');
    setPower(8);
    setInitiative(2);
    setLiveLength(20);
    setPowerToReproduce(16);
}

Wolf::Wolf() : Animal() {
    setSpecies("Wolf");
    setType('W');
    setPower(8);
    setInitiative(2);
    setLiveLength(20);
    setPowerToReproduce(16);
}

Wolf::~Wolf() = default;


std::string Wolf::toString() const
{
    return std::string("{ species: Wolf") + 
           ", power: " + std::to_string(getPower()) + 
           ", initiative: " + std::to_string(getInitiative()) +
           ", liveLength: " + std::to_string(getLiveLength()) +
           ", powerToReproduce: " + std::to_string(getPowerToReproduce()) +
           ", birthTurn: " + std::to_string(getBirth()) +
           ", deathTurn: " + std::to_string(getDeath()) +
           ", position: " + getPosition().toString() +
           ", lastPosition: " + getLastPosition().toString() +
           ", ancestors: " + ancestorsToString() +
           " }";
}

Organism* Wolf::reproduce(Position position) {
    // Tworzymy nowy organizm
    Organism* newOrganism = new Wolf(position);

    // Kopiowanie przodków z rodzica do potomka
    for (const auto& ancestorData : this->getAncestors()) {
        // Dodajemy przodka do potomka
        newOrganism->addAllAncestor(ancestorData);  
    }

    // Dodajemy bieżącego organizmu (rodzica) do przodków nowego organizmu
    AncestorInfo parentAncestor;
    parentAncestor.type = this->getType();  
    parentAncestor.species = this->getSpecies();  
    parentAncestor.birthTurn = this->getBirth();  
    parentAncestor.deathTurn = this->getDeath();  
    parentAncestor.uuid = reinterpret_cast<uintptr_t>(this);  

    newOrganism->addAllAncestor(parentAncestor);  // Dodajemy przodka (rodzica) do potomka

    return newOrganism;
}

    