using System;
using System.Collections.Generic;

namespace Csharp_Src
{
    public class Node
    {
        public string NodeName { get; set; }
        public int ActiveFlag { get; set; }
        public List<double> Weights { get; set; }
        public double Basis { get; set; }
        public List<Pipe> FrontPipes { get; set; }
        public List<Pipe> BackPipes { get; set; }

        public Node(int size, int activeFlag=1, string name="", bool isRandom = true)
        {
            Random rand = new Random();

            this.NodeName = name;
            this.ActiveFlag = activeFlag;
            this.Weights = new List<double>();

            this.Basis = isRandom ? rand.NextDouble() : 0.5;

            for (int i = 0; i < size; i++)
                this.Weights.Add(isRandom ? rand.NextDouble() : 0.5);

            this.FrontPipes = new List<Pipe>();
            this.BackPipes = new List<Pipe>();
        }

        private double CalculateT()
        {
            double ans = this.Basis;

            if (this.BackPipes.Count != this.Weights.Count)
                throw new Exception("This node is not working due to pipe and or weight configuration");
            
            for (int index = 0; index < this.Weights.Count; index++)
                ans += this.BackPipes[index].ForwardResult * this.Weights[index];
            
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


        public override string ToString()
        {
            string ans = $"Node : {this.NodeName} \n";
            ans += $"weights: {this.Weights} \n";
            ans += $"basis: {this.Basis}";

            return ans;
        }
    }
}
