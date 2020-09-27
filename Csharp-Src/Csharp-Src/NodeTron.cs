using System;
using System.Collections.Generic;

namespace Csharp_Src
{
    public class NodeTron : Network
    {
        public List<List<double>> AndCases { get; }
        public List<List<double>> OrCases { get; }
        public NodeTron() : base()
        {
            this.AndCases = new List<List<double>>()
            {
                new List<double>() {1.0, 1.0, 1.0},
                new List<double>() {1.0, 0.0, 0.0},
                new List<double>() {0.0, 1.0, 0.0},
                new List<double>() {0.0, 0.0, 0.0},
            };
            this.OrCases = new List<List<double>>()
            {
                new List<double>() {1.0, 1.0, 1.0},
                new List<double>() {0.0, 1.0, 1.0},
                new List<double>() {0.0, 0.0, 0.0},
                new List<double>() {1.0, 0.0, 1.0},
            };
        }

        public override void BuildNetwork()
        {
            Node mainNode = new Node(2, 1, "mainNode");
            Layer hiddenLayer = new Layer(this.LearningRate);
            List<State> inputLayer = new List<State>() { new State(), new State() };
            List<State> outputLayer = new List<State>() { new State() };

            foreach (var state in inputLayer)
                this.ConnectStateToNode(state, mainNode);
            foreach (var state in outputLayer)
                this.ConnectNodeToState(mainNode, state);

            hiddenLayer.AddNode(mainNode);

            this.Layers.Add(hiddenLayer);
            this.OutputLayer = outputLayer;
            this.InputLayer = inputLayer;
        }

        public override void TrainNetwork(int iterations, List<List<double>> cases)
        {
            Random rand = new Random();
            while (iterations > 0)
            {
                List<double> inst = cases[rand.Next(0, cases.Count)];
                this.RunForward(new List<double> { inst[0], inst[1] });
                this.RunBackward(new List<double> { inst[2] });
                iterations--;
            }
        }
    }
}
