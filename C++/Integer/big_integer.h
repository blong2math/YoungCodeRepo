#ifndef BIGINTEGER
#define BIGINTEGER

#include "list.h"
#include <string>
#include <iostream>

using namespace std;

class BigInteger{
private:
	DLList<int>* nums;
	bool positive = true;
public:
	BigInteger(string input){
		nums = new DLList<int>();
		const char* numbers = input.data();
		for (int i = input.length() - 1; i >= 0; i--){
			if (numbers[i] != ',' && numbers[i] != '-'){
				nums->append(numbers[i] - '0');
			}
			if (numbers[i] == '-'){
				positive = false;
			}
		}
	}

	bool isPositive(){
		return positive;
	}

	void setPositive(bool t){
		positive = t;
	}

	void add(BigInteger* plus){
		if (plus->isPositive() == this->isPositive()){
			int addbit = 0;

			int length1 = nums->getLength();
			int length2 = plus->getNums()->getLength();
			int max = 0;
			if (length1 > length2){
				max = length1;
			}
			else{
				max = length2;
			}

			for (int i = 0; i < max - length1; i++){
				nums->append(0);
			}
			nums->moveToStart();
			plus->getNums()->moveToStart();
			for (int i = 0; i < max; i++){
				int temp = nums->getValue() + plus->getNums()->getValue() + addbit;
				if (temp >= 10){
					temp = temp - 10;
					addbit = 1;
				}
				nums->remove();
				nums->insert(temp);
				nums->next();
				plus->getNums()->next();
				if (i == max - 1 && addbit == 1){
					nums->append(1);
				}
			}
		}
		else{

		}

	}

	void print(){
		if (!positive){
			cout << "-";
		}
		nums->moveToEnd();
		nums->prev();
		int l = nums->getLength();
		for (int i = l; i > 0; i--){
			nums->prev();
			if (i % 4 == 0 && i != l){
				cout << ",";
			}
			cout << nums->getValue();
		}
	}

	DLList<int>* getNums(){
		return nums;
	}

	BigInteger operator +(BigInteger plus){
		this->add(&plus);
		return *this;
	}
};

#endif