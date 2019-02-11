// Micah Maness
// I typed all of my own code

#include <cstdlib>
#include <thread>
#include <iostream>
#include <fstream>
using namespace std;

string get_file_contents(string file) {
    ifstream infile { file };
    string file_contents { istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };
    return file_contents;
}

const string CONTENTS = get_file_contents("nums.txt");
const int CORES = 4;
int count = 0;

int get_thread_partition_size(string numbers) {
    return numbers.length() / CORES;
}

const int PARTITION_SIZE = get_thread_partition_size(CONTENTS);

int count3s(int id) {
    int start = id * PARTITION_SIZE;
    string subString = CONTENTS.substr(start, PARTITION_SIZE);
    int count = 0;
    for (int pos = 0; pos < PARTITION_SIZE; ++pos) {
        if (subString[pos] == '3') {
            count++;
        }
    }
    totalCount += count;
}
    
int main() {
    thread threads[CORES];
    int totCount = 0;
    for (int i = 0; i < CORES; ++i) {
        threads[i] = thread(count3s, i);
    }
    
    for (int threadNum = 0; threadNum < CORES; ++threadNum) {
        threads[threadNum].join;
    }
    cout << totCount << endl;
    return EXIT_SUCCESS;
}