#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>

template <typename T>
class Heap
{
public:
	Heap() {}; 
	Heap( const std::vector<T>& anArray ) {
		myData = anArray;
		FloydAlgorithm();
	};
	~Heap() {};

	void Enqueue( const T& aValue ) {
		myData.push_back( aValue );
		BubbleUp( myData.size()-1 );
	}

	bool Dequeue(T &aValue ){
		if( myData.size() )
		{
			aValue = myData[0];
			myData.erase(myData.begin());
			return true;
		}
		return false;
	}

	bool Head(const T &aValue ){
		if( myData.size() )
		{
			aValue = myData[0];
			return true;
		}
		return false;
	}

	inline unsigned int Size() const{
		return size();
	}
	void FloydAlgorithm(){
		int nonLeafLevel = ( static_cast<int>(myData.size()) - 1 ) / 2;
		for( int index = nonLeafLevel; index >= 0; index-- ) {
			BubbleDown( index );
		}
	} 

	void Clear(){
		myData.clear();
	}


	const bool ExistsIn(const T& aTarget) {
		for(auto& data : myData) {
			if(memcmp(&aTarget, &data, sizeof(T) == 0)) {
				return true;
			}
		}
		return false;
	}

	typename std::vector<T>::iterator begin() {
		return myData.begin();
	}

	typename std::vector<T>::iterator end() {
		return myData.end();
	}

	const size_t size() const {
		return myData.size();
	}

	T& front() {
		return myData.front();
	}


private: 
	void BubbleUp( const unsigned int &aPosition ){
		for( unsigned int index = aPosition; index > 0; index = ( index - 1 ) / 2 )
		{
			unsigned int parent = ( index - 1 ) / 2;
			if( myData[index] > myData[parent] )
			{
				break;
			}
			Swap( myData[parent], myData[index] );
		}
	};
	void BubbleDown( const unsigned int &aPosition ){
		if( aPosition < myData.Count() )
		{
			unsigned int index = aPosition;
			unsigned int testIndex = 2 * aPosition + 1;
			T value( myData[aPosition] );
			if( ( testIndex < myData.Count() ) && ( value < myData[testIndex] ) )
			{
				index = testIndex;
				value = myData[testIndex];
			}
			if( ( testIndex+1<myData.Count() ) && ( value < myData[testIndex+1] ) )
			{
				index = testIndex+1;
			}
			if( index != aPosition )
			{
				Swap( myData[aPosition], myData[index] );
				BubbleDown( index );
			}
		}
	};
	inline void Swap( T &aValue1, T &aValue2 ){
		T tempValue( aValue1 );
		aValue1 = aValue2;
		aValue2 = tempValue;
	};

private:
	std::vector<T> myData;
};  

#endif
