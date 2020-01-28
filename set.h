#ifndef _SET_H
#define _SET_H
#include <sstream>
#include <iostream>


struct secondarynode //holds the value of an element of a set
{
	int value;
	secondarynode* next;

	secondarynode(int v) : value(v), next(nullptr) {}
};

class Set;

class List
{
	friend class Set;
private:
	secondarynode* head;
	secondarynode* tail;
public:
	List(List* & copy);
	List(int a[], int size);
	void addToList(int num);
	friend ostream & operator<<(ostream & os, const Set & set); //cout operator
};

struct primarynode //holds a list and the size of that integer list
{
	List* l;
	int size;
	primarynode* next;

	primarynode (int a[], int s, primarynode* n = nullptr) : size(s), next(n) 
	{
		l = new List(a, s);
	}

	primarynode (List* copy, int s, primarynode* n = nullptr) : size(s), next(n) 
	{
		l = new List(copy);
	}
};

class Set
{
private:
	primarynode* head;
	primarynode* tail;
public:
	Set(); //constructor
	Set(const Set & set); //copy constructor
	void addSet(int a[], int size); //adds element to the set
	primarynode* createClone(const Set & set); //creates clone and returns the head of the clone
	Set & operator=(const Set & rhs); //assignment operator
	Set & operator+(const Set & rhs); //union operator
	Set & operator/(const Set & rhs); //difference operator
	Set & operator%(const Set & rhs); //intersection operator
	friend ostream & operator<<(ostream & os, const Set & set); //cout operator
	bool isEqual(primarynode* & lhs, primarynode* & rhs);
	void deleteSet();
};
#endif