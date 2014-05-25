template <typename E> class CList { // List ADT
private:
	void operator =(const CList&) {}      // Protect assignment
	CList(const CList&) {}           // Protect copy constructor
public:
	CList() {}          // Default constructor
	virtual ~CList() {} // Base destructor

	// Clear contents from the list, to make it empty.
	virtual void clear() = 0;

	// Insert an element at the current location.
	// item: The element to be inserted
	virtual void insert(const E& item) = 0;

	// Remove and return the current element.
	// Return: the element that was removed.
	virtual E remove() = 0;

	// Move the current position one step left. No change
	// if already at beginning.
	virtual void prev() = 0;

	// Move the current position one step right. No change
	// if already at end.
	virtual void next() = 0;

	// Return: The number of elements in the list.
	virtual int length() const = 0;


};