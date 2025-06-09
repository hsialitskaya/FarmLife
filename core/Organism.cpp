#include "Organism.h"
#include "FoodChainConfig.h"
#include <iostream>

std::unordered_map<uintptr_t, Organism*> Organism::registry;


Organism::Organism(int power, Position position, std::string species, char type, int initiative, int liveLength, int powerToReproduce)
    : power(power),
      position(position),
      species(species),
      type(type),
      initiative(initiative),
      liveLength(liveLength),
      powerToReproduce(powerToReproduce),
      lastPosition(position),
      ancestors(),
      birth(0),
      death(-1),
      edibleSpecies()
    {
        uuid = reinterpret_cast<uintptr_t>(this);  // Unikalny identyfikator na podstawie adresu
        registry[uuid] = this;                     // Rejestracja w globalnym rejestrze
    }

Organism::Organism(int power, Position position, int initiative, int liveLength, int powerToReproduce)
    : power(power),
      position(position),
      species("Organizm"), 
      type('O'),          
      initiative(initiative),
      liveLength(liveLength),
      powerToReproduce(powerToReproduce),
      birth(0),
      death(-1),
      lastPosition(position),
      ancestors(),
      descendants(),
      edibleSpecies()
    {
        uuid = reinterpret_cast<uintptr_t>(this);  // Unikalny identyfikator
        registry[uuid] = this;                     // Rejestracja w globalnym rejestrze
    }



Organism::Organism(Position position)
    : power(0),
      position(position),
      species("Organizm"),
      type('O'),
      initiative(0),
      liveLength(0),
      powerToReproduce(0),
      birth(0),
      death(-1),
      lastPosition(position),
      ancestors(),
      descendants(),
      edibleSpecies()
{
    uuid = reinterpret_cast<uintptr_t>(this);
    registry[uuid] = this;
}


int Organism::getPower() const 
{
	return this->power;
}

void Organism::setPower(int power)
{
	this->power = power;
}

Position Organism::getPosition() const 
{
	return this->position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}

std::string Organism::getSpecies() const 
{
	return this->species;
}

void Organism::setSpecies(std::string spec)
{
	this->species = spec;
    updateEdibleSpecies(spec);
}

char Organism::getType() const
{
	return this->type;
}

void Organism::setType(char type)
{
	this->type = type;
}

int Organism::getInitiative() const
{
    return this->initiative;
}

void Organism::setInitiative(int initiative) 
{
    this->initiative = initiative;
}

int Organism::getLiveLength() const 
{
    return this->liveLength;
}

void Organism::setLiveLength(int liveLength) 
{
    this->liveLength = liveLength;
}

int Organism::getPowerToReproduce() const 
{
    return this->powerToReproduce;
}

void Organism::setPowerToReproduce(int powerToReproduce) 
{
    this->powerToReproduce = powerToReproduce;
}

const std::list<AncestorInfo>& Organism::getAncestors() const {
    return this->ancestors;
}


void Organism::addAllAncestor(const AncestorInfo& ancestor) {
    AncestorInfo info;
    info.uuid = ancestor.uuid;       
    info.type = ancestor.type;
    info.species = ancestor.species;
    info.birthTurn = ancestor.birthTurn;
    info.deathTurn = -1; // Domyślnie "żywy"
    ancestors.push_back(info);
}


std::string Organism::ancestorsToString() const {
    std::string result;
    for (const auto& ancestor : ancestors) {
        result += "[Type: " + std::string(1, ancestor.type) + 
                  ", Species: " + ancestor.species + 
                  ", Birth: " + std::to_string(ancestor.birthTurn) + 
                  ", Death: " + (ancestor.deathTurn == -1 ? "Alive" : std::to_string(ancestor.deathTurn)) + "] ";
    }
    return result.empty() ? "No ancestors" : result;
}

int Organism::getBirth() const
{
    return this->birth;
}

void Organism::setBirth(int t_birth)
{
    this->birth = t_birth;
}


int Organism::getDeath() const
{
    return this->death;
}

void Organism::setDeath(int t_death)
{
    this->death = t_death;
}


Position Organism::getLastPosition() const
{
    return this->lastPosition;
}

void Organism::setLastPosition(Position position)
{
    this->lastPosition = position;
}

const std::vector<std::string>& Organism::getEdibleSpecies() const {
    return edibleSpecies;
}


void Organism::setEdibleSpecies(const std::vector<std::string>& species) {
    edibleSpecies = species;
}

void Organism::updateEdibleSpecies(const std::string& spec)
{
    auto foodChain = FoodChainConfig::getFoodChain();

    // Znajdź listę jadalnych gatunków dla tego gatunku
    auto it = foodChain.find(spec);
    if (it != foodChain.end()) {
        this->setEdibleSpecies(it->second); // Ustaw listę
    }
}

void Organism::eatAdjacent(const std::vector<std::shared_ptr<Organism>>& adjacentOrganisms) {
    for (auto& org : adjacentOrganisms) {
        // Sprawdź, czy gatunek jest jadalny i ofiara jest żywa
        if (org->getLiveLength() > 0 && 
            std::find(edibleSpecies.begin(), edibleSpecies.end(), org->getSpecies()) != edibleSpecies.end()) 
        {
            if (org->isAnimal()) {
                if (this->getPower() > org->getPower()) {
                    this->setPower(this->getPower() + org->getPower());
                    org->setLiveLength(0); 
                    break; 
                }
            } else {
                this->setPower(this->getPower() + org->getPower());
                org->setLiveLength(0);
                break;
            }
        }
    }
}


