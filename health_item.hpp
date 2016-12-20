#ifndef __HEALTHITEM
#define __HEALTHITEM

#include <string>
namespace lab3 {
	
	class Item;
	
	class HealthItem : public Item {		
		
		const float _heal_amount;
		
		public:
			HealthItem(std::string n, std::string d, int w, int v, float a);
			
			bool use(Entity* actor);
			std::string description() const;

	};
}
#endif
