#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// quick sort
int partition(int* arr, int low, int high) 
{
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j < high; j++) 
    {
        if (arr[j] < pivot) 
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

void quickSort(int* arr, int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void countingSort(int* arr, int size) 
{
    if (size <= 0) return;

    int maxVal = arr[0];
    int minVal = arr[0];
    for (int i = 1; i < size; i++) 
    {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    int range = maxVal - minVal + 1;
    
    int* count = new int[range](); 
    int* output = new int[size];

    for (int i = 0; i < size; i++) 
    {
        count[arr[i] - minVal]++;
    }

    for (int i = 1; i < range; i++) 
    {
        count[i] = count[i] + count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) 
    {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    for (int i = 0; i < size; i++) 
    {
        arr[i] = output[i];
    }

    //freemem
    delete[] count;
    delete[] output;
}

int main() 
{
    //data files
    string filenames[12] = {
        "100a.txt", "100b.txt", "100c.txt", 
        "1000a.txt", "1000b.txt", "1000c.txt", 
        "10000a.txt", "10000b.txt", "10000c.txt",
        "100000a.txt", "100000b.txt", "100000c.txt"
    };

    int iterations = 1000;

    //output
    cout << left << setw(15) << "Filename" << setw(20) << "Avg Quick (ns)" << setw(20) << "Avg Count (ns)" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    for (int f = 0; f < 12; f++) 
    {
        ifstream inFile(filenames[f].c_str());
        if (!inFile) 
        {
            cout << left << setw(15) << filenames[f] << "FILE NOT FOUND\n";
            continue;
        }

        int countItems = 0;
        int tempVal;
        while (inFile >> tempVal) 
        {
            countItems++;
        }
        
        inFile.clear();
        inFile.seekg(0);

        int* originalData = new int[countItems];
        for (int i = 0; i < countItems; i++) 
        {
            inFile >> originalData[i];
        }
        inFile.close();

        //temp array
        int* workingArr = new int[countItems];

        // QS time
        high_resolution_clock::time_point startQS = high_resolution_clock::now();
        for(int i = 0; i < iterations; i++) 
        {
            for(int j = 0; j < countItems; j++) workingArr[j] = originalData[j];
            quickSort(workingArr, 0, countItems - 1);
        }
        high_resolution_clock::time_point endQS = high_resolution_clock::now();
        
        double totalQS = (double)duration_cast<nanoseconds>(endQS - startQS).count();
        double avgQS = totalQS / iterations;

        // CS Time
        high_resolution_clock::time_point startCS = high_resolution_clock::now();
        for(int i = 0; i < iterations; i++) 
        {
            for(int j = 0; j < countItems; j++) workingArr[j] = originalData[j];
            countingSort(workingArr, countItems);
        }
        high_resolution_clock::time_point endCS = high_resolution_clock::now();
        
        double totalCS = (double)duration_cast<nanoseconds>(endCS - startCS).count();
        double avgCS = totalCS / iterations;

        //results
        cout << left << setw(15) << filenames[f] << fixed << setprecision(2) << setw(20) << avgQS << setw(20) << avgCS << endl;

        //free mem
        delete[] originalData;
        delete[] workingArr;
    }

    return 0;
}
