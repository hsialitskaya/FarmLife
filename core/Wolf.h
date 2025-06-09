#pragma once
#include "Animal.h"

class Wolf : public Animal {
public:
    Wolf(Position position);
    Wolf();
    ~Wolf() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};