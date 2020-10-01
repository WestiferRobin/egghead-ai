#ifndef _TEST_CASE_H_
#define _TEST_CASE_H_
#include "egghead_comp.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class PosTron : public Network
{
public:
	PosTron() : Network(0.01)
	{
		
	}
	~PosTron() {}
	void buildNetwork()
	{
		Node* mainNode = new Node(2, 1, "mainNode", true);
		Layer* hiddenLayer = new Layer(*this->learningRate, "hiddenLayer");
		
		this->inputLayer = new vector<State*>{ new State(), new State() };
		this->outputLayer = new vector<State*>{ new State() };

		for (int i = 0; i < this->inputLayer->size(); i++)
		{
			this->connectStateToNode(this->inputLayer->at(i), mainNode);
		}
		for (int i = 0; i < this->outputLayer->size(); i++)
		{
			this->connectNodeToState(mainNode, this->outputLayer->at(i));
		}

		hiddenLayer->layerNodes->push_back(mainNode);
		this->layers->push_back(hiddenLayer);
	}
	void trainNetwork(int iterations, vector<vector<double>*>* cases)
	{
		while (iterations > 0)
		{
			vector<double>* inst = cases->at(rand() % cases->size());
			this->runForward({ inst->at(0), inst->at(1) });
			this->runBackward({ inst->at(2) });
			iterations--;
		}
	}
};

class XorTron : public Network
{
public:
	XorTron() : Network(0.01) {}
	~XorTron() {}
	void buildNetwork()
	{
		this->inputLayer = new vector<State*>{ new State(), new State() };
		this->outputLayer = new vector<State*>{ new State() };

		Layer* hiddenLayer1 = new Layer(*this->learningRate, "layer1");
		Layer* hiddenLayer2 = new Layer(*this->learningRate, "layer2");

		hiddenLayer1->layerNodes = new vector<Node*>{ new Node(2, 1, "n11", true), new Node(2, 1, "n12", true) };
		hiddenLayer2->layerNodes = new vector<Node*>{ new Node(2, 1, "n21", true) };

		for (int i = 0; i < this->inputLayer->size(); i++)
		{
			for (int j = 0; j < hiddenLayer1->layerNodes->size(); j++)
			{
				this->connectStateToNode(this->inputLayer->at(i), hiddenLayer1->layerNodes->at(j));
			}
		}

		for (int i = 0; i < hiddenLayer1->layerNodes->size(); i++)
		{
			for (int j = 0; j < hiddenLayer2->layerNodes->size(); j++)
			{
				this->connectPipeline(hiddenLayer1->layerNodes->at(i), hiddenLayer2->layerNodes->at(j));
			}
		}

		this->connectNodeToState(hiddenLayer2->layerNodes->at(0), this->outputLayer->at(0));

		this->layers->push_back(hiddenLayer1);
		this->layers->push_back(hiddenLayer2);
	}
	void trainNetwork(int iterations, vector<vector<double>*>* cases)
	{
		while (iterations > 0)
		{
			vector<double>* inst = cases->at(rand() % cases->size());
			this->runForward({ inst->at(0), inst->at(1) });
			this->runBackward({ inst->at(2) });
			iterations--;
		}
	}
};

#endif