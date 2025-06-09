#include "Berries.h"

Berries::Berries(Position position) : Plant(position) {
    setSpecies("Berries");
    setType('E');
    setLiveLength(14);
    setPowerToReproduce(5);
}

Berries::Berries() : Plant() {
    setSpecies("Berries");
    setType('E');
    setLiveLength(14);
    setPowerToReproduce(5);
}

Berries::~Berries() = default;


std::string Berries::toString() const
{
    return std::string("{ species: Berries") + 
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


Organism* Berries::reproduce(Position position) {
    // Tworzymy nowy organizm
    Organism* newOrganism = new Berries(position);

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

