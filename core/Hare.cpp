#include "Hare.h"

Hare::Hare(Position position) : Animal(position) {
    setSpecies("Hare");
    setType('H');
    setPower(3);
    setInitiative(4);
    setLiveLength(6);
    setPowerToReproduce(5);
}

Hare::Hare() : Animal() {
    setSpecies("Hare");
    setType('H');
    setPower(3);
    setInitiative(4);
    setLiveLength(6);
    setPowerToReproduce(5);
}

Hare::~Hare() = default;


std::string Hare::toString() const
{
    return std::string("{ species: Hare") + 
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

Organism* Hare::reproduce(Position position) {
    // Tworzymy nowy organizm
    Organism* newOrganism = new Hare(position);

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

   