#pragma once
#include "Plant.h"

class Amanita : public Plant  {
public:
    Amanita(Position position);
    Amanita();
    ~Amanita() override;

    std::string toString() const override; 
    Organism* reproduce(Position position) override;
};
