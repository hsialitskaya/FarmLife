#include "Goat.h"

Goat::Goat(Position position) : Animal(position) {
    setSpecies("Goat");
    setType('K');
    setPower(5);
    setInitiative(4);
    setLiveLength(7);
    setPowerToReproduce(6);
}

Goat::Goat() : Animal() {
    setSpecies("Goat");
    setType('K');
    setPower(5);
    setInitiative(4);
    setLiveLength(7);
    setPowerToReproduce(6);
}

Goat::~Goat() = default;


std::string Goat::toString() const
{
    return std::string("{ species: Goat") + 
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

Organism* Goat::reproduce(Position position) {
    // Tworzymy nowy organizm
    Organism* newOrganism = new Goat(position);

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

   