#pragma once
#include "Common.h"

class Character{
public:
	// the camera should be initialized here possible and it should be based on the position
	Character();
	~Character();

	void setPosition(sf::Vector2f newPosition){ position = newPosition; };
	void setPosition(float x, float y){ position.x = x; position.y = y; };
	void applyTileConfig(TileConfig config, RunningMode mode);
	sf::View getCamera(){ return *camera; };
	Status modeLevelEditorUpdate(sf::RenderWindow*);
	Status modeGameUpdate(sf::RenderWindow*);

private:
	TileConfigID id;
	sf::View* camera;
	sf::Vector2f cameraSize = sf::Vector2f(128, 80);
	sf::Vector2f position;
	sf::CircleShape shape = sf::CircleShape(TILE_SIZE);
	sf::RenderWindow* currWindow = NULL;

	int height;
};

