namespace lab3 {
	
	Entity* create_hans(const std::string name = "Menkers") {
		Entity* actor = new Vendor(name, world_map);
		actor->set_friendly();
		actor->pick_up(new HealthItem("Salmon", "", 2, 12, 15));
		actor->pick_up(new HealthItem("Salmon", "", 2, 12, 15));
		actor->pick_up(new HealthItem("Salmon", "", 2, 12, 15));
		actor->pick_up(new HealthItem("Prawns", "", 1, 20, 25));
		actor->pick_up(new Weapon("Fishing Rod", "", 6, 50, 4, 18));
		return actor;
	}
	
	Entity* create_deer(const std::string name = "Deer") {
		Entity* actor = new Entity("Wild Beast", name, 5, 3, 0, world_map);
		actor->pick_up(new HealthItem("Venison", "Fresh meat", 2, 20, 15));
		actor->set_friendly();
		return actor;
	}
	
	Entity* create_spider(const std::string name = "Spider") {
		Entity* actor = new Entity("Insectoid", name, 18, 40, 2, world_map);
		actor->add_gold(15 + std::rand() % 20);
		actor->pick_up(new Item("Spider Eye", "Used by alchemists or something", 1, 8));
		return actor;
	}

	Entity* create_raptor(const std::string name = "Raptor") {
		Entity* actor = new Entity("Beast", name, 32, 10, 2, world_map);
		actor->add_gold(30 + std::rand() % 30);
		actor->pick_up(new Item("Raptor Claws", "Would look good as a necklace", 1, 20));
		return actor;
	}	
	
	Entity* create_ancient_ghoul(const std::string name = "Ancient Ghoul") {
		Entity* actor = new Entity("Undead", name, 70, 14, 3, world_map);
		actor->add_gold(105 + std::rand() % 130);
		actor->pick_up(new Armor("Bronze Cuirass", "Dusty, but not rusty", 12, 195, 10, "Chest"));
		return actor;
	}	

	Entity* create_ent(const std::string name = "Ent") {
		Entity* actor = new Entity("Monster", name, 70, 14, 3, world_map);
		actor->add_gold(7 + std::rand() % 29);
		Weapon * w = new Weapon("Enchanted Stick", "Infused with mysterious magic", 3, 165, 7, 10);
		w->_mana_bonus = 20;
		actor->pick_up(w);
		return actor;
	}

	Entity* create_keywarden(const std::string name = "Keywarden") {
		Entity* actor = new Entity("Humanoid", name, 32, 8, 3, world_map);
		actor->add_gold(37 + std::rand() % 49);
		actor->pick_up(new Key("Brass Key", "A large metal key", std::pair<int,int>(7,8)));
		return actor;
	}

}
