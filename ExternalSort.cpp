#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>
#include <chrono>
using namespace std;
#define SIZE 10000

struct FileIterator
{
    ifstream file;
    int value;

    FileIterator(const string &filename) : file(filename), value(0)
    {
        file >> value;
    }
};

// string get_file_name(string filepath)
// {
//     int index = filepath.find_last_of("/");

//     if (index != string::npos)
//         return filepath.substr(index + 1);

//     return filepath;
// }

long get_file_size(string filepath) {
  FILE* file = fopen(filepath.c_str(), "rb");
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fclose(file);
  return size;
}

void merge(int files, string outfile)
{
    vector<FileIterator> iterators;

    for (int i = 0; i < files; i++)
    {
        string tempfile = "trash/sorted_temp_" + to_string(i) + ".txt";
        iterators.push_back(FileIterator(tempfile));
    }

    ofstream output(outfile);
    // Perform K-way merge

    long sizecount = 0;
    long filecount = 0;

    while (!iterators.empty())
    {
        int minIndex = -1;
        int minValue = INT_MAX;

        for (int i = 0; i < iterators.size(); i++)
        {
            if (iterators[i].value < minValue)
            {
                minIndex = i;
                minValue = iterators[i].value;
            }
        }

        output << minValue << endl;

        if (iterators[minIndex].file >> iterators[minIndex].value)
        {
            // do nothing
        }
        else
        {
            iterators[minIndex].file.close();
            iterators.erase(iterators.begin() + minIndex);
        }
        sizecount++;
        if(sizecount == SIZE){
            filecount++;
            sizecount = 0;
        }
        cout << "progress: " <<  (filecount / (float)files) * 100 << "%\r";
    }
    cout << endl;
    output.close();
}

void delete_temp(int files)
{
    for (int i = 0; i < files; i++)
    {
        string tempfile = "trash/sorted_temp_" + to_string(i) + ".txt";
        
        if (remove(tempfile.c_str()) != 0)
            cerr << "Error deleting file: " << tempfile << endl;
    }
}

void externalSort(string &infile, string &outfile)
{
    ifstream input(infile);
    vector<int> chunk;

    int counter = 0;
    while (!input.eof())
    {
        chunk.clear();
        for (int i = 0; i < SIZE; i++)
        {
            int num;
            if (input >> num)
                chunk.push_back(num);
            else
                break;
        }

        sort(chunk.begin(), chunk.end());

        string tempfile = "trash/sorted_temp_" + to_string(counter) + ".txt";
        ofstream tf(tempfile);
        for (int num : chunk)
        {
            tf << num << endl;
        }
        tf.close();
        counter++;
        cout << "\rTemporary files generated: " << counter;
    }
    cout << endl;

    input.close();

    merge(counter, outfile);

    delete_temp(counter);

}

int main(int argc, char *argv[])
{
    auto start = chrono::high_resolution_clock::now();

    if (argc != 3)
    {
        cerr << "Error: Invalid number of arguments." << endl;
        exit(0);
    }

    string input_file_path = argv[1];
    string output_file_path = argv[2];

    long file_size = get_file_size(input_file_path);

    // string input_file = get_file_name(input_file_path);
    // string output_file = get_file_name(output_file_path);

    cout << "Number of integers in temporary files: " << SIZE << endl;
    externalSort(input_file_path, output_file_path);

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << "Time taken: " << setprecision(2) << duration.count() << " seconds" << endl;

    return 0;
}
