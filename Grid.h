#ifndef _GRID_H_
#define _GRID_H_

#include <vector>  
#include <cassert>
#include "Vector.h"




template<typename Tile>
class Grid
{
public:
	Grid() {};
	~Grid() {};

	void Init(const Vector2i& aSize, const Vector2i& aTileSize) {
		mySize = aSize;
		myTileSize = aTileSize;
		myTiles.resize(aSize.x * aSize.y);
	}

	Tile& Get(const int anIndex) {
		return myTiles[anIndex];
	}

	Tile& Get(const Vector2i anIndex) {
		return Get(anIndex.x, anIndex.y);
	}

	Tile& Get(const int x, const int y) {
		assert(x < mySize.x && y < mySize.y &&
				x >= 0 && y >= 0 &&
				"Out of bounds index");
		return myTiles[x + y * mySize.y];
	}

	Vector2i Size2D() const {
		return mySize;
	}

	size_t Size() const {
		return myTiles.size();
	}

	Vector2i TileSize() const {
		return myTileSize;
	}

	typename std::vector<Tile>::iterator begin() {
		return myTiles.begin();
	}
	
	typename std::vector<Tile>::iterator end() {
		return myTiles.end();
	}
		 

private:
	Vector2i mySize;
	Vector2i myTileSize;
	std::vector<Tile> myTiles;
};


#endif