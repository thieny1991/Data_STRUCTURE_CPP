
#include<stack>
#include<cmath>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<cassert>
#include<vector>
#include "ArgumentManager.h"

using namespace std;
template<class Type>
struct nodeType {
	Type info;
	nodeType<Type> *next;
};
template <class Type>
class Stack {
private:
	nodeType<Type> *stackTop;

public:
	Stack();
	bool isEmptyStack();
	void push(const Type& newItem);
	Type top();
	void pop();
};

template<class Type>
Stack<Type>::Stack()
{
	stackTop = 0;
}

template<class Type>
bool Stack<Type>::isEmptyStack()
{
	return (stackTop == nullptr);
}

template<class Type>
void Stack<Type>::push(const Type & newItem)
{
	nodeType<Type> *newNode = new nodeType<Type>;
	newNode->info = newItem;
	newNode->next = stackTop;
	stackTop = newNode;
}

template<class Type>
Type Stack<Type>::top()
{
	assert(stackTop != 0);//terminate program
	return stackTop->info;
}

template<class Type>
void Stack<Type>::pop()
{
	if (stackTop != 0) {
		nodeType<Type> *temp;
		temp = stackTop;
		stackTop = stackTop->next;
		delete temp;
	}
	else cout << "stack is empty" << endl;

}

bool readInputFile(const char* inputFile, vector<string>&expression);
void processPlusSign(Stack<char>&exStack);
void processNegativeSign(Stack<char>&exStack);
bool simplifyExpression(string str,Stack<char>& stack);
void validateExpression(vector<string>list,const char * outputFile );
bool isAPaired(char open, char close);
bool processClosedBracket(Stack<char>&bracketStack, char closedBracket);
long evaluateCubeOfAsciiValue(Stack<char>&expression);
bool minusBeforeBracket(Stack<char>&bracketStack);
void print(vector<string> list);
void checkStack(Stack<char> thisStack);


/*********************************ENTRY OF THE PROGRAM********************************/

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "sort input=input.txt output=output.txt" << std::endl;
		return -1;
	}
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outFile = am.get("output");
	vector<string> list;
	if (!readInputFile(inputFile.c_str(), list)) {
		ofstream ofs(outFile.c_str());
		return -2;
	}
		
	print(list);
	validateExpression(list,outFile.c_str());
	
	system("PAUSE");
	return 0;
}

bool readInputFile(const char* inputFile, vector<string>&list) {
	ifstream ifs(inputFile);
	string str;
	getline(ifs, str);
	if (str.empty() && ifs.eof()) {
		cout << "CANNOT READ INPUT FILE" << endl;
		return false;
	}
	do {
		if (!str.empty()&&str!="\r") list.push_back(str);
	} while (getline(ifs, str));
	ifs.close();
	return true;
}


void processPlusSign(Stack<char> &exStack) {
	if (exStack.isEmptyStack()) return;
	else if (exStack.top() == '+'||exStack.top()=='-') return;
	else exStack.push('+');
}
void processNegativeSign(Stack<char>& exStack)
{
	if (exStack.isEmptyStack()) exStack.push('-');
	else if (exStack.top() == '+') {
		exStack.pop();
		exStack.push('-');
	}
	else if (exStack.top() == '-') {
		exStack.pop();
		processPlusSign(exStack);//don't use push ('+') because it won't check if stack is empty
	}								// we don't add + sign when stack empty
	else exStack.push('-');
}

bool simplifyExpression(string str, Stack<char>&exStack)
{
	Stack<char> bracketStack;
	for (int i = 0; i < str.length();i++) {
		//if it is alphanumeric push to exstack
		if (isalnum(str[i])) {
			//if exStack is empty, but bracket Stack has - sign
			if (minusBeforeBracket(bracketStack)) {
				 processNegativeSign(exStack);
			}
			exStack.push(str[i]);
		}
		else if (str[i] == '+') {
			processPlusSign(exStack);
		}
		else if (str[i] == '-') {
		    processNegativeSign(exStack);
		}
		else if (str[i] == '{' || str[i] == '(' || str[i] == '[') {
			if (minusBeforeBracket(bracketStack)) {
				processNegativeSign(exStack);
			}
			bracketStack.push(str[i]);
			//check the sign in front of bracket, if '-' push it on bracketStack
			if (!exStack.isEmptyStack()) {
				if (exStack.top() == '-') {
					processNegativeSign(exStack);//pop -, add + to exStack
					bracketStack.push('-');//then push it to bracketStack for later use
				}
			}
		}
		else {// this function assume that there is no dirty data
			if (!exStack.isEmptyStack()) {
				if (exStack.top() == '-' || exStack.top() == '+') 
					if (minusBeforeBracket(bracketStack)) processNegativeSign(exStack);
			}
			if (!processClosedBracket(bracketStack, str[i])) return false;//can return false here
		}
	}

	if (!exStack.isEmptyStack() && !isalnum(exStack.top())) return false;
	else if (!bracketStack.isEmptyStack()) return false;
	else return true;
}

