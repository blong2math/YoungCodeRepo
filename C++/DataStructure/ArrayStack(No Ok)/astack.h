#ifndef ASTACK
#define ASTACK

#include "alist.h"
#include "stack.h"

template<typename T>
class AStack : public Stack<T>{
private:
	AList<T> alist;
	int depth;
	int count;
public:

	AStack(int depth){
		this->depth = depth;
		alist = AList<T>(depth);
	}

	~AStack(){
		this->clear();
	}

	void print(){
		alist.print();
	}

	void push(const T& value){
		if (count < depth){
			alist.insert(value);
			count++;
		}else{
			// Assert
		}
	}

	T pop(){
		if (count > 0){
			return alist.remove();
		}else{
			// Assert
		}
	}

	void clear(){
		for(int i = 0; i < count; i++){
			this->pop();
		}
	}

	const T& topValue() const{
		return alist.getValue();
	}

	int length() const{
		return this->depth
	}
};

#endif