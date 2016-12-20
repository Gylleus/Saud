#ifndef __ENVIRONMENT
#define __ENVIRONMENT

#include <string>
#include <vector>

namespace lab3 {
	
	class Entity;
	
	class Environment {
		
		
		
		protected:
		std::vector<void (*)(Entity *actor)> random_encounters;
		std::vector<std::string> commands;
		std::vector<Entity*> _actors;
		
		
		public:
		
		Environment(std::string area_type, std::string d, std::pair<int,int> coords);
		
		bool _possible_directions[8] = {false,false,false,false,
			false,false,false,false};
		std::string _locked_direction = "";
		
		virtual ~Environment() {};
		const std::string _area_type;
		const std::string _description;
		const std::pair<int,int> _coords;
		
		
		Environment& operator=(Environment const &other);
		
		
		void print_directions() const;
		std::string description() const { return _description; };
		void check_neighbours(std::vector<std::vector<Environment*>> const &map);
		void add_encounter(void (*func)(Entity*)) {random_encounters.push_back(func);};
		void random_encounter(Entity *actor);
		std::vector<Entity*> actors() const { return _actors; };
		Entity* get_actor(std::string const name) const;
		
		virtual void enter(Entity *actor);
		virtual void leave(Entity const *actor);
		virtual void explore(Entity *actor);
		
		
	};
}

#endif


#ifndef __OOB
#define __OOB

namespace lab3 {
	
	class Oob : public Environment {		
		
		public:
			Oob(std::pair<int,int> const c);
	};
}
#endif
