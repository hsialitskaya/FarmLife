#pragma once

#include <vector>
#include <ctime>
#include "Organism.h"
#include "OrganismCreator.h"

class World
{
private:
    int worldX;
    int worldY;
    int turn = 1;
    std::vector<std::shared_ptr<Organism>> organisms;
    char separator = '.';

    char getOrganismSignFromPosition(int x, int y);
    std::vector<Position> getVectorOfFreePositionsAround(Position position);
    bool isPositionOnWorld(int x, int y);
    bool isPositionFree(Position position);

public:
    World(int worldX, int worldY);
    World() : World(10, 10) {};

    Organism* getOrganismFromPosition(const Position& pos) const;

    int getWorldX();
    void setWorldX(int worldX);
    int getWorldY();
    void setWorldY(int worldY);
    int getTurn();

    void addOrganism(std::shared_ptr<Organism> organism);
    void handleEatingPhase();
    void handleAgingAndPowerPhase();
    void updateAncestorDeathDates(Organism* org);
    void handleRemovalOfDeadOrganisms();
    void handleMovementPhase();
    std::shared_ptr<Organism> createChildOrganism(std::shared_ptr<Organism> parent1, std::shared_ptr<Organism> parent2, const Position& pos);
    void handleReproductionPhase();
    std::vector<std::shared_ptr<Organism>> getAdjacentOrganisms(Position position);

    void makeTurn();

    void writeWorld(const std::string& fileName);
    void readWorld(const std::string& fileName);

    std::string toString();
    std::string organismsToString();

    ~World();
};
