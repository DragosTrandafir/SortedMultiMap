#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


Node::Node(TElem e, int next, int prev)
{
	this->e = e;
	this->nextNode = next;
	this->prevNode = prev;

}

TElem Node::element()
{
	return this->e;
}

int Node::next()
{
	return this->nextNode;
}

int Node::prev()
{
	return this->prevNode;
}

void SortedMultiMap::resize() {

	// allocate a new array with double capacity somewhere in the computer's memory
	PNod* eNew = new PNod[2 * cp];
	//copy all the elements from the old array into the new array
	for (int i = 0; i < this->size(); i++) 
		eNew[i] = elements[i];

	for (int i = cp; i < 2*cp; i++) {
		eNew[i] = new Node(TElem(), i + 1, i - 1);
	}

	firstEmpty = cp;
	eNew[cp]->prevNode = -1;
	eNew[2*cp-1]->nextNode = -1;
	// double the capacity
	cp = 2 * cp;

	//release the memory space occupied by the old array
	delete[] elements;

	// make the field e to refer the new array (with double capacity)
	elements = eNew;
}


int SortedMultiMap::allocate()
{
	int i = firstEmpty;
	if (i != -1) {
		firstEmpty = elements[firstEmpty]->next();
		if (firstEmpty != -1)
			elements[firstEmpty]->prevNode = -1;
		elements[i]->nextNode = -1;
		elements[i]->prevNode = -1;
	}
	return i;
}

void SortedMultiMap::deallocate(int i)
{
	elements[i]->nextNode = firstEmpty;
	elements[i]->prevNode = -1;
	if (firstEmpty != -1)
		elements[firstEmpty]->prevNode = i;
	firstEmpty = i;
}

int SortedMultiMap::createNode(TElem elem)
{
	if (this->isEmpty())
		resize();
	int i = allocate();
	if (i != -1) {
		elements[i]->e = elem;
		elements[i]->nextNode = -1;
		elements[i]->prevNode = -1;

	}
	return i;
}

SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->cp = 10;
	elements = new PNod[cp];
	this->rel = r;

	head = -1;
	last = -1;
	firstEmpty = 0;

	for (int i = 0; i < cp ; i++) {
		elements[i] = new Node(TElem(), i + 1, i - 1);
	}
	elements[cp - 1]->nextNode = -1;
	elements[0]->prevNode = -1;

	
}


void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	int current = this->head;
	int whereToInsert = 0;


	while (current != -1 && elements[current]->element().first != c && rel(elements[current]->element().first, c)) {
		whereToInsert++;
		current = elements[current]->next();
	}

	int currentIndex;
	int posC;

	if (firstEmpty==-1)
		resize();
	
	int newElemIndex = allocate();
	if (newElemIndex == -1) {
		resize();
		newElemIndex = allocate();
	}

	elements[newElemIndex]->e = pair<TKey, TValue>(c, v);
	if (whereToInsert == 0) {
		if (head == -1) { 
			head = newElemIndex;
			last = newElemIndex;
		}
		else {
			elements[newElemIndex]->nextNode = head;
			elements[head]->prevNode = newElemIndex;
			head = newElemIndex;
		}
	}
	else {
		currentIndex = head;
		posC = 0;
		while (currentIndex != -1 && posC < whereToInsert - 1) {
			currentIndex = elements[currentIndex]->nextNode;
			posC++;
		}
		if (currentIndex != -1) { //it should never be -1, the position is correct
			int nextNode = elements[currentIndex]->nextNode;
			elements[newElemIndex]->nextNode = nextNode;
			elements[newElemIndex]->prevNode = currentIndex;
			elements[currentIndex]->nextNode = newElemIndex;
			if (nextNode == -1)
				last = newElemIndex;
			else
				elements[nextNode]->prevNode = newElemIndex;
		}
	}

}

vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	int current = this->head;

	vector<TValue> foundValues;

	while (current != -1 && elements[current]->element().first != c && rel(elements[current]->element().first, c)) {
		current = elements[current]->next();
	}

	while (current != -1 && elements[current]->element().first == c) {
		foundValues.emplace_back(elements[current]->element().second);
		current = elements[current]->next();
	}
	return foundValues;

		
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	int currentIndex, previousIndex;
	currentIndex = head;
	previousIndex = -1;
	//efficiency
	while (currentIndex != -1 && (elements[currentIndex]->e.first != c || elements[currentIndex]->e.second != v) && rel(elements[currentIndex]->element().first, c)) {
		previousIndex = currentIndex;
		currentIndex = elements[currentIndex]->next();
	}
	if (currentIndex != -1) {
		if (currentIndex == head)
			head = elements[head]->next();
		else
			elements[previousIndex]->nextNode = elements[currentIndex]->nextNode;
		elements[firstEmpty]->prevNode = currentIndex;
		elements[currentIndex]->nextNode = firstEmpty;
		firstEmpty = currentIndex;
		return true;
	}
	else return false;
}


int SortedMultiMap::size() const {
	int count = 0;
	int current = head;
	while (current != -1) {
		//if (elements[current]->prevNode == -1 || elements[current]->element().first != elements[elements[current]->prevNode]->element().first) {
		//	count++;
		//}
		count++;
		current = elements[current]->nextNode;
	}
	return count;
}



bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return (head == -1);
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
	for (int i = 0; i < cp; i++) {
		delete elements[i];
	}
	delete[] elements;
}

