#ifndef __VENDOR
#define __VENDOR

#include <string>
#include "entity.hpp"


namespace lab3 {
	
	class Environment;
	class Entity;
	
	class Vendor : public Entity {
		
		public:
			Vendor(std::string const name, std::vector<std::vector<Environment*>> &m);
			std::string dialog() const;
			};
	
}
#endif
