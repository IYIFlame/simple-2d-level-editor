#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <vector>

struct Tile{
	sf::RectangleShape shape;

	Tile::Tile(){};
	Tile::Tile(sf::Vector2f position){ shape = sf::RectangleShape(position); };
};

typedef std::vector< std::vector<Tile*> > Tiles;
Tiles tiles;

const unsigned int MAP_SIZE_WIDTH = 800;
const unsigned int MAP_SIZE_HEIGHT = 600;
const unsigned int TILE_SIZE = 16;

void initMap(){
	int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
	int columns = MAP_SIZE_WIDTH / TILE_SIZE;
	printf("rows %d columns %d\n", rows, columns);
	for(int i = 0; i < rows; ++i){
		std::vector<Tile*> row;

		int jj = 0;
		for(int j = 0; j < columns; ++j){
			Tile* tile = new Tile();
			tile->shape.setFillColor(sf::Color::Green);
			tile->shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			tile->shape.setPosition(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
			printf("y %d x %d\n", j * TILE_SIZE, i * TILE_SIZE);
			row.push_back(tile);
			jj = j;
		}
		//printf("i %d j %d y %d x %d\n", i, jj, jj*TILE_SIZE, i*TILE_SIZE);
		tiles.push_back(row);
	}
}

int main(){
	sf::RenderWindow window(sf::VideoMode(MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT), "FOCKEN OP EDITOR M8");

	initMap();

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
			}

			sf::Vector2i position = sf::Mouse::getPosition(window);
			int posX = position.x;
			int posY = position.y;

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				printf("%d %d %d %d\n", position.x, position.y, position.x/ TILE_SIZE, position.y/ TILE_SIZE);
				tiles[posY / TILE_SIZE][posX / TILE_SIZE]->shape.setFillColor(sf::Color::Green);				
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				printf("%d %d %d %d\n", position.x, position.y, position.x / TILE_SIZE, position.y / TILE_SIZE);
				tiles[posY / TILE_SIZE][posX / TILE_SIZE]->shape.setFillColor(sf::Color::Red);
			}
		}		

		window.clear();
		int rows = MAP_SIZE_HEIGHT / TILE_SIZE + 1;
		int columns = MAP_SIZE_WIDTH / TILE_SIZE;
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				if(tiles[i][j] != NULL){
					window.draw(tiles[i][j]->shape);
				}
			}
		}
		window.display();
	}

	return 0;
}