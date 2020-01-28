#include<iostream>
#include<sstream>
#include <string>

using namespace std;
#include"set.h"

//member function implementations for set

Set::Set()
{
	head = nullptr;
	tail = nullptr;
}

Set::Set(const Set & rhs)
{
	head = createClone(rhs);
	primarynode* temp = head;
	while (temp->next)
	{
		temp = temp->next;
	}
	tail = temp;
}

void Set::addSet(int a[], int size) //used in adding complete sets given as arrays
{
	if (head == nullptr)
	{
		head = tail = new primarynode(a, size);
	}
	else
	{
		tail->next = new primarynode(a, size);
		tail = tail->next;
	}
}

primarynode* Set::createClone(const Set & rhs)
{
	Set* clone = new Set; //clone is the new clone created
	
	primarynode* settrail = rhs.head; //settrail will watch over rhs and adds its elements into the new set
	clone->head = new primarynode(settrail->l, settrail->size);
	primarynode* temp = clone->head;
	settrail = settrail->next;
	while (settrail)
	{
		temp->next = new primarynode(settrail->l, settrail->size);
		temp = temp->next;
		settrail = settrail->next;
	}
	
	return clone->head;
}

Set & Set::operator=(const Set & rhs) //assignment
{
	if (this == &rhs) //does nothing if this is self assignment
		return *this;
	deleteSet(); //deletes the original
	head = createClone(rhs); //copies rhs into lhs
	primarynode* temp = head;
	while (temp->next)
	{
		temp = temp->next;
	}
	tail = temp;

	return *this;
}

Set & Set::operator+(const Set & rhs) //union will copy lhs and add the different in rhs into the new set
{
	Set* united = new Set;
	//just as a copy constructor
	united->head = createClone(*this);
	primarynode* temp = united->head;
	while (temp->next)
	{
		temp = temp->next;
	}
	united->tail = temp;
	//we have copied the lhs and now we will add the different lists of rhs
	primarynode* settrail1 = rhs.head; //settrail1 will watch over rhs
	while (settrail1)
	{
		bool exists = false;
		primarynode* settrail2 = this->head; //settrail 2 will watch over "this"
		while (settrail2)
		{
			if (isEqual(settrail1, settrail2))
			{
				exists = true;
				break;
			}
			
			settrail2 = settrail2->next;
		}
		if (!exists) //if an element of rhs doesnt exist in "this"
		{
			united->tail->next = new primarynode(settrail1->l, settrail1->size);
			united->tail = united->tail->next;
		}
		settrail1 = settrail1->next;
	}
	return *united;
}

Set & Set::operator/(const Set & rhs) //difference will add only the different lists into the new set
{
	Set* difference = new Set;

	primarynode* settrail1 = this->head; //settrail1 will watch over "this"
	while (settrail1)
	{
		bool exists = false;
		primarynode* settrail2 = rhs.head; //settrail 2 will watch over rhs
		while (settrail2)
		{
			if (isEqual(settrail1, settrail2))
			{
				exists = true;
				break;
			}
			
			settrail2 = settrail2->next;
		}
		if (!exists) //if an element of "this" doesnt exist in rhs
		{
			if (difference->head == nullptr)
			{
				difference->head = difference->tail = new primarynode(settrail1->l, settrail1->size);
			}
			else
			{
				difference->tail->next = new primarynode(settrail1->l, settrail1->size);
				difference->tail = difference->tail->next;
			}
			
		}
		settrail1 = settrail1->next;
	}

	return *difference;
}

Set & Set::operator%(const Set & rhs) //intersection will add only the same lists into the new set
{
	Set* intersection = new Set;

	primarynode* settrail1 = this->head; //settrail 1 will watch over "this"
	while (settrail1)
	{
		bool exists = false;
		primarynode* settrail2 = rhs.head;
		while (settrail2)
		{
			if (isEqual(settrail1, settrail2))
			{
				exists = true;
				break;
			}
			
			settrail2 = settrail2->next;
		}
		if (exists) //if an element of "this" exists in rhs
		{
			if (intersection->head == nullptr)
			{
				intersection->head = intersection->tail = new primarynode(settrail1->l, settrail1->size);
			}
			else
			{
				intersection->tail->next = new primarynode(settrail1->l, settrail1->size);
				intersection->tail = intersection->tail->next;
			}
		}
		settrail1 = settrail1->next;
	}

	return *intersection;
}

void Set::deleteSet() //deletes all elements of a set
{ //settrail watches primarynodes, listtrail watches secondarynodes
	primarynode* settrail = head;
	primarynode* settemp;
	while (settrail)
	{
		secondarynode* listtrail = settrail->l->head;
		secondarynode* listtemp;
		while (listtrail)
		{
			listtemp = listtrail->next;
			delete listtrail;
			listtrail = listtemp;
		}
		settemp = settrail->next;
		delete settrail;
		settrail = settemp;
	}
	head = tail = nullptr;
}

bool Set::isEqual(primarynode* & lhs, primarynode* & rhs) //checks if two lists are same or not
{
	if (lhs->size != rhs->size)
		return false;
	secondarynode* listtrail1 = lhs->l->head;
	secondarynode* listtrail2 = rhs->l->head;
	while (listtrail1)
	{
		if (listtrail1->value != listtrail2->value)
			return false;
		listtrail1 = listtrail1->next;
		listtrail2 = listtrail2->next;
	}
	return true;
}

//member function implementations for list

List::List(List* & copy) //used in copying and assigning
{
	head = tail = nullptr;
	secondarynode* listtrail = copy->head;
	while (listtrail)
	{
		if (head == nullptr)
		{
			head = tail = new secondarynode(listtrail->value);
		}
		else
		{
			tail->next = new secondarynode(listtrail->value);
			tail = tail->next;
		}
		listtrail = listtrail->next;
	}
}

List::List(int a[], int size) //used in adding complete lists given as arrays
{
	head = tail = new secondarynode(a[0]);

	for (int i = 1; i < size; i++)
	{
		tail->next = new secondarynode(a[i]);
		tail = tail->next;
	}
}

void List::addToList(int num) //adds standalone numbers into list, used in copying and assigning
{
	if (head == nullptr)
	{
		head = tail = new secondarynode(num);
	}
	else
	{
		tail->next = new secondarynode(num);
		tail = tail->next;
	}
}
