#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation
	this->current = this->map.head;
}

void SMMIterator::first(){
	//TODO - Implementation
	this->current = this->map.head;
}

void SMMIterator::next(){
	//TODO - Implementation
	if (!valid()) {
		throw exception();
	}
	else {
		this->current = this->map.elements[this->current]->next();
	}
}

bool SMMIterator::valid() const{
	//TODO - Implementation
	return (this->current != -1);
}

TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
	if (!valid()) {
		throw exception();
	}
	else {
		return this->map.elements[this->current]->element();
	}
}


