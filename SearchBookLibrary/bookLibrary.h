
#pragma once
#include<iostream>
#include <string>
#include<fstream>
using namespace std;

struct book {
	book *pre;
	string bookID;
	string name;
	string author;
	book *next;
};

class bookLibrary {
private:
	book *first;
	book *last;
	book *current;
	int count;
	void removeAtCurrent();
public:

	bookLibrary();
	//bookLibrary(const bookLibrary& other);
	//Default constructer
	//set pointer first, last, current to null state
	//set the number of books to zero
	void addFirst(book*&);
	void addLast(book*&);
	void insertAt(int index, book *&);
	void removeFirst();
	void removeLast();
	bool searchID(string id);
	bool isEmpty();
	void removeAt(int);
	void removeID(string id);
	void removeAllTitle(string title);
	void removeBookByAuthor(string aut);
	string bookInfo(book *&aBook, string key);
	void sort(string key);
	void printList();
	void printR();
	void exportList(const char*);
};