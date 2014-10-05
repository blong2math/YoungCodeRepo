#ifndef LIST
#define LIST

#include <iostream>

using namespace std;

#ifndef LINK
#define LINK

// Link class for linked list
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

// Double side link for double linked list
template <typename E>
class DLink {
public:
	E value;      // Value for this node
	DLink *next;        // Pointer to next node in list
	DLink *prev;
	DLink(const E& elemval, DLink* nextval = NULL, DLink* prevval = NULL)
	{
		value = elemval;
		next = nextval;
		prev = prevval;
	}

	DLink(DLink* nextval = NULL, DLink* prevval = NULL) {
		next = nextval;
		prev = prevval;
	}
};

#endif

// Abstract base class of all list
template <typename E>
class List{
public:
	List() {}

	virtual ~List() {}

	virtual void clear() = 0;

	virtual void insert(const E& item) = 0;

	virtual void append(const E& item) = 0;

	virtual E remove() = 0;

	virtual void moveToStart() = 0;

	virtual void moveToEnd() = 0;

	virtual void prev() = 0;

	virtual void next() = 0;

	virtual int getLength() const = 0;

	virtual int currPos() const = 0;

	virtual void moveToPos(int pos) = 0;

	virtual const E& getValue() const = 0;
};

// Array list with a maxsize
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
		delete[] alist;
	}

	void clear(){
		delete[] alist;
		curr = length = 0;
	}

	void insert(const E& item){
		if (length < maxSize){
			for (int i = length; i > curr; i--){
				alist[i] = alist[i - 1];
			}
			alist[curr] = item;
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

	void append(const E& item){
		if (length < maxSize){
			alist[length] = item;
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
			curr = pos;
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

	int currPos() const{
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
		else{
			return NULL;
		}
	}

	int getLength() const{
		return length;
	}
};

// Linked list class
template<typename E>
class LList : public List<E>{
private:
	int length;
	Link<E>* curr;
	Link<E>* head;
	Link<E>* tail;

public:
	LList() {
		head = curr = tail = new Link<E>();
		length = 0;
	}

	~LList() {
		clear();
	}

	void print(){
		Link<E>* temp = head;
		for (int i = 0; i < length; i++){
			cout << temp->next->value << "\t";
			temp = temp->next;
		}
		cout << endl;
	}

	void clear(){
		this->moveToStart();
		next();
		for (int i = 0; i < length; i++){
			Link<E>* temp = curr->next;
			delete curr;
			curr = temp;
		}
		length = 0;
		tail = head;
		curr = head;
	};

	void insert(const E& item){
		curr->next = new Link<E>(item, curr->next);
		length++;
	}

	void append(const E& item){
		Link<E>* temp = new Link<E>(item);
		tail->next = temp;
		tail = temp;
		length++;
	}

	E remove(){
		if (length > 1){
			Link<E>* temp = curr->next;
			curr->next = temp->next;
			E tempE = temp->value;
			delete temp;
			length--;
			return tempE;
		}
		else if (length = 1){
			E temp = head->next->value;
			clear();
			length = 0;
			return temp;
		}
		else{
			//Assert
		}
	}

	void moveToStart(){
		curr = head;
	}

	void moveToEnd(){
		curr = tail;
	}

	void prev(){
		if (curr != head){
			int pos = this->currPos();
			this->moveToStart();
			for (int i = 0; i < pos - 1; i++){
				next();
			}
		}
	}

	void next(){
		if (curr->next != NULL){
			curr = curr->next;
		}
	}

	int currPos() const{
		int i;
		Link<E>* search = head;
		for (i = 0; search->next != curr->next; i++){
			search = search->next;
		}
		return i;
	}

	void moveToPos(int pos){
		for (int i = 0; i < pos; i++){
			curr = curr->next;
		}
	}

	int getLength() const{
		return length;
	}

	const E& getValue() const{
		if (curr->next != NULL){
			return curr->next->value;
		}
	}
};

// Double side Linked list
template<typename E>
class DLList : public List<E>{
private:
	int length;
	DLink<E>* curr;
	DLink<E>* tail;
	DLink<E>* head;

public:
	DLList() {
		head = curr = new DLink<E>();
		tail = new DLink<E>();
		tail->prev = head;
		head->next = tail;
		length = 0;
	}

	~DLList() {
		clear();
		delete tail;
		delete head;
	}

	void clear(){
		while (head->next != tail){
			curr = head->next;
			head->next = curr->next;
			delete curr;
		}
		curr = head;
		length = 0;
	}

	void insert(const E& item){
		curr->next = curr->next->prev = new DLink<E>(item, curr->next, curr);
		length++;
	}

	void append(const E& item){
		tail->prev = tail->prev->next = new DLink<E>(item, tail, tail->prev);
		length++;
	}

	E remove(){
		if (curr->next == tail){
			return NULL;
		}
		E it = curr->next->value;
		DLink<E>* temp = curr->next;
		temp->next->prev = curr;
		curr->next = temp->next;
		delete temp;
		length--;
		return it;
	}

	void print(){
		DLink<E>* temp = head;
		while (temp->next != tail){
			cout << temp->next->value << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void moveToStart(){
		curr = head;
	}

	void moveToEnd(){
		curr = tail;
	}

	void prev(){
		if (curr != head){
			curr = curr->prev;
		}
	}

	void next(){
		if (curr != tail){
			curr = curr->next;
		}
	}

	int getLength() const{
		return length;
	}

	int currPos() const{
		int i = 0;
		DLink<E>* temp = head;
		while (temp != curr){
			temp = temp->next;
			i++;
		}
		return i;
	}

	void moveToPos(int pos){
		moveToStart();
		for (int i = 0; i < pos; i++){
			next();
		}
	}

	const E& getValue() const{
		if (curr->next != NULL){
			return curr->next->value;
		}
	}
};


// Circle list base class
template <typename E>
class CList{
private:
	void operator =(const CList&) {}
	CList(const CList&) {}
public:
	CList() {}
	virtual ~CList() {}

	virtual void clear() = 0;

	virtual void insert(const E& item) = 0;

	virtual E remove() = 0;

	virtual void prev() = 0;

	virtual void next() = 0;

	virtual int length() const = 0;
};


// Circle linked list
template <typename E>
class CLList : public CList<E> {
private:
	Link<E>* curr;       // Access to current element
	int cnt;    	       // Size of list

	void init(){
		curr = NULL;
		cnt = 0;
	}

	void removeall(){
		for (int i = 0; i < cnt; i++){
			Link<E>* temp = curr;
			curr = curr->next;
			delete temp;
		}
		cnt = 0;
	}

public:
	CLList() {
		init();
	}

	~CLList() {
		removeall();
	}

	void print() {
		if (curr != NULL){
			for (int i = 0; i < cnt; i++){
				cout << curr->element << '\n';
				this->next();
			}
			cout << endl;
		}
		else{
			cout << "no element in this daisy-chain" << endl;
		}
	};

	void clear() {
		removeall();
		init();
	}

	// Insert "it" at current position
	void insert(const E& it) {
		if (curr != NULL){
			curr->next = new Link<E>(it, curr->next);
		}
		else{
			curr = new Link<E>(it, NULL);
			curr->next = curr;
		}
		cnt++;
	}

	// Remove and return current element
	E remove() {
		E tempele = curr->element;
		if (curr != NULL){
			Link<E>* temp = curr;
			this->next();
			delete temp;
			cnt--;
			temp = curr;
			this->prev();
			curr->next = temp;
		}
		return tempele;
	}

	// Move curr one step left; no change if already at front
	void prev() {
		for (int i = 1; i < cnt; i++){
			curr = curr->next;
		}
	}

	// Move curr one step right; no change if already at end
	void next(){
		curr = curr->next;
	}

	int length() const  {
		return cnt;
	}

	const E& getValue() const { // Return current element
		if (curr != NULL){
			return curr->element;
		}
		else{
			return NULL;
		}
	}
};

// Circle double linked list
template <typename E>
class CDList : public CList<E> {
private:
	DLink<E>* curr;       // Access to current element
	int cnt;    	       // Size of list

	void init(){
		curr = NULL;
		cnt = 0;
	}

	void removeall(){
		for (int i = 0; i < cnt; i++){
			DLink<E>* temp = curr;
			this->next();
			delete temp;
		}
		cnt = 0;
	}

public:
	CDList() {
		init();
	}

	~CDList() {
		removeall();
	}

	void clear() {
		removeall();
		init();
	}

	void print() {
		if (curr != NULL){
			for (int i = 0; i < cnt; i++){
				cout << curr->element << '\t';
				this->next();
			}
			cout << endl;
		}
		else{
			cout << "no element in this daisy-chain" << endl;
		}
	};

	// Insert "it" at current position
	void insert(const E& it) {
		if (curr != NULL){
			curr->next = new DLink<E>(it, curr->next, curr);
			curr->next->next->prev = curr->next;
		}
		else{
			curr = new DLink<E>(it, NULL, NULL);
			curr->next = curr;
			curr->prev = curr;
		}
		cnt++;
	}

	// Remove and return current element
	E remove() {
		E tempele = curr->element;
		if (curr != NULL){
			DLink<E> *tempnext = curr->next;
			DLink<E> *temppre = curr->prev;
			temppre->next = tempnext;
			tempnext->prev = temppre;
			DLink<E> *tempcurr = curr;
			this->next();
			delete tempcurr;
			cnt--;
		}
		else{
			cout << "There is no element to remove" << endl;
		}
		return tempele;
	}

	// Move curr one step left; no change if already at front
	void prev() {
		curr = curr->prev;
	}

	// Move curr one step right; no change if already at end
	void next(){
		curr = curr->next;
	}

	int length() const  {
		return cnt;
	}

	const E& getValue() const { // Return current element
		if (curr != NULL){
			return curr->element;
		}
		else{
			return NULL;
		}
	}
};

#endif