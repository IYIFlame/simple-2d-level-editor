#pragma once
#include "CommonConstants.h"
#include <string>

//put these in namespace
static void getRowsAndCols(int& resHeight, int& resWidth){
	resHeight = resHeight / TILE_SIZE + 1;
	resWidth /= TILE_SIZE;
};

static void PRINT_ERROR(std::string errorLocation, std::string errorMessage){
	printf("[%s] Error: %s\n", errorLocation, errorMessage);
};

static bool outOfWindowBounds(int x, int y, int maxWidth, int maxHeight){
	return maxWidth < x || x < 0 || maxHeight < y || y < 0;
};
