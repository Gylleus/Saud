#include <iostream>
#include <vector>

#include "vendor.hpp"
#include "environment.hpp"

namespace lab3 {
	
	Vendor::Vendor(std::string const name, std::vector<std::vector<Environment*>> &m) 
			: Entity("Vendor", name, 5, 1, 0, m) {}
	
	
	std::string Vendor::dialog() const {
		std::cout << _dialog << "\nTake a look at my wares: \n";
		print_inventory();
		return "";
	}
}
