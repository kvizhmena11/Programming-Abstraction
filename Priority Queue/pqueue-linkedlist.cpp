/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	// TODO: Fill this in!
	numbOfElements = 0;
	smallHead = nullptr;
}
// in this method we store our current head and after we delete old node.
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	// TODO: Fill this in!
	while (true) {
		if (smallHead == nullptr) {
			break;
		}
		linkedStruct* curr = smallHead;
		smallHead = smallHead->linked;
		delete curr;
	}
}

int LinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	
	return numbOfElements;
}

bool LinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return numbOfElements==0;
}
//first we create a new node called currCellvand with values.
void LinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	linkedStruct* currCell = new linkedStruct;
	currCell->linked = nullptr;
	currCell->value = value;

	linkedStruct* curr = smallHead;
	
	// until we dont find the right place to insert this loop continues.
	if (smallHead != nullptr&& value >= smallHead->value) {
		while (true) {
			if (curr->linked == nullptr || curr->linked->value > value)
				break;
			curr = curr->linked;
		}
		currCell->linked = curr->linked;
		curr->linked = currCell;
	}
	else {
		currCell->linked = smallHead;
		smallHead =currCell;
	}

	numbOfElements++;
}

string LinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	
	if (!isEmpty()) {
		return smallHead->value;
	}
	else {
		error("you cant peek in there because its empty!!!");
	}
}
// we save the value and decrease numbOfelements.
string LinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (!isEmpty()) {
		linkedStruct* deleteHead = smallHead;
		smallHead = smallHead->linked;
		string res = deleteHead->value;
		delete deleteHead;
		numbOfElements--;
		return res;

	}
	else {
		error("you cant use dequeueMin method because its empty!!!");
	}
}

