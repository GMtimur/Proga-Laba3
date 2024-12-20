#include <iostream>
#include <iomanip>
#include <cmath>

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

void findMaxLengths(double arr[], double startX, double endX, int& maxLenX, int& maxLenF) {
    int n = 15;
    double step = (endX - startX) / (n - 1);

    maxLenX = to_string(startX).length();
    maxLenF = 0;

    for (int i = 0; i < n; ++i) {
        double x = startX + step * i;
        int lenX = to_string(x).length(); 
        int lenF = to_string(arr[i]).length();

        if (lenX > maxLenX) {
            maxLenX = lenX;
        }
        if (lenF > maxLenF) {
            maxLenF = lenF;
        }
    }
}

void printTable(double arr[], double startX, double endX) {
    int n = 15;
    double step = (endX - startX) / (n - 1);

    int maxLenX, maxLenF;
    findMaxLengths(arr, startX, endX, maxLenX, maxLenF);

    header(maxLenX, maxLenF);
   
    for (int i = 0; i < n; ++i) {
        double x = startX + step * i;
        table(x, arr[i], maxLenX, maxLenF);
    }

    tab(maxLenX + maxLenF + 8, "_");
    cout << endl;
}

int countDuplicates(double arr[]) {
    int duplicateCount = 0;
    for (int i = 0; i < 15; ++i) {
        bool isDuplicate = false;
        for (int j = 0; j < i; ++j) {
            if (arr[i] == arr[j]) {
                isDuplicate = true;
                break;
            }
        }
        if (isDuplicate) {
            continue;
        }
        int count = 0;
        for (int j = i; j < 15; ++j) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > 1) {
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

void roundArrays(double array[], double x1, double x2, double a, double b, double c, bool isArray1){
    for (int i = 0; i < 15; ++i) {
        double x = 0;
        if(isArray1){
            x = x1 + (x2 - x1) * (i / 14.0);
        }
        else {
            x = -x2 + (x2 - x1) * (i / 14.0);
        }
        if(x == -0) x = 0;
        array[i] = roundValue(F(x, a, b, c), a, b, c);
    }
}

void printArrays(double array[]){
    for (int i = 0; i < 15; i++) {
            if(array[i] == -0) array[i] = 0;
            cout << array[i];
            if(i != 14){
            cout << " ";
        }
    }
    cout << endl;
}

void printMinGroups(double arr[]) {
    for (int i = 0; i < 3; ++i) {
        double minVal = arr[i * 5];
        for (int j = 1; j < 5; ++j) {
            if (arr[i * 5 + j] < minVal) {
                minVal = arr[i * 5 + j];
            }
        }
        cout << minVal << endl;
    }
}

void customCopy(double array[], double copyArray[], int size) {
    for (int i = 0; i < size; ++i) {
        copyArray[i] = array[i];
    }
}

void customSort(double* begin, double* end) {
    int size = end - begin;
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (begin[j] > begin[j + 1]) {
                // Обмен значений
                double temp = begin[j];
                begin[j] = begin[j + 1];
                begin[j + 1] = temp;
            }
        }
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
    roundArrays(array1, x1, x2, a, b, c, true);
    roundArrays(array2, x1, x2, a, b, c, false);
    if(isHuman) {
        cout << "Первый массив: " << endl;
        printTable(array1, x1, x2);
        cout << "Второй массив: " << endl;
        printTable(array2, -x2, -x1);
    }
    else {
        printArrays(array1);
        printArrays(array2);
    }

    if(isHuman) cout << "Минимальные элементы групп: " << endl;
    printMinGroups(array1);
    double sortedArray1[15];
    customCopy(array1, sortedArray1, 15);
    customSort(sortedArray1, sortedArray1 + 15);
    if(isHuman) cout << "Сортированный массив: " << endl;
    printArrays(sortedArray1);
    if(isHuman) cout << "Дубликаты: " << endl;
    cout << countDuplicates(array1) << endl;
    if(isHuman) cout << "Индекс степени двойки: " << endl;
    cout << findPowerOfTwoSequenceIndex(array1) << endl;

    double negativeArray1[15] = {}, positiveArray2[15] = {};
    int negIndex = 0, posIndex = 0;

    for(int i = 0; i < 15; i++){
            negativeArray1[i] = 0;
            positiveArray2[i] = 0;
        }

    for (int i = 0; i < 15; ++i) {  
        if (array2[i] < 0) {
            negativeArray1[negIndex++] = array2[i];
        }
        if (array2[i] > 0) {
            positiveArray2[posIndex++] = array2[i];
        }
    }
    
    for (int i = 0; i < 15; ++i) {
        if (array1[i] < 0) {
            if (negativeArray1[negIndex] == 0) negativeArray1[negIndex++] = array1[i];
        }
        if (array1[i] > 0) {
            if (positiveArray2[posIndex] == 0) positiveArray2[posIndex++] = array1[i];
        }
    }

    if(isHuman) cout << "Отрицательный массив: " << endl;
    printArrays(negativeArray1);
    if(isHuman) cout << "Положительный массив: " << endl;
    printArrays(positiveArray2);

    return 0;
}
