#ifndef AQUEUE
#define AQUEUE

#include "quene.h"
#include "alist.h"

template <typename E>
class AQueue : public Queue<E>{
private:
	AList<E> alist;
	int length;
	int maxsize;

public:
	AQueue(int maxsize){
		alist = AList<E>(maxsize);
		this->maxsize = maxsize;
		length = 0;
	}

	~AQueue(){
		alist.clear();
		length = 0;
		maxsize = 0;
	}

	void print(){
		alist.print();
	}

	void clear(){
		alist.clear();
		length = 0;
	}

	void enqueue(const E& value){
		alist.append(value);
		length++;
	}

	E dequeue(){
		E temp = alist.getValue();
		alist.remove();
		length--;
		return temp;
	}

	int getLength(){
		return length;
	}

	const E& frontValue() const{
		return alist.getValue();
	}
};

#endif