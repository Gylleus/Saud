#ifndef __ENTITY
#define __ENTITY

#include <string>
#include <vector>
#include <map>

namespace lab3 {

	class Item;
	class Environment;
	class Weapon;
	class Armor;
	
	class Entity {
	
		protected:
		
		std::string _type, _description, _name, _dialog;
		
		Weapon *_equipped_weapon;
		std::vector<Armor*> _equipped_armor;
		float _current_health, _max_health;
		int _defense;
		int _attack_power;
		int _gold = 0;
		std::vector<Item*> _inventory;
		bool _dead = false;
		bool _friendly = false;
		
		std::pair<int,int> _coords;
		std::vector<std::vector<Environment*>> &_world_map;
		
		public:
				
		// Constructors
		Entity(std::string t, std::string n, float hp, int ap, int d, std::vector<std::vector<Environment*>> &m);
		Entity(Entity const &other, std::vector<std::vector<Environment*>> &m);
		
		
		virtual ~Entity();	
	
		// "Get" functions
		std::string type() const { return _type; };
		std::string name() const { return _name; };
		virtual std::string dialog() const { return _dialog; };
		std::string description() const { return _description; };
		std::pair<int,int> coords() const { return _coords; };
		float current_health() const { return _current_health; };
		float max_health() const { return _max_health; };
		int attack_power() const { return _attack_power; };
		int gold() const { return _gold;};
		std::vector<std::vector<Environment*>> world_map() const {return _world_map;};
		bool is_dead() const { return _dead; };
		bool is_friendly() const { return _friendly;};
		
		int attack_damage() const;
		int defense() const;
		Item* get_inventory_item(std::string const name) const;
		
		// Set functions
		void set_description(const std::string d);
		void set_dialog(const std::string d);
		void set_coords(const std::pair<int,int> c);
		void set_coords(const int x, const int y);
		void set_hostile() { _friendly = false; }
		void set_friendly() { _friendly = true; }
	
		void add_gold(const int amount);
		bool damage(float const amount);
		bool damage(float const amount, Entity* attacker);
		void add_health(float const amount);
		void add_damage(int const amount);

		// action functions
		void pick_up(Item *item);
		void drop(Item *item);
		void equip_weapon(Weapon *item);
		void equip_armor(Armor *armor);
		void unequip_weapon(Item *item);
		void unequip_armor(Item *item);
		void print_inventory() const;
		void remove_item(Item* const item);

		virtual void die(Entity *killer);
		
		// command functions
		bool go(std::vector<std::string> words);
		virtual bool print_stats(std::vector<std::string> words);
		bool explore(std::vector<std::string> words);
		bool attack(std::vector<std::string> words);
		bool use(std::vector<std::string> words);
		bool inventory(std::vector<std::string> words);
		bool equip(std::vector<std::string> words);
		bool unequip(std::vector<std::string> words);
		bool sell(std::vector<std::string> words);
		bool buy(std::vector<std::string> words);
		bool talk_to(std::vector<std::string> words);
		
	};
}
#endif
