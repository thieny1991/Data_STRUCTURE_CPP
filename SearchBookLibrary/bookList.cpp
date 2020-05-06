#include "bookList.h"



/*****************************************************************************
*Function: defaul constructor 
* Assign all member variables to null state
******************************************************************************/
bookList::bookList()
{
	first = 0;
	last = 0;
	current = 0;
	count = 0;
}

/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::addFirst(book *&newBook)
{
	if (!searchID(newBook->bookID)) {
		//create a newBook
		//case1: List is empty
		if (first == 0) {
			first = newBook;
			last = first;

		}
		else {
			newBook->next = first;
			first->pre = newBook;
			first = newBook;
		}
		count++;
	}
}


/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::addLast(book *&newBook)
{
	//cout << searchID(newBook->bookID) << endl;
	if (!searchID(newBook->bookID)) {
		//case1: List is empty
		if (first == 0)
		{
			first = newBook;
			last = first;
		}
		else {
			last->next = newBook;
			newBook->pre = last;
			last = newBook;
		}
		count++;
	}
}

/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::insertAt(int index, book *&newBook)
{

	//if the book is not in the list
	if (!searchID(newBook->bookID)) {
		//if index number does not exist in the list add the record at the end
		if (index<0 || (index>count - 1))
			addLast(newBook);
		else if (index == 0)
			addFirst(newBook);
		else
		{	
			//trace the list from begin
			current = first;
			//locate the book at given index
			for (int i = 0;i <= index - 1;i++) {
				current = current->next;
			}
			//insert the newBook at given index
			current->pre->next = newBook;
			newBook->next = current;
			newBook->pre = current->pre;
			current->pre = newBook;
			count++;
		}
	}
}


/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::removeFirst()
{
	if (!isEmpty()) {
		if (count == 1) {//first->next=0
			delete first;
			first = nullptr;
			last = nullptr;
		}
		else {
			current = first;
			first->next->pre = nullptr;
			first = first->next;
			delete current;
			current = first;
		}
		count--;
	}
}
/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::removeLast()
{
	if (!isEmpty()) {
		if (count == 1) {//first->next=nullptr
			delete first;
			first = nullptr;
			last = first;
		}
		else {
			current = last;
			last->pre->next = nullptr;
			last = last->pre;
			delete current;
			current = last;
		}
		count--;
	}
}
/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
bool bookList::searchID(string id)
{
	if (isEmpty())
		return false;
	else
	{
		book *trace;
		trace = first;
		//if book is not found, and not pass the end of list
		while (trace->bookID != id&& trace->next != 0)
		{
			trace = trace->next;
		}
		//check if the book id is found
		return (trace->bookID == id);
	}
}
/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
bool bookList::isEmpty()
{
	return(first == 0);
}
/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::removeAt(int index)
{
	//cout << "count" <<count << endl;
	//if index is valid
	if (index >= 0 && index < count) {
		//if not an invalid index
		if (index == 0) {
			current = first;
		}
		else if (index == count - 1) {
			current = last;
		}
		else {
			//locate index
			current = first;
			for (int i = 0; i < index;i++) {
				current = current->next;
			}
		}//end else
		removeAtCurrent();
	}//end if
}
void bookList::removeID(string id)
{
	if (!isEmpty()) {
		current = first;
		while (current->bookID != id &&current != 0)
			current = current->next;
		//check if id was found
		if (current->bookID == id)
			removeAtCurrent();
	}//eif if
}
/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::removeAllTitle(string title)
{
	current = first;
	if (!isEmpty()) {
			while (current != 0) {
				if (current->name == title)
					removeAtCurrent();
				else
					current = current->next;
			}//end while
	}//end if
}

/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::removeBookByAuthor(string author)
{
	current = first;
	if (!isEmpty()) {
		while (current != 0) {
			if (current->author == author)
				removeAtCurrent();// remove and update current
			else
				current = current->next;
		}//end while
	}//end if
}

