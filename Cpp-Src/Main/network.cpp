#include "egghead_comp.hpp"

void Network::forward(vector<double> inputs)
{
    for (int index = 0; index < inputs.size(); index++)
        this->inputLayer->at(index)->setStateValue(inputs[index]);
    for (int index = 0; index < this->inputLayer->size(); index++)
        this->inputLayer->at(index)->getPipeline()->setForwardResult(*this->inputLayer->at(index)->getStateValue());
    for (int index = 0; index < this->layers->size(); index++)
        this->layers->at(index)->forward();
    for (int index = 0; index < this->outputLayer->size(); index++)
        this->outputLayer->at(index)->setStateValue(*this->outputLayer->at(index)->getPipeline()->getForwardResult());
}

void Network::backward(vector<double> expected)
{
    double constant = 1.0 / expected.size();
    for (int index = 0; index < expected.size(); index++)
    {
        double paramValue = (-1.0 * constant * (expected[index] - *this->outputLayer->at(index)->getStateValue()));
        this->outputLayer->at(index)->getPipeline()->setBackwardResult(paramValue);
    }
    
    int indexLayer = this->layers->size() - 1;
    while (indexLayer >= 0)
    {
        this->layers->at(indexLayer--)->backward();
    }
}

Network::Network(double newLearningRate)
{
    learningRate = new double(newLearningRate);
    layers = new vector<Layer *>();
    inputLayer = nullptr;
    outputLayer = nullptr;
}

Network::~Network()
{
    delete learningRate;
    delete layers;
    delete inputLayer;
    delete outputLayer;
}

void Network::buildNetwork()
{
    cout << "Please implement BuildNetwork in the child class." << endl;
}

void Network::trainNetwork(int iterations, vector<vector<double>*>* cases)
{
    cout << "Please implement TrainNetwork in the child class." << endl;
}

void Network::connectPipeline(Node * sourceNode, Node * targetNode)
{
    Pipe * pipeline = new Pipe();
    sourceNode->getFrontPipes()->push_back(pipeline);
    targetNode->getBackPipes()->push_back(pipeline);
}

void Network::connectStateToNode(State * sourceState, Node * targetNode)
{
    if (sourceState->getPipeline() == nullptr)
    {
        Pipe * pipeline = new Pipe();
        sourceState->setPipeline(pipeline);
        targetNode->getBackPipes()->push_back(pipeline);
    }
    else
    {
        targetNode->getBackPipes()->push_back(sourceState->getPipeline());
    }
}

void Network::connectNodeToState(Node* sourceNode, State * targetState)
{
    if (targetState->getPipeline() == nullptr)
    {
        Pipe* pipeline = new Pipe();
        sourceNode->getFrontPipes()->push_back(pipeline);
        targetState->setPipeline(pipeline);
    }
    else
    {
        sourceNode->getFrontPipes()->push_back(targetState->getPipeline());
    }
}

vector<double> Network::runNormal(vector<double> inputs, bool returnRaw)
{
    this->forward(inputs);
    vector<double> ans;

    for (int index = 0; index < this->outputLayer->size(); index++)
    {
        if (returnRaw)
        {
            ans.push_back(*this->outputLayer->at(index)->getStateValue());
        }
        else
        {
            ans.push_back(0.5 <= *this->outputLayer->at(index)->getStateValue() ? 1.0 : 0.0);
        }
    }

    return ans;
}

void Network::runForward(vector<double> inputs)
{
    this->forward(inputs);
}

void Network::runBackward(vector<double> expected)
{
    this->backward(expected);
}