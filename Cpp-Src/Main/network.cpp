#include "egghead_comp.hpp"

void Network::forward(vector<double> inputs)
{
    for (int index = 0; index < inputs.size(); index++)
        *this->inputLayer->at(index)->stateValue = inputs[index];
    for (int index = 0; index < this->inputLayer->size(); index++)
        this->inputLayer->at(index)->pipeLine->forwardResult = this->inputLayer->at(index)->stateValue;
    for (int index = 0; index < this->layers->size(); index++)
        this->layers->at(index)->forward();
    for (int index = 0; index < this->outputLayer->size(); index++)
        this->outputLayer->at(index)->stateValue = this->outputLayer->at(index)->pipeLine->forwardResult;
}

void Network::backward(vector<double> expected)
{
    double constant = 1.0 / expected.size();
    for (int index = 0; index < expected.size(); index++)
    {
        double paramValue = (-1.0 * constant * (expected[index] - *this->outputLayer->at(index)->stateValue));
        *this->outputLayer->at(index)->pipeLine->backwardResult = paramValue;
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
    sourceNode->frontPipes->push_back(pipeline);
    targetNode->backPipes->push_back(pipeline);
}

void Network::connectStateToNode(State * sourceState, Node * targetNode)
{
    if (sourceState->pipeLine == nullptr)
    {
        Pipe * pipeline = new Pipe();
        sourceState->pipeLine = pipeline;
        targetNode->backPipes->push_back(pipeline);
    }
    else
    {
        targetNode->backPipes->push_back(sourceState->pipeLine);
    }
}

void Network::connectNodeToState(Node* sourceNode, State * targetState)
{
    if (targetState->pipeLine == nullptr)
    {
        Pipe* pipeline = new Pipe();
        sourceNode->frontPipes->push_back(pipeline);
        targetState->pipeLine = pipeline;
    }
    else
    {
        sourceNode->frontPipes->push_back(targetState->pipeLine);
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
            ans.push_back(*this->outputLayer->at(index)->stateValue);
        }
        else
        {
            ans.push_back(0.5 <= *this->outputLayer->at(index)->stateValue ? 1.0 : 0.0);
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

