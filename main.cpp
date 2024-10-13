#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <cstring>
#include <sstream>
#include <bitset>
#include <unordered_set>

using namespace std;

double F(double x, double a, double b, double c) {
    if (x < 0 && b != 0) {
        return a * x * x + b;
    } else if (x > 0 && b == 0) {
        return (x - a) / (x - c);
    } else {
        return x / c;
    }
}

double roundValue(double value, double a, double b, double c) {
    int a_int = static_cast<int>(a);
    int b_int = static_cast<int>(b);
    int c_int = static_cast<int>(c);
    if(((a_int | b_int) & (a_int | c_int)) == 0){
        return (value - static_cast<int>(value) >= 0.5) ? ceil(value) : floor(value);
    } else {
        return round(value * 100.0) / 100.0;
    }
}
void printMinGroups(const vector<double>& arr) {
    for (int i = 0; i < 3; ++i) {
        double minVal = *min_element(arr.begin() + i * 5, arr.begin() + (i + 1) * 5);
        cout << minVal << endl;
    }
}

string centerAlign(double value, int width) {
    stringstream ss;
    ss << fixed << setprecision(2) << value;
    string str = ss.str();
    int padding = width - str.length();
    if (padding > 0) {
        int leftPadding = padding / 2;
        int rightPadding = padding - leftPadding;
        return string(leftPadding, ' ') + str + string(rightPadding, ' ');
    }
    return str;
}

void printTable(const vector<double>& arr, double startX, double endX) {
    cout << "__________________________" << endl;
    cout << "|         x  | |   F   |" << endl;
    cout << "__________________________" << endl;

    for (size_t i = 0; i < arr.size(); ++i) {
        double x = startX + (endX - startX) * (i / 14.0);
        cout << "| " << setw(10) << fixed << setprecision(2) << x << " | "
             << "|" << centerAlign(arr[i], 7) << "|" << endl;
    }

    cout << "___________________________" << endl;
}

int countDuplicates(const vector<double>& arr) {
    map<double, int> counts;
    for (double num : arr) {
        counts[num]++;
    }
    int duplicateCount = 0;
    for (const auto& pair : counts) {
        if (pair.second > 1) {
            duplicateCount++;
        }
    }
    return duplicateCount;
}

bool isPowerOfTwo(double num) {
    return num > 0 && (std::floor(log2(num)) == log2(num));
}

int findPowersOfTwoIndex(const vector<double>& arr) {
    unordered_set<double> foundPowers;
    for (int i = 0; i < arr.size(); ++i) {
        if (isPowerOfTwo(arr[i])) {
            foundPowers.insert(arr[i]);
            if (foundPowers.size() >= 2) {
                return i - foundPowers.size() + 1;
            }
        }
    }
    return -1;
}


int main(int argc, char* argv[]) {
    setlocale(LC_CTYPE, "rus");
    bool isHuman = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
	{
		isHuman = true;
	}
    double x1, x2, a, b, c;
    if(isHuman) cout << "Введите х1, х2, а, b, c: " << endl;
    cin >> x1 >> x2 >> a >> b >> c;
    if(x1 == -0) x1 = 0;
    if(x2 == -0) x2 = 0;
    vector<double> array1(15), array2(15);
    for (int i = 0; i < 15; ++i) {
        double x = x1 + (x2 - x1) * (i / 14.0);
        if(x == -0) x = 0;
        array1[i] = roundValue(F(x, a, b, c), a, b, c);
    }
    for (int i = 0; i < 15; ++i) {
        double x = -x2 + (x2 - x1) * (i / 14.0);
        if(x == -0) x = 0;
        array2[i] = roundValue(F(x, a, b, c), a, b, c);
    }
    if(isHuman){
        cout << "Первый массив: " << endl;
        printTable(array1, x1, x2);
        cout << "Второй массив: " << endl;
        printTable(array2, -x2, -x1);
    }
    else{
        for (int i = 0; i < 15; i++) {
            if(array1[i] == -0) array1[i] = 0;
            cout << array1[i];
            if(i != 14){
                cout << " ";
            }
        }
        cout << endl;
        for (int i = 0; i < 15; i++) {
            if(array2[i] == -0) array2[i] = 0;
            cout << array2[i];
            if(i != 14){
                cout << " ";
            }
        }
        cout << endl;
    }
    if(isHuman) cout << "Минимальные элементы групп: " << endl;
    printMinGroups(array1);
    vector<double> sortedArray1 = array1;
    sort(sortedArray1.begin(), sortedArray1.end());
    if(isHuman) cout << "Сортированный массив: " << endl;
    for (int i = 0; i < 15; i++) {
            if(sortedArray1[i] == -0) sortedArray1[i] = 0;
            cout << sortedArray1[i];
            if(i != 14){
                cout << " ";
            }
        }
    cout << endl;
    if(isHuman) cout << "Дубликаты: " << endl;
    cout << countDuplicates(array1) << endl;
    if(isHuman) cout << "Индекс степени двойки: " << endl;
    cout << findPowersOfTwoIndex(sortedArray1) << endl;
    vector<double> negativeArray1, positiveArray2;
    for (double val : array2) {
        if (val < 0) {
            negativeArray1.push_back(val);
        }
        if (val > 0) {
            positiveArray2.push_back(val);
        }
    }
    for (double val : array1) {
        if (val < 0) {
            negativeArray1.push_back(val);
        }
        if (val > 0) {
            positiveArray2.push_back(val);
        }
    }
    while (negativeArray1.size() < 15) {
        negativeArray1.push_back(0);
    }
    while (positiveArray2.size() < 15) {
        positiveArray2.push_back(0);
    }
    if(isHuman) cout << "Отрицательный массив: " << endl;
    for (int i = 0; i < 15; i++) {
            cout << negativeArray1[i];
            if(i != 14){
                cout << " ";
            }
        }
    cout << endl;
    if(isHuman) cout << "Положительный массив: " << endl;
    for (int i = 0; i < 15; i++) {
            cout << positiveArray2[i];
            if(i != 14){
                cout << " ";
            }
        }
    cout << endl;

    return 0;
}