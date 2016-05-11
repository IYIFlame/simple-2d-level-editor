#pragma once
#include "CommonConstants.h"
#include "TileLib.h"
#include "Entity.h"

class Character:public Entity{
public:
	// the camera should be initialized here possible and it should be based on the position
	Character();
	Character(float, float, RunningContextTypes);
	~Character();

	void resetPosition(){ position = startPosition; };
	void setPosition(sf::Vector2f newPosition){ position = newPosition; };
	void setCurrentWindow(sf::RenderWindow* newWindow){ currWindow = newWindow; };
	CurrentViewport getCurrentViewport(){ return currentViewport; };
	sf::View* getCamera(){ return camera; };
	sf::Vector2f getPosition(){ return position; }

	void move(sf::Vector2f);
	void setPosition(float, float);
	void setStartPosition(float, float);
	void applyTileConfig(TileConfig config, RunningContextTypes mode);
	void applyRunningModeSettings(RunningContextTypes);
	void setCurrentViewport(CurrentViewport);
	Status modeLevelEditorUpdate();
	Status modeGameUpdate();

	TileConfigID id;
	sf::Vector2f startPosition;
protected:
//contextType
private://TODO lot of this will be protected not private...
	//sf::CircleShape shape = sf::CircleShape(TILE_SIZE);
	sf::RenderWindow* currWindow = NULL;
	//TestGame* game;
	sf::View* camera;
	sf::Vector2f cameraSize = sf::Vector2f(144, 112);
	CurrentViewport currentViewport = FIRST;
	sf::Vector2f position;

	int height;
};

