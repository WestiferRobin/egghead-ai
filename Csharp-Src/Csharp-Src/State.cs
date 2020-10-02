namespace Csharp_Src
{
    public class State
    {
        public double StateValue { get; set; }

        public Pipe Pipeline { get; set; }

        public State()
        {
            this.StateValue = 0.0;
            this.Pipeline = null;
        }
    }
}
