#include <iostream>
#include "Position.h"
#include "Organism.h"
#include "Plant.h"
#include "Animal.h"
#include "World.h"
#include "Dandelion.h"
#include "Sheep.h"
#include "Grass.h"
#include "Wolf.h"
#include "Amanita.h"
#include "Bear.h"
#include "Cow.h"
#include "Goat.h"
#include "Hare.h"
#include "Pig.h"
#include "Clover.h"
#include "Berries.h"

int main()
{
    World world;

    // Positions
    Position p1{2, 2};
    Position p2{2, 4};
    Position p3{2, 3};
    Position p4{5, 5};
    Position p5{4, 4};

    world.addOrganism(OrganismCreator::createOrganism("G", p1));
    world.addOrganism(OrganismCreator::createOrganism("S", p2));
    world.addOrganism(OrganismCreator::createOrganism("S", p3));
    world.addOrganism(OrganismCreator::createOrganism("W", p4));
    world.addOrganism(OrganismCreator::createOrganism("W", p5));

    std::srand(static_cast<unsigned int>(time(0))); // Inicjalizacja generatora liczb losowych

    // Tura 0
    std::cout << world.toString() << std::endl;

    // Tury 1–9
    for (int i = 1; i <= 9; ++i) {
        world.makeTurn();
        
        if (i == 5) {
            world.writeWorld("world.bin");
        }

        std::cout << world.toString() << std::endl;
    }

    world.readWorld("world.bin");
	std::cout << world.toString() << std::endl;

    return 0;
}
