#ifndef _GRID_TRAVERSER_H_
#define _GRID_TRAVERSER_H_


#include "Grid.h"
#include <algorithm> 
#include <array>

template<typename TileType>
class GridTraverser
{
public:
	GridTraverser(void) {
		myGrid = nullptr;
		myDirections[0] = Vector2i(1,1);
		myDirections[1] = Vector2i(-1,1);
		myDirections[2] = Vector2i(1,-1);
		myDirections[3] = Vector2i(-1,-1);
		myDirections[4] = Vector2i(0,1);
		myDirections[5] = Vector2i(0,-1);
		myDirections[6] = Vector2i(1,0);
		myDirections[7] = Vector2i(-1,0);
		

	} 
	~GridTraverser(void) {};


	void SetGrid(Grid<TileType>* aGrid) {
		myGrid = aGrid;
		
		myAStarData.resize(myGrid->Size());
		for(int y = 0; y < myGrid->Size2D().y; ++y) {
			 for(int x = 0; x < myGrid->Size2D().x; ++x) {
				AStarData& tile = myAStarData[x + y * myGrid->Size2D().y];
				tile.myIndex = Vector2i(x,y);
			}
		}
	}

	bool Pathfind(Vector2i start, Vector2i end) {
		if(!myGrid) {
			return false;
		}

		Vector2i endIndex = end;
		TileType& endTile( myGrid->Get(endIndex.x + endIndex.y * myGrid->Size2D().y) );
		if( endTile.IsTraverseable() == false ) {
			return false;
		}

		std::vector<AStarData> openList;
		std::vector<AStarData> closedList;

		AStarData& startTile( myAStarData[start.x + start.y * myGrid->Size2D().y] );
		std::push_heap(openList.begin(), openList.end(), startTile);//openList.push_back(startTile);//startTile.myIsInOpenList = true

		bool foundAnEnd = false;
		size_t openSize = openList.size();
		while( openSize > 0 ) {
			AStarData first = openList.front();
			std::pop_heap(openList.begin(), openList.end(), first);

			Vector2i currentTile = first.myIndex;
			if( currentTile == endIndex ) {
				foundAnEnd = true;
				break;
			}

			for( int offsetIndex = 0; offsetIndex < myDirections._EEN_SIZE; offsetIndex++ ) {
				Vector2i checkIndex = currentTile + myDirections[offsetIndex];
				TileType& checkTile = myGrid->Get(checkIndex.x + checkIndex.y * myGrid->Size2D().y);

				if( checkTile.IsTraverseable() && std::find(closedList.begin(), closedList.end(), myAStarData[checkIndex.x + checkIndex.y * myGrid->Size2D().y])) {
					if( !checkTile.myIsInOpenList )
					{
						checkTile.SetupTriangleInAStar( first.myTile, &endTile );
						openList.Enqueue( NavMeshHeapHelper( &checkTile ) );
					}
					else if( checkTile.CheckIfCheaperWay( first.myTile ) )
					{
						checkTile.SetupTriangleInAStar( first.myTile, &endTile );
						openList.Enqueue( NavMeshHeapHelper( &checkTile ) );
					}
				}
			}

			first.myTile->myIsInOpenList = false;
			first.myTile->myIsInClosedList= true;
			closedList.Enqueue( first );
		} 
		endTile.GetPath( someMovement );
		someMovement.Add( anEndPosition );

		NavMeshHeapHelper tempHelper;
		while(openList.Dequeue(tempHelper))
		{
			tempHelper.myTile->Reset();
		}
		while(closedList.Dequeue(tempHelper))
		{
			tempHelper.myTile->Reset();
		}
		endTile.Reset();
	}



private:

	struct AStarData
	{
		Vector2i myIndex;
		AStarData* myParent;
		float myG;
		float myH;
		float myF;
	};



	std::vector<AStarData> myAStarData;

	std::array<Vector2i, 8> myDirections; 

	std::vector<TileType> myOpenList;
	Grid<TileType>* myGrid;


};

#endif