#ifndef QUEUE_RAMKUMAR_HPP
#define QUEUE_RAMKUMAR_HPP

#include <stdexcept>
#include <stdio.h>

template<typename T>
class Queue {
private:
	int qSize;
	struct Node { //Node structure
		T data; //Data stored inside node
		Node* next; //Pointer to next node
		Node(T nodeData) : data(nodeData), next(nullptr) {}
	};

	Node* frontPtr; //Pointer for front of the queue
	Node* tailPtr; //Pointer for end of the queue

public:
	Queue(); //Constructor
	~Queue(); //Deconstuctor
	void enqueue(T addNode); //Add node to queue
	T dequeue(); //Remove and return the first node
	T front(); //Return the data of the first node
	int size(); //Return size of queue
	void empty(); //Remove all elements from queue
	bool isEmpty(); //Checks if queue is empty
};

template<typename T>
Queue<T>::Queue() {
	//Initializing
	qSize = 0;
	frontPtr = nullptr;
	tailPtr = nullptr;
}

template<typename T>
Queue<T>::~Queue() {
	empty();
}

template<typename T>
void Queue<T>::enqueue(T newNode) {
	Node* addData = new Node(newNode);
	if (frontPtr == nullptr && tailPtr == nullptr) {
		frontPtr = addData;
		tailPtr = addData;
	}
	else {
		tailPtr->next = addData;
		tailPtr = addData;
	}
	qSize++;
}

template<typename T>
T Queue<T>::dequeue() {
	if (frontPtr == nullptr && tailPtr == nullptr) {
		printf("The queue is empty!");
	}

	Node* temp = frontPtr;
	T valueDeq = frontPtr->data;
	frontPtr = frontPtr->next;
	if (frontPtr == nullptr) {
		tailPtr = nullptr; // Queue became empty

	}

	delete temp;
	qSize--;
	return valueDeq;
}

template<typename T>
T Queue<T>::front() {
	return frontPtr->data;
}

template<typename T>
int Queue<T>::size() {
	return qSize;
}

template<typename T>
void Queue<T>::empty() {
	while(frontPtr != nullptr) {
		Node* temp = frontPtr;
		frontPtr = frontPtr -> next;
		delete temp;
	}
}

template<typename T>
bool Queue<T>::isEmpty() {
	if (qSize == 0) {
		return true;
	}
	else {
		return false;
	}
}
#endif
