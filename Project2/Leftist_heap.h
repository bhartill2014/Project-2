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

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"
#include <cmath>

template <typename Type>
class Leftist_heap {
private:
	Leftist_node<Type> *root_node;
	int heap_size;

public:
	Leftist_heap();
	Leftist_heap(Leftist_heap const &);
	~Leftist_heap();

	void swap(Leftist_heap &heap);
	Leftist_heap &operator=(Leftist_heap);

	bool empty() const;
	int size() const;
	int null_path_length() const;
	Type top() const;
	int count(Type const &obj) const;

	void push(Type const &obj);
	Type pop();
	void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Leftist_heap<T> const &);
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap() :
root_node(nullptr),
heap_size(0) {
	// does nothing
}

template <typename Type>
Leftist_heap<Type>::Leftist_heap(Leftist_heap const &heap) :
root_node(nullptr),
heap_size(0) {
	// Traverses through the argument heap and pushes the entries
	// into this heap--you may use whatever traversal you want
}

template <typename Type>
Leftist_heap<Type>::~Leftist_heap() { //deconstructor 
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap(Leftist_heap<Type> &heap) {
	std::swap(root_node, heap.root_node);
	std::swap(heap_size, heap.heap_size);
}

template <typename Type>
Leftist_heap<Type> &Leftist_heap<Type>::operator=(Leftist_heap<Type> rhs) {
	swap(rhs);

	return *this;
}

// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

template <typename Type>
bool Leftist_heap<Type>::empty() const
{
	if (heap_size == 0)
		return true;  //if size is 0, it is empty
	return false; //otherwise it is not empty
}

template <typename Type>
int Leftist_heap<Type>::size() const
{
	return heap_size; //heap_size keeps track of the number of nodes in the heap
}

template <typename Type>
int Leftist_heap<Type>::null_path_length() const
{
	if (root_node == nullptr) //if root is null pointer
		return -1;
	else
		return root_node->null_path_length(); //otherwise returns the node path length
}

template <typename Type>
Type Leftist_heap<Type>::top() const
{
	if (empty())
	{
		throw underflow(); //no top if it is empty, exception
	}
	return root_node->element; //return the element of the root, which is the top 
}

template <typename Type>
int Leftist_heap<Type>::count(Type const &obj) const
{
	int count = 0; //counter starts at 0
	if (root_node->retrieve() == obj) //if the root is equal to the argument
		count++; //increase the counter by 1
	count += root_node->left()->count(obj); //for every instance of the argument in the left, add 1 to the counter
	count += root_node->right()->count(obj); //for every instance of the argument in the right, add 1 to the counter
	return count; //return the final counter value
}

template <typename Type>
void Leftist_heap<Type>::push(Type const &obj)
{
	Leftist_node<Type> *new_node = new Leftist_node<Type>(obj); //creates a new node to add
	root_node->push(new_node, root_node); //adds the node to the heap


	heap_size++; // increase heap size by 1
}

template <typename Type>
Type Leftist_heap<Type>::pop()
{
	if (empty()) {
		throw underflow(); //if it is empty, nothing pops, exception
	}

	Type result = root_node->retrieve(); //gets the element of the root node
	Leftist_node<Type> * temp = root_node; // sets temporary node equal to the root
	root_node = temp->left(); //root of the left tree is made the new root
	
	if (temp->right())
		root_node->push(temp->right(), root_node); // The right tree of the original root node is pushed into the new root node

	delete temp; //delete old root
	heap_size--; //decrease heap size by one
	return result; //return the element of the popped node
}

template <typename Type>
void Leftist_heap<Type>::clear()
{
	if (!empty()) //as long as it's not empty
	{
		root_node->clear(); //clear the root
		root_node = 0; //root becomes zero
		heap_size = 0; //size becomes zero
	}
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<(std::ostream &out, Leftist_heap<T> const &heap) {
	return out;
}

// Is an error showing up in ECE2552.h or elsewhere?
// Did you forget a closing '}' ?

#endif