#ifndef __WIZARD
#define __WIZARD

#include <string>
#include "entity.hpp"

namespace lab3 {
	
	class Wizard : public Entity {
		protected:
			
			float current_mana, max_mana;			

		
		public:
			
			Wizard(std::string n, float hp, float mp, int ap, int d, std::vector<std::vector<Environment*>> &m);
			Wizard(Wizard const &other);
			
			void die();
			void action();				
	};
}
#endif
