#include "page.h"

Page::Page(uint t)
{
    _t = t;
	child = vector<Page*>();
	keys = vector<int>();
    child.push_back(NULL);	
}

Page::~Page()
{
    this->keys.clear();
    this->child.clear();
}

uint Page::GetDepth()
{
	uint max = 0;
	for (uint i = 0; i < this->child.size(); i++)
	{
		if (this->child[i] != NULL)
		{
			uint len = this->child[i]->GetDepth();
			if (max < len) max = len;
		}
	}
	return max+1;
}

int Page::GetKey(const uint id)
{
	if (keys.size()>0)
		return this->keys[id];
	return 0;
}

Page* Page::GetChildren(const uint id)
{
    if (this->child.size()>id) return this->child[id];
    else return NULL;
}

bool Page::SetKey(const uint id, const int val)
{
    if (id < (this->keys.size()))
    {
        this->keys[id] = val;
        return true;
    }
    return false;
}

bool Page::SetChildren(const uint id, Page* val)
{
    if (val != NULL && id < this->child.size())
    {
        this->child[id] = val;
        return true;
    }
    return false;
}

bool Page::RemoveChildren(const uint id)
{
	if (child.size()!=0)
		this->child.erase(child.begin()+id);
    return true;
}

bool Page::AddChildren(Page* val)
{
    this->child.push_back(val);
    return true;
}

int Page::Split(Page* right) // Current size is 2*t+1.
{
    right = new Page(_t);

    for (uint i = _t + 1; i < 2 * _t+1 ; i++)
    {
        right->AddKey(this->keys[i]);
        right->AddChildren(this->child[i]);
        this->child.erase(child.begin() + i);
        this->keys.erase(keys.begin() + i);
    }
    right->AddChildren(this->child[2*_t]);
    this->child.erase(child.begin() + 2*_t);
    int val = this->keys[_t];
    this->keys.erase(keys.begin() + _t);
    return val;
}

/*
Вначале определим функцию, которая добавляет ключ K к дереву потомков узла x. После выполнения функции во всех пройденных узлах, кроме,
может быть, самого узла x, будет меньше 2t-1, но не меньше t-1, ключей.

Если х — не лист,
Определяем интервал, где должен находиться K. Пусть y — соответствующий сын.
Рекурсивно добавляем K к дереву потомков y.
Если узел y полон, то есть содержит 2t-1 ключей, расщепляем его на два. Узел y_1 получает первые t-1 из ключей y и первые t его потомков,
а узел y_2 — последние t-1 из ключей y и последние t его потомков. Медианный из ключей узла y попадает в узел х, а указатель на y в узле x заменяется указателями на узлы y_1 и y_2.
Если x — лист, просто добавляем туда ключ K.
Теперь определим добавление ключа K ко всему дереву. Буквой R обозначается корневой узел.

Добавим K к дереву потомков R.
Если R содержит теперь 2t-1 ключей, расщепляем его на два. Узел R_1 получает первые t-1 из ключей R и первые t его потомков,
а узел R_2 — последние t-1 из ключей R и последние t его потомков. Медианный из ключей узла R попадает вo вновь созданный узел,
 который становится корневым. Узлы R_1 и R_2 становятся его потомками.
*/

bool Page::AddKey(int val)
{
	if (!IsList(this))
	{
		uint i = 0;
		while (i<keys.size() && keys[i] < val)
			i++;

		if (child[i] != NULL)
			return child[i]->AddKey(val);
		else
		{
			if (keys.size() == 2 * _t + 1)
			{
				Page* t = new Page(_t);
				t->keys.push_back(val);
				t->child.push_back(NULL);
				child[i] = t;
				return true;
			}
			else
			{
				if (i == keys.size())
				{
					keys.push_back(val);
					child.push_back(NULL);
				}
				else
				{
					keys.insert(keys.begin()+i, val);
					child.insert(child.begin()+i, NULL);
				}
				return true;
			}
		}
	}
	else
	{
		if (keys.size() == 2 * _t + 1)
		{
			uint i = 0;
			Page* t = new Page(_t);
			t->keys.push_back(val);
			t->child.push_back(NULL);
			while (i<keys.size() && keys[i] < val)
				i++;
			child[i]=t;
			return true;
		}
		else
		{
			uint i = 0;
			while (i<keys.size() && keys[i] < val)
				i++;
			if (keys.size() == i)
			{
				keys.push_back(val);
				child.push_back(NULL);
			}
			else
			{
				keys.insert(keys.begin()+i, val);
				child.insert(child.begin()+i, NULL);
			}
			return true;
		}
	}
	return false;
}

uint Page::GetPos(const int val)
{
    if (this->keys.size()>0)
    {
        for (uint i = 0; i < keys.size(); i++)
        {
            if (keys[i] == val) return 1;
            else if (val < keys[i]) return (child[i]->GetPos(val))+1;
            else if (val>keys[i] && i==(keys.size()-1)) return (child[i+1]->GetPos(val))+1;
        }
    }
    return 0;
}

bool Page::RemoveKey(const uint id)
{
	if (keys.size()!=0) this->keys.erase(keys.begin()+id);
    return true;
}

bool Page::IsList(Page* p)
{
	if (p == NULL) return false;
	for (uint i = 0; i < p->GetSize(); i++)
	{
		if (p->child[i] != NULL)
		{
			return false;
		}
	}
	return true;
}

