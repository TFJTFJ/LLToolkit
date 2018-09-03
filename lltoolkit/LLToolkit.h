#pragma once

#include"Node.h"

namespace LinkedList
{
	// Precondition: 
	// Postcondition: A new element containing 'data' is inserted at the head of the list pointed to by 'head'
	template<typename T>
	void headInsert(Node<T>*& head, const T& data)
	{
		head = new Node<T>(data, head);
	}

	// Precondition: 
	// Postcondition: The head element (if any) has been removed and 'head' is updated to point to the new 
	// head element
	template<typename T>
	void headRemove(Node<T>*& head)
	{
		if (head != nullptr)
		{
			Node<T>* condemned = head;
			head = head->next;
			delete condemned;
		}
	}


	// Precondition: 'prev' points to Node just before insertion point
	// Postcondition: A new Node with data=info has been inserted into the list after 'prev'
	template<typename T>
	void insert(Node<T>*& prev, const T& data)
	{
		if (prev != nullptr) prev->next = new Node<T>(data, prev->next);
	}


	// Precondition: 'prev' points to node immediately before the node to remove
	// Postcondition: The Node after 'prev' has been removed from the list 
	template<typename T>
	void remove(Node<T>*& prev)
	{
		if (prev == nullptr || prev->next == nullptr) return;

		Node<T>* condemned = prev->next;
		prev->next = condemned->next;
		delete condemned;
	}


	// Precondition: source is the head pointer of a linked list.
	// Postcondition: A pointer to a copy of the linked list is returned. The original list is 
	// unaltered.
	template<typename T>
	Node<T>* copy(Node<T>* source)
	{
		Node<T>* copyHead = nullptr;	// Head of the copy
		
		// Handle the case of the empty list.
		if (source == nullptr) return copyHead;

		// Make the head LLNode for the newly created list, and put data in it.
		headInsert(copyHead, source->info);
		Node<T>* tail = tail = copyHead;

		// Copy the rest of the nodes one at a time, adding at the tail of new list.
		for (source = source->next; source != nullptr; tail = tail->next, source = source->next)
		{
			insert(tail, source->info);
		}
		return copyHead;
	}



	// Precondition: 'head' is the head pointer of a linked list.
	// Postcondition: All nodes of the list have been deleted, and the 'head' is nullptr.
	template<typename T>
	void clear(Node<T>*& head)
	{
		while (head) headRemove(head);
	}


	// Precondition: 'head' is the head pointer of a linked list.
	// Postcondition: 'head' points to the start of a list that is reversed with respect to the 
	// original list
	template<typename T>
	void reverse(Node<T>*& head)
	{
		// If the list is either empty or contains only one 
		// element, reversal is trivial
		if (head == nullptr || head->next == nullptr) return;

		Node<T> * prev = head;
		Node<T> *n = prev->next;

		while (n != nullptr)
		{
			Node<T> *next = n->next;
			n->next = prev;

			prev = n;
			n = next;
		}
		head->next = nullptr;
		head = prev;
	}

	// Precondition: splitPtr points to the node before the split point
	// Postcondition: A pointer is returned that points to the first node after splitPtr. The 
	// original list ends at splitPtr
	template<typename T>
	Node<T>* split(Node<T>* splitPtr)
	{
		if (splitPtr == nullptr) return nullptr;

		Node<T>* newHead = splitPtr->next;
		splitPtr->next = nullptr;
		return newHead;
	}


	// Precondition: head1 and head2 each point to the head of linked lists 
	// Postcondition: head1 points to a list containing head1-lists' elements followed by head1-lists 
	// element.
	template<typename T>
	void join(Node<T>*& head1, Node<T>* head2)
	{

		if (head2 == nullptr) return;
		if (head1 == nullptr)
		{
			head1 = head2;
			return;
		}

		Node<T>* cursor = head1;

		// FF to end of list 1
		while (cursor->next != nullptr) cursor = cursor->next;

		// Join lists
		cursor->next = head2;
	}

	// Precondition: head points to the head of a linked list
	// Postcondition: The list is rotated left by once - if it was 1-2-3-4, it is now 2-3-4-1
	template<typename T>
	void rotateLeft(Node<T>*& head)
	{
		if (head == nullptr || head->next == nullptr) return;
		Node<T>* newHead = split(head);
		join(newHead, head);
		head = newHead;
	}


	// Precondition: head points to the head of a linked list
	// Postcondition: The list is rotated right once - if it was 1-2-3-4, it is now 4-1-2-3
	template<typename T>
	void rotateRight(Node<T>*& head)
	{
		if (head == nullptr || head->next == nullptr) return;
		Node<T>* splitPtr = head;
		Node<T>* newHead = head;

		// Find next-to-last
		while (splitPtr->next->next != nullptr) splitPtr = splitPtr->next;
		newHead = split(splitPtr);
		join(newHead, head);
		head = newHead;
	}

	// Precondition: values points to an array of at least size n
	// Postcondition: A pointer is returned that points to the head
	// of a list in which the nodes contains values from the array values
	template<typename T>
	Node<T>* build(T* values, int n)
	{
		Node<T>* head = nullptr;
		for (int i = n - 1; i >= 0; i--)
		{
			headInsert(head, values[i]);
		}
		return head;
	}
}


