#include "item.hpp"
#include "health_item.hpp"
#include <iostream>


namespace lab3 {

	HealthItem::HealthItem(std::string n, std::string d, int w, int v, float a) :
		Item(n,d,w,v), _heal_amount(a) {}
		
	bool HealthItem::use(Entity* actor) {
		std::cout << actor->name() << " used " << _name << ".\n";			
		actor->add_health(_heal_amount);
		return true;
	}
	
	std::string HealthItem::description() const { 
		if (_description != "") return _description;
		return "Heals " + std::to_string((int)_heal_amount) + " health.";
	};

}
