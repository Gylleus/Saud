#include "entity.hpp"
#include "item.hpp"
#include <iostream>

namespace lab3 {

	Item::Item(std::string n, std::string d, int w, int v) : 
		_name(n), _description(d), _weight(w), _value(v) {}
	
	bool Item::operator==(Item const &other) const {
		return _name == other.name();
	}
	
	bool Item::operator!=(Item const &other) const {
		return !(*this==other);
	}
	
	bool Item::use(Entity* actor) {
		std::cout << "Cannot use " << _name << ".\n";
		return false;
	}
	
}
