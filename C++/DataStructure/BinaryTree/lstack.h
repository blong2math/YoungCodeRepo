#ifndef LSTACK
#define LSTACK

#include "stack.h"
#include "llist.h"

template<typename T>
class LStack : public Stack<T>{
private:
	LList<T> llist;
	int count;
public:
	LStack(){
		llist = LList<T>();
		count = 0;
	}

	~LStack(){
		this->clear();
	}

	void print(){
		llist.print();
	}

	void clear(){
		llist.clear();
	}

	void push(const T& value){
		llist.insert(value);
		count++;
	}

	T pop(){
		count--;
		return llist.remove();
	}

	int length() const{
		return this->count;
	}

	const T& topValue() const{
		return llist.getValue();
	}

};


#endif