#include "egghead_comp.hpp"

void Network::forward(vector<double> inputs)
{
    for (int index = 0; index < inputs.size(); index++)
        this->getInputLayer()[index].loadValue(inputs[index]);
    for (int index = 0; index < this->getInputLayer().size(); index++)
        this->getInputLayer()[index].getPipeline().setForwardResult(this->getInputLayer()[index].getStateValue());
    for (int index = 0; index < this->getLayers().size(); index++)
        this->getLayers()[index].forward();
    for (int index = 0; index < this->getOutputLayer().size(); index++)
        this->getOutputLayer()[index].loadValue(this->getOutputLayer()[index].getPipeline().getForwardResult());
}

void Network::backward(vector<double> expected)
{
    double constant = 1.0 / expected.size();
    for (int index = 0; index < expected.size(); index++)
    {
        double paramValue = (-1.0 * constant * (expected[index] - this->getOutputLayer()[index].getStateValue()));
        this->getOutputLayer()[index].getPipeline().setBackwardResult(paramValue);
    }
    
    int indexLayer = this->getLayers().size() - 1;
    while (indexLayer >= 0)
    {
        this->getLayers()[indexLayer--].backward();
    }
}

double Network::getLearningRate()
{
    return *learningRate;
}

vector<Layer> Network::getLayers()
{
    return *layers;
}

void Network::setLayers(vector<Layer> newLayers)
{
    delete layers;
    layers = &newLayers;
}

vector<State> Network::getInputLayer()
{
    return *inputLayer;
}

void Network::setInputLayer(vector<State> newLayer)
{
    delete inputLayer;
    inputLayer = &newLayer;
}

vector<State> Network::getOutputLayer()
{
    return *outputLayer;
}

void Network::setOutputLayer(vector<State> newLayer)
{
    delete outputLayer;
    outputLayer = &newLayer;
}

Network::Network(double newLearningRate, vector<Layer> newLayers)
{
    learningRate = &newLearningRate;
    layers = &newLayers;
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

void Network::trainNetwork(int, vector<vector<double>>)
{
    cout << "Please implement TrainNetwork in the child class." << endl;
}

void Network::connectPipeline(Node sourceNode, Node targetNode)
{
    Pipe pipeline;
    sourceNode.addFrontPipe(pipeline);
    targetNode.addBackPipe(pipeline);
}

void Network::connectStateToNode(State sourceState, Node targetNode)
{
    // fix this bullshit
    Pipe checker = sourceState.getPipeline();
    if (&checker == NULL)
    {
        Pipe pipeline;
        sourceState.addPipeline(pipeline);
        targetNode.addBackPipe(pipeline);
    }
    else
    {
        targetNode.addBackPipe(sourceState.getPipeline());
    }
}

void Network::connectNodeToState(Node sourceNode, State targetState)
{
    // fix this bullshit
    Pipe checker = targetState.getPipeline();
    if (&checker == NULL)
    {
        Pipe pipeline;
        sourceNode.addFrontPipe(pipeline);
        targetState.addPipeline(pipeline);
    }
    else
    {
        sourceNode.addFrontPipe(targetState.getPipeline());
    }
}

vector<double> Network::runNormal(vector<double> inputs, bool returnRaw)
{
    this->forward(inputs);
    vector<double> ans;

    for (State outputState : this->getOutputLayer())
    {
        if (returnRaw)
        {
            ans.push_back(outputState.getStateValue());
        }
        else
        {
            ans.push_back(0.5 <= outputState.getStateValue() ? 1.0 : 0.0);
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

