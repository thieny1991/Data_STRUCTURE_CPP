

#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include "ArgumentManager.h"

using namespace std;

void writeOutput(const char*, int);
bool readInput(const char*, char**&, int&);
int lcsOfLines( const char*);
int lcsOfThree(char*&, char*&, char*&, int, int, int);
int lcsOfFour(char*&, char*&, char*&, char*&,int, int, int, int);
int lcsOfTwo(char*&, char*&, int, int);
int max(int, int);
int max(int, int, int);
int max(int, int, int, int);

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "./Subsequence input=input1.txt;output=output1.txt" << std::endl;
		return -1;
	}

	//creating an Argument Manager object named am
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input"), outputFile = am.get("output");
	//cout << "Input file name: " << inputFile << endl
		//<< "Output file name: " << outputFile << endl;
	 {
		int lcs;
		lcs = lcsOfLines(inputFile.c_str());
		writeOutput(outputFile.c_str(), lcs);
	}
	 system("pause");
	return 0;
	}


/*
Function: lcsOfLines will be able to process a given file, compare each line in the file 
and return the length of the longest common sequences among the lines in the file
@para: const char*
@return: int 
*/
int lcsOfLines(const char* inputFile) {
	char **chPtr = NULL;;	//declare chPtr be a pointer to a pointer of char
	int line = 0;
	char* result=NULL;
	// if file is not empty and number of line>=2
	if (readInput(inputFile, chPtr, line)&&line>1){
		/*string str;
		result = chPtr[0];
		for (int i = 1;i <line ;i++) {
		str=commonSequence(result, chPtr[i]);
		strcpy(result, str.c_str());
		}//end for*/
		
		if (line == 2)
			return lcsOfTwo(chPtr[0], chPtr[1], strlen(chPtr[0]), strlen(chPtr[1]));
		else if (line == 3) {
			return lcsOfThree(chPtr[0], chPtr[1], chPtr[2],
				strlen(chPtr[0]), strlen(chPtr[1]), strlen(chPtr[2]));
		}//end if
		else if (line == 4) {
			return lcsOfFour(chPtr[0], chPtr[1], chPtr[2], chPtr[3],
				strlen(chPtr[0]), strlen(chPtr[1]), strlen(chPtr[2]), strlen(chPtr[3]));
		}//end else if
	}//end if
			return 0;// if number of string in file less than 2
}//end lcsOfLines
	
/*This function will return the length of the longest common sequence between two string
@para: char*, char*, int, int
@return: int
*/
int lcsOfTwo(char*&x, char*&y, int m, int n) {

	/*This method is very slow
	if (m == 0 || n == 0)
	returnT 0;
	if (x[m - 1] == y[n - 1])
	return lcsOfTwo(x, y, m - 1, n - 1) + 1;
	return  max(lcsOfTwo(x, y, m, n - 1), lcsOfTwo(x, y, m - 1, n));*/
	int len;
	int** matrix = new int*[m + 1];
	for (int i = 0; i < m + 1; i++)
		matrix[i] = new int[n + 1];

	/*method of Memoizing LCS
	creating an LCS matrix and find out the subsequence
	reference: http://www.cs.cmu.edu/afs/cs/academic/class/15451-s15/LectureNotes/lecture04.pdf
	*https://www.hackerrank.com/topics/longest-common-subsequence
	*https://www.ics.uci.edu/~eppstein/161/960229.html
	*/
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (i == 0 || j == 0) {
				matrix[i][j] = 0;
				//cout << matrix[i][j];
			}
			else if (x[i - 1] == y[j - 1]) {
				matrix[i][j] = matrix[i - 1][j - 1] + 1;
				//cout << matrix[i][j];
			}
			else {
				if (matrix[i - 1][j] > matrix[i][j - 1])
					matrix[i][j] = matrix[i - 1][j];
				else
					matrix[i][j] = matrix[i][j - 1];
			}// end else
		}
	}
	len = matrix[m][n];
		delete []matrix;
		matrix = NULL;
	return len;
}

