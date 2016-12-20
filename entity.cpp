#include "constants.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "environment.hpp"
#include "key.hpp"

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace lab3 {

	Entity::Entity(std::string t, std::string n, float hp, int ap, int d, std::vector<std::vector<Environment*>> &m) : 
	_type(t), _name(n), _current_health(hp), _max_health(hp), _defense(d), _attack_power(ap), _world_map(m) {		
		std::srand(std::time(0));
		_coords = std::pair<int,int>(0,0);
		_dialog = _name + " does not want to talk.";
	}
	
	Entity::Entity(Entity const &other, std::vector<std::vector<Environment*>> &m) : _world_map (m) {
		std::srand(std::time(0));
		_defense = other.defense();
		_attack_power = other.attack_power();
		_name = other.name();
		_type = other.type();
		_dialog = other.dialog();
		_description = other.description();
		_current_health = other.current_health();
		_max_health = other.max_health();
		_world_map = other.world_map();
		_gold = other.gold();
	}
	
	Entity::~Entity() {
		for (size_t i = 0; i < _inventory.size(); i++) {
			delete(_inventory[i]);
		}
	}
	
	int Entity::attack_damage() const {
		if (_equipped_weapon == nullptr) return _attack_power/2 + rand() % _attack_power;
		return _attack_power + _equipped_weapon->_min_damage + rand() % (_equipped_weapon->_max_damage - _equipped_weapon->_min_damage);
	}
	
	int Entity::defense() const {
		int def = _defense;
		for (auto a : _equipped_armor) {
			def += a->_defense;
		}
		return def;
	}
	
	bool Entity::damage(float const amount) {
		return damage(amount,nullptr);
	}
	
	bool Entity::damage(float const amount, Entity* attacker) {
		_current_health -= amount;
		if (_current_health <= 0)
			die(attacker);
		return false;
	}	
	
	void Entity::add_health(float const amount) {
		float real_amount = std::min(_current_health+amount, _max_health) - _current_health;
		if (amount >= 0) {
			std::cout << "Healed for " << real_amount << ".\n";
			_current_health+=real_amount;
		} else {
			std::cout << "Took " << -real_amount << " damage.\n";
			damage(-real_amount);
		}
	}

	void Entity::add_damage(int const amount) {
		_attack_power += amount;
	}
	
	void Entity::add_gold(const int amount) { 
		std::cout << "Gained " << amount << " gold.\n";
		_gold+=amount; 
	}
	
	void Entity::set_coords(const std::pair<int,int> c) {
		_coords = c;
		_world_map[c.first][c.second]->enter(this);
	}
	
	void Entity::set_coords(const int x, const int y) {
		set_coords(std::pair<int,int>(x,y));
	}

//////////////////////////     Action functions        ////////////////////////////////s

	/* Looks in the inventory for a specified item. 
	 * If it is found, return its pointer. If not return nullptr */
	Item* Entity::get_inventory_item(std::string const name) const {
		for (auto i : _inventory) {
			if (i->name() == name) return i;
		}
		return nullptr;
	}
	
	// Picks up an item and adds it to the inventory
	void Entity::pick_up(Item *item) {
		std::cout << _name << " picked up " << item->name() << ".\n";
		_inventory.push_back(item);
		item->on_pickup(*this);
	}
	
	// Drops an item an removes it from the inventory
	void Entity::remove_item(Item *item) {
		for (size_t i = 0; i < _inventory.size(); ++i) {
			if (item == _inventory[i]) {
				unequip_weapon(item);
				unequip_armor(item);
				_inventory.erase(_inventory.begin() + i);
			}
		}
	}
	
	void Entity::drop(Item* item) {
		remove_item(item);
		delete(item);
	}
	
	// Equips a weapon that is in inventory
	void Entity::equip_weapon(Weapon* item) {
		unequip_weapon(_equipped_weapon);
		std::cout << _name << " equipped " << item->name() << ".\n";
		_equipped_weapon = item;
	}
	
	// Equips a piece of armor that is in inventory
	void Entity::equip_armor(Armor* armor) {
		unequip_armor(armor);
		std::cout << _name << " equipped " << armor->name() << ".\n";
		_equipped_armor.push_back(armor);
	}

	void Entity::unequip_armor(Item* item) {
		for (size_t i = 0; i < _equipped_armor.size(); i++) {
			if (item == _equipped_armor[i]) {
				std::cout << "Unequipped " << _equipped_armor[i]->name() << ".\n";
				_equipped_armor.erase(_equipped_armor.begin()+i);
				break;
			}
		}	
	}
	
	void Entity::unequip_weapon(Item* item) {
		if (_equipped_weapon != nullptr && item == _equipped_weapon) {
			std::cout << _name << " unequipped " << item->name() << ".\n";
			_equipped_weapon = nullptr;
		}
	}
	
	void Entity::die(Entity *killer) {
		if (killer == nullptr) return;
		std::cout << killer->name() << " has slain " << _name << "!\n";
		if (_gold > 0) {
			std::cout << killer->name() << " looted " << _gold << " gold.\n";
			killer->add_gold(_gold);
		}
		for (auto i : _inventory) {
			killer->pick_up(i);
		}
		_inventory.clear();
		_dead = true;
	}

	void Entity::print_inventory() const {
		int nl = 4; int dl = 11; int wl = 6; int vl = 5;
		for (auto i : _inventory) {
			nl = std::max(nl,(int)i->name().length());
			dl = std::max(dl,(int)i->description().length());
			wl = std::max(wl,(int)std::to_string(i->weight()).length());
			vl = std::max(vl,(int)std::to_string(i->value()).length());
		}
		std::cout << std::left << std::setw(nl+3) << "Name" << std::setw(dl+3) << "Description" << std::setw(vl+3) << "Value" << std::setw(wl+3) << "Weight" << '\n';
		for (int i = 0; i < nl+dl+wl+vl+15; i++) std::cout << "_";
		std::cout << "\n";
		for (auto i : _inventory) {
			std::cout << std::left << std::setw(nl+3) << i->name() << std::setw(dl+3) << i->description() << std::setw(vl+3) << i->value() << std::setw(wl+3) << i->weight() << '\n';
			if (typeid(*i) == typeid(Equippable)) {
				Equippable* e = static_cast<Equippable*>(i);
				if (e->_mana_bonus > 0 || e->_health_bonus > 0 || e->_spell_damage > 0) {
					std::cout << "\t Increases ";
					if (e->_mana_bonus > 0) {
						std::cout << " mana by " << e->_mana_bonus;
					}
					if (e->_health_bonus > 0) {
						std::cout << " health by " << e->_health_bonus;
					}
					if (e->_spell_damage > 0) {
						std::cout << " spell damage by " << e->_spell_damage;
					}
					std::cout << ".\n";
				}
			}
		}
	}

//////////////////////////     Command functions           ////////////////////////////////

	//Explores a zone, leading to a random encounter
	bool Entity::explore(std::vector<std::string> words) {
		_world_map[_coords.first][_coords.second]->explore(this);
		return true;
	}	
	
	// Prints the current stats of the actor
	bool Entity::print_stats(std::vector<std::string> words) {
		std::cout << "STATS:\n";
		std::cout << _current_health << "/" << _max_health << " HP\n";
		if (_equipped_weapon != nullptr) std::cout << _attack_power+_equipped_weapon->_min_damage << "-" << _attack_power+_equipped_weapon->_max_damage << " attack  ";
		else std::cout << (int)(_attack_power/2) << "-" << (int)(1.5f*_attack_power) << "  ";
		std::cout << defense() << " defense\n";
		std::cout << _gold << " gold\n";
		return false;
	}
	
	//Use an item, consuming it in the process
	bool Entity::use(std::vector<std::string> words) {
		// If the actor only typed "use"
		if (words.size() < 2) {
			std::cout << "Use what?\n";
		} else {
			bool item_found = false;
			for (auto i : _inventory) {
				// Search for the item
				if (i->name() == words[1]) {
					// Use the item
					if (i->use(this)) {
						// If the used item is a key, unlock the door.
						if (typeid(*i) == typeid(Key)) {
							_world_map[_coords.first][_coords.second]->_locked_direction = "";
							std::cout << "The lock clicks open!\n";
						}
						// If the item is consumable, remove it.
						drop(i);
					}
					item_found = true;
					return true;
				}
			}
			if (!item_found) std::cout << "No item called " << words[1] << " in inventory.\n";
		}
		return false;
	}
	
	bool Entity::inventory(std::vector<std::string> words) {
		if (_equipped_weapon != nullptr) std::cout << "Equipped Weapon: " << _equipped_weapon->name() << "\n";
		for (auto a : _equipped_armor) {
			std::cout << "Equipped " << a->_slot << ": " << a->name() << "\n";
		}
		print_inventory();
		return false;
	}
	
	bool Entity::attack(std::vector<std::string> words) {
		if (words.size() < 2) {
			std::cout << "Attack what?\n";
		} else {
			Entity* opponent = _world_map[_coords.first][_coords.second]->get_actor(words[1]);
			if (opponent == nullptr) {
				std::cout << "Nothing named " << words[1] << " here.\n";
			}
			else {
				float damage_amount = attack_damage() * (1 - 0.06f * opponent->defense()/(1+(0.06f*opponent->defense())));
				std::cout << _name << " hits " << opponent->name() << " for " << (int)damage_amount << ".\n";
				opponent->damage(damage_amount, this);
				return true;
			}
		}
		return false;
	}
	
	// Equip a specified item
	bool Entity::equip(std::vector<std::string> words) {
		for (auto i : _inventory) {
			if (i->name() == words[1]) {
				if (typeid(*i) == typeid(Weapon)) {
					Weapon* weapon = static_cast<Weapon*>(i);
					equip_weapon(weapon);
					return false;
				}
				if (typeid(*i) == typeid(Armor)) {
					Armor* armor = static_cast<Armor*>(i);
					equip_armor(armor);
					return false;
				}
				std::cout << "Cannot equip " << i->name() << "\n";
				return false;
			}
		}
		std::cout << "No item called " << words[1] << " to equip.\n";
		return false;
	}
		
	
	bool Entity::talk_to(std::vector<std::string> words) {
		if (words.size() < 2) {
			std::cout << "Talk to who?\n";
			return false;
		}
		Entity* character = _world_map[_coords.first][_coords.second]->get_actor(words[1]);
		if (character != nullptr) {
			std::cout << character->dialog() << '\n';
		} else {
			std::cout << "No one here named " << words[1] << ".\n";
		}
		return false;
	}
	
	bool Entity::sell(std::vector<std::string> words) {
		if (words.size() < 2) {
			std::cout << "Sell what?\n";
			return false;
		}
		Entity* shop_keeper = _world_map[_coords.first][_coords.second]->get_actor("Vendor");
		if (shop_keeper != nullptr) {
			for (auto i : _inventory) {
				if (i->name() == words[1]) {
					std::cout << "Sold " << i->name() << ".\n";
					add_gold(i->value());
					drop(i);
				}
			}
		} else {
			std::cout << "No one here to sell to.\n";
		}
		return false;
	}
	
	bool Entity::buy(std::vector<std::string> words) {
		if (words.size() < 2) {
			std::cout << "Buy what?\n";
			return false;
		}
		std::vector<Entity*> actors = _world_map[_coords.first][_coords.second]->actors();
		for (auto a : actors) {
			// If the actor can buy items
			if (a->type() == "Vendor") {
				// If the vendor has the specified item
				Item* item = a->get_inventory_item(words[1]);
				if (item != nullptr) {
					// FIXA, KOMMER VARA SAMMA PEKARE SOM TILL VENDORNS
					if (item->value() > _gold) {
						std::cout << "Not enough gold.\n";
					} else {
						std::cout << "Bought " << item->name() << " for " << item->value() << " gold.\n";
						_gold -= item->value();
						pick_up(item);
						a->remove_item(item);
					}
					return false;
				}
			}
		}
		std::cout << "Cannot purchase " << words[1] << " here.\n";
		return false;
	}	
	
	bool Entity::go(std::vector<std::string> words) {
		Environment ce = *_world_map[_coords.first][_coords.second];
		// 0 = north, 1 = east, 2 = south, 3 = west
		if (words[1] == ce._locked_direction) {
			std::cout << "Locked. Cannot go this direction.\n";
			return false;
		}

		if (words[1] == "north" && ce._possible_directions[north]) {
			_coords.first -= 1;
		}
		else if (words[1] == "northeast" && ce._possible_directions[northeast]) {
			_coords.first -= 1;
			_coords.second += 1;
		}
		else if (words[1] == "east" && ce._possible_directions[east]) {
			_coords.second += 1;
		}
		else if (words[1] == "southeast" && ce._possible_directions[southeast]) {
			_coords.first += 1;
			_coords.second += 1;
		}
		
		else if (words[1] == "south" && ce._possible_directions[south]) {
			_coords.first += 1;
		}
		else if (words[1] == "southwest" && ce._possible_directions[southwest]) {
			_coords.first += 1;
			_coords.second -= 1;
		}
		else if (words[1] == "west" && ce._possible_directions[west]) {
			_coords.second -= 1;
		}
		else if (words[1] == "northwest" && ce._possible_directions[northwest]) {
			_coords.first -= 1;
			_coords.second -= 1;
		} else {
			std::cout << "Go where?\n";
			return false;
		}
		if (ce._area_type != _world_map[_coords.first][_coords.second]->_area_type) std::cout << "Entered " << _world_map[_coords.first][_coords.second]->_area_type << "\n";
		ce.leave(this);
		_world_map[_coords.first][_coords.second]->enter(this);	
		return true;
	}
}
