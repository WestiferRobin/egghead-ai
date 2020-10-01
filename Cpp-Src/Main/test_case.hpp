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
		Layer* hiddenLayer = new Layer(*this->getLearningRate(), "hiddenLayer");
		
		this->setInputLayer(new vector<State*>{ new State(), new State() });
		this->setOutputLayer(new vector<State*>{ new State() });

		for (int i = 0; i < this->getInputLayer()->size(); i++)
		{
			this->connectStateToNode(this->getInputLayer()->at(i), mainNode);
		}
		for (int i = 0; i < this->getOutputLayer()->size(); i++)
		{
			this->connectNodeToState(mainNode, this->getOutputLayer()->at(i));
		}

		hiddenLayer->getLayerNodes()->push_back(mainNode);
		this->getLayers()->push_back(hiddenLayer);
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
	XorTron() : Network(0.1) {}
	~XorTron() {}
	void buildNetwork()
	{
		this->setInputLayer(new vector<State*>{ new State(), new State() });
		this->setOutputLayer(new vector<State*>{ new State() });

		Layer* hiddenLayer1 = new Layer(*this->getLearningRate(), "layer1");
		Layer* hiddenLayer2 = new Layer(*this->getLearningRate(), "layer2");

		hiddenLayer1->setLayerNodes(new vector<Node*>{ new Node(2, 1, "n11", true), new Node(2, 1, "n12", true) });
		hiddenLayer2->setLayerNodes(new vector<Node*>{ new Node(2, 1, "n21", true) });

		for (int i = 0; i < this->getInputLayer()->size(); i++)
		{
			for (int j = 0; j < hiddenLayer1->getLayerNodes()->size(); j++)
			{
				this->connectStateToNode(this->getInputLayer()->at(i), hiddenLayer1->getLayerNodes()->at(j));
			}
		}

		for (int i = 0; i < hiddenLayer1->getLayerNodes()->size(); i++)
		{
			for (int j = 0; j < hiddenLayer2->getLayerNodes()->size(); j++)
			{
				this->connectPipeline(hiddenLayer1->getLayerNodes()->at(i), hiddenLayer2->getLayerNodes()->at(j));
			}
		}

		this->connectNodeToState(hiddenLayer2->getLayerNodes()->at(0), this->getOutputLayer()->at(0));

		this->getLayers()->push_back(hiddenLayer1);
		this->getLayers()->push_back(hiddenLayer2);
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