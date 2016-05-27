#include "TreeWalker.h"

TreeWalker::TreeWalker()
{

}

TreeWalker::~TreeWalker()
{
	
}

void TreeWalker::print(std::ostream & os, B_Tree& tr)
{
	os << tr;
}

template<typename TYPE> inline void printData(TYPE data)
{
	*os << data;
}

std::ostream &operator<<(std::ostream& str, B_Tree& b)
{
	vector<Page*> v;// = new QList<Page*>();
	vector<Page*> v2;// = new QList<Page*>();
	v.push_back(b.getRoot());
	bool work = true;
	uint h = b.getHeight();
	if (b.getRoot()->keys.size() == 0)
	{
		str << "__" << endl;
		return str;
	}
	else
		while (v.size()>0 && work)
		{
			work = false;
			string space;
			//Page* buff;
			for (uint k = 0; k<h * 2; k++)
				space += " ";
			str << space;
			h--;
			v2.clear();
			for (uint i = 0; i < v.size(); i++)
			{
				if (v[i] != NULL)
				{
					for (uint j = 0; j < v[i]->GetSize(); j++)
					{
						v2.push_back(v[i]->GetChildren(j));
						str << v[i]->GetKey(j) << ";";
						if (v[i]->GetChildren(j) != NULL)
							work = true;
					}
					v2.push_back(v[i]->GetChildren(v[i]->GetSize()));
					if (v[i]->GetChildren(v[i]->GetSize()) != NULL)
						work = true;
					str << "  ";
				}
				else
				{
					str << "N;" << " ";
					v2.push_back(NULL);
				}
			}
			str << endl;
			str << space;
			if (work)
				for (uint i = 0; i < v.size(); i++)
				{
					if (v[i] != NULL)
					{
						uint s = v[i]->GetSize();
						for (uint j = 0; j <= s; j++)
						{
							if ((float)j < s / 2.0)
								str << "/" << " ";
							else if ((float)j == s / 2.0)
								str << "|" << " ";
							else
								str << "\\" << " ";
						}
					}
					else
						str << "   ";
				}
			str << endl;
			v = v2;
			v2.clear();
		}
	return str;
}
