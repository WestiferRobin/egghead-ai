using System;
using System.Collections.Generic;
using System.Text;

namespace Csharp_Src
{
    public class State
    {
        public double StateValue { get; set; }

        public Pipe PipeLine { get; set; }

        public State()
        {
            this.StateValue = 0.0;
            this.PipeLine = null;
        }

        public void LoadValue(double stateValue)
        {
            this.StateValue = stateValue;
        }

        public void AddPipeline(Pipe pipeline)
        {
            this.PipeLine = pipeline;
        }
    }
}
