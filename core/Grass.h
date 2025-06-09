#pragma once
#include "Plant.h"

class Grass : public Plant {
public:
    Grass(Position position);
    Grass();
    ~Grass() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};