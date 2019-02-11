// Micah Maness
// I typed all of my own code

#include <cstdlib>
#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Takes in a text file and turns it into a string
string fileContents(string file) {
    ifstream infile { file };
    string file_contents { istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };
    return file_contents;
}

const string numList = fileContents("nums.txt");
const int numCores = 8;
int totalCount = 0;

int partition(string numbers) {
    return numbers.length() / numCores;
}

const int partitionSize = partition(numList);

int count3s(int id) {
    int start = id * partitionSize;
    string subString = numList.substr(start, partitionSize);
    int count = 0;
    for (int pos = 0; pos < partitionSize; ++pos) {
        if (subString[pos] == '3') {
            count++;
        }
    }
    totalCount += count;
}
    
int main() {
    auto startTime = high_resolution_clock::now();
    thread threads[numCores];
    int totCount = 0;
    for (int i = 0; i < numCores; ++i) {
        threads[i] = thread(count3s, i);
    }
    
    for (int threadNum = 0; threadNum < numCores; ++threadNum) {
        threads[threadNum].join();
    }
    auto endTime = high_resolution_clock::now();
    auto runTime = duration_cast<milliseconds>(endTime - startTime);
    
    cout << "Number of 3s: " << totalCount << endl;
    cout << "Run time: " << runTime.count() << " milliseconds" << endl;
    return 0;
}
