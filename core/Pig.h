#pragma once
#include "Animal.h"

class Pig : public Animal {
public:
    Pig(Position position);
    Pig();
    ~Pig() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};