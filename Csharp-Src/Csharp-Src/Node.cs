using System;
using System.Collections.Generic;
using System.Text;

namespace Csharp_Src
{
    public class Node
    {
        public string NodeName { get; }
        private int ActiveFlag { get; }
        private List<double> Weights { get; set; }
        private double Basis { get; set; }
        private List<Pipe> FrontPipes { get;}
        private List<Pipe> BackPipes { get; }

        public Node(int size, int active_flag=1, string name="", bool isRandom = true)
        {
            Random rand = new Random();
            this.NodeName = name;
            this.ActiveFlag = active_flag;
            this.Weights = new List<double>();
            this.Basis = isRandom ? rand.NextDouble() : 0.5;
            for (int i = 0; i < size; i++)
                this.Weights.Add(isRandom ? rand.NextDouble() : 0.5);
            this.FrontPipes = new List<Pipe>();
            this.BackPipes = new List<Pipe>();
        }

        public void Derive(double learningRate)
        {
            double tValue = this.CalculateT();
            double outterDer = this.DeriveActive(tValue);
            double paramDer = 0.0;

            foreach (var pipe in this.FrontPipes)
                paramDer += pipe.BackwardResult;

            outterDer *= paramDer;

            for (int index = 0; index < this.Weights.Count; index++)
            {
                double innerDer = this.BackPipes[index].ForwardResult;
                this.Weights[index] -= (double)(learningRate * outterDer * innerDer);
                this.BackPipes[index].BackwardResult = outterDer * this.Weights[index];
            }
            this.Basis -= learningRate * outterDer;
        }

        public void Calculate()
        {
            double tValue = this.CalculateT();
            foreach (var pip in this.FrontPipes)
                pip.ForwardResult = this.Active(tValue);
        }

        private double CalculateT()
        {
            double ans = this.Basis;
            if (this.BackPipes.Count != this.Weights.Count)
                throw new Exception("This node is not working due to pipe and or weight configuration");
            for (int index = 0; index < this.Weights.Count; index++)
            {
                ans += this.BackPipes[index].ForwardResult * this.Weights[index];
            }
            return ans;
        }

        private double Active(double paramValue)
        {
            switch (this.ActiveFlag)
            {
                case 1:
                    return (double)(1.0 / (1.0 + Math.Exp(-paramValue)));
                default:
                    return 0.0;
            }
        }

        private double DeriveActive(double paramValue)
        {
            switch (this.ActiveFlag)
            {
                case 1:
                    double activeResult = this.Active(paramValue);
                    return (activeResult * (1.0 - activeResult));
                default:
                    return 0.0;
            }
        }

        public void AddFrontPipe(Pipe pipe)
        {
            this.FrontPipes.Add(pipe);
        }

        public void AddBackPipe(Pipe pipe)
        {
            this.BackPipes.Add(pipe);
        }

        public override string ToString()
        {
            string ans = $"Node : {this.NodeName} \n";
            ans += $"weights: {this.Weights} \n";
            ans += $"basis: {this.Basis}";

            return ans;
        }
    }
}
