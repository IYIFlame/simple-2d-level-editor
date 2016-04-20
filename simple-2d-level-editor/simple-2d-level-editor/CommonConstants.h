#pragma once

//for update functions
enum Status{
	NOT_RUNNING,
	RUNNING,
	SUSPENDED,
	EXITING,
};

//for giving ids to every type of tile we have
enum TileConfigID{
	GREEN,
	RED,
	CHARACTER,
};

enum RunningContextTypes{
	CONTEXT_LEVEL_EDITOR,
	CONTEXT_GAME,
	CONTEXT_INVALID,
};

const unsigned int NUMBER_OF_VIEWPORTS = 4;
enum CurrentViewport{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	DEFAULT,
};

enum EventTypes{
	CHANGE_VIEWPORT,
};

// for exporting the map
enum MapEntryTypeID :unsigned char{
	MAP_SIZE = '0',
	ID,
	POSITION,
};

//we moved this here for creating the window it should be renamed, the actual map sizes will vary per map...
const unsigned int MAP_SIZE_WIDTH = 1024;
const unsigned int MAP_SIZE_HEIGHT = 1024;
const int GAME_RES_WIDTH = 1024;//??
const int GAME_RES_HEIGHT = 768;
const unsigned int TILE_SIZE = 16;