#pragma once
#include "Common.h"

class Character{
public:
	// the camera should be initialized here possible and it should be based on the position
	Character();
	Character(float, float, RunningMode);
	~Character();

	void move(sf::Vector2f);
	void setPosition(sf::Vector2f newPosition){ position = newPosition; };
	void setPosition(float, float);
	void setStartPosition(float, float);
	void resetPosition(){ position = startPosition; };
	void applyTileConfig(TileConfig config, RunningMode mode);
	void applyRunningModeSettings(RunningMode);
	void setCurrentWindow(sf::RenderWindow* newWindow){ currWindow = newWindow; };
	void setCurrentViewport(CurrentViewport);
	sf::View* getCamera(){ return camera; };
	CurrentViewport getCurrentViewport(){ return currentViewport; };
	sf::Vector2f getPosition(){
		return position;
	}
	Status modeLevelEditorUpdate();
	Status modeGameUpdate();

	TileConfigID id;
	sf::CircleShape shape = sf::CircleShape(TILE_SIZE);
	sf::Vector2f startPosition;

private:
	sf::RenderWindow* currWindow = NULL;
	//TestGame* game;
	sf::View* camera;
	sf::Vector2f cameraSize = sf::Vector2f(144, 112);
	CurrentViewport currentViewport = FIRST;
	sf::Vector2f position;

	int height;
};

