#ifndef _EGGHEAD_H_
#define _EGGHEAD_H_
#include <iostream>
#include <vector>
#include <math.h> 

using namespace std;

class Pipe
{
private:
    double * forwardResult;
    double * backwardResult;
public:
    Pipe();
    ~Pipe();
    double getForwardResult();
    void setForwardResult(double);
    double getBackwardResult();
    void setBackwardResult(double);
};

class State
{
private:
    double * stateValue;
    Pipe * pipeLine;
public:
    State();
    ~State();
    double getStateValue();
    Pipe getPipeline();
    void loadValue(double);
    void addPipeline(Pipe);
};

class Node
{
private:
    string * nodeName;
    int * activeFlag;
    double * basis;
    vector<double> * weights;
    vector<Pipe> * frontPipes;
    vector<Pipe> * backPipes;

    double calculateT();
    double active(double);
    double deriveActive(double);
public:
    Node(int, int, string, bool);
    ~Node();
    void derive(double);
    void calculate();
    void addFrontPipe(Pipe);
    void addBackPipe(Pipe);
    string toString();
    string getNodeName();
    int getActiveFlag();
    vector<double> getWeights();
    void setWeights(vector<double>);
    double getBasis();
    void setBasis(double);
    void setFrontPipes(vector<Pipe>);
    vector<Pipe> getFrontPipes();
    void setBackPipes(vector<Pipe>);
    vector<Pipe> getBackPipes();
};

class Layer
{
private:
    double * learningRate;
    string * layerName;
    vector<Node> * layerNodes;
public:
    Layer(double, string);
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
    double * learningRate;
    vector<Layer> * layers;
    vector<State> * inputLayer;
    vector<State> * outputLayer;
    void forward(vector<double>);
    void backward(vector<double>);
protected:
    double getLearningRate();
    vector<Layer> getLayers();
    void setLayers(vector<Layer>);
    vector<State> getInputLayer();
    void setInputLayer(vector<State>);
    vector<State> getOutputLayer();
    void setOutputLayer(vector<State>);
public:
    Network(double, vector<Layer>);
    ~Network();
    virtual void buildNetwork();
    virtual void trainNetwork(int, vector<vector<double>>);
    void connectPipeline(Node, Node);
    void connectStateToNode(State, Node targetNode);
    void connectNodeToState(Node sourceNode, State);
    vector<double> runNormal(vector<double>, bool);
    void runForward(vector<double>);
    void runBackward(vector<double>);
};

#endif