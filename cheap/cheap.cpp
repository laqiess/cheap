// cheap.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// author:Ключерев Артем

#include <iostream>
#include "Heap.h"

using namespace std;
int main()
{
    setlocale(LC_ALL, "rus");

    try {


        // исходный массив
        int* arr1 = new int[10]{ 50, 20, 60, 65, 15, 25, 10, 30, 4, 45 };
        cout << "Исходный массив:" << endl;

        for (int i = 0; i < 10; i++) {
            cout << arr1[i] << " ";
        }

        // преобразование массива в пирамиду

        //          4
        //       /    \
        //      15      10
        //    /    \    / \
        //   20    45  25  60
        //  / \    / 
        // 30  65 50

        Heap<int> heap1(arr1, 10, 15);
        // распечатать новую версию массива А
        cout << "\nКуча:" << endl;

        heap1.PrintHeap();

        // Вставка
        cout << "Добавить 3: ";
        heap1.Insert(3);
        heap1.PrintHeap();

        cout << "Добавить 70: ";
        heap1.Insert(70);
        heap1.PrintHeap();

        // Поиск узла
        cout << "Найти 3: ";
        cout << heap1.Search(3) << "\n";
        cout << "Найти 4: ";
        cout << heap1.Search(4) << "\n";
        cout << "Найти 10: ";
        cout << heap1.Search(10) << "\n";

        // Удаление минимального элемента (корень дерева)
        cout << "Удалить 3: ";
        heap1.Delete();
        heap1.PrintHeap();

        cout << "Удалить 4: ";
        heap1.Delete();
        heap1.PrintHeap();

        // Пирамидальная сортировка
        int* A = new int[5]{ 50, 20, 75, 35, 25 };

        cout << "\nИсходный массив: ";
        for (int i = 0; i < 5; i++) {
            cout << A[i] << " ";
        }

        HeapSort(A, 5);

        cout << "\nОтсортированный массив: ";
        for (int i = 0; i < 5; i++) {
            cout << A[i] << " ";
        }

        Heap<int> heap2(5);

        cout << "\n" << heap2.GetMaxSize() << "\n";
        heap2.Insert(2);
        heap2.Insert(3);
        heap2.Insert(5);
        heap2.Insert(10);
        heap2.Insert(12);
        heap2.Insert(14);
        cout << heap2.GetMaxSize();

    }
    catch (invalid_argument const& ex) {
        cout << ex.what();
    }

}