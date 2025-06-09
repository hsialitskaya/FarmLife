#pragma once
#include "Plant.h"

class Clover : public Plant {
public:
    Clover(Position position);
    Clover();
    ~Clover() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};