package DataStructure;
/*
 * This is is an implementation of java queue;
 * 
 * it is given a parameter size to construct;
 * it is a sequential circular queue;  
 */
public class Queue{
	
	private int rear;
	private int front;
	private int [] elements;
	private int maxSize;
	
	public Queue(){
		System.out.println("Default Constructor: Default Size = 10");
		maxSize = 11;
		elements = new int[11];
		rear = 0;
		front = 1;
	}
	
	public Queue(int maxsize){
		maxSize = maxsize + 1;
		elements = new int[maxSize];
		rear = 0;
		front = 1;
	}
	
	public void print(){
		if(length() != 0){
			System.out.print("Printer: The queue is listed as followed:");
			for(int i = 0; i < length(); i++){
				System.out.print(elements[(front + i) % maxSize] + " ");
			}
		}else{
			System.out.print("Printer: The queue is empty!");
		}
		System.out.print("\n");
	}
	
	public int find(int search){
		int count = 0;
		for(int i = 0; i < length(); i++){
			if(elements[(front + i) % maxSize] == search){
				count++;
			}
		}
		System.out.println("Searcher: The number of " + search + " is " + count);
		return count;
	}
	
	public void enqueue(int value){
		if(((rear + 2) % maxSize) != front){
			rear = (rear + 1) % maxSize;
			elements[rear] = value;
			System.out.println("Enqueue: Success!");
			print(); // print to show the queue
		}else{
			System.out.println("Enqueue: The queue is full!");
			System.out.println("Enqueue: Failed!");
		}
	}
	
	public int dequeue(){
		if(length() != 0){
			int temp = elements[front];
			front = (front + 1) % maxSize;
			System.out.println("Dequeue: Success!");
			print(); // print to show the queue
			return temp;
		}else{
			System.out.println("Dequeue: The queue is empty!");
			System.out.println("Dequeue: Failed!");
			return -1;
		}
	}
	
	public int frontValue(){
		int temp = -1;
		if(length() != 0){
			temp = elements[front];
			System.out.println("Extractor: Success!");
		}else{
			System.out.println("Extractor: The queue is empty!");
			System.out.println("Extractor: Failed!");
		}
		return temp;
	}
	
	public int length(){
		return ((rear - front + maxSize + 1) % maxSize);
	}
	
}