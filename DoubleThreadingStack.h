#ifndef _DOUBLE_THREADING_QUEUE_H_
#define _DOUBLE_THREADING_QUEUE_H_

#include <array>
#include <vector>



template<typename Type>
class DoubleThreadingStack
{
public:
	DoubleThreadingStack(void) {
		myActiveStack = 0;
		myStacks[0].reserve(5);
		myStacks[1].reserve(5);
	}
	~DoubleThreadingStack(void) {
	}

	void Push(const Type aType) {
		myStacks[myActiveStack == 0 ? 1 : 0].push_back(aType);
	}

	Type Pop() {
		std::vector<Type>& target = myStacks[myActiveStack];
		Type toReturn = target[target.size()-1];
		target.pop_back();
		return toReturn;
	}

	template<typename IndexAccessor>
	Type& operator[](const IndexAccessor index) {
		return myStacks[myActiveStack][index];
	}

	const size_t Size() const {
		return myStacks[myActiveStack].size();
	}


	void Switch() {
		myStacks[myActiveStack].clear();
		if(myActiveStack == 0) {
			_InterlockedIncrement(&myActiveStack);
		}
		else {
			_InterlockedDecrement(&myActiveStack);
		}
	}
	typename std::vector<Type>::iterator begin() {
		return myStacks[myActiveStack].begin();
	}
	typename std::vector<Type>::iterator end() {
		return myStacks[myActiveStack].end();
	}

private:
	volatile long				myActiveStack;
	std::array<std::vector
		<Type>,2>				myStacks;
};


#endif