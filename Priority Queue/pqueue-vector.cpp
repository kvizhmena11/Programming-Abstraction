/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	// TODO: Fill this in!
	return vectorElements.size();
}

bool VectorPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return vectorElements.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	vectorElements.push_back(value);
}
// i just wrote code to return smallest lexicographical 
// elemnt without removint it.
string VectorPriorityQueue::peek() {
	// TODO: Fill this in!
	// if its empty then write error comes up.
	if (vectorElements.isEmpty()) {
		error("vector of elements is empty and you cant peek now!!!");
	}
	else {
		string minLexiconWord = vectorElements[0];
		// if not then we iterate to find smallest one.
		for (int k = 1; k < vectorElements.size(); k++) {
			if (vectorElements[k] < minLexiconWord) {
				minLexiconWord = vectorElements[k];
			}
		}
		return minLexiconWord;
	}
	
}
// in this case we remove as well.
string VectorPriorityQueue::dequeueMin() {
	if (vectorElements.isEmpty()) {
		error("vector of elements is empty and you cant use dequeueMin method!!!");
	}
	else {
		string minLexiconWord = vectorElements[0];
		int minimumIndex = 0;
		// our job was to find smallest element index. and return it.
		for (int k = 1; k < vectorElements.size(); k++) {
			if (vectorElements[k] < minLexiconWord) {
				minLexiconWord = vectorElements[k];
				minimumIndex = k;
			}
		}
		
		// at the end we must remove smallest element.
		vectorElements.remove(minimumIndex);
		return minLexiconWord;
	}
	
}

