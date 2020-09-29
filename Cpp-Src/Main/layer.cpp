#include "egghead_comp.hpp"

Layer::Layer(double learn_rate, string name)
{
    learningRate = &learn_rate;
    layerName = &name;
    layerNodes = new vector<Node>();
}

Layer::~Layer()
{
    delete learningRate;
    delete layerName;
    delete layerNodes;
}

void Layer::forward()
{
    for (int index = 0; index < this->getLayerNodes().size(); index++)
        this->getLayerNodes()[index].calculate();
}

void Layer::backward()
{
    for (int index = 0; index < this->getLayerNodes().size(); index++)
        this->getLayerNodes()[index].derive(this->getLearningRate());
}

void Layer::addNode(Node targetNode)
{
    getLayerNodes().push_back(targetNode);
}

string Layer::toString()
{
    return getLayerName();
}

double Layer::getLearningRate()
{
    return *learningRate;
}

string Layer::getLayerName()
{
    return *layerName;
}

vector<Node> Layer::getLayerNodes()
{
    return *layerNodes;
}
