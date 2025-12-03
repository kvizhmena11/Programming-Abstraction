/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	numbOfElements = 0;
	smallHead = nullptr;
}
// we delete head "smallHead" node and continue;
DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	while (true) {
		if (smallHead == nullptr) {
			break;
		}
		doublyLinkedStruct* curr = smallHead;
		smallHead = smallHead->nextOne;
		delete curr;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	
	return numbOfElements;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return numbOfElements == 0;
}
// we link the previous old head to new one and then update it.
void DoublyLinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	doublyLinkedStruct* currNode = new doublyLinkedStruct;
	currNode->previousOne = nullptr;
	currNode->nextOne = smallHead;
	currNode->value = value;
	if (smallHead != nullptr) {
		smallHead->previousOne = currNode;
	}
	numbOfElements++;
	smallHead = currNode;
}
// again the loop continues until we find the smallest value.
string DoublyLinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	if (!isEmpty()) {
		doublyLinkedStruct* currHead = smallHead;
		string lowestValue = currHead->value;
		while (true) {
			if (currHead == nullptr) {
				break;
			}
			if (currHead->value >= lowestValue) {
				currHead = currHead->nextOne;
			}
			else {
				lowestValue = currHead->value;
				currHead = currHead->nextOne;
			}
		}

		return lowestValue;
	}

	else {
		error("you can not physically peek because its empty!!!");
	}
}
// first we find the minimum value of the node.and after we store
// the result, delete the node and finally return the result.
string DoublyLinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (!isEmpty()) {
		doublyLinkedStruct* minimumHead = smallHead;
		for (doublyLinkedStruct* currHead = smallHead->nextOne; currHead != nullptr; currHead = currHead->nextOne) {
			if (minimumHead->value > currHead->value) {
				minimumHead = currHead;
			}
		}
		if (!minimumHead->previousOne) {
			smallHead = minimumHead->nextOne;
		}
		else {
			minimumHead->previousOne->nextOne = minimumHead->nextOne;
		}

		if (minimumHead->nextOne) {
			minimumHead->nextOne->previousOne = minimumHead->previousOne;
		}
		string res = minimumHead->value;
		numbOfElements--;
		delete minimumHead;
		return res;

	}
	else {
		error("you cant use the method dequeueMIn because its empty!!!");
	}
}

