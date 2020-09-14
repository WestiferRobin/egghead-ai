#ifndef _EGGHEAD_H_
#define _EGGHEAD_H_
#include <iostream>
#include <vector>

using namespace std;

class Layer
{
private:
    double learningRate;
    string layerName;
    vector<Node> layerNodes;
public:
    Layer(double learn_rate, string name);
    ~Layer();
    void forward(void);
    void backward(void);
    void addNode(Node);
    string toString();
    double getLearningRate();
    string getLayerName();
    vector<Node> getLayerNodes();
};

class Network
{
private:
    double learningRate;
    vector<Layer> layers;
    vector<State> inputState;
    vector<State> outputState;
    void forward(vector<double> inputs);
    void backward(vector<double> expected);
protected:
    double getLearningRate();
    vector<Layer> getLayers();
    void setLayers(vector<Layer>);
    vector<State> getInputState();
    void setInputState(vector<State>);
    vector<State> getOutputState();
    void setOutputState(vector<State>);
public:
    Network(double learningRate, vector<Layer> layers);
    ~Network();
    virtual void buildNetwork();
    virtual void trainNetwork(int iterations, vector<vector<double>> cases);
    void connectPipeline(Node sourceNode, Node targetNode);
    void connectStateToNode(State sourceState, Node targetNode);
    void connectNodeToState(Node sourceNode, State targetState);
    vector<double> runNormal(vector<double> inputs, bool returnRaw);
    void runForward(vector<double> inputs);
    void runBackward(vector<double> expected);
};

class Node
{
private:
    string nodeName;
    int activeFlag;
    vector<double> weights;
    double basis;
    vector<Pipe> FrontPipes;
    vector<Pipe> BackPipes;

    double calculateT();
    double active(double paramValue);
    double deriveActive(double paramValue);
public:
    Node(int size, int active_flag, string name, bool isRandom);
    ~Node();
    void derive(double learningRate);
    void calculate();
    void addFrontPipe(Pipe pipe);
    void addBackPipe(Pipe pipe);
    string toString();
    string getNodeName();
    int getActiveFlag();
    vector<double> getWeights();
    void setWeights(vector<double>);
    double getBasis();
    void setBasis(double);
    vector<Pipe> getFrontPipes();
    vector<Pipe> getBackPipes();
};

class State
{
private:
    double stateValue;
    Pipe pipeLine;
public:
    State();
    ~State();
    double getStateValue();
    void setStateValue(double);
    Pipe getPipeLine();
    void setPipeLine(Pipe);
    void loadValue(double);
    void addPipeline(Pipe);
};

class Pipe
{
private:
    double forwardResult;
    double backwardResult;
public:
    Pipe();
    ~Pipe();
    double getForwardResult();
    void setForwardResult(double);
    double getBackwardResult();
    void setBackwardResult(double);
};

#endif