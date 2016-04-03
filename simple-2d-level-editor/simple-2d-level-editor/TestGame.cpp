#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <vector>


class TestGame{
public:
	TestGame(){
		printf("creating window\n");
		testWindow = new sf::RenderWindow(sf::VideoMode(GAME_RES_WIDTH, GAME_RES_HEIGHT), "FOCKEN OP GAEM M8");
	};
	~TestGame(){
		delete testWindow;
	};

	int update(float dt){
		sf::Event event;
		if(testWindow->pollEvent(event)){ 
			if(event.type == sf::Event::Closed){
				testWindow->close();
				return 2;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				testWindow->close();
				return 2;
			}
		}
		testWindow->clear();

		/*int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				if(tiles[i][j] != NULL){
					window.draw(tiles[i][j]->shape);
				}
			}
		}*/
		testWindow->display();
		return 1;
	};

private:
	const int GAME_RES_WIDTH = 800;
	const int GAME_RES_HEIGHT = 600;
	sf::RenderWindow* testWindow = NULL;
};