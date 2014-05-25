// Singly linked list node
#ifndef DLINK
#define DLINK

template <typename E> class DLink {
public:
	E element;      // Value for this node
	DLink *next;        // Pointer to next node in list
	DLink *prev;
	// Constructors
	DLink(const E& elemval, DLink* nextval = NULL, DLink* prevval = NULL)
	{
		element = elemval;
		next = nextval;
		prev = prevval;
	}

	DLink(DLink* nextval = NULL, DLink* prevval = NULL) {
		next = nextval;
		prev = prevval;
	}
};

#endif