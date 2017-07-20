/*****************************************
* Instructions
*  - Replace 'userid' with your Florida Institute of Technology User ID
*  - Select the current calendar term and enter the year
*  - List students with whom you had discussions and who helped you
*
* FIT User ID:  bhartill2014@my.fit.edu
* Submitted for ECE 2552
* Department of Electrical and Computer Engineering
* Florida Institute of Technology
* Calender Term of Submission:  Spring 2017
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*
* The following is a list of FIT User IDs of those students
* I had discussions with in preparing this project:
*    -
*
* The following is a list of FIT User IDs of those students
* who helped me with this project (describe their help; e.g., debugging):
*    -
*****************************************/

#ifndef DQueue_H
#define DQueue_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "ECE2552.h"
#include "Exception.h"

template <typename Type>
class DQueue {
private:
	int initial_capacity;
	int array_capacity;
	Type *array;
	int ihead;
	int itail;
	int entry_count;
	// other integer member variables, as necessary

public:
	DQueue(int = 10);
	DQueue(DQueue const &);
	~DQueue();

	Type head() const;
	int size() const;
	bool empty() const;
	int capacity() const;

	void swap(DQueue &);
	DQueue &operator=(DQueue);
	void enqueue(Type const &);
	Type dequeue();
	void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, DQueue<T> const &);
};

template <typename Type>
DQueue<Type>::DQueue(int n) :
initial_capacity(std::max(n, 1)),
array_capacity(initial_capacity),
array(new Type[initial_capacity]),
ihead(0),
itail(initial_capacity - 1),
entry_count(0) {
	// Enter your implementation here.
}

template <typename Type>
DQueue<Type>::DQueue(DQueue const &queue) :
initial_capacity(queue.initial_capacity),
array_capacity(queue.array_capacity),
array(new Type[array_capacity]),
ihead(queue.ihead),
itail(queue.itail),
entry_count(queue.entry_count) {
	// The above initializations copy the values of the appropriate
	// member variables and allocate memory for the data structure;
	// however, you must still copy the stored objects.

	*this = queue; //holds a copy of queue
}

template <typename Type>
DQueue<Type>::~DQueue() {
	while (!empty())
	{
		clear(); //deletes the queue
	}
}

template <typename Type>
int DQueue<Type>::size() const {
	return entry_count; //returns number of entries in queue
}

template <typename Type>
int DQueue<Type>::capacity() const {
	// Enter your implementation here.
	return array_capacity; //the capacity of the array
}

template <typename Type>
bool DQueue<Type>::empty() const {
	if (size() == 0)
	{
		return true; //if entry count is 0, then it is empty
	}
}

template <typename Type>
Type DQueue<Type>::head() const {
	if (empty())
		throw underflow; //if empty throw exception
	return array[ihead]; //returns the head node
}

template <typename Type>
void DQueue<Type>::swap(DQueue<Type> &queue) {
	std::swap(initial_capacity, queue.initial_capacity);
	std::swap(array_capacity, queue.array_capacity);
	std::swap(array, queue.array);
	std::swap(ihead, queue.ihead);
	std::swap(itail, queue.itail);
	std::swap(entry_count, queue.entry_count);
}

template <typename Type>
DQueue<Type> &DQueue<Type>::operator=(DQueue<Type> rhs) {
	swap(rhs);

	return *this;
}

template <typename Type>
void DQueue<Type>::enqueue(Type const &obj) {
	if (itail != 0 && itail == array_capacity) //if array is full
	{
		array_capacity *= 2; //double the capacity
		Type *temp = new Type[array_capacity];
		for (int i = 0; iterator = ihead; iterator < itail; i++, iterator++)
			temp[i] = array[iterator];
		delete[] array;
		array = std::move(temp);
	}

	array[itail++] = obj;
	entry_count++;

}

template <typename Type>
Type DQueue<Type>::dequeue() {
	if (empty())
		throw underflow; //exception if empty

	Type dequeuedObj = array[ihead]; //set it equal to first array value
	array[ihead++] = NULL; //increment and set to NULL

	if ((itail - ihead + 1) / array_capacity > 1 / 4 && array_capacity > initial_capacity) { //if only 1/4 the capacity
		array_capacity *= .5; //half the capacity
		Type *temp = new Type[array_capacity];
		for (int i = 0, iterator = ihead; iterator <= itail; i++, iterator++)
			temp[i] = array[iterator];
		array = std::move(temp);
	}
}

template <typename Type>
void DQueue<Type>::clear() {
	initial_capacity = 10; //sets initial capacity to 10
	array_capacity = initial_capacity; //resets current capacity to initial capacity
	delete[] array; //delete array
	ihead = 0; //reset head
	itail = 0; //reset tail
	entry_count = 0; //reset entry count

	
}

// You can modify this function however you want:  it will not be tested

template <typename Type>
std::ostream &operator<<(std::ostream &out, DQueue<Type> const &queue) {
	// I don't know how you are implementing your queue so I cannot print it.
	// If you want, you can print whatever you want here and then call cout
	// in the driver.

	// Remember to redirect to out, e.g.,
	//      out << "Hello!";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif