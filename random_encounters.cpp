#include <cstdlib>
#include <ctime>
#include <iostream>
#include "entity.hpp"
#include "item.hpp"
#include "health_item.hpp"


namespace lab3 {
	
	void loose_rock(Entity *actor) {
		std::srand(std::time(0));
		int gold_amount = 40 + rand() % 80;
		actor->add_gold(gold_amount);
		std::cout << "You come across an odd looking boulder and decide to push it, revealing a hidden stash of " 
		<< gold_amount << " gold.\n";
	}
	
	void goblin_rock(Entity *actor) {
		std::srand(std::time(0));
		int damage_amount = 5 + rand() % 10;
		actor->damage(damage_amount);
		std::cout << "A goblin throws a rock in your head!\n";
		std::cout << "You take " << damage_amount << " damage.\n";
	}
	
	void apple_tree(Entity* actor) {
		std::cout << "You find an apple tree and decide to pick one of the fruits.\n";
		actor->pick_up(new HealthItem("Apple", "", 1, 5, 7));
	}
	
	void odd_mushroom(Entity* actor) {
		std::cout << "You come across a funky looking mushroom and decide to pick it up.\n";
		std::srand(std::time(0));
		actor->pick_up(new HealthItem("Funky Mushroom", "Not really sure if poisonous or healthy", 1, 20, -7 + std::rand()%22));
	}
	
	void rusty_sword(Entity* actor) {
		std::cout << "You find a rusty sword burrowed in the mud.\n";
		actor->pick_up(new Weapon("Rusty Sword", "A corroded steel sword", 5, 25, 7, 12));
	}
	
	void fallen_knight(Entity* actor) {
		std::cout << "You come across the corpses of several bandits and a knight in armor. He obviously did not go down without a fight.\n";
		std::cout << "The knight's gear is in pretty bad shape, except for his headgear.\n"; 
		std::cout << "You give him a proper burial and take his helmet as payment.\n";
		actor->pick_up(new Armor("Knight Sallet", "Forged in shining steel", 7, 110, 7, "Head"));
	}
	
	void faerie_pond(Entity* actor) {
		std::cout << "You come to a small pond and are greeted by a sparkling faerie.\n";
		std::cout << "Glad to have a visitor, she offers to heal some of your wounds\n";
		actor->add_health(actor->max_health()/3);
	}
	
	
	void ancient_tomb(Entity* actor) {
		std::cout << "You have stumbled upon an ancient tomb.\n";
		std::cout << "It seems to have been untouched for centuries.\n";
		std::vector<std::string> words;
		while (words.size() == 0 || (words[0] != "open" && words[0] != "leave")) {
			std::cout << "open/leave?\n";
			getPlayerCommand(words);
		}
		
		if (words[0] == "open") {
			create_actor(create_ancient_ghoul, "Ancient Ghoul", actor->coords().first, actor->coords().second);
			std::cout << "Disturbed in his rest the buried warrior rises and attacks you!\n";
		}
	}

	void forest_spring(Entity* actor) {
		std::cout << "Within the trees you come across a spring sparkling with energy.\n";
		std::cout << "You feel energized as you touch it with your hand.\n";
		int attack_boost = 2;
		std::cout << "Permanently added " << attack_boost << " attack power.\n";
		actor->add_damage(attack_boost);
	}

	void bark_shield(Entity* actor) {
		std::cout << "You find a perfectly circular piece of bark by a seemingly ancient tree.\n";
		std::cout << "The bark appears impervious to blows.\n";
		actor->pick_up(new Armor("Bark Shield", "Made by man or nature?", 4, 55, 7, "Off-hand"));

	}
	
	void find_ent(Entity* actor) {
		std::cout << "Walking through the woods you come across an odd looking tree, with roots shaped into forms of feet.\n";
		create_actor(create_ent, "Ent", actor->coords().first, actor->coords().second);		
	}

}
