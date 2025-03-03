// author:Ключерев Артем
#pragma once

#include<iostream>
#include<vector>
#include <stdexcept> // для исключений
#include <cstring>

using namespace std;
//максимальная куча
template <typename T>
class Heap
{
private:
	// hlist указывает на массив, который может быть динамически создан
	// конструктором (inArray == 0) или передан как параметр (inArray == 1)
	T* hlist;

	// максимальный и текущий размеры пирамиды
	int maxheapsize;
	int heapsize; // определяет конец списка

	// утилиты восстановления пирамидальной структуры
	void FilterDown(int i);
	void FilterUp(int i);

public:
	// конструкторы и деструктор
	// создать пустую пирамиду
	Heap(int maxsize) {
		hlist = nullptr;//будем использовать для хранения кучи

		// вместо cout выбрасывать исключения
		if (maxsize <= 0) {
			throw invalid_argument("Неправильная размерность массива");
			//std::cout << "Неправильная размерность массива";
		}
		else {
			maxheapsize = maxsize;
			heapsize = 0;
			hlist = new T[maxheapsize];//создает объект, который представляет собой кучу с максимальным размером maxsize.
		}

	}

	// конструктор с преобразованием arr в кучу
	Heap(const T* arr, int n, int maxsize) {
		int j, currentpos;
		hlist = nullptr;
		// n <= 0 является недопустимым размером массива
		if ((n <= 0) || (maxsize <= 0) || (n > maxsize)) {
			throw invalid_argument("Неправильная размерность массива");
		}

		// использовать n для установки размера пирамиды и максимального размера пирамиды.
		// копировать массив аrr в список пирамиды
		maxheapsize = maxsize;
		heapsize = n;
		hlist = new T[maxsize];

		memcpy(hlist, arr, n * sizeof(T));

		// присвоить переменной currentpos индекс последнего родителя.
		// вызывать FilterDown в цикле с индексами currentpos..0
		currentpos = (heapsize - 2) / 2;
		while (currentpos >= 0)
		{
			// выполнить условие пирамидальности для поддерева
			// с корнем hlist[currentpos]
			FilterDown(currentpos);
			currentpos--;
		}

	}

	// деструктор
	~Heap() {
		// освободить память, выделенную под массив
		// если эта память была выделенна
		if (hlist != nullptr) {
			delete[] hlist;
		}

	}


	// методы обработки списков

	// добавление элемента в кучу
	void Insert(const T& item);

	// удаление из корня
	void Delete();

	// печать дерева
	void PrintHeap();

	// Метод для поиска элемента в куче
	// возвращает индекс найденного элемента, либо
	// -1, если элемент не найден
	int Search(const T& element);

	// Получение значения из корня
	T GetMin();

	// Получение максимального значения
	int GetMaxSize();

	// Получить фактический размер массива
	int GetSize();

	// Получить массив
	std::vector<T> GetArray();
};

// Получение значения из корня
template <class T>
T Heap<T>::GetMin() {
	return hlist[0];
}

// Получение максимального значения
template <class T>
int Heap<T>::GetMaxSize() {
	return maxheapsize;
}

// Получить фактический размер массива
template <class T>
int Heap<T>::GetSize() {
	return heapsize;
}

// Получить массив
template <class T>
std::vector<T> Heap<T>::GetArray() {
	std::vector<T> v;

	for (int i = 0; i < heapsize; i++) {
		v.push_back(hlist[i]);
	}
	return v;
}

// утилита для восстановления пирамиды, начиная с индекса i,
// подниматься вверх по дереву, переходя от предка к предку.
// менять элементы местами, если сын меньше родителя
template <class T>
void Heap<T>::FilterUp(int i)//принимает индекс элемента
{
	int currentpos, parentpos;
	T target;
	// currentpos — индекс текущей позиции на пути предков.
	// target — вставляемое значение, для которого выбирается
	// правильная позиция в пирамиде
	currentpos = i;
	parentpos = (i - 1) / 2;
	target = hlist[i];

	// подниматься к корню по пути родителей
	while (currentpos != 0)
	{
		// если родитель <= target, то все в порядке,
		if (hlist[parentpos] <= target)
			break;
		else
			// поменять местами родителя с сыном и обновить индексы
			// для проверки следующего родителя
		{
			// переместить данные из родительской позиции в текущую.
			// назначить родительскую позицию текущей.
			// проверить следующего родителя
			hlist[currentpos] = hlist[parentpos];
			currentpos = parentpos;
			parentpos = (currentpos - 1) / 2;
		}
	}
	// правильная позиция найдена, поместить туда target
	hlist[currentpos] = target;
}

