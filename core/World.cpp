#include "World.h"
#include <fstream>
#include <iostream>
#include <unordered_set>

Organism* World::getOrganismFromPosition(const Position& pos) const {
    for (const auto& org : organisms){
        if (org->getPosition().getX() == pos.getX() && 
            org->getPosition().getY() == pos.getY()) { 
            return org.get();
        }
    }
    return nullptr; 
}

char World::getOrganismSignFromPosition(int x, int y) {
    Organism* org = getOrganismFromPosition(Position(x, y));
    return (org != nullptr) ? org->getType() : ' ';  
}


bool World::isPositionOnWorld(int x, int y)
{
	return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
    return this->getOrganismSignFromPosition(position.getX(), position.getY()) == ' ';
}

std::vector<Position> World::getVectorOfFreePositionsAround(Position position) {    
    std::vector<Position> result;
    int pos_x = position.getX(), pos_y = position.getY();
    
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
        }
    }
    
    result.erase(std::remove_if(result.begin(), result.end(),
        [this](Position pos) { return !isPositionFree(pos); }), result.end());

    return result;
}


std::vector<std::shared_ptr<Organism>> World::getAdjacentOrganisms(Position position) 
{
    std::vector<std::shared_ptr<Organism>> result;
    int pos_x = position.getX(), pos_y = position.getY();

    // Sprawdzamy tylko cztery sąsiednie pozycje (góra, dół, lewo, prawo)
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // (dx, dy)

    for (auto& direction : directions) {
        int dx = direction[0];
        int dy = direction[1];
        
        int x = pos_x + dx;
        int y = pos_y + dy;

        if (isPositionOnWorld(x, y)) {
            for (auto& org : organisms) {
                if (org->getPosition().getX() == x && org->getPosition().getY() == y) {
                    result.push_back(org);
                }
            }
        }
    }
    return result;
}

World::World(int worldX, int worldY)
{
	setWorldX(worldX);
	setWorldY(worldY);
}


int World::getWorldX()
{
	return this->worldX;
}

void World::setWorldX(int worldX)
{
	this->worldX = worldX;
}

int World::getWorldY()
{
	return this->worldY;
}

void World::setWorldY(int worldY)
{
	this->worldY = worldY;
}

int World::getTurn()
{
	return this->turn;
}

//Dodanie nowego organizmu
void World::addOrganism(std::shared_ptr<Organism> organism) 
{
    organism->setBirth(this->turn);
    organisms.push_back(organism);
}

// Jedzenie
void World::handleEatingPhase() {
    for (auto& org : organisms) {
        auto adjacent = getAdjacentOrganisms(org->getPosition());
        org->eatAdjacent(adjacent);
    }
}

// Starzenie i wzrost mocy
void World::handleAgingAndPowerPhase() {
    for (auto& org : organisms) {
        org->setLiveLength(org->getLiveLength() - 1);  // Starzenie
        org->setPower(org->getPower() + 1);            // Wzrost mocy
    }
}


void World::updateAncestorDeathDates(Organism* deadOrg) {
    int currentTurn = getTurn();
    
    for (auto& org : organisms) {
        org->notifyDescendantsAboutDeath(reinterpret_cast<uintptr_t>(deadOrg), currentTurn);
    }
}


void World::handleRemovalOfDeadOrganisms() {
    auto it = organisms.begin();
    while (it != organisms.end()) {
        if ((*it)->getLiveLength() <= 0) {
            updateAncestorDeathDates(it->get()); // Przekaż wskaźnik
            it = organisms.erase(it); // Automatycznie zwalnia pamięć
        } else {
            ++it;
        }
    }
}


// Przesuniecie
void World::handleMovementPhase() {
    for (auto& org : organisms) {
        const auto freePositions = getVectorOfFreePositionsAround(org->getPosition());
        if (!freePositions.empty()) {
            const int randomIndex = rand() % freePositions.size();
            const Position newPos = freePositions[randomIndex];
            
            const int dx = newPos.getX() - org->getPosition().getX();
            const int dy = newPos.getY() - org->getPosition().getY();
            
            org->move(dx, dy);
        }
    }
}

