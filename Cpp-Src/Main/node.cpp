#include "egghead_comp.hpp"

double Node::calculateT()
{
    double ans = this->getBasis();
    vector<double> instWeightes = this->getWeights();
    vector<Pipe> instBackPipes = this->getBackPipes();
    for (int index = 0; index < instWeightes.size(); index++)
    {
        ans += instBackPipes[index].getForwardResult() * instWeightes[index];
    }
    this->setWeights(instWeightes);
    this->setBackPipes(instBackPipes);
    return ans;
}

double Node::active(double paramValue)
{
    switch (this->getActiveFlag())
    {
        case 1:
            return (double)(1.0 / (1.0 + exp(-paramValue)));
    }
    return 0.0;
}

double Node::deriveActive(double paramValue)
{
    switch (this->getActiveFlag())
    {
        case 1:
            double activeResult = this->active(paramValue);
            return (activeResult * (1.0 - activeResult));
    }
    return 0.0;
}


Node::Node(int size, int newActiveFlag, string name, bool isRandom)
{
    nodeName = &name;
    activeFlag = &newActiveFlag;
    basis = new double(0.5);    // do random shit
    weights = new vector<double>();
    for (int i = 0; i < size; i++)
    {
        double weight = 0.5; // do random shit

    }
    frontPipes = new vector<Pipe>();
    backPipes = new vector<Pipe>();
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

    vector<Pipe> instFrontPipes = this->getFrontPipes();
    for (int index = 0; index < instFrontPipes.size(); index++)
        paramDer +=  instFrontPipes[index].getBackwardResult();

    outterDer *= paramDer;

    vector<double> instWeights = this->getWeights();
    vector<Pipe> instBackPipes = this->getBackPipes();
    for (int index = 0; index < instWeights.size(); index++)
    {
        double innerDer = instBackPipes[index].getForwardResult();
        instWeights[index] = (double)(learningRate * outterDer * innerDer);
        instBackPipes[index].setBackwardResult(outterDer * instWeights[index]);
    }
    this->setWeights(instWeights);
    this->setBackPipes(instBackPipes);
    this->setBasis(this->getBasis() - (learningRate * outterDer));
}

void Node::calculate()
{
    double tValue = this->calculateT();
    vector<Pipe> instFrontPipes = this->getFrontPipes();
    for (int index = 0; index < instFrontPipes.size(); index++)
        instFrontPipes[index].setForwardResult(this->active(tValue));
    this->setFrontPipes(instFrontPipes);
}

void Node::addFrontPipe(Pipe pipe)
{
    this->getFrontPipes().push_back(pipe);
}

void Node::addBackPipe(Pipe pipe)
{
    this->getBackPipes().push_back(pipe);
}

string Node::toString()
{
    string ans = "Node : " + this->getNodeName() + " \n";
    // ans += "weights: " + this->getWeights() + " \n";
    // ans += "basis: " + this->getBasis();

    return ans;
}

string Node::getNodeName()
{
    return *nodeName;
}

int Node::getActiveFlag()
{
    return *activeFlag;
}

vector<double> Node::getWeights()
{
    return *weights;
}

void Node::setWeights(vector<double> value)
{
    delete weights;
    weights = &value;
}

double Node::getBasis()
{
    return *basis;
}

void Node::setBasis(double value)
{
    delete basis;
    basis = &value;
}

vector<Pipe> Node::getFrontPipes()
{
    return *frontPipes;
}

void Node::setFrontPipes(vector<Pipe> newPipes)
{
    delete frontPipes;
    frontPipes = &newPipes;
}

vector<Pipe> Node::getBackPipes()
{
    return *backPipes;
}

void Node::setBackPipes(vector<Pipe> newPipes)
{
    delete backPipes;
    backPipes = &newPipes;
}
