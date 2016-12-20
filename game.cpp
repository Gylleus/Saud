#include "game.hpp"
#include "constants.hpp"
#include "entity.hpp"
#include "wizard.hpp"
#include "vendor.hpp"
#include "item.hpp"
#include "health_item.hpp"
#include "key.hpp"

#include "environment.hpp"
#include "enemies.cpp"
#include "area_types.cpp"

#include <cstdlib>
#include <ctime>
#include <cmath>

int main() {	

	lab3::game();
	return 0;
}

namespace lab3 {

void game() {
	init();
	std::cout << "\n\n" << lab3::welcome_message << '\n';
	std::cout << "\n\n" << lab3::background_story << '\n';
	
	player = character_creation();
	if (player == nullptr) exit_game();
	player->dialog();
	player->set_coords(start_pos);
	player->pick_up(new Weapon("Dagger", "A short dagger", 3, 15, 2, 7));

	int command_repetitions = 0;
	std::vector<std::string> words;
	
	std::srand(std::time(0));
	
	while (1) {
		check_dead();
		check_win();
		if (command_repetitions == 0) {
				print_map();
				for (auto a : bot_actors) {
				if (a->coords() == player->coords()) std::cout << a->name() << " is here.\n";
			}
			std::cout << prompt << '\n';
			command_repetitions = getPlayerCommand(words)-1;
		} else {
			command_repetitions-=1;
		}
		// If input was given
		if (words.size() > 0) {
			// If the handled command was successful and resulted in the end of the players turn
			if (handle_command(player, words)) {
				// Computers turn
				for (auto a : bot_actors) bot_action(a);
			}
		}
	}
}

bool handle_command(Entity *actor, std::vector<std::string> const &words) {
	cmd_func func = command_functions[words[0]];
	if (func == nullptr) return false;
	return (player->*func)(words);
}


// Reads user input from stdin and stores the separated words in a vector
int getPlayerCommand(std::vector<std::string> &words) {
	words.clear();
	std::cout << ">";
	std::string command;
	getline(std::cin,command);	
	int repetitions = 1;
	
	std::string buf; // Have a buffer string
	std::stringstream ss(command); // Insert the string into a stream
	
	while (ss >> buf)
		words.push_back(buf);
	if (words.size() > 0 && words[0] == "exit") exit_game();
	if (words.size() == 0) return 1;
	
	// If the player wants to repeat the input
	if (words[words.size()-1][0] == '-') {
		words[words.size()-1].erase(0,1);
		repetitions = std::stoi(words[words.size()-1]);
		words.erase(words.end());
	}
	
	// Add all words to index 2 in array
	for (size_t i = 2; i < words.size(); i++) {
		words[1] += " " + words[i];
	}
	return repetitions;
}

void bot_action(Entity* bot) {
	if (bot->is_dead() || bot->is_friendly()) return;
	if (bot->coords() == player->coords()) {
		bot->attack({"attack", player->name()});
	}
	else if (std::abs(bot->coords().first - player->coords().first) <= 1 &&
		std::abs(bot->coords().second - player->coords().second) <= 1
		&& bot->current_health() == bot->max_health()) {
			bot->set_coords(player->coords());
		}
	else if(rand()%3 == 1) {
		int n = 1 + rand() % 7;
		std::string direction = "";
		switch (n) {
			case 1:
				direction = "north";
				break;
			case 2:
				direction = "northeast";
				break;
			case 3:
				direction = "east";
				break;
			case 4:
				direction = "southeast";
				break;
			case 5:
				direction = "south";
				break;
			case 6:
				direction = "southwest";
				break;
			case 7:
				direction = "west";
				break;
			case 8:
				direction = "northwest";
				break;
		}
		bot->go({"go",direction});
	}
}

// Initialize the game
void init() {
	map_creation();
	generate_enemies();
	
	command_functions.insert(std::pair<std::string,cmd_func>("go", &Entity::go));	
	command_functions.insert(std::pair<std::string,cmd_func>("stats", &Entity::print_stats));	
	command_functions.insert(std::pair<std::string,cmd_func>("explore", &Entity::explore));	
	command_functions.insert(std::pair<std::string,cmd_func>("attack", &Entity::attack));	
	command_functions.insert(std::pair<std::string,cmd_func>("use", &Entity::use));	
	command_functions.insert(std::pair<std::string,cmd_func>("inventory", &Entity::inventory));	
	command_functions.insert(std::pair<std::string,cmd_func>("equip", &Entity::equip));	
	command_functions.insert(std::pair<std::string,cmd_func>("sell", &Entity::sell));	
	command_functions.insert(std::pair<std::string,cmd_func>("talk", &Entity::talk_to));	
	command_functions.insert(std::pair<std::string,cmd_func>("buy", &Entity::buy));	
		
	available_characters.push_back("Warrior");
	available_characters.push_back("Thief");
	available_characters.push_back("Wizard");
}

// Initializes the map and areas
void map_creation() {
	generate_areas();
	for (int x = 0; x < map_x_size; ++x) {
		world_map.emplace_back(std::vector<Environment*>());
		for (int y = 0 ; y < map_y_size; ++y) {
			world_map[x].emplace_back(new Oob(std::pair<int,int>(x,y)));
		}
	}
	
	for (auto a : areas) {
		insert_area(a);
	}
	
	for (int x = 0; x < map_x_size; ++x) {
		for (int y = 0 ; y < map_y_size; ++y) {
			world_map[x][y]->check_neighbours(world_map);
		}
	}
	
}

//Insert a new area into the world map, deleting the old area and its memory.
void insert_area(Environment* const &area) {
		int x = area->_coords.first;
		int y = area->_coords.second;
		delete world_map[x][y];
		world_map[x][y] = area;
}

// Handles the exiting of the game
void exit_game() {
	std::cout << "Exiting... \n";
	for (int x = 0; x < map_x_size; ++x) {
		for (int y = 0 ; y < map_y_size; ++y) {
			delete world_map[x][y];
		}
	}
	for (auto a : bot_actors) delete(a);
	delete(player);
	std::cout << "Goodbye!\n";
	exit(EXIT_SUCCESS);
}

void check_dead() {
	if (player->is_dead()) exit_game();
	for (size_t i = 0; i < bot_actors.size(); i++) {
		Entity* a = bot_actors[i];
		if (a->is_dead()) {
			world_map[a->coords().first][a->coords().second]->leave(a);
			delete(a);
			bot_actors.erase(bot_actors.begin() +i);
			i--;
		} 
	}
}

void check_win() {
	if (player->coords() == std::pair<int,int>(7,9)) {
		std::cout << "Congratulations!\nYou win!\n";
		exit_game();
	}
}

// Prints the world map using ASCII signs.
void print_map() 
{
	for (int x = 0; x < map_x_size; ++x) 
	{
		for (int y = 0 ; y < map_y_size; ++y) 
		{
			// Check if the player is here
			if (x == player->coords().first && y == player->coords().second) 
			{
				std::cout << "X";
				continue;
			}
			// Check if any bot is here
			bool bot_here = false;	
			for (auto a : bot_actors) 
			{
				if (x == a->coords().first && y == a->coords().second) 
				{
					std::cout << "o";
					bot_here = true;
					break;
				}		
			}
			if (bot_here) continue;
			if (world_map[x][y]->_area_type != "oob") std::cout << "-";
			else std::cout << "▓";
		}
		std::cout << "\n";
	}
}

// Handles creation of the player and returns it
Entity* character_creation() {
	int index = -1;
	std::string name = "";
	std::vector<std::string> words;
		
	while (words.size() != 1) {
		std::cout << "Choose your name.\n";
		getPlayerCommand(words);
	}
	name = words[0];
	return new Wizard(name, 10000, 10, 3, 0, world_map);
				
	std::cout << "Choose your character!\n";
	
	while(index == -1) {
		std::cout << "Available choices are: \n\n";
		for (auto s : available_characters) {
			std::cout << s << "   ";
		}
		std::cout << "\n";
		
		getPlayerCommand(words);
		if (words.size() > 0) {		
			for (size_t i = 0; i < available_characters.size(); ++i) {
				if (words[0] == available_characters[i]) index = i;
			}  
		}
		
		switch(index)  {
			case 0 : 
				break;
			case 1 : 
				break;
			case 2 : 
				return new Wizard(name, 100, 10, 1, 0, world_map);
				break;
			}
		std::cout << "Invalid choice. Please note that input is case sensitive." << '\n';	
	}
	
	return nullptr;
}

// Define the playable map area
void generate_areas() {
	for (size_t i = 0; i < 5; i++) {
		for (size_t j = 0; j < 7; j++) {
			areas.push_back(generate_plains(std::pair<int,int>(i,j)));
		}
	}
	areas.push_back(generate_town(std::pair<int,int>(5,3)));
	for (size_t i = 6; i < 9; i++) {
		for (size_t j = 1; j < 8; j++) {
			areas.push_back(generate_forest(std::pair<int,int>(i,j)));
		}
	}
	Environment* g = generate_gate(std::pair<int,int>(7,8));
	g->_locked_direction = "east";
	areas.push_back(g);
	areas.push_back(generate_town(std::pair<int,int>(7,9)));
}

void generate_enemies() {
	create_actor(create_spider, "Red Spider", 3,3);
	create_actor(create_deer, "Deer", 0,5);
	create_actor(create_hans, "Fisherman Hans", 5, 3);
	create_actor(create_keywarden, "Warden Zuth", 7, 2);
	
}

void create_actor(Entity* (*func)(std::string), const std::string name, int x, int y) {
	Entity* actor = func(name);
	actor->set_coords(x,y);
	bot_actors.push_back(actor);
} 

}
