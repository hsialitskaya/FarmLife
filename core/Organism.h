#pragma once
#include <string>
#include <list>
#include <utility> 
#include "Position.h"

struct AncestorInfo {
    char type;
    std::string species;
    int birthTurn;
    int deathTurn;
    uintptr_t uuid; // Unikalny identyfikator (adres przodka w pamięci)
};

class Organism
{
private:
	int power;
	Position position;
	std::string species;
	char type; // Znak na mapie w konsoli
	int initiative;
    int liveLength;
    int powerToReproduce;
	std::list<AncestorInfo> ancestors;
	std::list<std::weak_ptr<Organism>> descendants;
	std::vector<std::string> edibleSpecies;
	int birth;
	int death = -1;
	Position lastPosition;
	uintptr_t uuid; // Unikalny identyfikator
    static std::unordered_map<uintptr_t, Organism*> registry; // Globalny rejestr


public:
	Organism(int power, Position position, std::string species, char type, int initiative, int liveLength, int powerToReproduce);
	Organism(int power, Position position, int initiative, int liveLength, int powerToReproduce);
	Organism(Position position);
	Organism() : power(0), position(0, 0), species("Organizm"), type('O'), initiative(0), liveLength(0), powerToReproduce(0), ancestors(), edibleSpecies(), birth(0), lastPosition(0,0) {};

	// Konstruktor kopiujący (tworzy nowy Organizm na podstawie innego)
	Organism(const Organism& other);
    // Konstruktor kopiujący z wskaźnika (tworzy nowy Organizm na podstawie wskaźnika do innego)
	Organism(Organism *other);
    // Konstruktor przenoszący (efektywne przenoszenie zasobów z innego Organismu)
    Organism(Organism&& other) noexcept;
    // Operator przypisania kopiującego (przypisuje jeden organizm do drugiego poprzez kopiowanie)
    Organism& operator=(const Organism& other);
    // Operator przypisania przenoszącego (przypisuje jeden organizm do drugiego poprzez przeniesienie zasobów)
    Organism& operator=(Organism&& other) noexcept;
	// Destruktor do oczyszczania zasobów przy zniszczeniu obiektu Organism
    virtual ~Organism(); 


	int getPower() const;
	void setPower(int power);

	Position getPosition() const;
	void setPosition(Position position);

	std::string getSpecies() const;
	void setSpecies(std::string spec);

	char getType() const;
	void setType(char spec);

	int getInitiative() const;
    void setInitiative(int initiative);

    int getLiveLength() const;
    void setLiveLength(int liveLength);

    int getPowerToReproduce() const;
    void setPowerToReproduce(int powerToReproduce);

	const std::list<AncestorInfo>& getAncestors() const;
	//void addAncestorWhenBorn(Organism* ancestor, int birthTurn);
	void addAllAncestor(const AncestorInfo& ancestor); 
	//void updateAncestorsDeathDates();
	std::string ancestorsToString() const;

	int getBirth() const;
	void setBirth(int t_birth);

	int getDeath() const;
	void setDeath(int t_death);

	Position getLastPosition() const;
	void setLastPosition(Position position);

	const std::vector<std::string>& getEdibleSpecies() const;
	void setEdibleSpecies(const std::vector<std::string>& species);
	void updateEdibleSpecies(const std::string& spec);
	void eatAdjacent(const std::vector<std::shared_ptr<Organism>>&);

	void addDescendant(std::shared_ptr<Organism> descendant);
	void notifyDescendantsAboutDeath(uintptr_t deadAncestorUUID, int deathTurn) ;

	uintptr_t getUUID() const { return uuid; }

	// Czyste metody wirtualne do implementacji w klasach pochodnych
	virtual bool isAnimal() const = 0;
	virtual std::string toString() const = 0;
	virtual void move(int dx, int dy) = 0;
	virtual Organism* reproduce(Position position) = 0;

};