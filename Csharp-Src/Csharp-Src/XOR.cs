using System;
using System.Collections.Generic;
using System.Text;

namespace Csharp_Src
{
    public class XOR : Network
    {
        public List<List<double>> XorCases { get; set; }

        public XOR() : base()
        {
            this.XorCases = new List<List<double>>()
            {
                new List<double>() {1.0, 1.0, 0.0},
                new List<double>() {0.0, 1.0, 1.0},
                new List<double>() {0.0, 0.0, 0.0},
                new List<double>() {1.0, 0.0, 1.0},
            };
        }

        public override void BuildNetwork()
        {
            Console.WriteLine("Starting to build XOR Model");
            this.InputLayer = new List<State>() { new State(), new State() };
            this.OutputLayer = new List<State>() { new State() };

            Layer hiddenLayer1 = new Layer(this.LearningRate, "layer1");
            hiddenLayer1.AddNode(new Node(2, 1, "n11"));
            hiddenLayer1.AddNode(new Node(2, 1, "n12"));

            Layer hiddenLayer2 = new Layer(this.LearningRate, "layer2");
            hiddenLayer2.AddNode(new Node(2, 1, "n12"));

            foreach (var state in this.InputLayer)
            {
                foreach (var node in hiddenLayer1.LayerNodes)
                {
                    this.ConnectStateToNode(state, node);
                }
            }

            foreach (var node1 in hiddenLayer1.LayerNodes)
            {
                foreach (var node2 in hiddenLayer2.LayerNodes)
                {
                    this.ConnectPipeline(node1, node2);
                }
            }

            this.ConnectNodeToState(hiddenLayer2.LayerNodes[0], this.OutputLayer[0]);

            this.Layers.Add(hiddenLayer1);
            this.Layers.Add(hiddenLayer2);

            Console.WriteLine("Finished building XOR model");
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