/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::sortById()
{	// first list has at least 2 element
	if (first->next != 0) {
		book* foo; // first out of order;
		book* cu = 0;
		book* temp=0;
		foo = first->next;
			while(foo!=0){
				if (foo->bookID < foo->pre->bookID) {
					cu = foo;
					temp = foo;
					do {
						cu = cu->pre;
					} while (cu->pre != 0 && cu->pre->bookID > temp->bookID);


					//if foo is already the last element
					//no need to update foo
					if (foo == last) {
						last = foo->pre;
						last->next = nullptr;
						foo = nullptr;
						//temp->pre->next = nullptr;
					}
					else {
						temp = foo;
						//update first of of order foo
						foo = foo->next;
						temp->pre->next = foo;
						foo->pre = temp->pre;
						
					}
					if (cu == first) { // temp>the first element
						temp->next = first;
						first->pre = temp;
						first = temp;
						temp->pre = nullptr;
						cout << "Test cu=first" << endl;

					}
					else {
						cu->pre->next = temp;
						temp->next = cu;
						temp->pre = cu->pre;
						cu->pre = temp;
						cout << "Test cu is middle" << endl;
						//printList();
					}//end else
				//	printList();
					cout << endl;
				}
			}//end while		
		}//end else
	//printList();
	}

void bookList::sortByTitle()
{
}

string bookList::bookInfo( book *& aBook,string key)
{	
	if (key == "book_id")
		return aBook->bookID;
	else if (key == "book_name")
		return aBook->name;
	else if (key == "book_author")
		return aBook->author;
	else;
}

void bookList::sort(string key)
{	// first list has at least 2 element
	if (first->next != 0) {
		book* foo; // first out of order;
		book* cu = 0;
		book* temp = 0;
		foo = first->next;
		while (foo != 0) {
			if (bookInfo(foo,key) < bookInfo(foo->pre,key)) {
				cu = foo;
				temp = foo;
				do {
					cu = cu->pre;
				} while (cu->pre != 0 && bookInfo(cu->pre,key) > bookInfo(temp,key));


				//if foo is already the last element
				//no need to update foo
				if (foo == last) {
					last = foo->pre;
					last->next = nullptr;
					foo = nullptr;
					//temp->pre->next = nullptr;
				}
				else {
					temp = foo;
					//update first of of order foo
					foo = foo->next;
					temp->pre->next = foo;
					foo->pre = temp->pre;

				}
				if (cu == first) { // temp>the first element
					temp->next = first;
					first->pre = temp;
					first = temp;
					temp->pre = nullptr;
					cout << "Test cu=first" << endl;

				}
				else {
					cu->pre->next = temp;
					temp->next = cu;
					temp->pre = cu->pre;
					cu->pre = temp;
					cout << "Test cu is middle" << endl;
					//printList();
				}//end else
				 //	printList();
				cout << endl;
			}
		}//end while		
	}//end else
	 printList();
}

//end removeAllTitle

/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::removeAtCurrent()
{	
		if (count==1) {//first->next=0
			delete first;
			first = nullptr;
			last = nullptr;
			current = 0;
		}
		else if(current ==first){
			first->next->pre = nullptr;
			first = first->next;
			delete current;
			current = first;
		}
		else if (current == last)
		{
			last->pre->next = nullptr;
			last = last->pre;
			delete current;
			current = last;
		}
		else {
			book *temp = current;
			current = current->next;
			temp->pre->next = current;
			current->pre = temp->pre;
			delete temp;
			temp = nullptr;
		}
		count--;
	}


/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
/*book* bookList::bookInfo(string id, string title, string aut){
book *newBook = new book;
newBook->pre = nullptr;
newBook->bookID = id;
newBook->name = title;
newBook->author = aut;
newBook->next = nullptr;	
return newBook;
}*/

void bookList::printList()
{
	//case1: list is empty
	if (first == 0)
		cout << "Book List is empty";
	current = first;
	while (current!= 0) {
		cout << "book_id:" << current->bookID << ", book_name:"
			<< current->name << ", book_author:" << current->author << endl;
		current = current->next;
	}
}

/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim
*@para: const char**& matrix, int
*return:void
******************************************************************************/
void bookList::printR()
{
	current = last;
	while (current != 0) {
		cout << current->bookID << endl;
		current = current->pre;
	}

}

void bookList::exportList(const char* outfile)
{
	ofstream ofs(outfile);
	//case1: list is empty
	if (first == 0)
		ofs << "Book List is empty" << endl;
	else {
		current = first;
		while (current != 0) {
			ofs << "book_id:" << current->bookID << ", book_name:"
				<< current->name << ", book_author:" << current->author << endl;
			current = current->next;
		}
	}

}




