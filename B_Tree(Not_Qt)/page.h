#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <stdlib.h>
//#include <QList>
//#include <QString>
#include <vector>
#include <string>

typedef unsigned int uint;

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class Page
{
public:
    uint _t;
	vector<int> keys;
	vector<Page*> child;

	void addToKeys(int val); // adding to values durectly
    int GetKey(const uint id);
    Page* GetChildren(const uint id);
    bool SetKey(const uint id, const int val);
    bool SetChildren(const uint id, Page* val);
    bool AddChildren(Page* val);
    bool RemoveChildren(const uint id);
    bool RemoveKey(const uint id);
    bool AddKey(int val);
	bool IsList(Page* p);
    int Split(Page* right);
    uint GetPos(const int val);
    uint GetSize();
	void merge();

	uint GetDepth();

	Page* TurnLeft();
	Page* TurnRight();
	Page* SwapL();
	Page* SwapR();
	bool Balance(int* val, Page* rw);

    Page(uint t);
    ~Page();
};

#endif // PAGE_H
