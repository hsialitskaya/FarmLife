#pragma once
#include "Organism.h"

class Plant : public Organism
{
	public:
		Plant(int power, Position position, int initiative, int liveLength, int powerToReproduce);
		Plant(Position position);
		Plant();
		~Plant() override;

		bool isAnimal() const override { return false; } 
		void move(int dx, int dy) override;
		std::string toString() const override;

		// Czysta metoda wirtualna do implementacji w klasach pochodnych
		virtual Organism* reproduce(Position position) override = 0;
};

