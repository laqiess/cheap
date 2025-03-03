// author:Ключерев Артем
// тест кучи
#include "pch.h"
#include <algorithm>
#include "../cheap/Heap.h"



// тестирование конструкторов
TEST(TestHeap, TestConstructor) {
    setlocale(LC_ALL, "rus");
    Heap<int>heap0(15);
    EXPECT_EQ(15, heap0.GetMaxSize());
    EXPECT_EQ(0, heap0.GetSize());

    // коструктор с задание макимального размера кучи
    Heap<int> heap1(10);
    // добавление элементов в кучу
    heap1.Insert(10); heap1.Insert(15); heap1.Insert(40);
    heap1.Insert(50); heap1.Insert(30); heap1.Insert(100);
    //        10
    //      /   \
    //     15    50
    //    / \    / 
    //   30 40  100      


    // проверка максимального размера кучи и фактически используемого
    EXPECT_EQ(10, heap1.GetMaxSize());
    EXPECT_EQ(6, heap1.GetSize());

    vector<int> v = heap1.GetArray();
    vector<int> v1 = { 10, 15, 40,50,30,100 };
    // make_heap создаёт кучу на основе вектора (меняется сам вектор)
    // первые два параметра - итераторы, определяющие диапазон, который нужно преобразовать в кучу
    // третий параметр - функция сравнения для создания min_heap
    // третий параметр опционален, по умолчанию создаётся max_heap
    make_heap(v1.begin(), v1.end(), std::greater<>{});
    EXPECT_EQ(v1, v); v.clear();

    int* arr = new int[6]{ 10, 15, 40, 50, 30, 100 };
    // конструктор, принимающий массив
    Heap<int> heap2(arr, 6, 10);
    delete[] arr;
    EXPECT_EQ(10, heap2.GetMaxSize());
    EXPECT_EQ(6, heap2.GetSize());

    v = heap2.GetArray();
    EXPECT_EQ(v1, v);
    v.clear(); v1.clear();


    // пустая куча
    Heap<int>heap3(3);
    EXPECT_EQ(3, heap3.GetMaxSize());
    EXPECT_EQ(0, heap3.GetSize());
    v = heap3.GetArray();
    EXPECT_EQ(v1, v);

    arr = nullptr;
    try {
        Heap<int> heap4(arr, 0, 5);
    }
    catch (invalid_argument const& ex) {
        string s = ex.what();
        EXPECT_EQ(s, "Неправильная размерность массива");
    }
    v.clear(); v1.clear();

    // куча с одним элементом
    Heap<int>heap5(3);
    heap5.Insert(2);
    EXPECT_EQ(3, heap5.GetMaxSize());
    EXPECT_EQ(1, heap5.GetSize());

    v = heap5.GetArray();
    v1 = { 2 };
    EXPECT_EQ(v1, v);
    v.clear(); v1.clear();

    arr = new int[1]{ -2 };
    Heap<int> heap6(arr, 1, 5);
    delete[] arr;
    EXPECT_EQ(5, heap6.GetMaxSize());
    EXPECT_EQ(1, heap6.GetSize());
    v = heap6.GetArray();
    v1 = { -2 };
    EXPECT_EQ(v1, v);
}

// тестирование вставки
TEST(TestHeap, TestInsert) {

    Heap<int> heap1(10);
    heap1.Insert(2);

    EXPECT_EQ(10, heap1.GetMaxSize());
    EXPECT_EQ(1, heap1.GetSize());
    vector<int>v1 = heap1.GetArray();
    vector<int> v = { 2 };
    EXPECT_EQ(v1, v);

    heap1.Insert(1);
    v1 = heap1.GetArray();
    v = { 1,2 };
    EXPECT_EQ(10, heap1.GetMaxSize());
    EXPECT_EQ(2, heap1.GetSize());
    EXPECT_EQ(v1, v);

    heap1.Insert(3);
    v1 = heap1.GetArray();
    v.push_back(3);
    EXPECT_EQ(10, heap1.GetMaxSize());
    EXPECT_EQ(3, heap1.GetSize());
    EXPECT_EQ(v1, v);
}

