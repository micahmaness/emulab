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

// Initiates a string of the numbers and the number of cores
const string numList = fileContents("nums.txt");
const int numCores = 8;
int totalCount = 0;

int partition(string numbers) {
    return numbers.length() / numCores;
}

const int partitionSize = partition(numList);

// Counts the 3s in the string
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

// Clocks the time run for the program
// Partitions based on cores
// Searches each partition on a different thread
// Outputs the time and 3s found
int main() {
    auto startTime = high_resolution_clock::now();
    thread threads[numCores];
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
