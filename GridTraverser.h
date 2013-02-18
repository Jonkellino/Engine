#ifndef _GRID_TRAVERSER_H_
#define _GRID_TRAVERSER_H_


#include "Grid.h"
#include "heap.h"
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
				tile.Reset();
				tile.myIndex = Vector2i(x,y);
				tile.myTile = &myGrid->Get(x,y);
			}
		}
	}

	const bool Inside(Vector2i index) {
		if(index.x < 0 || index.y < 0 ||
			index.x >= myGrid->Size2D().x || index.y >= myGrid->Size2D().y) {
				return false;
		}
		return true;
	}

	bool Pathfind(Vector2i start, Vector2i end, std::vector<TileType*>& outputPath) {
		if(!myGrid) {
			return false;
		}
		Vector2i startIndex = start;
		if( !Inside( startIndex ) ) {
			return false;
		}

		Vector2i endIndex = end;
		if( !Inside( endIndex ) ) {
			return false;
		} 

		AStarData* endTile = &myAStarData[endIndex.x + endIndex.y * myGrid->Size2D().x];
		if( myGrid->Get(endTile->myIndex.x, endTile->myIndex.y).IsTraverseable() == false ) {
			return false;
		}

		Heap<AStarSortWrapper> openList;
		const int gridWidth = myGrid->Size2D().x;

		AStarData& startTile( myAStarData[startIndex.x + startIndex.y * gridWidth] );
		startTile.myIsInOpenList = true;
		openList.Enqueue( AStarSortWrapper(&startTile) );

		bool foundAnEnd = false;
		size_t openSize = openList.size();
		while( openSize > 0 ) {
			AStarSortWrapper temp = openList.front();
			AStarData* first = temp.myData;
			openList.Dequeue(temp);
			--openSize;

			Vector2i currentTile = first->myIndex;
			if( currentTile == endIndex ) {

				foundAnEnd = true;
				break;
			}

			for( int offsetIndex = 0; offsetIndex < myDirections._EEN_SIZE; offsetIndex++ ) {
				const Vector2i checkIndex = currentTile + myDirections[offsetIndex];
				if(!Inside(checkIndex)) {
					continue;
				}
				const int index = checkIndex.x + checkIndex.y * gridWidth;
				AStarData* checkData = &myAStarData[index];
				if(checkData->myIsInClosedList || !checkData->myTile->IsTraverseable()) {
					continue;
				} 

				if( !checkData->myIsInOpenList) {
					checkData->Visit( first, endTile );
					openList.Enqueue(checkData);
					++openSize;
				}
				else if( checkData->CheckIfCheaperWay( first ) ) {
					checkData->Visit( first, endTile );
					openList.Enqueue(checkData); 
					++openSize;
				}
			}
			first->myIsInOpenList = false;
			first->myIsInClosedList = true; 
		} 

		endTile->GetPath( outputPath );
		for(auto& data : myAStarData) {
			data.Reset();
		} 
		return true;
	}

private:


	struct AStarData
	{
		AStarData() {
			Reset();
		} 

		Vector2i myIndex;
		TileType* myTile;
		AStarData* myParent;
		float myG;
		float myH;
		float myF;
		bool myIsInOpenList;
		bool myIsInClosedList; 

		void Visit(AStarData* aParent, AStarData* aDestination) {
			myParent = aParent;
			myG = myParent->myG + CalculateG(myParent->myTile->GetPosition());
			myH = CalculateH(aDestination->myTile->GetPosition());
			myF = myG + myH;
			myIsInOpenList = true;
		}

		bool CheckIfCheaperWay( AStarData* aPotentialParent ) {
			return aPotentialParent->myG + CalculateG( aPotentialParent->myTile->GetPosition() ) < myG;
		}

		void GetPath(std::vector<TileType*>& outputPath) {
			if(myParent) {	
				AStarData* parent = myParent;
				myParent = NULL;
				parent->GetPath(outputPath);
			}
			outputPath.push_back(myTile);
		}

		void Reset() {
			myParent = NULL;
			myG = 0;
			myH = 0;
			myF = 0;
			myIsInOpenList = false;
			myIsInClosedList = false;
		}

		float CalculateG( Vector2f aParentPosition ) {
			return(( myTile->GetPosition() - aParentPosition ).LengthSquared());
		}

		float CalculateH( Vector2f aTargetPosition ) {
			return(( myTile->GetPosition() - aTargetPosition  ).LengthSquared());
		}
	};

	
	struct AStarSortWrapper 
	{ 
		AStarData* myData;
		AStarSortWrapper(AStarData* data) {
			myData = data;
		}

		const bool operator>(const AStarSortWrapper& other) const {
			return myData->myF > other.myData->myF;
		}
	};

	std::vector<AStarData> myAStarData;

	std::array<Vector2i, 8> myDirections; 

	Grid<TileType>* myGrid;


};

#endif