#include "item.hpp"
#include "key.hpp"
#include <iostream>

namespace lab3 {

	Key::Key(std::string n, std::string d, std::pair<int,int> c) :
		Item(n,d,1,0), _opening_location(c) {}
		
	bool Key::use(Entity* actor) {
		if (actor->coords() == _opening_location) {
			std::cout << actor->name() << " used " << _name << ".\n";
			return true;			
		} else {
			std::cout << "There is nothing to unlock with " << _name << " here.\n";
			return false;
		}
	}
	
	std::string Key::description() const { 
		if (_description != "") return _description;
		return "A key likely used to open a door.";
	};

}
