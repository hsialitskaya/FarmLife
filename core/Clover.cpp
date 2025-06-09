#include "Clover.h"

Clover::Clover(Position position) : Plant(position) {
    setSpecies("Clover");
    setType('L');
    setLiveLength(8);
    setPowerToReproduce(4);
}

Clover::Clover() : Plant() {
    setSpecies("Clover");
    setType('L');
    setLiveLength(8);
    setPowerToReproduce(4);
}

Clover::~Clover() = default;


std::string Clover::toString() const
{
    return std::string("{ species: Clover") + 
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


Organism* Clover::reproduce(Position position) {
    // Tworzymy nowy organizm
    Organism* newOrganism = new Clover(position);

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

