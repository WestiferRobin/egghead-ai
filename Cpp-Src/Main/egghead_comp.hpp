#ifndef _EGGHEAD_H_
#define _EGGHEAD_H_
#include <iostream>
#include <vector>
#include <math.h> 

using namespace std;

class Pipe
{
public:
    double* forwardResult;
    double* backwardResult;
    Pipe();
    ~Pipe();
};

class State
{
public:
    double* stateValue;
    Pipe* pipeLine;
    State();
    ~State();
};

class Node
{
public:
    double calculateT();
    double active(double);
    double deriveActive(double);
    string* nodeName;
    int* activeFlag;
    double* basis;
    vector<double>* weights;
    vector<Pipe*>* frontPipes;
    vector<Pipe*>* backPipes;
    Node(int, int, string, bool);
    ~Node();
    void derive(double);
    void calculate();
    string toString();
};

class Layer
{
public:
    double* learningRate;
    string* layerName;
    vector<Node*>* layerNodes;
    Layer(double, string);
    ~Layer();
    void forward(void);
    void backward(void);
    string toString();
};

class Network
{
public:
    void forward(vector<double>);
    void backward(vector<double>);
    double* learningRate;
    vector<Layer*>* layers;
    vector<State*>* inputLayer;
    vector<State*>* outputLayer;
    Network(double);
    ~Network();
    virtual void buildNetwork();
    virtual void trainNetwork(int, vector<vector<double>*>*);
    void connectPipeline(Node*, Node*);
    void connectStateToNode(State*, Node*);
    void connectNodeToState(Node*, State*);
    vector<double> runNormal(vector<double>, bool);
    void runForward(vector<double>);
    void runBackward(vector<double>);
};

#endif