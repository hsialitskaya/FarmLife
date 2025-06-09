#pragma once
#include "Plant.h"

class Dandelion : public Plant {
public:
    Dandelion(Position position);
    Dandelion();
    ~Dandelion() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};