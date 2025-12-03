/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"
//i used dummy element at first index and afterwards i added
// spaces with empty strings the size of capacity.
HeapPriorityQueue::HeapPriorityQueue() {
	// TODO: Fill this in!
	numbOfElements = 0;
	string empty = "";
	heapVector.add(empty);
	capacity = START_CAPACITY;

	for (int k = 0; k < capacity; k++) {
		heapVector.add(empty);
	}
}

HeapPriorityQueue::~HeapPriorityQueue() {
	// TODO: Fill this in!

}

int HeapPriorityQueue::size() {
	// TODO: Fill this in!
	
	return numbOfElements;
}

bool HeapPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return numbOfElements == 0;
}
//so in this code if we exceed the capacity we just use
// expandCapacityu method. and afterwards we place value .
void HeapPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	numbOfElements++;
	if (numbOfElements>=heapVector.size()) {
		expandCapacity();
	}
	heapVector[numbOfElements] = value;
	bubbleUp(numbOfElements);
}
//i just returned the smallest element.
string HeapPriorityQueue::peek() {
	// TODO: Fill this in!
	if (!isEmpty()) {
		return heapVector[1];
	}
	else {
		error("you cant peek because heap is empty");
	}
	
}
// i just moved the last to root then decreased the size of numbOfElements
// and restored heap.and returned minimum.
string HeapPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (!isEmpty()) {
		
		string minimum = heapVector[1];
		heapVector[1] = heapVector[numbOfElements];
		numbOfElements--;
		bubbleDown(1);
		return minimum;
	}
	else {
		error("you cant use dequeueMin method because heap is empty");
	}
}
// with this method i restored the heap order going up.
// if the value is smaller then its parents index then we swap.
void HeapPriorityQueue::bubbleUp(int currIndex) {
	int indexOfParent = currIndex / 2;
	while (true) {
		if (currIndex <= 1 || heapVector[currIndex] >= heapVector[indexOfParent]) break;
			swapIndex(currIndex, indexOfParent);
			currIndex = indexOfParent;
			indexOfParent = currIndex / 2;
		}
}
// and with this method i restored the heap goind down. first we
// compare curr with the left one and then curr min with the rightone.
// if this code manages to find the minimum of the the childs
// we swap again and use recursive method and bubledown on that value.
void HeapPriorityQueue::bubbleDown(int currIndex) {
	int minimum = currIndex;
	int rightOne = currIndex * 2 + 1;
	int leftOne = currIndex * 2;

	if (rightOne <= numbOfElements && heapVector[rightOne] < heapVector[minimum]) {
		minimum = rightOne;
	}
	if (leftOne <= numbOfElements && heapVector[leftOne] < heapVector[minimum]) {
		minimum = leftOne;
	}
	if (currIndex != minimum) {
		swapIndex(currIndex, minimum);
		bubbleDown(minimum);
	}
}
// as i mentioned earlier we double our capacity.
void HeapPriorityQueue::expandCapacity() {
	capacity *= 2;
	string empty = "";
	for (int i = heapVector.size(); i <= capacity; i++) {
		heapVector.add(empty);   
	}
}
// we swap indexes.
void HeapPriorityQueue::swapIndex(int index1, int index2) {
	string stored = heapVector[index1];
	heapVector[index1] = heapVector[index2];
	heapVector[index2] = stored;
}
