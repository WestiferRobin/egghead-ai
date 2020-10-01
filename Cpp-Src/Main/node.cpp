#include "egghead_comp.hpp"

double Node::calculateT()
{
    double ans = *this->basis;
    for (int index = 0; index < this->weights->size(); index++)
    {
        ans += *this->backPipes->at(index)->getForwardResult() * this->weights->at(index);
    }
    return ans;
}

double Node::active(double paramValue)
{
    switch (*this->activeFlag)
    {
        case 1:
            return (double)(1.0 / (1.0 + exp(-paramValue)));
    }
    return 0.0;
}

double Node::deriveActive(double paramValue)
{
    switch (*this->activeFlag)
    {
        case 1:
            double activeResult = this->active(paramValue);
            return (activeResult * (1.0 - activeResult));
    }
    return 0.0;
}


Node::Node(int size, int newActiveFlag, string name, bool isRandom)
{
    nodeName = new string(name);
    activeFlag = new int(newActiveFlag);
    basis = new double(isRandom ? (double)rand() / RAND_MAX : 0.5);    // do random shit
    weights = new vector<double>();
    for (int i = 0; i < size; i++)
    {
        double weight = isRandom ? (double)rand() / RAND_MAX : 0.5; // do random shit
        weights->push_back(weight);

    }
    frontPipes = new vector<Pipe*>();
    backPipes = new vector<Pipe*>();
}

Node::~Node()
{
    delete nodeName;
    delete activeFlag;
    delete basis;
    delete weights;
    delete frontPipes;
    delete backPipes;
}

void Node::derive(double learningRate)
{
    double tValue = this->calculateT();
    double outterDer = this->deriveActive(tValue);
    double paramDer = 0.0;

    for (int index = 0; index < this->frontPipes->size(); index++)
        paramDer += *this->frontPipes->at(index)->getBackwardResult();

    outterDer *= paramDer;

    for (int index = 0; index < this->weights->size(); index++)
    {
        double innerDer = *this->backPipes->at(index)->getForwardResult();
        this->weights->at(index) -= (double)(learningRate * outterDer * innerDer);
        this->backPipes->at(index)->setBackwardResult(outterDer * (this->weights->at(index)));
    }

    *this->basis -= (learningRate * outterDer);
}

void Node::calculate()
{
    double tValue = this->calculateT();
    for (int index = 0; index < this->frontPipes->size(); index++)
        this->frontPipes->at(index)->setForwardResult(this->active(tValue));
}

string Node::toString()
{
    string ans = "Node : " + *this->nodeName + " \n";
    // ans += "weights: " + this->getWeights() + " \n";
    // ans += "basis: " + this->getBasis();

    return ans;
}