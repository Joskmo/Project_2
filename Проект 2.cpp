#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <map>
#include <cmath>

using namespace std;

typedef map <int, vector <int>> vector_map;

// константы для тестировки
const vector <pair <int, vector <int>>> test_dividers = { { 1, { 1 }}, { 2, { 1, 2 } }, { 3, { 1, 3 }}, { 4, { 1, 2, 4 }}, { 210, { 1, 2, 3, 5, 6, 7, 10, 14, 15, 21, 30, 35, 42, 70, 105, 210 }} }; // проверка нахождения делителей
const vector <pair <int, char>> test_prime_num = { {1, 0 }, {2, 1}, {3, 1}, {4, 0}, {9, 0} }; // проверка нахождения простого числа
const vector <pair <vector <int>, pair <int, unsigned long long> >> test_gcd_lcm = { {{1, 1}, {1, 1}}, {{2, 1}, {1, 2}}, {{4, 2}, {2, 4}}, {{6, 9}, {3, 18}}, {{3, 20}, {1, 60}}, {{1000000001, 4}, {1, 4000000004}} }; // проверка НОД и НОК
const vector <pair <int, int>> test_perfect_num = { {1, 0}, {2, 0}, {6, 1}, {28, 1} }; // проверка нахождения совершенного числа
const vector <pair <vector <int>, vector <int>> > test_easier = { { {2, 4, 3, 9},{1, 2, 1, 3} }, { {2, 2, 4, 4},{1, 1, 1, 1} }, { {1, 3, 4, 9},{1, 3, 4, 9} }, { {8, 6, 10, 4},{4, 3, 5, 2} } }; // проверка упрощения дробей

void function_choose();

int input_int(int low_lim, int high_lim) { // проверка ввода
    string input;
    int test = 0, output = 0;
    try {
        cin >> input;
        for (int i = 0; i < input.size(); i++) {
            test = ((int)input[i] > 47 && (int)input[i] < 58);
            if (!test) {
                cout << "Проверьте введённые данные" << endl;
                output = 0;
                break;
            }
            else {
                output = stoi(input);
                if (output < low_lim || output > high_lim) {
                    cout << "Проверьте введённые данные" << endl;
                    output = 0;
                    break;
                }
            }
        }
    }
    catch (...) {
        output = 0;
        cout << "Проверьте введённые данные" << endl;
    }
    return output;
}

vector <int> get_dividers(int num, vector_map& dividers) { // получение делителей числа
    if (!dividers.count(num)) {
        vector <int> div_num;
        for (int i = 1; i <= num / 2; i++) {
            if (!(num % i)) div_num.push_back(i);
        }
        div_num.push_back(num);
        dividers[num] = div_num;
    }
    return dividers[num];
}

char detect_prime_num(int num, vector_map& dividers) { // определение простого числа
    get_dividers(num, dividers);
    int output = 0;
    vector <int> div_num = dividers[num];
    int i = div_num.size();
    if (i == 2) output = 1;
    return output;
}

pair <int, unsigned long long> detect_gcd_lcm(unsigned long long num1, unsigned long long num2, vector_map& dividers) { // нахождение НОД и НОК чисел
    get_dividers(num1, dividers);
    get_dividers(num2, dividers);
    vector <int> vect1 = dividers[num1];
    vector <int> vect2 = dividers[num2];
    int gcd = 1;
    for (int i = (vect1.size() - 1); i >= 0; --i) {
        for (int k = (vect2.size() - 1); k >= 0; --k) {
            if (vect2[k] == vect1[i]) {
                gcd = vect1[i];
                break;
            }
        }
        if (gcd > 1) break;
    }
    unsigned long long lcm = num1 * num2 / gcd;
    return make_pair(gcd, lcm);
}

int detect_perfect_num(int num, vector_map& dividers) {
    int key_perfect_num = 0;
    vector <int> divs = dividers[num];
    for (int i = 0; i < divs.size(); i++) key_perfect_num += divs[i];
    if (key_perfect_num == num * 2) key_perfect_num = 1;
    else key_perfect_num = 0;
    return key_perfect_num;
}

void analyse_nums() { // функция анализатора чисел (функция 1)
    string message[2]{ " НЕ ", " " };
    vector_map dividers;
    int num1 = 0, num2 = 0;
    while (!num1 || !num2) {
        cin.clear();
        while (cin.get() != '\n');
        num1 = input_int(1, INT_MAX);
        if (!num1) {
            num2 = 0;
        }
        else num2 = input_int(1, INT_MAX);
    }
    cout << "Число " << num1 << message[detect_prime_num(num1, dividers)] << "простое" << endl;
    cout << "Число " << num1 << message[detect_perfect_num(num1, dividers)] << "совершенное" << endl;
    cout << "Число " << num2 << message[detect_prime_num(num2, dividers)] << "простое" << endl;
    cout << "Число " << num2 << message[detect_perfect_num(num2, dividers)] << "совершенное" << endl;
    cout << "Наибольший общий делитель: " << detect_gcd_lcm(num1, num2, dividers).first << endl;
    cout << "Наименьшее общее кратное: " << detect_gcd_lcm(num1, num2, dividers).second << endl << endl;
    function_choose();
}

int input_func2() { // проверка ввода для калькулятора
    bool flag = false;
    int num;
    do {
        flag = false;
        num = input_int(1, INT_MAX);
        if (!num) flag = true;
    } while (flag);
    return num;
}

