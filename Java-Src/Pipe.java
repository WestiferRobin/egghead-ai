public class Pipe
{
    private double _forwardResult;
    private double _backwardResult;

    public Pipe()
    {
        this.setForwardResult(0.0);
        this.setBackwardResult(0.0);
    }

    public double getForwardResult() 
    {
        return this._forwardResult;
    }

    public void setForwardResult(double value) 
    {
        this._forwardResult = value;
    }

    public double getBackwardResult() 
    {
        return this._backwardResult;
    }

    public void setBackwardResult(double value) 
    {
        this._backwardResult = value;
    }
}
