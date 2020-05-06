#pragma once
#include<iostream>
#include<string>
using namespace std;

struct number {
	number *next;
	int data;
};
class numList {
private:
	number*head;
	number*last;
	int count;
public:
	numList();
	void addLast(number*newNum);
	void print();
	number * mergeList(number * first1, number * first2);
	number * mergeListR(number*first1, number*first2);
	void recursiveMergeSort(number *& head);
	void recursiveMergeSortR(number *& head);
	void mergeSort();
	void mergeSortR();
	void divideList(number * first1, number *& first2);
	int getDataAtIndex(int index);
	void writeOutPut(const char*);
	//void writeOutPutAtIndexes(const char*,vector<int>&indexList);
};
numList::numList() {
	numList::head = nullptr;
	numList::last = nullptr;
	count = 0;
}
void numList::addLast(number * newNum)
{
	if (head == 0) {
		head = newNum;
		last = head;
		head->next = 0;
	}
	else {
		last->next = newNum;
		last = last->next;
		last->next = 0;
	}
	count++;
}
void numList::print() {
	number *cu = numList::head;
	while (cu != 0) {
		std::cout << cu->data << " ";
		cu = cu->next;
	}
}

number * numList::mergeList(number * first1, number * first2)
{
	number *newHead;//to hold the new merged List 
	number *lastMerged;//pointer points to the last element 
						 // in the new merged list

	if (first1 == 0)return first2;//the first list is empty
	else if (first2 == 0) return first1;
	else {
		//compare the first node
		if (first1->data < first2->data) {
			newHead = first1;
			first1 = first1->next;
			lastMerged = newHead;
		}
		else {
			newHead = first2;
			first2 = first2->next;
			lastMerged = newHead;
		}
		while (first1 != 0 && first2 != 0) {
			if (first1->data < first2->data) {
				lastMerged->next = first1;
				lastMerged = lastMerged->next;
				first1 = first1->next;
			}
			else {
				lastMerged->next = first2;
				lastMerged = lastMerged->next;
				first2 = first2->next;
			}
		}
		if (first1 != 0) {//first list is not exhausted first
			lastMerged->next = first1;
		}
		else {
			lastMerged->next = first2;
		}
	}

	return newHead;
}


number * numList::mergeListR(number * first1, number * first2)
{
	number *newHead;//to hold the new merged List 
	number *lastMerged;//pointer points to the last element 
					   // in the new merged list

	if (first1 == 0)return first2;//the first list is empty
	else if (first2 == 0) return first1;
	else {
		//compare the first node
		if (first1->data > first2->data) {
			newHead = first1;
			first1 = first1->next;
			lastMerged = newHead;
		}
		else {
			newHead = first2;
			first2 = first2->next;
			lastMerged = newHead;
		}
		while (first1 != 0 && first2 != 0) {
			if (first1->data > first2->data) {
				lastMerged->next = first1;
				lastMerged = lastMerged->next;
				first1 = first1->next;
			}
			else {
				lastMerged->next = first2;
				lastMerged = lastMerged->next;
				first2 = first2->next;
			}
		}
		if (first1 != 0) {//first list is not exhausted first
			lastMerged->next = first1;
		}
		else {
			lastMerged->next = first2;
		}
	}

	return newHead;
}


void numList::recursiveMergeSort(number *& head)
{
	number *otherHead;
	if (head != 0 && head->next != 0) {
		divideList(head, otherHead);//otherHead was passed by reference
									//otherHead will point to the second list
									//after the list was splitted
		recursiveMergeSort(head);
		recursiveMergeSort(otherHead);
		head = mergeList(head, otherHead);
	}
}
void numList::recursiveMergeSortR(number *& head)
{
	number *otherHead;
	if (head != 0 && head->next != 0) {
		divideList(head, otherHead);//otherHead was passed by reference
									//otherHead will point to the second list
									//after the list was splitted
		recursiveMergeSortR(head);
		recursiveMergeSortR(otherHead);
		head = mergeListR(head, otherHead);
	}
}

void numList::mergeSort()
{
	recursiveMergeSort(head);
}

inline void numList::mergeSortR()
{
	recursiveMergeSortR(head);
}

void numList::divideList(number * first1, number *& first2)
{
	number *middle;
	number *current;
	//case 1 list is empty
	if (first1 == 0) first2 = 0;
	//case2: list contains one node
	else if (first1->next == 0) first2 = 0;
	else {
		middle = first1;
		current = first1->next;
		if (current != nullptr) current = current->next;
		while (current != nullptr) {
			middle = middle->next;
			current = current->next;
			if (current != 0) current = current->next;
		}//end while
		first2 = middle->next;
		middle->next = nullptr;
	}
}

inline int numList::getDataAtIndex(int index)// index already validated no need to check
{
	number*cu = head;
	if (index == 0) return cu->data;
	for (int i = 0;i <= index - 1;i++)
		cu = cu->next;
	return cu->data;
}

inline void numList::writeOutPut(const char* fileName)
{
	ofstream ofs(fileName);
	number *cu = numList::head;
	while (cu != 0) {
		ofs<< cu->data << " ";
		cu = cu->next;
	}
	ofs.close();
}

