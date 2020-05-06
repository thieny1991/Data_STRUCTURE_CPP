#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include"ArgumentManager.h"
#include"numList.h"



using namespace std;
/*--------------------INPUT-----------------------*/
bool readInputFile(const char* inputFile, vector<int>&list);
bool readCommandFile(const char*file,const char* outFile, vector<int>&list);
bool searchString(string str, string key);
bool isNumber(const std::string& s);
/*------------------QUICK SORT ------------------*/
void doQuickSort(string sortBy, vector<int>&list);
int partition(vector<int>&list, int first, int last);
void swap(vector<int>&list, int first, int second);
void recQuickSort(vector<int>&list, int first, int last);
void quickSort(vector<int>&list, int length);
int partitionR(vector<int>&list, int first, int last);
void recQuickSortR(vector<int>&list, int first, int last);
void quickSortR(vector<int>&list, int length);
/*------------------MERGE SORT-------------------*/
void doMergeSort(string&sortBy, vector<int>&list,numList& numLinkedList);
void createLinkedList(vector<int>&list, numList&linkedList);
void writeSortResult(const char* outFile, const char* cmdFile,  vector<int>&index, numList&linkedList );

/*------------------SHELL SORT-------------------*/
void doShellSort(string sortBy, vector<int>&list);
void shellSort(vector<int>&list);
//void intervalInsertionSortAscending(vector<int>&list, int begin, int end);

void shellSortD(vector<int>&list);
void intervalInsertionSortDescending(vector<int>&list, int begin, int inc);
/*--------------------OUTPUT--------------------*/
void printList(vector<int>&list);
void writeSortResult(const char* outFile,const char*cmdFile, vector<int>&list);

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "sort input=input31.txt output=output31.txt command=commandt31.txt" << std::endl;
		return -1;
	}
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outFile = am.get("output");
	string commandFile = am.get("command");
	vector<int>list;
	vector<int>indexList;
	//string sortMethod;//quick sort, merge sort, or shell sort
	//string sortBy;//ascending or descending

	if (!readInputFile(inputFile.c_str(), list))
		return -2;
	//printList(list);
	/*READ COMMAND FILE*/
	if (!readCommandFile(commandFile.c_str(),outFile.c_str(),list))
		return -1;
	//list.clear();
	//indexList.clear();
	return 0;
}


bool readInputFile(const char* inputFile, vector<int>& list) {
	ifstream ifs(inputFile);
	string str;
	getline(ifs, str);
	if (str.empty() && ifs.eof()) {
		cout << "Cannot read input file" << endl;
		return false;
	}
	int num;
	do {
		stringstream ss(str);
		while (!str.empty() && ss >> num) list.push_back(num); //a copy of num is inserted intoList at the end
	} while (getline(ifs, str));

	return true;
}

void printList(vector<int>&list)
{
	int len = list.size();
	for (int i = 0; i <len;i++)
		cout << list[i] << " ";
}


bool readCommandFile(const char*file,const char*outFile, vector<int>&list) {
	ifstream ifs(file);
	string str;
	getline(ifs, str);
	while (str.empty() && !ifs.eof()) getline(ifs, str);
	if (str.empty()) {
		cout << "Cannot open command file" << endl;
		return false;
	}
	int len = list.size();
	string sortBy;
	//Determine sortBy value
	if (searchString(str, "descending")) sortBy = "descending";
	else sortBy = "ascending";
	//Determine sortMethod
	if (searchString(str, "quick sort")) {
		doQuickSort(sortBy,list);
		writeSortResult(outFile, file, list);
	}
	else if (searchString(str, "shell sort")) {
		doShellSort(sortBy,list);
		writeSortResult(outFile, file, list);
	}
	else if (searchString(str, "merge sort")) {
		numList linkedList;
		createLinkedList(list,linkedList);
		doMergeSort(sortBy, list, linkedList);
		writeSortResult(outFile,file, list, linkedList);
	}
	else { cout << "can not find search command" << endl; return false; }
	
	return true;
}

bool searchString(string str, string key) {
	return (str.find(key) != string::npos);
}

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void doQuickSort(string sortBy, vector<int>& list)
{
	if (sortBy == "descending") quickSortR(list,list.size());//shellsort by descending;
	else quickSort(list,list.size());
}

/*****************************************************************************
*This section includes functions for quick sort method
*
******************************************************************************/
int partition(vector<int>&list, int first, int last)
{
	int pivot;
	int index, smallIndex;
	swap(list, first, (first + last) / 2);
	pivot = list[first];
	smallIndex = first;
	for (index = first + 1;index <= last;index++)
		if (list[index] < pivot) {
			smallIndex++;
			swap(list, smallIndex, index);
		}
	swap(list, first, smallIndex);
	return smallIndex;
}//end partition

void swap(vector<int>&list, int first, int second) {
	int temp;
	temp = list[first];
	list[first] = list[second];
	list[second] = temp;
}//end swap

