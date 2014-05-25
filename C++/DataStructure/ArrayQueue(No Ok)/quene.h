#ifndef QUEUE
#define QUEUE

template<typename E>
class Queue{
public:
	Queue(){}

	virtual ~Queue(){}

	virtual void clear() = 0;

	virtual void enqueue(const E& value) = 0;

	virtual E dequeue() = 0;

	virtual int getLength() = 0;

	virtual const E& frontValue() const = 0;
};

#endif