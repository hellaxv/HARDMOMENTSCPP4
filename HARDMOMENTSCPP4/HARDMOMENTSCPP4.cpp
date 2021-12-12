#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>

using namespace std;

void DZ1()
{
    cout << "//===================================================[DZ1]===================================================//\n";
}

void DZ2()
{
    cout << "\n\n//===================================================[DZ2]===================================================//\n\n";
}

void END()
{
    cout << "\n\n//===================================================[END]===================================================//\n";
}

/*      DZ1
    Имеется отсортированный массив целых чисел.
    Необходимо разработать функцию insert_sorted,
которая принимает вектор и новое число и вставляет новое число в определенную позицию в векторе,
чтобы упорядоченность контейнера сохранялась. Реализуйте шаблонную функцию insert_sorted,
которая сможет аналогично работать с любым контейнером, содержащим любой тип значения.
*/

template<typename T, typename N>
void insert_sorted(T& v, const N  n)
{
    const auto insert_pos(lower_bound(begin(v), end(v), n));
    v.insert(insert_pos, n);
}

template<typename T>
void inform(const T& v)
{
    for (const auto e : v) cout << e << ' ';
}

/*      DZ2
    Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой значения аналогового сигнала.
    На основе этого массива чисел создайте другой вектор целых чисел b, представляющий цифровой сигнал,
в котором будут откинуты дробные части чисел. Выведите получившиеся массивы чисел.
    Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с аналоговым по формуле:
                                      i=0N-1(ai-bi)2

где:    N - количество элементов в векторе,
        a - элемент вектора с дробными числами,
        b - элемент вектора с целыми числами
*/

int GetRandNum(int min, int max) {
    const static auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937_64 generator(seed);
    uniform_int_distribution<int> dis(min, max);
    return dis(generator);
}

int main()
{
    setlocale(LC_ALL, "ru");
    {
        DZ1();

        vector<int> Vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15 };
        cout << "\nВаш массив\n";
        inform(Vec);
        cout << "\n\nВаш массив после функции (insert_sorted)\n";
        assert(true == is_sorted(begin(Vec), end(Vec)));
        insert_sorted(Vec, 12);
        inform(Vec);
    }

    {
        DZ2();

        const size_t SizeArr(14);

        vector<float> RealArray(SizeArr);
        generate(RealArray.begin(), RealArray.end(), []() { return float(GetRandNum(1, 100)) + (float(GetRandNum(1, 100)) / 100); });
        cout << "Массив целочисленных чисел\n";
        for (auto n : RealArray)
        {
            cout << n << "\t";
        }
        cout << endl;

        vector<int> IntegerArray;
        IntegerArray.reserve(SizeArr);
        transform(RealArray.begin(), RealArray.end(), back_inserter(IntegerArray), [](float f) {return int(f); });
        cout << "\nМассив вещественных чисел\n";
        for (auto n : IntegerArray)
        {
            cout << n << "\t";
        }

        cout << "\n\n[Error] Ошибка цифрового сигнала " << inner_product(IntegerArray.begin(), IntegerArray.end(), RealArray.begin(), 0.f, plus<>(), [](float a, float d)
            {
                return (a - d) * (a - d);
            });

        END();
    }
}