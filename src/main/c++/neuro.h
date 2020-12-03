#pragma once

#include <math.h>
#include <vector>
#include "layer.h"

using namespace std;

class Neuro
{
private:
    vector<Layer> _nList;
    int _inputNeurons;
    int _outputNeurons;
    int _nlCount;

    vector<float> _inputs;;
    vector<float> _targets;

public:
    Neuro();
    ~Neuro();


    void feedForwarding(bool ok);
    void backPropagate();
    void train(vector<float> in, vector<float> targ);
    void query(vector<float> in);
    void printArray(vector<float> arr, int s);
};

