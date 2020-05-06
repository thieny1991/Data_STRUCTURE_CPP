#include "bookLibrary.h"



/*****************************************************************************
*Function: defaul constructor
* Assign all member variables to null state
******************************************************************************/
bookLibrary::bookLibrary()
{
	first = 0;
	last = 0;
	current = 0;
	count = 0;
}

/*****************************************************************************
*Function: 
*@para:
*return:void
******************************************************************************/
void bookLibrary::addFirst(book *&newBook)
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
*Function:
*@para:
*return:void
******************************************************************************/
void bookLibrary::addLast(book *&newBook)
{
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
*Function:
*@para:
*return:void
******************************************************************************/
void bookLibrary::insertAt(int index, book *&newBook)
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
*Function:
*@para:
*return:void
******************************************************************************/
void bookLibrary::removeFirst()
{
	if (!isEmpty()) {
		if (count == 1) {//first->next=0
			delete first;
			first = 0;
			last = 0;
		}
		else {
			current = first;
			first->next->pre = 0;
			first = first->next;
			delete current;
			current = first;
		}
		count--;
	}
}
/*****************************************************************************
*Function:
*@para:
*return:void
******************************************************************************/
void bookLibrary::removeLast()
{
	if (!isEmpty()) {
		if (count == 1) {//first->next=0
			delete first;
			first = 0;
			last = first;
		}
		else {
			current = last;
			last->pre->next = 0;
			last = last->pre;
			delete current;
			current = last;
		}
		count--;
	}
}
/*****************************************************************************
*Function:
*@para:
*return:void
******************************************************************************/
bool bookLibrary::searchID(string id)
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
*Function:
*@para:
*return:void
******************************************************************************/
bool bookLibrary::isEmpty()
{
	return(first == 0);
}
/*****************************************************************************
*Function: 
*@para:
*return:void
******************************************************************************/
void bookLibrary::removeAt(int index)
{	
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
void bookLibrary::removeID(string id)
{
	//cout << "Test remove id" << id << endl;
	if (!isEmpty()) {
		current = first;
		while (current->bookID != id &&current->next != 0)
			current = current->next;
		//check if id was found
		if (current->bookID == id)
			removeAtCurrent();
	}//eif if
}
/*****************************************************************************
*Function: 
*@para:
*return:void
******************************************************************************/
void bookLibrary::removeAllTitle(string title)
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
*Function: 
*@para:
*return:void
******************************************************************************/
void bookLibrary::removeBookByAuthor(string author)
{
	//cout << "Remove book author " << author << endl;
	current = first;
	if (!isEmpty()) {
		while (current != 0) {
			if (current->author == author) {
				removeAtCurrent();// remove and update current
			}
			else
				current = current->next;
		}//end while
	}//end if
}

/*****************************************************************************
*Function: 
*@para: 
*return:void
******************************************************************************/


string bookLibrary::bookInfo(book *& aBook, string key)
{
	if (key == "book_id")
		return aBook->bookID;
	else if (key == "book_name")
		return aBook->name;
	else
		return aBook->author;
}

void bookLibrary::sort(string key)
{
	//cout << "test sort function" << endl;
			// first list has at least 2 element
	if (first !=0) {
		if (first->next != 0) {
			book* foo; // first out of order;
			book* cu = 0;
			book* temp = 0;
			foo = first->next;

			while (foo != 0) {
				if (bookInfo(foo, key) < bookInfo(foo->pre, key)) {
					/*|| ((bookInfo(foo, key) == bookInfo(foo->pre, key))
						&&(foo->bookID<foo->pre->bookID))){	*/
					cu = foo;
					temp = foo;
					do {
						cu = cu->pre;
					} while (cu->pre != 0 && bookInfo(cu->pre, key) > bookInfo(temp, key));

					//if foo is already the last element
					//no need to update foo
					if (foo == last) {
						last = foo->pre;
						last->next = 0;
						foo = 0;
						//temp->pre->next = 0;
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
						temp->pre = 0;
						//cout << "Test cu=first" << endl;

					}
					else {
						cu->pre->next = temp;
						temp->next = cu;
						temp->pre = cu->pre;
						cu->pre = temp;
						//cout << "Test cu is middle" << endl;

					}//end else
						//printList();
				}
				else
					foo = foo->next;
			}//end while		
		}//end else
	}
}

//end removeAllTitle

/*****************************************************************************
*Function:
*@para: 
*return:void
******************************************************************************/
void bookLibrary::removeAtCurrent()
{
	if (count == 1) {//first->next=0
		delete first;
		first = 0;
		last = 0;
		current = 0;
	}
	else if (current == first) {
		first->next->pre = 0;
		first = first->next;
		delete current;
		current = first;
	}
	else if (current == last)
	{
		last->pre->next = 0;
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
		temp = 0;
	}
	count--;
}


/*****************************************************************************
*Function:
*@para: 
*return:void
******************************************************************************/


void bookLibrary::printList()
{
	//case1: list is empty
	if (first == 0)
		cout << "Book List is empty";
	current = first;
	while (current != 0) {
		cout << "book_id:" << current->bookID << ", book_name:"
			<< current->name << ", book_author:" << current->author << endl;
		current = current->next;
	}
}

/*****************************************************************************
*Function: 
*@para: 
*return:void
******************************************************************************/
void bookLibrary::printR()
{
	current = last;
	while (current != 0) {
		cout << current->bookID << endl;
		current = current->pre;
	}
}

void bookLibrary::exportList(const char* outfile)
{
	//cout << "file name: " << outfile << endl;
	ofstream ofs(outfile);
	//case1: list is empty
	if (first != 0)
		current = first;
		while (current != 0) {
			ofs << "book_id:" << current->bookID << ", book_name:"
				<< current->name << ", book_author:" << current->author << endl;
			current = current->next;
		}

		ofs.close();
}




