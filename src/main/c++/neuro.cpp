#include "neuro.h"
#include <stdlib.h>
#include <iostream>


Neuro::Neuro()
{
    /*Picture resolution 28x28*/
    _inputNeurons = 784;
    /*Number of digits*/
    _outputNeurons = 10;
    
    /*Number of layers*/
    _nlCount = 2;
    _nList.resize(_nlCount);


    /*End of first layer is begining of second*/
    _nList.at(0).setIO(_inputNeurons, 200);
    _nList.at(1).setIO(200, _outputNeurons);
    /*_nList.at(2).setIO(60, 40);
    _nList.at(3).setIO(40, _outputNeurons);*/

}

Neuro::~Neuro()
{
}

void Neuro::feedForwarding(bool ok)
{

    //--- for first layer argument is _inputs
    _nList.at(0).makeHidden(_inputs);
    //--- for other layer argument is "hidden" array previous's layer
    for (int i = 1; i < _nlCount; i++)
        _nList.at(i).makeHidden(_nList.at(i - 1).getHiddenPoint());


    //--- bool condition for query NN or train NN
    if (!ok)
    {
        int idx_max = 0;
        float max = 0;
        cout << "Feed Forward: " << endl;
        for (int out = 0; out < _outputNeurons; out++)
        {
            cout << out << ". learnRate" << _nList.at(_nlCount - 1).getHidden(out) << endl;
            if (_nList.at(_nlCount - 1).getHidden(out) > max) {
                max = _nList.at(_nlCount - 1).getHidden(out);
                idx_max = out;
            }
        }
        cout << "\nAnswer: " << idx_max << endl;
        return;
    }
    else
    {
        // printArray(list[3].getErrors(),list[3].getOutCount());
        backPropagate();
    }
}

void Neuro::backPropagate()
{
    //--- calculate errors for last layer
    _nList.at(_nlCount - 1).calcOutError(_targets);
    //--- for others layers to calculate errors we need information about "next layer"
    //---   //for example// to calculate 4'th layer errors we need 5'th layer errors
    for (int i = _nlCount - 2; i >= 0; i--)
        _nList.at(i).calcHidError(
            _nList.at(i + 1).getErrors(),
            _nList.at(i + 1).getMatrix(),
            _nList.at(i + 1).getInCount(),
            _nList.at(i + 1).getOutCount()
        );

    //--- updating weights
    //--- to UPD weight for current layer we must get "hidden" value array of previous layer
    for (int i = _nlCount - 1; i > 0; i--)
        _nList.at(i).updMatrix(_nList.at(i - 1).getHiddenPoint());
    //--- first layer hasn't previous layer.
    //--- for him "hidden" value array of previous layer be NN input
    _nList.at(0).updMatrix(_inputs);
}

void Neuro::train(vector<float> in, vector<float> targ)
{
    if (in.at(0))
        _inputs = in;
    if (targ.at(0))
        _targets = targ;

    //--- bool == true enable backPropogate function, else it's equal query without print
    feedForwarding(true);
}

void Neuro::query(vector<float> in)
{
    _inputs = in;
    //--- bool == false call query NN with print NN output
    feedForwarding(false);
}

void Neuro::printArray(vector<float> arr, int s)
{
    cout << "__" << endl;
    for (int inp = 0; inp < s; inp++)
    {
        cout << arr[inp] << endl;
    }
}
