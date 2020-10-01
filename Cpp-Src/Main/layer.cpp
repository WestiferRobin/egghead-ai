#include "egghead_comp.hpp"

Layer::Layer(double learn_rate, string name)
{
    learningRate = new double(learn_rate);
    layerName = new string(name);
    layerNodes = new vector<Node*>();
}

Layer::~Layer()
{
    delete learningRate;
    delete layerName;
    delete layerNodes;
}

void Layer::forward()
{
    for (int index = 0; index < this->layerNodes->size(); index++)
        this->layerNodes->at(index)->calculate();
}

void Layer::backward()
{
    for (int index = 0; index < this->layerNodes->size(); index++)
        this->layerNodes->at(index)->derive(*this->learningRate);
}


string Layer::toString()
{
    return *this->layerName;
}
