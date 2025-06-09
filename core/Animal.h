#pragma once
#include "Organism.h"

class Animal : public Organism
{
	public:
		Animal(int power, Position position, int initiative, int liveLength, int powerToReproduce);
		Animal(Position position);
		Animal();
		~Animal() override;

		bool isAnimal() const override { return true; }
		void move(int dx, int dy) override;
		std::string toString() const override;

		// Czysta metoda wirtualna do implementacji w klasach pochodnych
		virtual Organism* reproduce(Position position) override = 0;
};

