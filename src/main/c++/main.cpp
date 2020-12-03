#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "neuro.h"

using namespace std;


vector<string> split(string& s, char split_by) {
    vector<string> result;
    int last_word_beg = 0;
    bool in_word = false;
    int index = 0, len = s.length();
    int this_length;
    for (char c : s) {
        if (c == split_by) {
            if (in_word) {
                in_word = false;
                this_length = index - last_word_beg;
                string this_word;
                this_word.reserve(this_length);
                for (int i = last_word_beg; i < index; i++) {
                    this_word.push_back(s[i]);
                }
                result.push_back(this_word);
            }
            else {

            }
        }
        else {
            if (in_word) {

            }
            else {
                last_word_beg = index;
                in_word = true;
            }
        }
        index++;
    }

    if (s[len] != split_by) {
        this_length = index - last_word_beg;
        string this_word;
        this_word.reserve(this_length);
        for (int i = last_word_beg; i < len; i++) {
            this_word.push_back(s[i]);
        }
        result.push_back(this_word);
    }

    return result;
}

template<typename T> T fromString(const string& str, bool& ok)
{
    stringstream ss(str);
    T t;
    ss >> t;
    ok = !ss.fail();
    return t;
}

vector<float> inputs_list(const vector<string> strList)
{
    vector<float> inputs(784);
    string str;
    bool ok = true;
    for (int i = 1; i < (int)strList.size(); i++)
    {

        str = strList.at(i);
        inputs.at(i - 1) = ((fromString<float>(str, ok) / 255.0 * 0.99) + 0.01);
    }
    return inputs;
}

vector<float> targets_list(const int j)
{
    vector<float> targets(10);
    for (int i = 0; i < 10; i++)
    {
        if (i == j)
            targets.at(i) = (0.99);
        else
            targets.at(i) = (0.01);
    }

    return targets;
}


int main(int argc, char* argv[])
{

    Neuro nW;
    vector<string> wordList;
    bool ok = true;

    ifstream file("C:\\Users\\Tony\\Documents\\Study\\neurodigit\\archive\\mnist_train.csv");
    if (file.is_open())
    {
        int qq = 0;
        while (qq < 3000)
        {
            qq++;
            if (qq % 100 == 0)
                cout << qq;
            string data;
            getline(file, data);
            wordList = split(data, ',');
            if (wordList[0] == "label") {
                wordList.erase(wordList.begin());
            }
            string str = wordList.at(0);
            vector<float> tmpIN = inputs_list(wordList);
            vector<float> tmpTAR = targets_list(fromString<int>(str, ok));
            nW.train(tmpIN, tmpTAR);
        }

        file.close();
    }

    ifstream file2("C:\\Users\\Tony\\Documents\\Study\\neurodigit\\archive\\mnist_test.csv");
    if (file2.is_open()) {
        int cnt = 0;
        while (50 > cnt++)
        {
            string data;
            getline(file2, data);
            wordList = split(data, ',');
            if (wordList[0] == "label") {
                wordList.erase(wordList.begin());
            }
            string str = wordList.at(0);
            cout << "\n__________________";
            cout << "For number " << str;
            vector<float> tmpIN = inputs_list(wordList);
            nW.query(tmpIN);
        }
        file2.close();
    }
    cout <<"_______________THE____END_______________";



    return 0;
}
