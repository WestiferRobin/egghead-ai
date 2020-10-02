using System;
using System.Collections.Generic;
using System.Text;

namespace Csharp_Src
{
    public class Layer
    {
        public double LearningRate { get; set; }
        public string LayerName { get; set; }
        public List<Node> LayerNodes { get; set; }

        public Layer(double learnRate, string name = "")
        {
            this.LearningRate = learnRate;
            this.LayerName = name;
            this.LayerNodes = new List<Node>();
        }

        public void Forward()
        {
            foreach (var node in LayerNodes)
                node.Calculate();
        }

        public void Backward()
        {
            foreach (var node in LayerNodes)
                node.Derive(this.LearningRate);
        }

        public override string ToString()
        {
            return this.LayerName;
        }
    }
}
