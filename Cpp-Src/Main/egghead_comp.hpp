#ifndef _EGGHEAD_H_
#define _EGGHEAD_H_
#include <iostream>
#include <vector>
#include <math.h> 

using namespace std;

class Pipe
{
private:
    double* forwardResult;
    double* backwardResult;
public:
    Pipe();
    ~Pipe();

    void setForwardResult(double value) { *this->forwardResult = value; }
    void setBackwardResult(double value) { *this->backwardResult = value; }
    double* getForwardResult() { return this->forwardResult; }
    double* getBackwardResult() { return this->backwardResult; }
};

class State
{
private:
    double* stateValue;
    Pipe* pipeline;
public:
    State();
    ~State();

    void setStateValue(double value) { *this->stateValue = value; }
    void setPipeline(Pipe* value) { this->pipeline = value; }
    double* getStateValue() { return this->stateValue; }
    Pipe* getPipeline() { return this->pipeline; }
};

class Node
{
private:
    string* nodeName;
    int* activeFlag;
    double* basis;
    vector<double>* weights;
    vector<Pipe*>* frontPipes;
    vector<Pipe*>* backPipes;

    double calculateT();
    double active(double);
    double deriveActive(double);
public:
    Node(int, int, string, bool);
    ~Node();
    void derive(double);
    void calculate();
    string toString();

    void setNodeName(string value) { *this->nodeName = value; }
    string* getNodeName() { return this->nodeName; }
    void setActiveFlag(int value) { *this->activeFlag = value; }
    int* getActiveFlag() { return this->activeFlag; }
    void setBasis(double basis) { *this->basis = basis; }
    double* getBasis() { return this->basis; }
    void setWeights(vector<double>* value) { this->weights = value; }
    vector<double>* getWeights() { return this->weights; }
    void setFrontPipes(vector<Pipe*>* value) { this->frontPipes = value; }
    vector<Pipe*>* getFrontPipes() { return this->frontPipes; }
    void setBackPipes(vector<Pipe*>* value) { this->backPipes = value; }
    vector<Pipe*>* getBackPipes() { return this->backPipes; }
};

class Layer
{
private:
    double* learningRate;
    string* layerName;
    vector<Node*>* layerNodes;
public:
    Layer(double, string);
    ~Layer();
    void forward(void);
    void backward(void);
    string toString();

    void setLearningRate(double* value) { this->learningRate = value; }
    double* getLearningRate() { return this->learningRate; }
    void setLayerName(string* value) { this->layerName = value; }
    string* getLayerName() { return this->layerName; }
    void setLayerNodes(vector<Node*>* value) { this->layerNodes = value; }
    vector<Node*>* getLayerNodes() { return this->layerNodes; }
};

class Network
{
private:
    double* learningRate;
    vector<Layer*>* layers;
    vector<State*>* inputLayer;
    vector<State*>* outputLayer;

    void forward(vector<double>);
    void backward(vector<double>);
public:
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

    double* getLearningRate() { return this->learningRate; }
    void setLearningRate(double value) { *this->learningRate = value; }
    vector<Layer*>* getLayers() { return this->layers; }
    void setLayers(vector<Layer*>* value) { this->layers = value; }
    void setInputLayer(vector<State*>* value) { this->inputLayer = value; }
    vector<State*>* getInputLayer() { return this->inputLayer; }
    void setOutputLayer(vector<State*>* value) { this->outputLayer = value; }
    vector<State*>* getOutputLayer() { return this->outputLayer; }
};

#endif