int lcsOfThree(char*&x, char*&y, char*&z, int m, int n, int p) {
	int len;
	int ***matrix = NULL;
	matrix = new int**[m + 1];
	for (int i = 0;i < m + 1;i++) {
		matrix[i] = new int*[n + 1];
		for (int j = 0;j < n + 1;j++)
			matrix[i][j] = new int[p+1];
	}//end for

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			for (int k = 0; k <= p; k++)
			{
				if (i == 0 || j == 0 || k == 0)
					matrix[i][j][k] = 0;

				else if (x[i - 1] == y[j - 1] && x[i - 1] == z[k - 1])
					matrix[i][j][k] = matrix[i - 1][j - 1][k - 1] + 1;

				else
					matrix[i][j][k] = max(max(matrix[i - 1][j][k],
						matrix[i][j - 1][k]),
						matrix[i][j][k - 1]);
			}//end for
		}//end for
	}//end for
	len=matrix[m][n][p];
	delete []matrix;
	matrix = NULL;
	return len;
}


int lcsOfFour(char*&x, char*&y, char*&z, char*&t, int m, int n, int o, int p) {
	int len;
	int ****matrix = NULL;
	matrix = new int***[m + 1];
	for (int i = 0;i < m + 1;i++) {
		matrix[i] = new int**[n + 1];
		for (int j = 0;j < n + 1;j++) {
			matrix[i][j] = new int*[o + 1];
			for (int k = 0; k < o + 1; k++) {
				matrix[i][j][k] = new int[p +1];
			}//end for
		}
	}

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			for (int k = 0; k <= o; k++)
			{
				for (int h = 0; h <= p;h++)
				{
					if (i == 0 || j == 0 || k == 0 || h == 0)
						matrix[i][j][k][h] = 0;

					else if (x[i - 1] == y[j - 1] && x[i - 1] == z[k - 1] && x[i - 1] == t[h - 1]) {
						matrix[i][j][k][h] = matrix[i - 1][j - 1][k - 1][h - 1] + 1;
						//cout << matrix[i][j][k][h];
					}

					else
					{
						matrix[i][j][k][h] = max(matrix[i - 1][j][k][h], matrix[i][j - 1][k][h],
							matrix[i][j][k - 1][h], matrix[i][j][k][h - 1]);
						//cout << matrix[i][j][k][h];
					}
				}//end for
			}//end for
		}//end for

	}
	len=matrix[m][n][o][p];
	delete []matrix;
	matrix = NULL;
	return len;
}


bool readInput(const char* filename,char **&chPtr,int &countLine) {
	ifstream ifs(filename);// filename is c_string type
						   //why we don't need to open the file before processing
	const int MAX_LINE = 4;//max numbers of lines in the file
	chPtr = new char*[MAX_LINE];// create an array of MAX_LINE= char pointer

	string str;
	getline(ifs, str);
	// if file is empty, prompt to user
	if (str != "") {// not "\n" because getline doesn't get the newline character
		chPtr[countLine] = new char[str.size() + 1];//C-strings are null terminated
		strcpy(chPtr[countLine], str.c_str());
		countLine++;//increment the number of lines in the file 1 unit
	}//end if
	while (getline(ifs,str)) {
		if (str != "") {
			chPtr[countLine] = new char[str.size() + 1];//C-strings are null terminated
			strcpy(chPtr[countLine], str.c_str());
			countLine++;//increment the number of lines in the file 1 unit
			//cout << countLine;
		}//end if
		//getline(ifs, str);
	}//end while
	ifs.close();

	return true;
}//end readInput

void writeOutput(const char* filename, int len) {
	ofstream ofs(filename);
	ofs << "Len: " << len;
	ofs.close();
}


int max(int a, int b) {
	if (a >= b) {
		return a;
	}
	else return b;
}
int max(int a, int b, int c) {
	if (a >= max(b, c))
		return a;
	else
		return max(b, c);
}
int max(int a, int b, int c, int d) {
	if (a >= max(b, c, d))
		return a;
	else
		return max(b, c, d);
}