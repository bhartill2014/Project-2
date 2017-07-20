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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include "DynamicQueue.h"
#include <algorithm>

// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
private:
	Leftist_node *left_tree;
	Leftist_node *right_tree;
	int heap_null_path_length;
protected:
	Type element;
public:
	Leftist_node(Type const &);

	Type retrieve() const;
	bool empty() const;
	Leftist_node *left() const;
	Leftist_node *right() const;
	int count(Type const &) const;
	int null_path_length() const;

	void push(Leftist_node *, Leftist_node *&);
	void clear();

	template<typename Type> friend class Leftist_heap;
};

template <typename Type>
Leftist_node<Type>::Leftist_node(Type const &obj) :
element(obj),
left_tree(nullptr),
right_tree(nullptr),
heap_null_path_length(0) {
	// does nothing
}

// You may need this

template <typename Type>
Type Leftist_node<Type>::retrieve() const
{
	return element; //gets the element of the node
}

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return (this == nullptr); 
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const
{
	return left_tree; //returns address of left tree
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const
{
	return right_tree; //returns address of right tree
}

template <typename Type>
int Leftist_node<Type>::count(Type const &obj) const
{
	int count = 0; //counter starts at 0

	if (element == obj)
		count++; // If element is equal to the obj increase count by 1

	count += left_tree->count(obj); //recursively increase for the left tree if it has elements equal to obj
	count += right_tree->count(obj); //recursively increase for the right tree if it has elements equal to obj

	return count; //return the final counter value
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const
{
	return heap_null_path_length; //returns the path length
}

template <typename Type>
void Leftist_node<Type>::push(Leftist_node<Type> *new_heap, Leftist_node<Type> *&ptr_to_this)
{
	if (new_heap == nullptr) //if the heap is null
		return;

	
	else if (ptr_to_this == nullptr) //if empty
	{
		ptr_to_this = new_heap; //points to empty heap
		return;
	}

	if (new_heap->element < ptr_to_this->element) //if inserting value is smaller than the smallest element in heap
		std::swap(ptr_to_this, new_heap); //swap the values

	if (ptr_to_this->right_tree == nullptr) //no right subtree
		if (ptr_to_this->left_tree == nullptr) //no left subtree
			ptr_to_this->left_tree = new_heap; //insert as the left child
	
		else ptr_to_this->right_tree = new_heap; //insert as a right child if there already is a left
		
	else (push(new_heap, ptr_to_this->right_tree)); //recursively add to right subtree

	// If the heap's left tree has a null path length lower than that of the right tree, swap them
	if (ptr_to_this->left_tree && ptr_to_this->right_tree) //if there are right and left children
		if (ptr_to_this->left_tree->heap_null_path_length < ptr_to_this->right_tree->heap_null_path_length) //if left tree path is less than right tree path
			std::swap(ptr_to_this->left_tree, ptr_to_this->right_tree); //swap left and right trees

	if (ptr_to_this->right_tree) // point to right tree
		ptr_to_this->heap_null_path_length = ptr_to_this->right_tree->heap_null_path_length + 1; //the path length becomes the right path length plus one
}

template <typename Type>
void Leftist_node<Type>::clear()
{
	if (left_tree)
		left_tree->clear(); //deletes the left subtree if there is one
	if (right_tree)
		right_tree->clear(); //deletes the right subtree if there is one
	delete this; //deletes the pointer
}

#endif