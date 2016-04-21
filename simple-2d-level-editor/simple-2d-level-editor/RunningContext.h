#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "CommonConstants.h"
#include "CommonHelperFunctions.h"
#include "TileLib.h"

class RunningContext{
private:
	RunningContextTypes contextType = CONTEXT_INVALID;
	sf::View* camera;
	Tiles tiles;
public:
	RunningContext();
	virtual ~RunningContext();

	virtual Status update(float dt);

	virtual sf::RenderWindow* getWindow() = 0;

	virtual sf::View* getCamera();

	virtual Character* getCharacter();

	virtual void setCurrentViewport(CurrentViewport newViewport);

	virtual CurrentViewport getCurrentViewport() =0;

	virtual Tiles& getTiles();

	virtual RunningContextTypes getContextType();

	virtual void importMap(const std::string);

	virtual void exportMap(const std::string);

	virtual void applyTileConfig(int, int, TileConfigID);

	virtual void updateCharacter(int, int);
};