// Tworzenie dziecka
std::shared_ptr<Organism> World::createChildOrganism(std::shared_ptr<Organism> parent1, std::shared_ptr<Organism> parent2, const Position& pos) {
    // Parent1 tworzy dziecko
    Organism* childRaw = parent1->reproduce(pos);
    auto child = std::shared_ptr<Organism>(childRaw);

    parent1->setPower(parent1->getPower() / 2);
    if (parent2) {
        parent2->setPower(parent2->getPower() / 2);
    }

    // Zbierz unikalne uuid-y przodków już obecnych w dziecku
    std::unordered_set<uintptr_t> existingAncestorUuids;
    for (const auto& ancestor : child->getAncestors()) {
        existingAncestorUuids.insert(ancestor.uuid);
    }

    // Dodaj przodków z parent2, jeśli ich jeszcze nie ma
    if (parent2) {
        for (const auto& ancestor : parent2->getAncestors()) {
            if (existingAncestorUuids.find(ancestor.uuid) == existingAncestorUuids.end()) {
                child->addAllAncestor(ancestor);
                existingAncestorUuids.insert(ancestor.uuid);  // aktualizuj zestaw
            }
        }

        // Dodaj samego parent2 jako przodka, jeśli nie dodany
        uintptr_t p2uuid = reinterpret_cast<uintptr_t>(parent2.get());
        if (existingAncestorUuids.find(p2uuid) == existingAncestorUuids.end()) {
            AncestorInfo parentAncestor;
            parentAncestor.type = parent2->getType();
            parentAncestor.species = parent2->getSpecies();
            parentAncestor.birthTurn = parent2->getBirth();
            parentAncestor.deathTurn = parent2->getDeath();
            parentAncestor.uuid = p2uuid;
            child->addAllAncestor(parentAncestor);
        }
    }

    // Przypisanie dziecka jako potomka rodziców
    parent1->addDescendant(child);
    if (parent2) {
        parent2->addDescendant(child);
    }

    return child;
}


void World::handleReproductionPhase() {
    std::vector<std::shared_ptr<Organism>> newOrganisms;
    std::unordered_set<std::shared_ptr<Organism>> processed;

    for (auto& org : organisms) {
        if (processed.find(org) != processed.end()) continue;

        if (org->getPower() >= org->getPowerToReproduce()) {
            bool canReproduce = true;
            std::shared_ptr<Organism> mate = nullptr;

            if (org->isAnimal()) {
                auto adjacent = getAdjacentOrganisms(org->getPosition());
                
                for (auto& adjOrg : adjacent) {
                    if (adjOrg->isAnimal() && 
                        adjOrg->getSpecies() == org->getSpecies() &&
                        adjOrg->getPower() >= adjOrg->getPowerToReproduce() &&
                        processed.find(adjOrg) == processed.end()) 
                    {
                        mate = adjOrg;
                        break;
                    }
                }
                if (!mate) canReproduce = false;
            }

            if (canReproduce) {
                const auto freePositions = getVectorOfFreePositionsAround(org->getPosition());
                if (!freePositions.empty()) {
                    const Position newPos = freePositions[rand() % freePositions.size()];
                    auto child = createChildOrganism(org, mate, newPos);
                    newOrganisms.push_back(child);

                    processed.insert(org);
                    if (mate) processed.insert(mate);
                }
            }
        }
    }
    
    for (auto& child : newOrganisms) {
        addOrganism(child);
    }
}

void World::makeTurn()
{
	handleEatingPhase();
    handleAgingAndPowerPhase();
    handleRemovalOfDeadOrganisms();
    handleMovementPhase();
    handleReproductionPhase();

    // Wypisanie informacji o wszystkich organizmach po każdej turze
    std::cout << organismsToString() << std::endl;
	turn++;
}


void World::writeWorld(const std::string& fileName) {
    std::ofstream my_file(fileName, std::ios::binary);
    if (!my_file) {
        std::cerr << "Nie można otworzyć pliku do zapisu: " << fileName << std::endl;
        return;
    }

    my_file.write(reinterpret_cast<const char*>(&worldX), sizeof(worldX));
    my_file.write(reinterpret_cast<const char*>(&worldY), sizeof(worldY));
    my_file.write(reinterpret_cast<const char*>(&turn), sizeof(turn));

    int orgs_size = static_cast<int>(organisms.size());
    my_file.write(reinterpret_cast<const char*>(&orgs_size), sizeof(orgs_size));

    for (const auto& org : organisms) {
        int data;

        data = org->getPower();
        my_file.write(reinterpret_cast<const char*>(&data), sizeof(data));

        data = org->getPosition().getX();
        my_file.write(reinterpret_cast<const char*>(&data), sizeof(data));
        data = org->getPosition().getY();
        my_file.write(reinterpret_cast<const char*>(&data), sizeof(data));

        char type = org->getType();
        my_file.write(&type, sizeof(type));

        data = org->getLiveLength();
        my_file.write(reinterpret_cast<const char*>(&data), sizeof(data));

        data = org->getBirth();
        my_file.write(reinterpret_cast<const char*>(&data), sizeof(data));

        Position lastPos = org->getLastPosition();
        data = lastPos.getX();
        my_file.write(reinterpret_cast<const char*>(&data), sizeof(data));
        data = lastPos.getY();
        my_file.write(reinterpret_cast<const char*>(&data), sizeof(data));

        // Przodkowie
        const auto& ancestors = org->getAncestors();
        int ancestorsSize = static_cast<int>(ancestors.size());
        my_file.write(reinterpret_cast<const char*>(&ancestorsSize), sizeof(ancestorsSize));

        for (const auto& ancestor : ancestors) {
            my_file.write(reinterpret_cast<const char*>(&ancestor.type), sizeof(char));

            int speciesLength = static_cast<int>(ancestor.species.size());
            my_file.write(reinterpret_cast<const char*>(&speciesLength), sizeof(int));
            my_file.write(ancestor.species.data(), speciesLength);

            my_file.write(reinterpret_cast<const char*>(&ancestor.birthTurn), sizeof(int));
            my_file.write(reinterpret_cast<const char*>(&ancestor.deathTurn), sizeof(int));

            my_file.write(reinterpret_cast<const char*>(&ancestor.uuid), sizeof(uintptr_t));
        }
    }

    my_file.close();
}


