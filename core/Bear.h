#pragma once
#include "Animal.h"

class Bear : public Animal {
public:
    Bear(Position position);
    Bear();
    ~Bear() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};