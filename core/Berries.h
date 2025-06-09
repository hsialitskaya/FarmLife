#pragma once
#include "Plant.h"

class Berries : public Plant {
public:
    Berries(Position position);
    Berries();
    ~Berries() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};