void print_fractions(vector<int>& numbers, char input_do) {
    char message[4]{ '/', input_do, '/', '=' };
    for (int i = 0; i < 4; i++) {
        if (i % 2) cout << numbers[i] << " " << message[i] << " ";
        else cout << numbers[i] << message[i];
    }
}

void print_sum(unsigned long long numerator, unsigned long long denominator, vector_map& dividers) {
    int bubble = numerator;
    numerator = numerator / detect_gcd_lcm(numerator, denominator, dividers).first;
    denominator = denominator / detect_gcd_lcm(bubble, denominator, dividers).first;
    cout << numerator << "/" << denominator;
    if (numerator > denominator and numerator % denominator != 0) cout << " = " << (numerator / denominator) << " " << (numerator % denominator) << "/" << denominator;
    else if (numerator % denominator == 0) cout << " = " << (numerator / denominator);
    cout << endl << endl;
    function_choose();
}

void print_dif(__int64 numerator, unsigned long long denominator, vector_map& dividers) {
    int bubble = numerator;
    numerator = numerator / detect_gcd_lcm(numerator, denominator, dividers).first;
    denominator = denominator / detect_gcd_lcm(bubble, denominator, dividers).first;
    cout << numerator << "/" << denominator;
    int negative = false;
    const string sym[2] = { "", "-" };
    if (numerator < 0) negative++;
    numerator = abs(numerator);
    if (numerator > denominator and numerator % denominator != 0) 
        cout << " = " << sym[negative] << (numerator / denominator) << " " << (numerator % denominator) << "/" << denominator;
    else if (numerator % denominator == 0) cout << " = " << sym[negative] << (numerator / denominator);
    cout << endl << endl;
    function_choose();
}

void calc_result(vector <int> numbers, vector_map& dividers) { // выбор действия и подсчёт
    char input_do;
    do {
        cin >> input_do;
        if (input_do != '+' && input_do != '-') {
            input_do = false;
            cout << "Проверьте введённые данные" << endl;
        }
    } while (!input_do);
    cout << endl;
    print_fractions(numbers, input_do);
    unsigned long long denominator = detect_gcd_lcm(numbers[1], numbers[3], dividers).second;
    bool flag1 = false;
    do {
        flag1 = false;
        try {
            switch (input_do) {
            case '+':
                unsigned long long numerator1;
                numerator1 = denominator / numbers[1] * numbers[0] + denominator / numbers[3] * numbers[2];
                print_sum(numerator1, denominator, dividers);
                break;
            case '-':
                __int64 numerator;
                numerator = denominator / numbers[1] * numbers[0] - denominator / numbers[3] * numbers[2];
                print_dif(numerator, denominator, dividers);
                break;
            }
        }
        catch (...) {
            cout << "Проверьте введённые данные" << endl;
            flag1 = true;
        }
    } while (flag1);
}

vector <int> make_frac_easier(vector <int> numbers, vector_map& dividers) {
    for (int i = 0; i < 4; i += 2) {
        int bubble = numbers[i];
        numbers[i] = numbers[i] / detect_gcd_lcm(numbers[i], numbers[i + 1], dividers).first;
        numbers[i + 1] = numbers[i + 1] / detect_gcd_lcm(bubble, numbers[i + 1], dividers).first;
    }
    return numbers;
}

void fractions_calc() { // калькулятор дробей (функция 2)
    vector_map dividers;
    const string message[4] = { "числитель первой", "знаменатель первой", "числитель второй", "знаменатель второй" };
    vector <int> numbers(4);
    for (int i = 0; i < 4; i++) {
        cout << endl << "Введите " << message[i] << " дроби: ";
        numbers[i] = input_func2();
    }
    cout << endl << "Введены дроби: " << numbers[0] << "/" << numbers[1] << " и " << numbers[2] << "/" << numbers[3];
    cout << endl << "Выберите действие (+ или -): ";
    numbers = make_frac_easier(numbers, dividers);
    calc_result(numbers, dividers);
}

void test_func() { // функция тестировки
    vector_map dividers;
    for (auto test : test_dividers)
        assert(get_dividers(test.first, dividers) == test.second);
    for (auto test : test_prime_num)
        assert(detect_prime_num(test.first, dividers) == test.second);
    for (auto test : test_gcd_lcm)
        assert(detect_gcd_lcm(test.first[0], test.first[1], dividers) == test.second);
    for (auto test : test_perfect_num) {
        get_dividers(test.first, dividers);
        assert(detect_perfect_num(test.first, dividers) == test.second);
    }
    for (auto test : test_easier)
        assert(make_frac_easier(test.first, dividers) == test.second);
    cout << "Предварительный тест пройден успешно!" << endl << endl;
}

void (function_choose)() { // выбор функции
    cout << "Выберете нужную функцию:" << endl << "1 - Функция анализатора" << endl << "2 - Функция калькулятора дробей" << endl << "3 - Завершить работу программы" << endl << endl << "Ваш выбор: ";
    int func_choose = 0;
    do {
        func_choose = input_int(1, 3);
        switch (func_choose) {
        case 1:
            system("cls");
            cout << "Выбрана функция анализатора" << endl << "Введите два целых числа через пробел: ";
            analyse_nums();
            break;
        case 2:
            system("cls");
            cout << "Выбрана функция калькулятора дробей" << endl;
            fractions_calc();
            break;
        case 3:
            system("cls");
            cout << "Завершено выполнение программы" << endl;
            break;
        }
    } while (!func_choose);
}

void main() {
    setlocale(LC_ALL, "Russian");
    test_func();
    function_choose();
}