// вставить в пирамиду новый элемент и восстановить ее структуру
template <typename T>
void Heap<T>::Insert(const T& item)
{
	// проверить, заполнена ли пирамида и, если да, увеличить maxheapsize
	if (heapsize == maxheapsize) {
		maxheapsize = maxheapsize * 2;
		T* temp = new T[maxheapsize];


		memcpy(temp, hlist, heapsize * sizeof(T));

		delete[] hlist;
		hlist = temp;

		hlist[heapsize] = item;
		FilterUp(heapsize);
		heapsize++;
	}
	else {
		// записать элемент в конец пирамиды и увеличить heapsize.
		// вызвать FilterUp для восстановления пирамидального упорядочения
		hlist[heapsize] = item;
		FilterUp(heapsize);
		heapsize++;
	}
}

// утилита для восстановления пирамиды, начиная с индекса i,
// менять местами родителя и сына так, чтобы поддерево,
// начинающееся в узле i, было пирамидой
template <typename T>
void Heap<T>::FilterDown(int i)
{
	int currentpos, childpos;
	T target;

	// начать с узла i и присвоить его значение переменной target
	currentpos = i;
	target = hlist[i];

	// вычислить индекс левого сына и начать движение вниз по пути,
	// проходящему через меньших сыновей до конца списка
	childpos = 2 * i + 1;

	while (childpos < heapsize) // пока не конец списка
	{
		// индекс правого сына равен childpos+1. присвоить переменной
		// childpos индекс наименьшего из двух сыновей
		if ((childpos + 1 < heapsize) && (hlist[childpos + 1] <= hlist[childpos]))
			childpos = childpos + 1;

		// если родитель меньше сына, пирамида в порядке, выход
		if (target <= hlist[childpos])
			break;
		else
		{
			// переместить значение меньшего сына в родительский узел.
			// теперь позиция меньшего сына не занята
			hlist[currentpos] = hlist[childpos];
			// обновить индексы и продолжить сканирование
			currentpos = childpos;
			childpos = 2 * currentpos + 1;
		}
	}

	// поместить target в только что ставшую незанятой позицию
	hlist[currentpos] = target;
}

// удалить значение корневого элемента и обновить пирамиду
template <typename T>
void Heap<T>::Delete()
{
	T tempitem;

	// проверить, не пуста ли пирамида
	if (heapsize != 0) {

		// копировать корень в tempitem. заменить корень последним элементом
		// пирамиды и произвести декремент переменной heapsize
		tempitem = hlist[0];
		hlist[0] = hlist[heapsize - 1];
		heapsize--;
		// вызвать FilterDown для установки нового значения корня
		FilterDown(0);
	}
}

//печать кучи 
template <typename T>
void Heap<T>::PrintHeap()
{
	for (int i = 0; i < heapsize; i++)
	{
		std::cout << hlist[i] << " ";
	}
	std::cout << std::endl;
}

// Метод для поиска элемента в куче
// Возвращает индекс элемента или -1, если элемент не найден
template <typename T>
int Heap<T>::Search(const T& element) {
	for (int i = 0; i < heapsize; i++) {
		if (hlist[i] == element)
			return i;
	}
	return -1;
}

// отсортировать массив А размера n по возрастанию
template <typename T>
void HeapSort(T* A, int n)
{
	// конструктор, преобразующий А в пирамиду
	Heap<T> heap1(A, n, n);//первая n указыва
	T elt;
	// цикл заполнения элементов А[n-1] ... А[1]
	//for (int i = n - 1; i >= 0; i--)
	for (int i = 0; i < n; i++)
	{
		// исключить наименьший элемент из пирамиды и запомнить его в A[i]
		elt = heap1.GetMin();
		A[i] = elt;
		heap1.Delete();
	}
}