void World::readWorld(const std::string& fileName) {
    std::ifstream my_file(fileName, std::ios::binary);
    if (!my_file) {
        std::cerr << "Nie można otworzyć pliku do odczytu: " << fileName << std::endl;
        return;
    }

    organisms.clear();

    my_file.read(reinterpret_cast<char*>(&worldX), sizeof(worldX));
    my_file.read(reinterpret_cast<char*>(&worldY), sizeof(worldY));
    my_file.read(reinterpret_cast<char*>(&turn), sizeof(turn));

    int orgs_size;
    my_file.read(reinterpret_cast<char*>(&orgs_size), sizeof(orgs_size));

    std::vector<std::shared_ptr<Organism>> new_organisms;

    for (int i = 0; i < orgs_size; i++) {
        int power, pos_x, pos_y;
        my_file.read(reinterpret_cast<char*>(&power), sizeof(int));
        my_file.read(reinterpret_cast<char*>(&pos_x), sizeof(int));
        my_file.read(reinterpret_cast<char*>(&pos_y), sizeof(int));
        Position position(pos_x, pos_y);

        char type;
        my_file.read(&type, sizeof(type));
        std::string species(1, type);

        auto org = OrganismCreator::createOrganism(species, position);

        int liveLength, birthTurn, lastPosX, lastPosY;
        my_file.read(reinterpret_cast<char*>(&liveLength), sizeof(int));
        my_file.read(reinterpret_cast<char*>(&birthTurn), sizeof(int));
        my_file.read(reinterpret_cast<char*>(&lastPosX), sizeof(int));
        my_file.read(reinterpret_cast<char*>(&lastPosY), sizeof(int));

        org->setPower(power);
        org->setLiveLength(liveLength);
        org->setBirth(birthTurn);
        org->setLastPosition(Position(lastPosX, lastPosY));

        // Przodkowie
        int ancestorsSize;
        my_file.read(reinterpret_cast<char*>(&ancestorsSize), sizeof(ancestorsSize));
        for (int j = 0; j < ancestorsSize; ++j) {
            AncestorInfo ancestor;
            my_file.read(reinterpret_cast<char*>(&ancestor.type), sizeof(char));

            int speciesLength;
            my_file.read(reinterpret_cast<char*>(&speciesLength), sizeof(int));
            ancestor.species.resize(speciesLength);
            my_file.read(&ancestor.species[0], speciesLength);

            my_file.read(reinterpret_cast<char*>(&ancestor.birthTurn), sizeof(int));
            my_file.read(reinterpret_cast<char*>(&ancestor.deathTurn), sizeof(int));
            my_file.read(reinterpret_cast<char*>(&ancestor.uuid), sizeof(uintptr_t));

            org->addAllAncestor(ancestor);
        }

        new_organisms.push_back(org);
    }

    organisms = std::move(new_organisms);
    my_file.close();
}


std::string World::toString()
{
	std::string result = "\nturn: " + std::to_string(getTurn()) + "\n";
	std::string spec;

	for (int wY = 0; wY < getWorldY(); ++wY) {
		for (int wX = 0; wX < getWorldX(); ++wX) {
			spec = getOrganismSignFromPosition(wX, wY);
			if (spec[0] != ' ')
				result += spec;
			else
				result += separator;
		};
		result += "\n";
	}
	return result;
}

std::string World::organismsToString()
{
    std::string result = "All organisms:\n";

    for (const auto &org : this->organisms) {
        result += org->toString() + ' ' + '\n';
    }

    return result;
}

// Destruktor
World::~World() {
	organisms.clear();
}

