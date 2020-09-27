public class State
{
    private double _stateValue;
    private Pipe _pipeLine;

    public State()
    {
        this._stateValue = 0.0;
        this._pipeLine = null;
    }

    public double getStateValue() 
    {
        return this._stateValue;
    }
    
    public Pipe getPipeline()
    {
        return _pipeLine;
    }

    public void loadValue(double stateValue)
    {
        this._stateValue = stateValue;
    }

    public void addPipeline(Pipe pipeline)
    {
        this._pipeLine = pipeline;
    }
}