Page* Page::SwapL()
{
	for (uint i = 0; i < this->GetSize(); i++)
	{
		if (child[i] != NULL)
		{
			Page* pp = child[i]->SwapL();
			if (pp != NULL)
			{
				child[i] = pp;
			}
		}
	}
	if (child[0] != NULL && child[GetSize()] != NULL)
	{
		int ls = child[0]->GetDepth();
		int rs = child[GetSize()]->GetDepth();
		//cout << "let's turn! : " << keys[0] << " because : " << ls << " <= " << rs - 2 << endl;
		if (ls <= rs - 2)
		{
			//cout << "let's turn! : " << keys[0] << " because : " << ls << " <= " << rs - 2 << endl;
			if (this->child[this->GetSize()] != NULL)
			{
				if (this->child[this->GetSize()]->child[0] == NULL)
				{
					this->child[this->GetSize()]->child[0] = this;
					Page* k = child[this->GetSize()];
					child[this->GetSize()] = NULL;
					return k;
				}
			}
		}
	}
	return NULL;
}

Page* Page::SwapR()
{
	for (uint i = 0; i < this->GetSize(); i++)
	{
		if (child[i] != NULL)
		{
			Page* pp = child[i]->SwapR();
			if (pp != NULL)
			{
				//cout << "new child for " << (child[i])->keys[0] << " == " << pp->keys[0] << endl;
				child[i] = pp;
			}
		}
	}

	if (child[0] != NULL && child[GetSize()] != NULL)
	{
		int ls = child[0]->GetDepth();
		int rs = child[GetSize()]->GetDepth();
		if (ls >= rs + 2)
		{
			Page* l = child[0];
			{
				if (l->child[l->GetSize()] == NULL)
				{
					//cout << "new child for " << (l)->keys[0] << " = " << keys[0] << endl;
					l->child[l->GetSize()] = this;
					child[0] = NULL;
					return l;
				}
			}
		}
	}
	return NULL;
}

Page* Page::TurnLeft()
{
		for (uint i = 0; i < this->GetSize(); i++)
		{
			if (child[i] != NULL)
			{
				Page* pp = child[i]->TurnLeft();
				if (pp != NULL)
				{
					child[i] = pp;
				}
			}
		}
		if (child[0] != NULL && child[GetSize()] != NULL)
		{
			Page* l0 = child[GetSize()];
			Page* l1 = l0->child.at(l0->child.size() - 1);
			int rs = l0->GetDepth();
			int ls = child[0]->GetDepth();
			if (ls == rs + 1)
			{
				if (l1 != NULL && (l1->child.at(0) == NULL) && (l1->child.at(l1->child.size() - 1) == NULL))
				{
					child[GetSize()] = NULL;
					l0->child[0] = NULL;
					l1->child[l1->child.size() - 1] = l0;
					l1->child[0] = this;
					return l1;
				}
			}
		}
	return NULL;
}

Page* Page::TurnRight()
{
	for (uint i = 0; i < this->GetSize(); i++)
	{
		if (child[i] != NULL)
		{
			Page* pp = child[i]->TurnRight();
			if (pp != NULL)
			{
				child[i] = pp;
			}
		}
	}
	if (child[0] != NULL && child[GetSize()] != NULL)
	{
		Page* l0 = child[0];
		Page* l1 = l0->child.at(l0->child.size()-1);
		int ls = l0->GetDepth();
		int rs = child[GetSize()]->GetDepth();
		if (ls == rs + 1)
		{
			if (l1!=NULL && (l1->child.at(0) == NULL) && (l1->child.at(l1->child.size()-1) == NULL))
			{
				child[0] = NULL;
				l0->child[l0->child.size() - 1] = NULL;
				l1->child[0] = l0;
				l1->child[l1->child.size()-1] = this;
				return l1;
			}
		}
	}
	return NULL;
}

void Page::merge()
{
	bool ok = false;
	for (uint i = 0; i < child.size(); i++)
	{
		if (child[i] != NULL)
		{
			(child[i])->merge();
			Page* buff = child[i];
			if (buff->GetSize() < 2 * _t + 1 - GetSize())
			{
				child.erase(child.begin()+i);
				for (int j = buff->GetSize() - 1; j >= 0; j--)
				{
					keys.insert(keys.begin()+i, buff->GetKey(j));
					child.insert(child.begin()+i, buff->GetChildren(j + 1));
				}
				child.insert(child.begin()+i, buff->GetChildren(0));
				ok = true;
				for (uint k = 0; k < buff->keys.size()-1; k++)
				{
					buff->child.erase(child.begin());
					buff->keys.erase(keys.begin());
				}
				buff->child.erase(child.begin());
				break;
			}
			if (ok) break;
		}
	}
}

bool Page::Balance(int* val, Page* rw)
{
    if (this->keys.size() == 2*_t+1)
    {
		*val = this->keys.at(_t);
		this->keys.erase(keys.begin()+_t);
		rw->RemoveChildren(0);
		// after all size is 2*t
		for (uint i = 0; i < _t ; i++)
		{
			rw->AddChildren(this->child.at(_t+1));
			this->child.erase(child.begin()+_t + 1);
			rw->addToKeys(this->keys.at(_t));
			this->keys.erase(keys.begin() + _t);
		}
		rw->AddChildren(this->child.at(_t+1));
		this->child.erase(child.begin()+_t + 1);
		return true;
    }
	else
	{
		for (uint i = 0; i < this->child.size(); i++)
			if (child.at(i) != NULL)
			{
				int v=-1;
				Page* r = new Page(_t);
				r->RemoveChildren(0);
				bool isNotBalanced = this->child.at(i)->Balance(&v, r);
				if (r->GetSize()>0)
				{
					this->child.insert(child.begin() + i+1, r);
					this->keys.insert(keys.begin() + i, v);
				}
				if (isNotBalanced)
					return true;
			}
	}
    return false;
}

uint Page::GetSize()
{
    return (uint)keys.size();
}

void Page::addToKeys(int val)
{
	this->keys.push_back(val);
}