#pragma once
#include "Animal.h"

class Goat : public Animal {
public:
    Goat(Position position);
    Goat();
    ~Goat() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};