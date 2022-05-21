#pragma once
#include <iostream>

template <typename T>
struct Node
{
	Node<T>* pNext;
	Node<T>* pRev;

	T value;
};

template <typename T>
class List
{
public:
	List();
	List(const List<T>& other);
	~List();

	class Iterator
	{
	public:
		Node<T>* nodePtr;

	public:
		Iterator(Node<T>* newPtr) : nodePtr(newPtr) {}

		Iterator() : nodePtr(nullptr) {}

		bool operator!=(const Iterator& iterator);
		bool operator==(const Iterator& iterator);

		Iterator& operator++()
		{
			if (nodePtr)
			{
				nodePtr = nodePtr->pNext;
			}
			return *this;
		}
		Iterator& operator--()
		{
			if (nodePtr)
			{
				nodePtr = nodePtr->pRev;
			}

			return *this;
		}
		Iterator& operator++(int)
		{
			Iterator iterator = *this;
			++* this;
			return iterator;
		}
		Iterator& operator--(int)
		{
			Iterator iterator = *this;
			nodePtr = nodePtr->pRev;
			return iterator;
		}
		T& operator*();

		Iterator& operator+=(int n)
		{
			for (size_t i = 0; i < n; i++)
			{
				if (nodePtr)
				{
					nodePtr = nodePtr->pNext;
				}

			}
			return *this;
		}
	};

	Iterator begin()
	{
		return Iterator(Begin);
	}
	Iterator end()
	{
		Node<T>* temp = new Node <T>;
		temp->pRev = End;
		End->pNext = temp;

		return Iterator(temp);
	}

	Iterator rbegin()
	{
		Node<T>* newNode = new Node<T>;
		newNode->pNext = Begin;
		newNode->pRev = nullptr;
		Begin->pRev = newNode;
	}
	Iterator rend()
	{
		return Iterator(End);
	}

	//в процессе реализации
	/*
	  Iterator cbegin()
	  Iterator cend() {}
	*/

	Iterator& insert(Iterator pos, const T& value)
	{
		Node<T>* newNode = Begin;

		if (pos == Begin)
		{
			push_front(value);
			return pos;
		}
		else if (pos == End)
		{
			push_back(value);
			return pos;
		}

		else
		{
			while (pos != newNode)
			{
				newNode = newNode->pNext;
			}

			Node<T>* pRevNewNode = newNode->pRev;
			Node<T>* temp = new Node<T>;

			temp->value = value;
			if (pRevNewNode != 0 && Count != 1)
				pRevNewNode->pNext = temp;

			temp->pNext = newNode;
			temp->pRev = pRevNewNode;
			newNode->pRev = temp;

			Count++;
		}
		return pos;
	}	//<	э
	Iterator& insert(Iterator pos, int n, const T& value)
	{
		for (int i = 0; i < n; i++)
		{
			insert(pos, value);
		}
		return pos;
	}
	Iterator& insert(Iterator pos, Iterator bbegin, Iterator eend)
	{
		if (pos == Begin)
		{
			Node<T>* newNode = Begin;

			push_front(*bbegin);
			pos++;
			bbegin++;

			while (pos != newNode->pNext)
			{
				newNode = newNode->pNext;
			}

			while (bbegin != eend)
			{
				Node<T>* pRevNewNode = newNode->pRev;
				Node<T>* temp = new Node<T>;

				temp->value = *bbegin;
				if (pRevNewNode != 0 && Count != 1)
					pRevNewNode->pNext = temp;

				temp->pNext = newNode;
				temp->pRev = pRevNewNode;
				newNode->pRev = temp;

				bbegin++;
				Count++;
			}


		}

		if (pos == End)
		{
			while (bbegin != eend)
			{
				push_back(*bbegin);
				bbegin++;
			}
			return pos;
		}
		else
		{
			Node<T>* newNode = Begin;
			while (pos != newNode)
			{
				newNode = newNode->pNext;
			}

			while (bbegin != eend)
			{
				Node<T>* pRevNewNode = newNode->pRev;
				Node<T>* temp = new Node<T>;

				temp->value = *bbegin;
				if (pRevNewNode != 0 && Count != 1)
					pRevNewNode->pNext = temp;

				temp->pNext = newNode;
				temp->pRev = pRevNewNode;
				newNode->pRev = temp;

				bbegin++;
				Count++;
			}
		}

		return pos;
	}
	Iterator& insert(Iterator pos, List<T>& list)
	{
		List<T>::Iterator begin = list.begin();
		List<T>::Iterator end = list.end();
		insert(pos, begin, end);
		return pos;
	}

