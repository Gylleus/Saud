#include "wizard.hpp"
#include "item.hpp"

namespace lab3 {
	
	Wizard::Wizard(std::string n, float hp, float mp, int ap, int d, std::vector<std::vector<Environment*>> &m) : 
	Entity("Wizard",n,hp,ap,d,m), current_mana(mp), max_mana(mp) 	{
		
			_description = "An old man that devoted his life to magic after realising that programming was too much work. He also has a really bad breath.";
		
		}
	
	void Wizard::die() {
		exit(EXIT_SUCCESS);
	}
	
	void Wizard::action() {
		
	}
	
	
}
