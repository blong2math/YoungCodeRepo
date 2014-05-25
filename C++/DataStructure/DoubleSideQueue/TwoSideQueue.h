#ifndef TWOQUEUE
#define TWOQUEUE

#include "llist.h"

template<typename E>
class TwoSideQueue{
private:
	LList<E> l;
	int length;
public:

	TwoSideQueue(){
		l = LList<E>();
		length = 0;
		l.moveToStart();
	}

	~TwoSideQueue(){
		l.clear();
		length = 0;
	}

	int getLength(){
		return length;
	}

	void enqueue_end(const E& e){
		l.append(e);
		length++;
	}

	void enqueue_head(const E& e){
		l.insert(e);
		length++;
	}

	E dequeue_head(){
		if (length > 0){
			length--;
			return l.remove();
		}
		else{
			cout << "the queue is empty" << endl;
			return NULL;
		}
	}
		

	E dequeue_end(){
		if (length > 0){
			l.moveToEnd();
			length--;
			E temp = l.remove();
			l.moveToStart();
			return temp;
		}
		else{
			cout << "the queue is empty" << endl;
			return NULL;
		}
	}
		

	// if you want to watch this queue, use this function
	void print(){
		if (length > 0){
			l.print();
		}
		else{
			cout << "empty" <<endl;
		}
		
	}
};

#endif