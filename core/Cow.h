#pragma once
#include "Animal.h"

class Cow : public Animal {
public:
    Cow(Position position);
    Cow();
    ~Cow() override;

    std::string toString() const override;
    Organism* reproduce(Position position) override;
};