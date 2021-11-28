#include<iostream>
#include<string>

using namespace std;
struct Formula
{
	char data = 0;
	Formula* left = NULL, * right = NULL;
};

void printTreePost(Formula* symbol)
{
	if (!symbol) return;
	printTreePost(symbol->left);
	printTreePost(symbol->right);
	cout << symbol->data;
}

void printTreePre(Formula* symbol)
{
	if (!symbol) return;
	cout << symbol->data;
	printTreePre(symbol->left);
	printTreePre(symbol->right);
}

void printTreeIn(Formula* symbol)
{
	if (!symbol) return;
	printTreeIn(symbol->left);
	cout << symbol->data;
	printTreeIn(symbol->right);
}

int answerFormula(Formula* symbol)
{
	int answer = 0;
	if (!symbol->left)
	{
		answer = symbol->data - '0';
	}
	else
	{
		switch (symbol->data)
		{
		case '+':
			answer = answerFormula(symbol->left) +
				answerFormula(symbol->right);
			break;
		case '-':
			answer = answerFormula(symbol->left) -
				answerFormula(symbol->right);
			break;
		case '*':
			answer = answerFormula(symbol->left) *
				answerFormula(symbol->right);
			break;
		}
	}
	return answer;
}

void scanTree(Formula* firstSymbol) {
	string input;
	Formula* nowSymbol;
	int bracket = 0;

	getline(cin, input);
	for (int i = 0; input[i]; i++)
	{
		if (input[i] != ' ') {
			if (input[i] == '(')
				bracket++;
			else
				if (input[i] == ')')
					bracket--;
				else
				{
					nowSymbol = firstSymbol;
					int n = bracket;
				if ((input[i] == '+') || (input[i] == '*') || (input[i] == '-'))
						n--;
					for (int j = 0; j < n; j++)
					{
						if ((nowSymbol->data == '+') || (nowSymbol->data == '*') || (nowSymbol->data == '-'))
						{
							if (!nowSymbol->right) nowSymbol->right = new Formula;
							nowSymbol = nowSymbol->right;
						}
						else
						{
							if (!nowSymbol->left) nowSymbol->left = new Formula;
							nowSymbol = nowSymbol->left;
						}
					}
					nowSymbol->data = input[i];
				}
		}
	}
}

int main()
{
	Formula firstSymbol;
	scanTree(&firstSymbol);
	printTreePre(&firstSymbol);
	cout << "\n";
	printTreeIn(&firstSymbol);
	cout << "\n";
	printTreePost(&firstSymbol);
	cout << "\n";
	cout << "\n" << answerFormula(&firstSymbol);
	return 0;
}
