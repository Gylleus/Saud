#ifndef __ITEM
#define __ITEM

#include <string>
#include <vector>
#include "entity.hpp"

namespace lab3 {

	class Entity;
	
	class Item {
		
		protected:
			
			std::string _name, _description;			
			int _weight;
			int _value;
			
		public:
		
			Item(std::string n, std::string d, int w, int v);
			virtual ~Item() {};
			
			bool operator==(Item const &other) const;
			bool operator!=(Item const &other) const;
		
			std::string name() const { return _name; };
			virtual std::string description() const { return _description; };
			
			int weight() const { return _weight; };
			int value() const { return _value; };
			
			virtual void on_pickup(Entity &ent) {};
			virtual bool use(Entity* actor);
	};
	
	class Equippable : public Item {
		public:
			int _mana_bonus, _health_bonus, _spell_damage;
		Equippable(std::string n, std::string d, int w, int v) : Item(n,d,w,v) {
			_mana_bonus = 0;
			_health_bonus = 0;
			_spell_damage = 0;
		};

	};
	
	class Weapon : public Equippable {
		public:
		int _min_damage, _max_damage;
		Weapon(std::string n, std::string d, int w, int v, int min, int max) :
			Equippable(n,d,w,v), _min_damage(min), _max_damage(max) {};
		std::string description() const { return std::to_string(_min_damage) + "-" + std::to_string(_max_damage) + " damage";};
	};
	
	class Armor : public Equippable {
		public:
		int _defense;
		std::string _slot;
		Armor(const std::string n, const std::string d, const int w, const int v, const int def, const std::string s) :
			Equippable(n,d,w,v), _defense(def), _slot(s) {};
		std::string description() const { return std::to_string(_defense) + " armor  (" + _slot + ")"; };
	};
}
#endif
