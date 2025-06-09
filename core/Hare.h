#pragma once
#include "Animal.h"

class Hare : public Animal {
public:
    Hare(Position position);
    Hare();
    ~Hare() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};