//Created by Ahmed Ali
//Implementation of a Deque

#pragma once
#include <iostream>
#include <stdexcept>

//Node class used for the doubly linked list
template <typename T>
class Node {
public:
	Node* previous;
	Node* next;
	T value;

	Node() {
		this->next = nullptr;
		this->previous = nullptr;
		this->value = 0;
	}
};

template <typename T>
class Deque {
private:
	Node<T>* head;
	Node<T>* tail;
public:
	//Definitions
	Deque();
	Deque(const Deque& object);
	~Deque();
	Deque& operator=(const Deque& oper);
	void insertFront(T value);
	void insertBack(T value);
	T removeFront();
	T removeBack();
	T peekFront() const;
	T peekBack() const;
	bool empty() const;
	int size() const;
};

//Default constructor
template <typename T>
Deque<T>::Deque() {
	this->head = nullptr;
	this->tail = nullptr;
}

//Copy constructor
template <typename T>
Deque<T>::Deque(const Deque& object)
{
	Node<T>* newNode = object.head;
	while (newNode != nullptr)
	{
		this->insertBack(newNode->value);

		newNode = newNode->next;
	}
}

//Destructor
template <typename T>
Deque<T>::~Deque()
{
	Node<T>* x = this->head;

	while (x != nullptr)
	{
		x = x->next;
		delete x->previous;
	}
}

//Overloaded = operator
template <class T>
Deque<T>& Deque<T>::operator=(const Deque& oper)
{
	if (this != &oper)
	{
		while (head != nullptr)
		{
			Node<T>* newNode = head;
			head = head->next;
			delete newNode;
		}
		head = nullptr;
		tail = nullptr;

		Node<T>* temp = oper.head;
		while (temp != nullptr)
		{
			insertBack(temp->value);
			temp = temp->next;
		}
	}
	return *this;
}

//Method that inserts its template parameter at the front of the deque
template <typename T>
void Deque<T>::insertFront(T value) {
	Node<T>* temp = new Node<T>();
	temp->value = value;
	temp->next = this->head;
	temp->previous = nullptr;
	if (this->head != nullptr)
		this->head->previous = temp;
	if (this->head == nullptr)
		this->tail = temp;
	this->head = temp;
}

//Method that inserts its template parameter at the back of the deque
template <typename T>
void Deque<T>::insertBack(T value) {
	Node<T>* temp = new Node<T>();
	temp->value = value;
	temp->next = nullptr;
	temp->previous = this->tail;
	if (this->tail != nullptr)
		this->tail->next = temp;
	if (this->tail == nullptr)
		this->head = this->tail;
	this->tail = temp;
}

//Removes and returns the value at the front of the deque
template <typename T>
T Deque<T>::removeFront() {
	if (this->head == nullptr)
		throw std::runtime_error("Empty Deque");
	Node<T>* temp = this->head;
	this->head = this->head->next;
	return temp->value;
}

//Removes and returns the value at the back of the deque
template <typename T>
T Deque<T>::removeBack() {
	if (this->head == nullptr)
		throw std::runtime_error("Empty Deque");
	Node<T>* temp = this->tail;
	this->tail = this->tail->previous;
	this->tail->next = nullptr;
	return temp->value;
}

//Returns the value at the front of the deque without removing it
template <typename T>
T Deque<T>::peekFront() const {
	if (this->head == nullptr)
		throw std::runtime_error("Empty Deque");
	return this->head->value;
}

//Returns the value at the back of the deque without removing it
template <typename T>
T Deque<T>::peekBack() const {
	if (this->head == nullptr)
		throw std::runtime_error("Empty Deque");
	return this->tail->value;
}

//Method that returns true if the deque is empty, false otherwise
template <typename T>
bool Deque<T>::empty() const {
	if (this->head == nullptr && this->tail == nullptr)
		return true;
	else
		return false;
}

//Returns the number of items stored in the deque
template <typename T>
int Deque<T>::size() const {
	int s = 0;
	Node<T>* temp = this->head;
	while (temp != nullptr)
	{
		++s;
		temp = temp->next;
	}
	return s;
}