// тестирование поиска
TEST(TestHeap, TestSearch) {

    int* arr = new int[6]{ 10, 15, 40, 50, 30, 100 };
    Heap<int> heap2(arr, 6, 10);
    delete[] arr;

    int s = heap2.Search(10);
    EXPECT_EQ(s, 0);

    s = heap2.Search(50);
    EXPECT_EQ(s, 3);

    s = heap2.Search(30);
    EXPECT_EQ(s, 4);

    s = heap2.Search(100);
    EXPECT_EQ(s, 5);

    s = heap2.Search(16);
    EXPECT_EQ(s, -1);

    // пустая куча
    Heap<int> heap0(2);
    s = heap0.Search(2);
    EXPECT_EQ(s, -1);

    // куча с одним элементом
    Heap<int> heap1(2);
    heap1.Insert(2);
    s = heap1.Search(2);
    EXPECT_EQ(s, 0);

    s = heap1.Search(-5);
    EXPECT_EQ(s, -1);

}

// тестирование удаления
TEST(TestHeap, TestDelete) {

    int* arr = new int[6]{ 10, 15, 40, 50, 30, 100 };
    Heap<int> heap2(arr, 6, 10);

    heap2.Delete(); // удаляем 10

    EXPECT_EQ(10, heap2.GetMaxSize());
    EXPECT_EQ(5, heap2.GetSize());

    vector<int> v = heap2.GetArray();
    EXPECT_TRUE(is_heap(v.begin(), v.end(), std::greater<>{}));
    vector<int> v1 = { 15,30,40,50,100 };
    make_heap(v1.begin(), v1.end(), std::greater<>{});
    EXPECT_EQ(v1, v);

    heap2.Delete(); // удаляем 15

    EXPECT_EQ(10, heap2.GetMaxSize());
    EXPECT_EQ(4, heap2.GetSize());

    v = heap2.GetArray();

    // is_heap проверяет, является ни массив кучей
    // первые два параметра - итераторы, определяющие диапазон, который нужно проверить
    // третий параметр - функция сравнения для min_heap
    // третий параметр опционален, по умолчанию поверяется, является ли max_heap
    EXPECT_TRUE(is_heap(v.begin(), v.end(), std::greater<>{}));
    v1 = { 30,50,40,100 };
    make_heap(v1.begin(), v1.end(), std::greater<>{});
    EXPECT_EQ(v1, v);

    heap2.Delete(); // удаляем 30
    EXPECT_EQ(10, heap2.GetMaxSize());
    EXPECT_EQ(3, heap2.GetSize());

    v = heap2.GetArray();
    EXPECT_TRUE(is_heap(v.begin(), v.end(), std::greater<>{}));
    v1 = { 50, 40,100 };
    make_heap(v1.begin(), v1.end(), std::greater<>{});
    EXPECT_EQ(v1, v);

    // куча с одним элементом
    Heap<int> heap1(2);
    heap1.Insert(-3);
    heap1.Delete();
    EXPECT_EQ(2, heap1.GetMaxSize());
    EXPECT_EQ(0, heap1.GetSize());
    v = heap1.GetArray();
    v1 = {};
    EXPECT_EQ(v1, v);


    // пустая куча
    Heap<int> heap0(2);
    heap0.Delete();
    EXPECT_EQ(2, heap0.GetMaxSize());
    EXPECT_EQ(0, heap0.GetSize());
    v = heap0.GetArray();
    v1 = {};
    EXPECT_EQ(v1, v);


}

// тестирование пирамидальной сортировки
TEST(TestHeap, TestHeapSort) {
    int* arr = new int[6]{ 10, 15, 40, 50, 30, 100 };
    HeapSort(arr, 6);

    int* arr1 = new int[6]{ 10, 15, 30, 40, 50, 100 };

    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(arr[i], arr1[i]);
    }

    delete[] arr;
    delete[] arr1;

    arr = new int[10]{ 55, 48, -54, 36, -24, 38, 12, 5, 2, -1 };
    arr1 = new int[10]{ -54, -24, -1, 2, 5, 12, 36, 38, 48, 55 };
    HeapSort(arr, 10);

    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(arr[i], arr1[i]);
    }

    delete[] arr;
    delete[] arr1;

    arr = new int[8]{ 34, 9, -44, 35, -72, -79, 8, 56 };
    arr1 = new int[8]{ -79, -72, -44, 8, 9, 34, 35, 56 };
    HeapSort(arr, 8);

    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(arr[i], arr1[i]);
    }

    delete[] arr;
    delete[] arr1;

    //из одного элемента
    arr = new int[1]{ 5 };
    arr1 = new int[1]{ 5 };
    HeapSort(arr, 1);
    EXPECT_EQ(arr[0], arr1[0]);

    delete[] arr;
    delete[] arr1;

    // пустой массив
    try {
        arr = nullptr;
        HeapSort(arr, 0);
    }
    catch (invalid_argument const& ex) {
        string s = ex.what();
        EXPECT_EQ(s, "Неправильная размерность массива");
    }


}