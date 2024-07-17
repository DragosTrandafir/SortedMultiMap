#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class Node;
// We define the type PNode as being the address of a Node
typedef Node* PNod;

//---------------------------//
class Node
{
public:
    friend class SortedMultiMap;
    //constructor
    Node(TElem e, int next, int prev);
    TElem element(); //info field
    int next();
    int prev();

private:
    TElem e;
    int nextNode;
    int prevNode;
};

class SortedMultiMap {
	friend class SMMIterator;
    private:
		//TODO - Representation

        PNod* elements; // PNod [prev, <k,v>, next] vector
        void resize(); //for resizing the array allocated dynamically

        int cp;// capacity
        int head; // refrence to the first element of the list
        int last;   // refrence to the last element of the list
        int firstEmpty; // refrence to the first empty of the list

        Relation rel; // define the relation between keys

        //se returneaza pozitia unui spatiu liber in lista
        int allocate();
        //dealoca spatiul de indice i
        void deallocate(int i);
        //functie privata care creeaza un nod in lista inlantuita
        int createNode(TElem elem);

    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);//

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);//

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