	Iterator& erase(Iterator pos)
	{
		Node<T>* Del = Begin;
		while (pos != Del)
		{
			Del = Del->pNext;
		}

		Node<T>* preDel = Del->pRev;
		Node<T>* nextDel = Del->pNext;

		if (preDel != 0 && Count != 1)
		{
			preDel->pNext = nextDel;

		}
		if (nextDel != 0 && Count != 1)
		{
			nextDel->pRev = preDel;
		}

		if (pos == Begin)
		{
			Begin = nextDel;
		}

		if (pos == End)
		{
			End = preDel;
		}
		delete Del;
		Count--;

		return ++pos;
	}
	Iterator& erase(Iterator position, Iterator& enddd)
	{
		do
		{
			Node<T>* Del = Begin;
			while (position != Del)
			{
				Del = Del->pNext;
			}

			Node<T>* preDel = Del->pRev;
			Node<T>* nextDel = Del->pNext;

			if (preDel != 0 && Count != 1)
			{
				preDel->pNext = nextDel;

			}
			if (nextDel != 0 && Count != 1)
			{
				nextDel->pRev = preDel;
			}

			if (position == Begin)
			{
				Begin = nextDel;
			}

			if (position == End)
			{
				End = preDel;
			}
			position++;
			delete Del;
			Count--;
		} while (position != enddd);
		return position;
	}


	//получение элементов
	Node<T> ind(int n);							  //<
	T front();									  //<
	T back();									  //<

	//добавление
	void push_back(T val);//в конец списка		   //<
	void insert(T val, int pos);			       //<
	void push_front(T val);//в начало списка       //<

	/*and how is it different from the functions above?
	  void emplace_front(T val);
	  void emplace_back(T val);
	  void emplace_front(pos, val);
	*/

	//void search(int pos);
	////////////110-234/////////////////
	//void insert(pos, val);					   //<
	//void insert(pos, n, val);					   //<
	//void insert(pos, Begin, end);				   //<
	//void insert(pos, values);					   //<   Through another container. I'm too lazy,but i did it!				   

	//удаление
	void clear();									//<
	void clearInd(int index);						//<
	void pop_back();//последний						//<
	void pop_front();//первый						//<

	/////////////235-308///////////////////
	// erase(p);									//<
	// erase(Begin, end);							//<

	//размер списка
	int size();									   //<
	bool empty();								   //<
	void resize(int n);							   //<
	void resize(int n, const int value);		   //<

	//изменеие элементов списка 
	void assign(List<T>& other);				   //<
	void assign(const int n, T value);			   //<
	void assign(Iterator bbegin, Iterator eend);   //<

	//обмен двух списков
	void swap(List<T>& other);					   //<

	//вывести
	void print();								   //<
	friend std::ostream& operator<<(std::ostream& out, List<T>& list)
	{
		/*Моя перегрузка,руки убрал!*/
		Node<T>* tempEnd = list.End;

		for (Node<T>* temp = list.Begin; temp; temp = temp->pNext) {
			out << temp->value << " ";
		}
		out << "\n";
		return out;
	}

	//bool 
	bool operator==(const List<T>& list);		   //<
	bool operator!=(const List<T>& list);		   //<


	void Swap(Node<T> *one, Node<T> *two)
	{
		Node<T>* temp = new Node<T>;
		temp->value = one->value;
		one->value = two->value;
		two->value = temp->value;
	}

