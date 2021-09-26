#include <iostream>
using namespace std;
template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "Econstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "Edestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	/*Element* Head;
	Element* Tail;*/
	size_t size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return this->Temp->Data;
		}
		int& operator*()
		{
			return this->Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	size_t get_size()const
	{
		return this->size;
	}
	List()
	{
		//Конструктор по умолчанию - создает пустой список. 
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const initializer_list<T>& il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List<T>& other) :List()
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyConstructor: " << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyAssignment\t" << this << endl;
		return *this;
	}

	//				Adding Elements
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;*/
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(T Data)
	{
		if (!Head && !Tail)return push_front(Data);
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail); 
		size++;
	}

	//				Removing Elements:
	void pop_front()
	{
		//0) Проверяем не является ли удаляемы эл. списка последним:
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		//1)Исключаем элемент из списка
		Head = Head->pNext;
		//2)Удаляем элемент из памяти
		delete Head->pPrev;
		//3)Забываем об удаленном элементе
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	//				Methods:
	void print()const
	{
		cout << "Адрес начала списка: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << endl << Temp << "\t" << Temp->Data << endl << Temp->pNext;

		cout << "Количество элементов списка: " << this->size << endl;
	}
	void reverse_print()const
	{
		cout << "Адрес конца списка: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << endl << Temp << "\t" << Temp->Data << endl << Temp->pNext;
		cout << "Количество элементов списка: " << this->size << endl;
	}
};

//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	list = list;
	list.print();
	//List list2 = list;  //CopyConstructor
	List list2;				//DefaultConstructor
	list2 = list;
	//list2.print();
	for (List::Iterator it = list2.begin(); it != list2.end(); it++)
	{
		cout << *it << "\t";
	}
	cout << endl;
	list2.reverse_print();
#endif // ITERATORS_CHECK
	typedef int DataType;
	DataType arr[] = { 0,1,1,2,3,5,8,13,21};
	for (int i = 0; i < sizeof(arr) / sizeof(DataType); i++)
	{
		cout << arr[i] << endl;
	}cout << endl;
	for (int i : arr)		//Ranch-based for intended to work only with containers
	{
		cout << i << "\t";
	}cout << endl;

	/*
	for(type i : container)
	{
		//i - iterator;
		cout << i;
	}
	*/

	List<int> list = { 0,1,1,2,3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << "\t";
	}cout << endl;
}


/*
					ШАБЛОНЫ КЛАССОВ
Шаблонным называется класс, тип членов которого определяется при создании объектов.
Переменные члены класса могут быть абсолютно любого типа и методы, реализованные внутри шаблонного класса автоматически становятся шаблонными. 
Для того, чтобы сделать класс шаблонным перед ним достаточно просто создать шаблон.
-----
template<typename T>
-----
Ключевое слово template показывает создание шаблона.
Ключевое слово typename определяет шаблонный тип данных.
Т - это имя шаблонного типа.
любая переменная в классе 

*/