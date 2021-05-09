#include "AssetsManager.h"


void AssetsManager::loadTexturesFromFile(const std::string& path, const std::string& texturesFolder)
{
    std::fstream file(path);
    if (!file)
        throw std::invalid_argument(path + " opening error");

    std::string textureFileName;
    while (file >> textureFileName) 
    {   
        // extracts texture name without extension
        std::string textureName = textureFileName.substr(0,textureFileName.find_last_of('.'));
        textures[textureName].reset(new sf::Texture());
        if (!textures[textureName]->loadFromFile(texturesFolder +'/'+ textureFileName))
            throw std::invalid_argument("Error while loading " + textureName + " defined in file " + path);
    }

}

void AssetsManager::loadTexture(const std::string& name, const std::string& path)
{
    textures[name].reset(new sf::Texture());
    if (!textures[name]->loadFromFile(path))
        throw std::invalid_argument("Error while loading " + name + " from " + path);

}

void AssetsManager::loadFont(const std::string& name, const std::string& path)
{
    fonts[name].reset(new sf::Font);
    if (!fonts[name]->loadFromFile(path))
        throw std::invalid_argument("Error while loading " + name + " from " + path);
}


sf::Texture * const AssetsManager::getTexture(const std::string& name) const
{
    try {
        return textures.at(name).get();
    }
    catch(std::out_of_range &e){
        throw AssetsManager::invalid_map_arg("Out of range, key " + name + " not found in textures");
    }

}

sf::Font * const AssetsManager::getFont(const std::string& name) const
{
    try {
        return fonts.at(name).get();
    }
    catch (std::out_of_range& e) {
        throw AssetsManager::invalid_map_arg("Out of range, key " + name + " not found in fonts");
    }
}


