using System;
using System.Collections.Generic;

namespace Csharp_Src
{
    public class Network
    {
        public double LearningRate { get; }
        public List<Layer> Layers { get; set; }
        public List<State> InputLayer { get; set; }
        public List<State> OutputLayer { get; set; }

        public Network(double learningRate = 0.01, List<Layer> layers = null)
        {
            this.LearningRate = learningRate;
            this.Layers = layers != null ? layers : new List<Layer>();
            this.InputLayer = null;
            this.OutputLayer = null;
        }

        public virtual void BuildNetwork()
        {
            throw new Exception("Please implement BuildNetwork in the child class.");
        }

        public virtual void TrainNetwork(int iterations, List<List<double>> cases)
        {
            throw new Exception("Please implement TrainNetwork in the child class.");
        }

        public void ConnectPipeline(Node sourceNode, Node targetNode)
        {
            Pipe pipeLine = new Pipe();
            sourceNode.AddFrontPipe(pipeLine);
            targetNode.AddBackPipe(pipeLine);
        }

        public void ConnectStateToNode(State sourceState, Node targetNode)
        {
            if (sourceState.Pipeline == null)
            {
                Pipe pipeLine = new Pipe();
                sourceState.AddPipeline(pipeLine);
                targetNode.AddBackPipe(pipeLine);
            }
            else
            {
                targetNode.AddBackPipe(sourceState.Pipeline);
            }
        }

        public void ConnectNodeToState(Node sourceNode, State targetState)
        {
            if (targetState.Pipeline == null)
            {
                Pipe pipeLine = new Pipe();
                sourceNode.AddFrontPipe(pipeLine);
                targetState.AddPipeline(pipeLine);
            }
            else
            {
                sourceNode.AddFrontPipe(targetState.Pipeline);
            }
        }

        public List<double> RunNormal(List<double> inputs, bool returnRaw = false)
        {
            this.Forward(inputs);
            List<double> ans = new List<double>();

            foreach (var outputState in this.OutputLayer)
            {
                if (returnRaw)
                {
                    ans.Add(outputState.StateValue);
                }
                else
                {
                    ans.Add(0.5 <= outputState.StateValue ? 1 : 0);
                }
            }

            return ans;
        }

        public void RunForward(List<double> inputs)
        {
            this.Forward(inputs);
        }

        private void Forward(List<double> inputs)
        {
            if (inputs.Count != this.InputLayer.Count)
                throw new Exception("Inputs don\'t aline with input states. Please check again.");

            for (int index = 0; index < inputs.Count; index++)
                this.InputLayer[index].LoadValue(inputs[index]);
            foreach (var inputState in this.InputLayer)
                inputState.Pipeline.ForwardResult = inputState.StateValue;
            foreach (var layer in this.Layers)
                layer.Forward();
            foreach (var outputState in this.OutputLayer)
                outputState.LoadValue(outputState.Pipeline.ForwardResult);
        }

        public void RunBackward(List<double> expected)
        {
            this.Backward(expected);
        }

        private void Backward(List<double> expected)
        {
            if (expected.Count != this.OutputLayer.Count)
                throw new Exception("Expected and actual length isn\'t valid.");
            
            double constant = 1.0 / expected.Count;
            for (int index = 0; index < expected.Count; index++)
                this.OutputLayer[index].Pipeline.BackwardResult = (-1.0 * constant * (expected[index] - this.OutputLayer[index].StateValue));
            
            int indexLayer = this.Layers.Count - 1;
            while (indexLayer >= 0)
            {
                this.Layers[indexLayer--].Backward();
            }
        }
    }
}
