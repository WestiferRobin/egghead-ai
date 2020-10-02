using System;
using System.Collections.Generic;

namespace Csharp_Src
{
    public class NodeTronModel : Network
    {
        public NodeTronModel() : base()
        {
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

            hiddenLayer.LayerNodes.Add(mainNode);

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