	void bubbleSort() 
	{
		for  (int i = 0;i<this->Count-1;i++)
		{
			Node<T> *temp = Begin;
			Node<T> *nextTemp = Begin->pNext;

			for (int j = 0; j < this->Count - 1; j++)
			{
				if (temp->value > nextTemp->value)
				{
					/*Node <T> *t = new Node<T>;
					t->value = temp->value;
					temp->value = nextTemp->value;
					nextTemp->value = t->value;*/
					Swap(temp,nextTemp);
				}

				temp = temp->pNext;
				nextTemp = nextTemp->pNext;
			}
		}
	}

	void partition()
	{
		//int pivot = arr[right];
		Node<T>* pivot = End;
		//int j = left - 1;
		Node<T>* j = new Node<T>;
		j->pNext = Begin;
		Begin->pRev = j;

		for (Node<T> *i = Begin; i != nullptr; i = i->pNext)
		{
			if (i->value < pivot->value)
			{
				j=j->pNext;
				Swap(i, j);
			}
		}
		Swap(j->pNext, pivot);
	}
	//void quickSort(int arr[], int left, int right)
	//{
	//	if (left >= right)
	//		return;

	//	Node<T> pivot = partition(, left, right);

	//	quickSort(arr, left, pivot - 1);
	//	quickSort(arr, pivot + 1, right);
	//}

private:
	Node<T>* Begin;
	Node<T>* End;
	int Count{};
};

///////////////////////КОНСТРУКТОР И ДЕСТРУКТОР////////////////////////////////
template<typename T>
List<T>::List()
{
	Begin = End = nullptr;
	Count = 0;
}
template<typename T>
List<T>::List(const List<T>& other)
{
	Begin = End = nullptr;
	Count = 0;

	Node<T>* temp = other.Begin;

	while (temp != nullptr)
	{
		push_back(temp->value);
		temp = temp->pNext;
	}
}
template<typename T>
List<T>::~List()
{
	clear();
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////НАЧАЛЬНЫЙ И КОНЕЧНЫЙ ЭЛЕМЕНТ///////////////////////////
template <typename T>
T List<T>::front()
{
	return Begin->value;
}
template <typename T>
T List<T>::back()
{
	return End->value;
}
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////Размер////////////////////////////////////////
template<typename T>
int List<T>::size()
{
	return Count;
}
template<typename T>
bool List<T>::empty()
{
	return Count == 0;
}

template<typename T>
void List<T>::resize(int n)
{
	const int Default{};
	if (Count < n)
	{
		while (Count != n)
		{
			push_back(Default);
		}
	}
	else
	{
		int k = Count - n;

		while (k != 0)
		{
			clearInd(n + 1);
			k--;
		}
	}

}
template<typename T>
void List<T>::resize(int n, const int value)
{
	if (Count < n)
	{
		while (Count != n)
		{
			push_back(value);
		}
	}
	else
	{
		int k = Count - n;
		while (k != 0)
		{
			clearInd(n + 1);
			k--;
		}
	}

}
///////////////////////////////////////////////////////////////////////////

//////////////////////////////Добавление///////////////////////////////////
template<typename T>
void List<T>::push_back(T val)
{
	Node<T>* temp = new Node<T>;

	temp->pNext = nullptr;
	temp->pRev = End;
	temp->value = val;

	if (End != nullptr)
	{
		End->pNext = temp;
	}

	if (Count == 0)
	{
		End = Begin = temp;
	}
	else
	{
		End = temp;
	}


	Count++;
}
template<typename T>
void List<T>::push_front(T val)
{
	Node<T>* temp = new Node<T>;

	temp->pNext = Begin;
	temp->pRev = nullptr;
	temp->value = val;

	if (Begin != nullptr)
	{
		Begin->pRev = temp;
	}

	if (Count == 0)
	{
		Begin = End = temp;
	}
	else

	{
		Begin = temp;
	}

	Count++;
}
template <typename T>
void List<T>::insert(T val, int pos)
{
	Node<T>* newNode = Begin;

	if (pos == Count + 1)
	{
		push_back(val);
		return;
	}

	else if (pos == 1)
	{
		push_front(val);
		return;
	}

	int i = 1;
	while (i < pos)
	{
		newNode = newNode->pNext;
		i++;
	}

	Node<T>* pRevNewNode = newNode->pRev;
	Node<T>* temp = new Node<T>;

	temp->value = val;
	if (pRevNewNode != 0 && Count != 1)
		pRevNewNode->pNext = temp;

	temp->pNext = newNode;
	temp->pRev = pRevNewNode;
	newNode->pRev = temp;

	Count++;
}
//////////////////////////////////////////////////////////////////////////

///////////////////////////////Удаление///////////////////////////////////
template<typename T>
void List<T>::pop_back()
{
	Node<T>* temp = End;
	End = End->pRev;
	Count--;
	delete temp;
}
template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = Begin;
	Begin = Begin->pNext;

	Count--;
	delete temp;
}

