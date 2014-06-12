#ifndef LINK
#define LINK

template<typename E>
class Link{
public:
	Link<E>* next;
	E value;

	Link(E value, Link<E>* next = NULL){
		this->value = value;
		this->next = next;
	}

	Link(){
		this->next = NULL;
	}

};

#endif