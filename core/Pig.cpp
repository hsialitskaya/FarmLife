#include "Pig.h"

Pig::Pig(Position position) : Animal(position) {
    setSpecies("Pig");
    setType('I');
    setPower(4);
    setInitiative(3);
    setLiveLength(8);
    setPowerToReproduce(8);
}

Pig::Pig() : Animal() {
    setSpecies("Pig");
    setType('I');
    setPower(4);
    setInitiative(3);
    setLiveLength(8);
    setPowerToReproduce(8);
}

Pig::~Pig() = default;


std::string Pig::toString() const
{
    return std::string("{ species: Pig") + 
           ", power: " + std::to_string(getPower()) + 
           ", initiative: " + std::to_string(getInitiative()) +
           ", liveLength: " + std::to_string(getLiveLength()) +
           ", powerToReproduce: " + std::to_string(getPowerToReproduce()) +
           ", birthTurn: " + std::to_string(getBirth()) +
           ", position: " + getPosition().toString() +
           ", deathTurn: " + std::to_string(getDeath()) +
           ", lastPosition: " + getLastPosition().toString() +
           ", ancestors: " + ancestorsToString() +
           " }";
}

Organism* Pig::reproduce(Position position) {
    // Tworzymy nowy organizm
    Organism* newOrganism = new Pig(position);

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

   