#pragma 
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<memory>
#include<map>
#include<iostream>
#include<string>
#include<fstream>

class AssetsManager
{
	// Loads and holds resources for game states
	// Loading methods could throw invalid_argument exception

	std::map<std::string, std::unique_ptr<sf::Texture>> textures;
	std::map<std::string, std::unique_ptr<sf::Font>> fonts;
public:
	AssetsManager() {};
	~AssetsManager() {};

	
	// loads textures defined in txt file(only names with extension, one per line) , from textures folder
	void loadTexturesFromFile(const std::string & path, const std::string& texturesFolder);
	// loads resource from path, adds to map by name key 
	void loadTexture(const std::string& name, const std::string& path);
	void loadFont(const std::string& name, const std::string & path);


	sf::Texture *const  getTexture(const std::string& name)const;
	sf::Font *const getFont(const std::string& name)const ;

	//custom error for re-throw when key does not exists in map
	class invalid_map_arg : public std::invalid_argument
	{
	public:
		invalid_map_arg(const std::string& s = "Invalid map argument") :std::invalid_argument(s) {} 
		~invalid_map_arg() noexcept {} //cannot throw exceptions
		
	};
};

