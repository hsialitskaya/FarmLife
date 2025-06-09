#pragma once
#include "Animal.h"

class Sheep : public Animal {
public:
    Sheep(Position position);
    Sheep();
    ~Sheep() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};