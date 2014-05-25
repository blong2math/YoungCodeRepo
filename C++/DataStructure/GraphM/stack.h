#ifndef STACK
#define STACK

template<typename T>
class Stack{
public:
	Stack(){}

	virtual ~Stack(){};

	virtual void clear() = 0;

	virtual void push(const T& value) = 0;

	virtual T pop() = 0;

	virtual int length() const = 0;

	virtual const T& topValue() const = 0;

};


#endif