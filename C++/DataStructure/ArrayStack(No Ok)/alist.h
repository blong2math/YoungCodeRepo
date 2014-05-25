#ifndef ALIST
#define ALIST

#include "list.h"
#include <iostream>

using namespace std;

template<typename E>
class AList : public List<E>{
private:
	int length;
	int curr;
	int maxSize;
	E* alist;

public:
	AList(int maxsize){
		maxSize = maxsize;
		length = 0;
		curr = 0;
		alist = new E[maxsize];
	}

	~AList(){
		delete [] alist;
	}

	void clear(){
		delete[] alist;
		curr = length = 0
	}

	void insert(const E &value){
		if (length < maxSize){
			for (int i = length; i > curr; i--){
				alist[i] = alist[i - 1];
			}
			alist[curr] = value;
			length++;
		}
		else{
			cout << "overload" << endl;
		}
	}
	
	E remove(){
		E temp = alist[curr];
		length--;
		for (int i = curr; i < length; i++){
			alist[i] = alist[i + 1];
		}
		return temp;
	}

	void append(const E& value){
		if (length < maxSize){
			alist[length] = value;
			length++;
		}
		else{
			cout << "overload" << endl;
		}
	}

	void next(){
		if (curr < length){
			curr++;
		}
		else{
			//Assert
		}
	}

	void prev(){
		if (curr > 0){
			curr--;
		}
		else{
			//Assert
		}
	}

	void moveToPos(int pos){
		if (pos <= length){
			curr = pos
		}
		else{
			//Assert
		}
	}

	void print(){
		for (int i = 0; i < length; i++){
			cout << alist[i] << "\t";
		}
		cout << endl;
	}

	int getCurrPos() const{
		return curr;
	}

	void moveToStart(){
		curr = 0;
	}

	void moveToEnd(){
		curr = length;
	}

	const E& getValue() const{
		if (length != 0){
			return alist[curr];
		}
	}

	int getLength() const{
		return length;
	}
};

#endif