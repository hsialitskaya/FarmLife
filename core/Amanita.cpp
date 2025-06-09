#include "Amanita.h"

Amanita::Amanita(Position position) 
    : Plant(position) {  
    setSpecies("Amanita");
    setType('T');
    setLiveLength(12);
    setPowerToReproduce(4);
}

Amanita::Amanita() 
    : Plant() {  
    setSpecies("Amanita");
    setType('T');
    setLiveLength(12);
    setPowerToReproduce(4);
}

Amanita::~Amanita() = default;


std::string Amanita::toString() const
{
    return std::string("{ species: Amanita") + 
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

Organism* Amanita::reproduce(Position position) {
    // Tworzymy nowy organizm
    Organism* newOrganism = new Amanita(position);

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

   

// make 
// ./Projekt.app/Contents/MacOS/Projekt