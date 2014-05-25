template <typename E>
class List {
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

  virtual int length() const = 0;

  virtual int currPos() const = 0;

  virtual void moveToPos(int pos) = 0;

  virtual const E& getValue() const = 0;
};
