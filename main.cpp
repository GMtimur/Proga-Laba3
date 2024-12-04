#include <iostream>
#include <iomanip>
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

void tab(int a, string d)
{
    for (int i = 0; i < a; i++)
        cout << d;
}

void header(int widthX, int widthF){
    tab(widthX + 4, "_");
    cout << endl;
    cout << "|";
    tab((widthX - 1) / 2, " ");
    cout << "x";
    tab((widthX - 1) / 2, " ");
    cout << "||";
    tab((widthF - 1) / 2, " ");
    cout << "F";
    tab((widthF - 1) / 2, " ");
    cout << "|";
    cout << endl;
    tab(widthX + widthF + 8, "_");
    cout << endl;
}

void table(double a, double b, int widthX, int widthF) {
    cout << "|";
    string num1 = to_string(a);
    num1.erase(num1.length() - 4, 4);
    string num2 = to_string(b);
    num2.erase(num2.length() - 4, 4); 
    
    while (num1.length() < widthX)
        num1 = " " + num1;
    while (num2.length() < widthF)
        num2 = " " + num2;
        
    cout << num1 << "||" << num2 << "|" << endl;
}

void printTable(double arr[], double startX, double endX) {
    int n = 15;
    double step = (endX - startX) / (n - 1);

    int maxLenX = to_string(startX).length();
    int maxLenF = 0;
    for (int i = 0; i < n; ++i) {
        int len = to_string(arr[i]).length();
        if (len > maxLenF) {
            maxLenF = len;
        }
    }
    
    header(maxLenX, maxLenF); 
    for (int i = 0; i < n; ++i) {
        double x = startX + step * i;
        table(x, arr[i], maxLenX, maxLenF);
    }
    tab(maxLenX + maxLenF + 8, "_");
    cout << endl;
}

int countDuplicates(double arr[]) {
    map<double, int> counts;
    for (int i = 0; i < 15; ++i) {
        counts[arr[i]]++;
    }
    int duplicateCount = 0;
    for (const auto& pair : counts) {
        if (pair.second > 1) {
            duplicateCount++;
        }
    }
    return duplicateCount;
}

bool isPowerOfTwo(double a, double b)
{
    double log = log2(a);
    if ((a < b) && (log == round(log)) && (a >= 1) && (log >= 0))
        return true;
    else
        return false;
}

int findPowerOfTwoSequenceIndex(double arr[]) {
    int ind = -1;
    for (int i = 14; i > -1; i--) {
        if (i == 14) {
            if(isPowerOfTwo(arr[i], arr[i] + 1))
                ind = i;
            else
                break;
        }
        else{
            if(isPowerOfTwo(arr[i], arr[i + 1]))
                ind = i;
            else
                break;
        }
    }
    return ind;
}

void printMinGroups(double arr[]) {
    for (int i = 0; i < 3; ++i) {
        double minVal = *min_element(arr + i * 5, arr + (i + 1) * 5);
        cout << minVal << endl;
    }
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
    
    double array1[15], array2[15];
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
    if(isHuman) {
        cout << "Первый массив: " << endl;
        printTable(array1, x1, x2);
        cout << "Второй массив: " << endl;
        printTable(array2, -x2, -x1);
    }
    else {
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
    double sortedArray1[15];
    copy(begin(array1), end(array1), begin(sortedArray1));
    sort(sortedArray1, sortedArray1 + 15);
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
    cout << findPowerOfTwoSequenceIndex(array1) << endl;

    double negativeArray1[15], positiveArray2[15];
    int negIndex = 0, posIndex = 0;

    for (int i = 0; i < 15; ++i) {
        if (array1[i] > 0) {
            positiveArray2[posIndex++] = array1[i];
        } 
        if (array2[i] > 0) {
            positiveArray2[posIndex++] = array2[i];
        } 
    }
    for (int i = 0; i < 15; ++i) {
        if (array2[i] < 0) {
            negativeArray1[negIndex++] = array2[i];
        }
        if (array1[i] < 0) {
            negativeArray1[negIndex++] = array1[i];
        }
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
