#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>


namespace lab3 {
	
	class Entity;
	class Environment;
	class Oob;
	
	//typedef std::function<void(std::vector<std::string>)> cmd_func;
	typedef bool (Entity::*cmd_func)(std::vector<std::string>);
	std::map<std::string,cmd_func> command_functions;
	std::vector<std::string> commands;

	Entity * player;
	
	
	const int map_x_size = 10;
	const int map_y_size = 15;
	
	std::pair<int,int> start_pos(1,5);
	std::vector<std::vector<Environment*>> world_map;
	std::vector<Entity*> bot_actors;
	std::vector<Environment*> areas;
	
	int getPlayerCommand(std::vector<std::string> &words);
	Entity * character_creation();

	const std::string prompt = "What do you choose to do?";
	const std::string welcome_message = "Welcome to kingdom of Saud!";
	const std::string background_story = "You are on an important errand given by the king himself.\nYou have to make it to the town across the plains and the forest, to deliver an important message.\nGood luck!";
	
	std::vector<std::string> available_characters;

	void game();
	bool handle_command(Entity *actor, std::vector<std::string> const &words);
	void check_dead();
	void check_win();
	void bot_action(Entity* bot);
	
	void insert_area(Environment* const &a);
	void map_creation();
	void print_map();
	void generate_areas();
	void init();
	void generate_enemies();
	void create_actor(Entity* (*func)(std::string), const std::string name, const int x, const int y);
	
	
	void exit_game();
	
}
