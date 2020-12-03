#pragma once

#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std;

class Layer
{
private:
    /*number of input/output weight*/
    int in = 0;
    int out = 0;
    vector<vector<float>> matrix;
    vector<float> hidden;
    /* for backPropagate */
    vector<float> errors;
    float learnRate = 0.5;

    inline float randWeight() {
        return ((((float)rand() / (float)RAND_MAX) - 0.5) * (float)pow(out, -0.5));
    }

public:
    Layer() {
    };
    ~Layer() {
        
    };

    int getInCount();
    int getOutCount();
    vector<vector<float>> getMatrix();
    void updMatrix(vector<float> enteredVal);
    void setIO(int inputs, int outputs);
    void makeHidden(vector<float> inputs);
    vector<float> getHiddenPoint();

    float getHidden(int num);

    void calcOutError(vector<float> targets);
    void calcHidError(vector<float> targets, vector<vector<float>> outWeights, int inS, int outS);
    vector<float> getErrors();
    float sigmoida(float val);
    float sigmoidasDerivate(float val);
};



