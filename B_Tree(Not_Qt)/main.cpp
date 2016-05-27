#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

typedef unsigned int uint;

//using namespace std;

#include "b_tree.h"
#include "page.h"
#include "TreeWalker.h"

#define TREE_PW 2

bool contains(vector<int>* v, int val)
{
	for (uint i = 0; i < v->size(); i++)
	{
		if (v->at(i) == val)
		{
			return true;
		}
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////////

void testSorted(int c, TreeWalker* trw, std::ostream* out) //const string s)
{
	clock_t b;
	clock_t e;
	B_Tree* tr = new B_Tree(TREE_PW);
	trw->print(*out, *tr);
	trw->printData(*out, "\nAdding ");
	trw->printData(*out, c);
	trw->printData(*out, " elements sorted: \n");
 	b = clock();
	for (int i = 1; i <= c; i++)
	{
		tr->Paste(i);
	}
	e = clock();
	trw->printData(*out, "Time: ");
	trw->printData(*out, (e - b) / 1000.0);
	trw->printData(*out, " seconds\n");
	trw->print(*out, *tr);
	delete tr;
}
//////////////////////////////////////////////////////////////////////////////

void testUnsorted(int c, TreeWalker* trw, std::ostream* out)// const string s)
{
	vector<int> v;
	clock_t b;
	clock_t e;
	B_Tree* tr = new B_Tree(TREE_PW);
	trw->print(*out, *tr);
	trw->printData(*out, "\nAdding ");
	trw->printData(*out, c);
	trw->printData(*out, " elements unsorted: \n");
	v.clear();
	srand((unsigned int)time(NULL));
	unsigned int t;
	b = clock();
	for (int i = 1; i <= c; i++)
	{
		t = rand() % c;
		while (contains(&v, t))
		{
			t = rand() % c;
		}
		tr->Paste(t);
		v.push_back(t);
	}
	e = clock();
	trw->printData(*out, "Time: ");
	trw->printData(*out, (e - b) / 1000.0);
	trw->printData(*out, " seconds\n");
	trw->print(*out, *tr);
	delete tr;
}
//////////////////////////////////////////////////////////////////////////////

void testZeroLen(int c, TreeWalker* trw, std::ostream* out)//const string s)
{
	vector<int> v;
	clock_t b;
	clock_t e;
	B_Tree* tr = new B_Tree(TREE_PW);
	trw->print(*out, *tr);
	trw->printData(*out, "\nAdding ");
	trw->printData(*out, c);
	trw->printData(*out, " an element: \n");
	v.clear();
	srand((unsigned int)time(NULL));
	unsigned int t;
	b = clock();
	t = rand() % c;
	while (contains(&v, t))
	{
		t = rand() % c;
	}
	tr->Paste(t);
	if (tr->GetVal(0) != t) trw->printData(*out, "Unsuccessful pasting!");
	tr->Remove(0);
	tr->Remove(0);
	trw->printData(*out, "The element is successfully removed from the tree, additional removing action is skipped.");
	v.push_back(t);
	e = clock();
	trw->printData(*out, "Time: ");
	trw->printData(*out, (e - b) / 1000.0);
	trw->printData(*out, " seconds\n");
	trw->print(*out, *tr);
	delete tr;
}
//////////////////////////////////////////////////////////////////////////////

int main()
{
	std::ofstream fout;
	fout.open("out.txt");
	std::ostream* out = &fout;


	//std::ostream* out = &cout;

	B_Tree* tr;
	{
		tr = new B_Tree(TREE_PW);
	}

	TreeWalker* trw = new TreeWalker();

	trw->printData(*out, "An empty tree:    ");
	trw->print(*out, *tr);
	//cout << *tr;
	for (int j = 1; j < 66; j++)
	{
		tr->Paste(j);
	}
	trw->print(*out, *tr);
	if (tr != NULL)
		delete tr;
	for (int k = 25; k < 5000; k *= 2)
	{
		testSorted(k, trw, out);
		testUnsorted(k, trw, out);
	}
	testZeroLen(1, trw, out);

	delete[] trw;
	delete[] tr;
	system("pause");
    return 0;
}