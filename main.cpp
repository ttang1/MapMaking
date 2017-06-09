#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

int getR(int variations){
	return rand()%variations;
}

// Parse Map File
// Load Map File To Vector
std::vector<std::string> getContentsFromFile(std::string map_filename) {
	std::ifstream infile;
	infile.open(map_filename);
	std::vector<std::string> contents;
	for(std::string line; getline(infile, line); ) {
		contents.push_back(line);
	}
	infile.close();
	return contents;
}

// Load Images To Vector
std::vector<sf::Image> loadImages(std::string tile_list_filename) {
	std::ifstream infile;
	infile.open(tile_list_filename);
	std::vector<sf::Image> contents;
	for (std::string line; getline(infile, line); ) {
		sf::Image img;
		if (img.loadFromFile(line)) {// should catch failed loads
			contents.push_back(img);
		}
	}
	infile.close();
	return contents;
}

// argv[1] is map file
// argv[2] is tile list file
int main(int argc, char* argv[]) {

	std::vector<std::string> _map = getContentsFromFile(argv[1]);

	std::istringstream iss(_map[0]);
	int col, row;
	std::string filename;
	iss >> col >> row >> filename;

	std::vector<sf::Image> _images = loadImages(argv[2]);
	int variations = _images.size() / 4;
	int tileSize = _images[0].getSize().x;

	sf::Image mapTile;
	mapTile.create(col*tileSize, row*tileSize, sf::Color::Black);

	for(int r = 1; r < row + 1; ++r) { // row 0 is the file description

		for(int c = 0; c < col; ++c) {
			
			int x = 0;
			switch(_map[r][c]) {
				case 'e':
					x = 0;
					break;
				case 'g':
					x = variations;
					break;
				case 'w':
					x = 3*variations;
					break;
				case 'v':
					x = 2*variations;
					break;
				default:
					x = 2*variations;
					break;
			}

			int index = getR(variations) + x;
			mapTile.copy(_images[index], 
				(c)*tileSize, 
				(r-1)*tileSize );
		}
	}

	if(!mapTile.saveToFile(filename)) {
		return -1;
	}

	return 0;
}
