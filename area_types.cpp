#include <string>
#include "environment.hpp"
#include "random_encounters.cpp"

namespace lab3 {

	Environment* generate_plains(std::pair<int,int> c) { 
		Environment* area = new Environment("Plains", "Open plains that stretch as far as the eye can see.", c); 
		if (rand() % 7 == 1) area->add_encounter(loose_rock);
		if (rand() % 7 == 1) area->add_encounter(goblin_rock);
		if (rand() % 7 == 1) area->add_encounter(apple_tree);
		if (rand() % 7 == 1) area->add_encounter(odd_mushroom);
		if (rand() % 7 == 1) area->add_encounter(rusty_sword);
		if (rand() % 7 == 1) area->add_encounter(fallen_knight);
		if (rand() % 7 == 1) area->add_encounter(faerie_pond);
		if (rand() % 7 == 1) area->add_encounter(ancient_tomb);
		return area;
	}
	
	Environment* generate_town(std::pair<int,int> c) { 
		Environment* area = new Environment("Town", "Civilized and inhabited area", c); 
		return area;
	}

	Environment* generate_forest(std::pair<int,int> c) { 
		Environment* area = new Environment("Forest", "Thick woods with creatures lurking within.", c); 
		if (rand() % 10 == 1) area->add_encounter(forest_spring);
		if (rand() % 7 == 1) area->add_encounter(loose_rock);
		if (rand() % 4 == 1) area->add_encounter(odd_mushroom);
		if (rand() % 7 == 1) area->add_encounter(bark_shield);
		if (rand() % 7 == 1) area->add_encounter(find_ent);
		return area;
	}

	Environment* generate_gate(std::pair<int,int> c) { 
		Environment* area = new Environment("Gate", "A large gate with a visible keyhole.", c);
		return area;
	}
}