void validateExpression(vector<string> list, const char * outputFile)
{
	vector<vector<char>> simExpressions(list.size());//simplified expressions
	vector<Stack<char>> exStack(list.size());//expression stack
	ofstream ofs(outputFile);
	long value;
	long temp = 0;

	int countErr = 0;
	for (int i = 0;i < list.size();i++) {
		if (!simplifyExpression(list[i], exStack[i])) {
			cout << "Error at: " << i + 1 << endl;
			ofs << "Error at: " << i + 1 << endl;
			countErr++;
		}
		//checkStack(exStack[i]);
	}
	if (countErr == 0) {
		bool valid = true;
		if (!exStack[0].isEmptyStack()) {
			value = evaluateCubeOfAsciiValue(exStack[0]);
			for (int i = 1;i < exStack.size();i++) {
				temp = evaluateCubeOfAsciiValue(exStack[i]);
				if (value != temp) {
					valid = false;
					break;
				}
			}
		}//end if
		else {
			for (int i = 1;i < exStack.size();i++) {
				if (!exStack[i].isEmptyStack()) {//need to be updated in the server
					valid = false;
					break;
				}
			}
			
		}
		if (valid == true) ofs << "Yes";
		else ofs << "No";
	}
	ofs.close();
}

long evaluateCubeOfAsciiValue(Stack<char>&expr) {
	int sum = 0;
	vector<char> opStack;
	vector<long> ascStack;
	while (!expr.isEmptyStack()) {
		if (isalpha(expr.top())) ascStack.push_back(expr.top());
		else if (isdigit(expr.top())) ascStack.push_back(expr.top() -'0');
		else opStack.push_back(expr.top());
			expr.pop();
	}
	if (opStack.size() == ascStack.size()&&!opStack.empty()) {
		opStack.pop_back();
		if (ascStack.back() >= 0 && ascStack.back() <= 9) 
			sum = sum - ascStack.back();
		else	
			sum = sum - pow(ascStack.back(),3);
		ascStack.pop_back();

	}
	else {
		if (ascStack.back() >= 0 && ascStack.back() <= 9)
			sum = sum + ascStack.back();
		else
			sum = sum + pow(ascStack.back(), 3);
		ascStack.pop_back();
	}
	while (!ascStack.empty()&&!opStack.empty()) {
		if (opStack.back() == '+') {
			if (ascStack.back() >= 0 && ascStack.back() <= 9) sum = sum + ascStack.back();
			else sum = sum + pow(ascStack.back(), 3);
		}
		else {
			if (ascStack.back() >= 0 && ascStack.back() <= 9)
				sum = sum - ascStack.back();
			else
				sum = sum - pow(ascStack.back(), 3);
		}
		opStack.pop_back();
		ascStack.pop_back();
	}
	return sum;
}

bool minusBeforeBracket(Stack<char>& bracketStack)
{
	if (!bracketStack.isEmptyStack()) {
		if (bracketStack.top() == '-') return true;
		else return false;
	}
	else  false;
}

bool isAPaired(char open, char close)
{
	if (open == ('(') && close == (')')) return true;
	else if (open == ('[') && close == (']')) return true;
	else if (open == ('{') && close == ('}')) return true;
	else return false;
}



bool processClosedBracket(Stack<char>& bracketStack, char closedBracket)
{
	// pop the - sign if it is in stack

	if (bracketStack.isEmptyStack()) return false;// there is no open bracket
	if (bracketStack.top() == '-') bracketStack.pop();
	if (isAPaired(bracketStack.top(), closedBracket)) {
		bracketStack.pop();
		return true;
	}
	else	return false;
}



void print(vector<string> list)
{
	for (int i = 0;i < list.size();i++)
		cout << list[i] << endl;
	cout << endl;
}
void checkStack(Stack<char> thisStack) {
	while (!thisStack.isEmptyStack()) {
		cout << thisStack.top();
		thisStack.pop();
	}
}
