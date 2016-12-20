#include <cstdlib>
#include <ctime>
#include <iostream>
#include "environment.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "constants.hpp"

namespace lab3 {

	Environment::Environment(std::string t, std::string d, std::pair<int,int> c) :
		 _area_type(t), _description(d), _coords(c) {
			}
	
	Oob::Oob(std::pair<int,int> const c) : Environment("oob", "How did you get here?", c) {}
	
	void Environment::enter(Entity *actor) {
		_actors.push_back(actor);
	}
	
	void Environment::leave(Entity const *actor) {
		for (size_t i = 0; i < _actors.size(); ++i) {
			if (_actors[i] == actor) _actors.erase(_actors.begin() + i);
		}	
	}
	
	void Environment::explore(Entity *actor) {
		if (random_encounters.size() > 0) {
			random_encounter(actor);
		}
		else {
			std::cout << "You explore the area but find nothing of interest.\n";
		}
	}
	
	void Environment::random_encounter(Entity *actor) {
		std::srand(std::time(0));		
		size_t func_index = rand() % random_encounters.size();
		void (*func)(Entity *actor) = random_encounters[func_index];
		func(actor);
		random_encounters.erase(random_encounters.begin() + func_index);
	}
	
	Entity* Environment::get_actor(std::string const name) const {
		for (auto a : _actors) {
			if (a->name() == name || a->type() == name) return a;
		}
		return nullptr;
	}
	
	void Environment::print_directions() const {
		if (_possible_directions[north]) std::cout << "north ";
		if (_possible_directions[northeast]) std::cout << "northeast ";
		if (_possible_directions[northwest]) std::cout << "northwest ";		
		if (_possible_directions[east]) std::cout << "east ";
		if (_possible_directions[west]) std::cout << "west ";
		if (_possible_directions[southeast]) std::cout << "southeast ";
		if (_possible_directions[south]) std::cout << "south ";
		if (_possible_directions[southwest]) std::cout << "southwest ";
	}
		
	void Environment::check_neighbours(std::vector<std::vector<Environment*>> const &map) {
		int x = _coords.first;
		int y = _coords.second;
		int x_max = map.size();
		if (x_max > 0) {
			int y_max = map[x].size();
			if (y_max > 0) {
				// -x = north, +x = south
				// -y = west, +y = east
				if (x > 0 && map[x-1][y]->_area_type != "oob") _possible_directions[north] = true;
				if (x > 0 && y < y_max-1 && map[x-1][y+1]->_area_type != "oob") _possible_directions[northeast] = true;
				if (y < y_max-1 && map[x][y+1]->_area_type != "oob") _possible_directions[east] = true;
				if (x < x_max-1 && y < y_max-1 && map[x+1][y+1]->_area_type != "oob") _possible_directions[southeast] = true;
				if (x < x_max-1 && map[x+1][y]->_area_type != "oob") _possible_directions[south] = true;
				if (x < x_max-1 && y > 0 && map[x+1][y-1]->_area_type != "oob") _possible_directions[southwest] = true;
				if (y > 0 && map[x][y-1]->_area_type != "oob") _possible_directions[west] = true;
				if (x > 0 && y > 0 && map[x-1][y-1]->_area_type != "oob") _possible_directions[northwest] = true;
			}
		}
	}
}