void Organism::addDescendant(std::shared_ptr<Organism> descendant) {
    // Sprawdź, czy już istnieje
    for (const auto& existing : descendants) {
        if (auto existingShared = existing.lock()) {
            if (existingShared == descendant) {
                return; // Już istnieje – nie dodajemy
            }
        }
    }

    // Jeśli nie istnieje – dodaj
    descendants.push_back(std::weak_ptr<Organism>(descendant));
}


void Organism::notifyDescendantsAboutDeath(uintptr_t deadAncestorUUID, int deathTurn) {
    // Aktualizuj dane przodka
    for (auto& ancestor : ancestors) {
        if (ancestor.uuid == deadAncestorUUID) {
            ancestor.deathTurn = deathTurn;
            break;
        }
    }

    // Powiadom tylko istniejących potomków
    for (auto& weakChild : descendants) {
        // Sprawdzamy, czy weak_ptr nadal wskazuje na ważny obiekt
        if (auto child = weakChild.lock()) {  // Sprawdzenie, czy weak_ptr nie jest już wygasły
            child->notifyDescendantsAboutDeath(deadAncestorUUID, deathTurn);
        }
    }
}

// Konstruktor kopiujący
Organism::Organism(const Organism& other)
    : power(other.power),
      position(other.position),
      species(other.species),
      type(other.type),
      initiative(other.initiative),
      liveLength(other.liveLength),
      powerToReproduce(other.powerToReproduce),
      ancestors(other.ancestors),
      descendants(), // nie kopiujemy wskaźników do potomków
      edibleSpecies(other.edibleSpecies),
      birth(other.birth),
      death(other.death),
      lastPosition(other.lastPosition),
      uuid(reinterpret_cast<uintptr_t>(this))
{
    registry[uuid] = this;
}


// Konstruktor kopiujący z wskaźnika
Organism::Organism(Organism* other)
{
    if (other) {
        power = other->power;
        position = other->position;
        species = other->species;
        type = other->type;
        initiative = other->initiative;
        liveLength = other->liveLength;
        powerToReproduce = other->powerToReproduce;
        ancestors = other->ancestors;
        edibleSpecies = other->edibleSpecies;
        birth = other->birth;
        death = other->death;
        lastPosition = other->lastPosition;
    } else {
        power = 0;
        position = Position(0, 0);
        species = "Organizm";
        type = 'O';
        initiative = 0;
        liveLength = 0;
        powerToReproduce = 0;
        ancestors.clear();
        edibleSpecies.clear();
        birth = 0;
        death = -1;
        lastPosition = Position(0, 0);
    }

    uuid = reinterpret_cast<uintptr_t>(this);
    registry[uuid] = this;
}


// Konstruktor przenoszący
Organism::Organism(Organism&& other) noexcept
    : power(std::move(other.power)),
      position(std::move(other.position)),
      species(std::move(other.species)),
      type(std::move(other.type)),
      initiative(std::move(other.initiative)),
      liveLength(std::move(other.liveLength)),
      powerToReproduce(std::move(other.powerToReproduce)),
      ancestors(std::move(other.ancestors)),
      descendants(), // nie przenosimy potomków
      edibleSpecies(std::move(other.edibleSpecies)),
      birth(std::move(other.birth)),
      death(std::move(other.death)),
      lastPosition(std::move(other.lastPosition)),
      uuid(reinterpret_cast<uintptr_t>(this))
{
    registry[uuid] = this;
}


// Operator przypisania kopiujący
Organism& Organism::operator=(const Organism& other)
{
    if (this != &other) {
        power = other.power;
        position = other.position;
        species = other.species;
        type = other.type;
        initiative = other.initiative;
        liveLength = other.liveLength;
        powerToReproduce = other.powerToReproduce;
        ancestors = other.ancestors;
        edibleSpecies = other.edibleSpecies;
        birth = other.birth;
        death = other.death;
        lastPosition = other.lastPosition;

        // UUID się nie zmienia, ale można nadpisać rejestr:
        registry[uuid] = this;
    }
    return *this;
}


// Operator przypisania przenoszący
Organism& Organism::operator=(Organism&& other) noexcept
{
    if (this != &other) {
        power = std::move(other.power);
        position = std::move(other.position);
        species = std::move(other.species);
        type = std::move(other.type);
        initiative = std::move(other.initiative);
        liveLength = std::move(other.liveLength);
        powerToReproduce = std::move(other.powerToReproduce);
        ancestors = std::move(other.ancestors);
        edibleSpecies = std::move(other.edibleSpecies);
        birth = std::move(other.birth);
        death = std::move(other.death);
        lastPosition = std::move(other.lastPosition);

        // UUID zostaje stare, ale odśwież rejestr:
        registry[uuid] = this;
    }
    return *this;
}


Organism::~Organism() {
    registry.erase(uuid); // Usuń z rejestru przy niszczeniu
}
