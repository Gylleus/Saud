#ifndef __KEY
#define __KEY

#include <string>
namespace lab3 {
	
	class Item;
	
	class Key : public Item {		
		
	const std::pair<int,int> _opening_location;

		public:
			Key(std::string n, std::string d, std::pair<int,int> c);
			
			bool use(Entity* actor);
			std::string description() const;

	};
}
#endif
