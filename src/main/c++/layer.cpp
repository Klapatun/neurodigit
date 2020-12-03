#include "layer.h"

int Layer::getInCount() {
	return in;
}

int Layer::getOutCount() {
	return out;
}

vector<vector<float>> Layer::getMatrix() {
	return matrix; 
}

void Layer::updMatrix(vector<float> enteredVal)
{
    /* upd weight with considering errors */
    for (int ou = 0; ou < out; ou++)
    {

        for (int hid = 0; hid < in; hid++)
        {
            matrix.at(hid).at(ou) += (learnRate * errors[ou] * enteredVal[hid]);
        }
        matrix.at(in).at(ou) += (learnRate * errors[ou]);
    }
}

void Layer::setIO(int inputs, int outputs)
{
    /* initialization values and allocating memory*/
    in = inputs;
    out = outputs;

    errors.resize(out);
    hidden.resize(out);

    matrix.resize(in + 1);
    for (int inp = 0; inp < in + 1; inp++)
    {
        matrix[inp].resize(out);
    }
    for (int inp = 0; inp < in + 1; inp++)
    {
        for (int outp = 0; outp < out; outp++)
        {
            matrix.at(inp).at(outp) = randWeight();
        }
    }
}

void Layer::makeHidden(vector<float> inputs)
{
    /* make value after signal passing current layer*/
    for (int hid = 0; hid < out; hid++)
    {
        float tmpS = 0.0;
        for (int inp = 0; inp < in; inp++)
        {
            tmpS += inputs[inp] * matrix[inp][hid];
        }
        tmpS += matrix[in][hid];
        hidden[hid] = sigmoida(tmpS);
    }
}

vector<float> Layer::getHiddenPoint()
{
    return hidden;
}

float Layer::getHidden(int num) {
    return hidden[num];
}

void Layer::calcOutError(vector<float> targets)
{
    /* calculating error if layer is last*/
    for (int ou = 0; ou < out; ou++)
    {
        errors[ou] = (targets[ou] - hidden[ou]) * sigmoidasDerivate(hidden[ou]);
    }
}

void Layer::calcHidError(vector<float> targets, vector<vector<float>> outWeights, int inS, int outS)
{
    /* calculating error if layer is hidden */
    for (int hid = 0; hid < inS; hid++)
    {
        errors[hid] = 0.0;
        for (int ou = 0; ou < outS; ou++)
        {
            errors[hid] += targets[ou] * outWeights[hid][ou];
        }
        errors[hid] *= sigmoidasDerivate(hidden[hid]);
    }
}

vector<float> Layer::getErrors()
{
    return errors;
}

float Layer::sigmoida(float val)
{
    return (1.0 / (1.0 + exp(-val)));
}

float Layer::sigmoidasDerivate(float val)
{
    return (val * (1.0 - val));
}