void recQuickSort(vector<int>&list, int first, int last) {
	int pivotLocation;
	if (first < last) {
		pivotLocation = partition(list, first, last);
		recQuickSort(list, first, pivotLocation - 1);
		recQuickSort(list, pivotLocation + 1, last);
	}
}//end recQuickSort

void quickSort(vector<int>&list, int length) {
	recQuickSort(list, 0, length - 1);
}
/*******************************************************************************
*Quick Sort in Descending Order
********************************************************************************/

int partitionR(vector<int>&list, int first, int last)
{
	int pivot;
	int index, largeIndex;
	swap(list, first, (first + last) / 2);
	pivot = list[first];
	largeIndex = first;
	for (index = first + 1;index <= last;index++)
		if (list[index] > pivot) {
			largeIndex++;
			swap(list, largeIndex, index);
		}
	swap(list, first, largeIndex);
	return largeIndex;
}//end partition


void recQuickSortR(vector<int>&list, int first, int last) {
	int pivotLocation;
	if (first < last) {
		pivotLocation = partitionR(list, first, last);
		recQuickSortR(list, first, pivotLocation - 1);
		recQuickSortR(list, pivotLocation + 1, last);
	}
}//end recQuickSort

void quickSortR(vector<int>&list, int length) {
	recQuickSortR(list, 0, length - 1);
}

void doMergeSort(string & sortBy, vector<int>& list,numList &numLinkedList)
{
	if (sortBy == "descending") numLinkedList.mergeSortR();
	else numLinkedList.mergeSort();
}
/******************************************************************************
*This section includes functions for merge sort method
*******************************************************************************/
void createLinkedList(vector<int>&list, numList&linkedList) {
	int len = list.size();
	for (int i = 0;i <len;i++) {
		number *newNum = new number;
		newNum->data = list[i];
		linkedList.addLast(newNum);
	}
}

/******************************************************************************
*This section includes functions for shell sort method ascending
*******************************************************************************/

void doShellSort(string sortBy, vector<int>& list)
{
	if (sortBy == "descending") shellSortD(list);//shellsort by descending;
	else shellSort(list);
}

void shellSort(vector<int>&list) {
	int inc;
	int len = list.size();
	for (inc = 1;inc < (len - 1) / 9;inc = 3 * inc + 1);// change the subarrays 
	do {
		for (int begin = 0;begin < inc;begin++)
		{
			int foo;
			for (foo = begin + inc;foo<list.size();foo += inc) {
				if (list[foo] < list[foo - inc]) {
					int temp = list[foo];
					int loc = foo;
					do {
						list[loc] = list[loc - inc];
						loc = loc - inc;
					} while (loc > begin && list[loc - inc] > temp);
					list[loc] = temp;
				}//end if
			}//end for
		}//endfor
		inc = inc / 3;
	} while (inc>0);
}//end shellSort

 /******************************************************************************
 *This section includes functions for shell sort method descending
 *******************************************************************************/
void shellSortD(vector<int>&list) {
	int inc;
	int len = list.size();
	for (inc = 1;inc < (len - 1 / 9);inc = 3 * inc + 1);// change the subarrays 
	do {
		for (int begin = 0;begin < inc;begin++)
			intervalInsertionSortDescending(list, begin, inc);
		inc = inc / 3;
	} while (inc > 0);
}//end shelSort

void intervalInsertionSortDescending(vector<int>&list, int begin, int inc) {
	int foo;
	int len = list.size();
	for (foo = begin + inc;foo<len;foo += inc) {
		if (list[foo] > list[foo - inc]) {
			int temp = list[foo];
			int loc = foo;
			do {
				list[loc] = list[loc - inc];
				loc = loc - inc;
			} while (loc > begin && list[loc - inc] < temp);
			list[loc] = temp;
		}//end if
		else;
	}//end for
}

/******************************************************************************
*This section includes functions write output to the file
*******************************************************************************/
void writeSortResult(const char * outFile, const char* cmdFile, vector<int>&list)
{
	ifstream ifs(cmdFile);
	ofstream ofs(outFile);
	string word;
	int index;
	string str;
	getline(ifs, str);

	do {
		stringstream ss(str);
		while (ss >> word) {
			if (isNumber(word)) {
				index = stoi(word);
				if (index >= 0 && index < list.size())
					ofs << list[index] << " ";
			}
		}
	}
		while (getline(ifs, str));
		ofs.close();
		ifs.close();
}

	void writeSortResult(const char * outFile, const char *cmdFile, vector<int>&list, numList &linkedList)
	{
		ifstream ifs(cmdFile);
		ofstream ofs(outFile);
		
		string word;
		int index;
		string str;
		getline(ifs, str);
		do {
			stringstream ss(str);
			while (ss >> word) {
				if (isNumber(word)) {
					index = stoi(word);
					if (index >= 0 && index < list.size())
					{
						ofs << linkedList.getDataAtIndex(index) << " ";
					}
				}
			}
		}
			while (getline(ifs, str));
			ofs.close();
			ifs.close();
	}
