import java.util.*;

public class Node
{
    private String _nodeName;
    private int _activeFlag;
    private ArrayList<Double> _weights;
    private double _basis;
    private ArrayList<Pipe> _frontPipes;
    private ArrayList<Pipe> _backPipes;

    public Node(int size, int active_flag, String name, boolean isRandom)
    {
        Random rand = new Random();
        this._nodeName = name;
        this._activeFlag = active_flag;
        this._weights = new ArrayList<Double>();
        this._basis = isRandom ? rand.nextDouble() : 0.5;
        for (int i = 0; i < size; i++)
            this._weights.add(isRandom ? rand.nextDouble() : 0.5);
        this._frontPipes = new ArrayList<Pipe>();
        this._backPipes = new ArrayList<Pipe>();
    }

    public String getNodeName()
    {
        return this._nodeName;
    }

    public int getActiveFlag()
    {
        return this._activeFlag;
    }

    public ArrayList<Double> getWeights()
    {
        return this._weights;
    }

    public void setWeights(ArrayList<Double> value)
    {
        this._weights = value;
    }

    public void setBasis(double value)
    {
        this._basis = value;
    }

    public double getBasis()
    {
        return this._basis;
    }

    public ArrayList<Pipe> getFrontPipes()
    {
        return this._frontPipes;
    }

    public void setFrontPipes(ArrayList<Pipe> newPipes)
    {
        this._frontPipes = newPipes;
    }

    public ArrayList<Pipe> getBackPipes()
    {
        return this._backPipes;
    }

    public void setBackPipes(ArrayList<Pipe> newPipes)
    {
        this._frontPipes = newPipes;
    }

    public void derive(double learningRate)
    {
        double tValue = this.calculateT();
        double outterDer = this.deriveActive(tValue);
        double paramDer = 0.0;

        for (Pipe pipe : this.getFrontPipes())
            paramDer += pipe.getBackwardResult();

        outterDer *= paramDer;

        ArrayList<Double> instWeights = this.getWeights();
        ArrayList<Pipe> instBackpipes = this.getBackPipes();
        for (int index = 0; index < this.getWeights().size(); index++)
        {
            double innerDer = instBackpipes.get(index).getForwardResult();
            instWeights.set(index, (double)(learningRate * outterDer * innerDer));
            instBackpipes.get(index).setBackwardResult(outterDer * instWeights.get(index));
        }
        this.setBackPipes(instBackpipes);
        this.setWeights(instWeights);
        this.setBasis(this.getBasis() - (learningRate * outterDer));
    }

    public void calculate()
    {
        double tValue = this.calculateT();
        for (Pipe pipe : this.getFrontPipes())
            pipe.setForwardResult(this.active(tValue));
    }

    private double calculateT()
    {
        double ans = this.getBasis();
        ArrayList<Double> instWeights = this.getWeights();
        ArrayList<Pipe> instBackpipes = this.getBackPipes();
        for (int index = 0; index < instWeights.size(); index++)
        {
            ans += instBackpipes.get(index).getForwardResult() * instWeights.get(index);
        }
        return ans;
    }

    private double active(double paramValue)
    {
        switch (this.getActiveFlag())
        {
            case 1:
                return (double)(1.0 / (1.0 + Math.exp(-paramValue)));
            default:
                return 0.0;
        }
    }

    private double deriveActive(double paramValue)
    {
        switch (this.getActiveFlag())
        {
            case 1:
                double activeResult = this.active(paramValue);
                return (activeResult * (1.0 - activeResult));
            default:
                return 0.0;
        }
    }

    public void addFrontPipe(Pipe pipe)
    {
        this.getFrontPipes().add(pipe);
    }

    public void addBackPipe(Pipe pipe)
    {
        this.getBackPipes().add(pipe);
    }

    public String toString()
    {
        String ans = "Node : " + this.getNodeName() + " \n";
        ans += "weights: " + this.getWeights() + " \n";
        ans += "basis: " + this.getBasis();

        return ans;
    }
}