template <typename T>
void List<T>::clearInd(int index)
{
	Node<T>* Del = Begin;
	int i = 1;
	while (i < index)
	{
		Del = Del->pNext;
		i++;
	}

	Node<T>* preDel = Del->pRev;
	Node<T>* nextDel = Del->pNext;

	if (preDel != 0 && Count != 1)
	{
		preDel->pNext = nextDel;
	}
	if (nextDel != 0 && Count != 1)
	{
		nextDel->pRev = preDel;
	}

	if (index == 1)
	{
		Begin = nextDel;
	}

	if (index == Count)
	{
		End = preDel;
	}

	delete Del;
	Count--;

}
template <typename T>
void List<T>::clear()
{
	while (Count)
	{
		clearInd(1);
	}
}
///////////////////////////////////////////////////////////////////////////


/////////////////////////////Изменение элементов списка////////////////////
template<typename T>
void List<T>::assign(List<T>& other)
{
	clear();
	Node<T>* temp = other.Begin;
	while (temp != nullptr)
	{
		push_back(temp->value);
		temp = temp->pNext;
	}

}
template<typename T>
void List<T>::assign(const int n, T value)
{
	clear();
	int i = 0;

	while (i < n)
	{
		push_back(value);
		i++;
	}
}
template<typename T>
void List<T>::assign(Iterator bbegin, Iterator eend)
{
	Node<T>* newNode = Begin;
	int n{};
	while (bbegin != eend)
	{
		newNode->value = *bbegin;
		newNode = newNode->pNext;
		bbegin++;
		n++;
	}
	int k = Count - n;
	n++;
	while (k)
	{
		clearInd(n);
		k--;
	}
}
////////////////////////////////////////////////////////////////////////////


///////////////////////////////Обмен элементов списка//////////////////////
template<typename T>
void List<T>::swap(List<T>& other)
{
	List<T> Temp;

	Node<T>* listOne = this->Begin;
	Node<T>* listTwo = other.Begin;

	while (listOne != nullptr)
	{
		Temp.push_back(listOne->value);
		listOne = listOne->pNext;
	}
	clear();

	while (listTwo != nullptr)
	{
		push_back(listTwo->value);
		listTwo = listTwo->pNext;
	}
	other.clear();

	Node<T>* temp = Temp.Begin;
	while (temp != nullptr)
	{
		other.push_back(temp->value);
		temp = temp->pNext;
	}
	Temp.clear();
}
////////////////////////////////////////////////////////////////////////////


///////////////////////////////Вывод списка/////////////////////////////////
template<typename T>
void List<T>::print()
{
	if (Count != 0)
	{
		Node<T>* temp = Begin;
		while (temp->pNext != 0)
		{
			std::cout << temp->value << " ";
			temp = temp->pNext;
		}

		std::cout << temp->value << "\n";
	}
}
////////////////////////////////////////////////////////////////////////////


///////////////////////////////Методы итератора/////////////////////////////
template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& iterator)
{
	return nodePtr != iterator.nodePtr;
}
template <typename T>
bool List<T>::Iterator::operator==(const Iterator& iterator)
{
	return nodePtr == iterator.nodePtr;
}
template<typename T>
T& List<T>::Iterator::operator*()
{
	return nodePtr->value;
}
////////////////////////////////////////////////////////////////////////////




//................можно и бухнуть....
// ........... я люблю Вадима....... P.S. ILDAR