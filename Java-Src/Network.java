import java.util.*;

public class Network
{
    private double _learningRate;
    private ArrayList<Layer> _layers;
    private ArrayList<State> _inputLayer;
    private ArrayList<State> _outputLayer;

    public Network(double learningRate, ArrayList<Layer> layers)
    {
        this._learningRate = learningRate;
        this._layers = layers != null ? layers : new ArrayList<Layer>();
        this._inputLayer = null;
        this._outputLayer = null;
    }

    protected double getLearningRate() 
    {
        return this._learningRate;
    }

    protected ArrayList<Layer> getLayers() 
    {
        return this._layers;
    }

    protected void setLayers(ArrayList<Layer> value) 
    {
        this._layers = value;
    }

    protected ArrayList<State> getInputLayer() 
    {
         return this._inputLayer; 
    }

    protected void setInputLayer(ArrayList<State> value) 
    {
        this._inputLayer = value;
    }

    protected ArrayList<State> getOutputLayer() 
    {
        return this._outputLayer;
    }

    protected void setOutputLayer(ArrayList<State> value) 
    {
        this._outputLayer = value;
    }

    public void buildNetwork()
    {
        System.out.print("Please implement BuildNetwork in the child class.");
    }

    public void trainNetwork(int iterations, ArrayList<ArrayList<Double>> cases)
    {
        System.out.print("Please implement TrainNetwork in the child class.");
    }

    public void connectPipeline(Node sourceNode, Node targetNode)
    {
        Pipe pipeLine = new Pipe();
        sourceNode.addFrontPipe(pipeLine);
        targetNode.addBackPipe(pipeLine);
    }

    public void connectStateToNode(State sourceState, Node targetNode)
    {
        if (sourceState.getPipeline() == null)
        {
            Pipe pipeLine = new Pipe();
            sourceState.addPipeline(pipeLine);
            targetNode.addBackPipe(pipeLine);
        }
        else
        {
            targetNode.addBackPipe(sourceState.getPipeline());
        }
    }

    public void connectNodeToState(Node sourceNode, State targetState)
    {
        if (targetState.getPipeline() == null)
        {
            Pipe pipeLine = new Pipe();
            sourceNode.addFrontPipe(pipeLine);
            targetState.addPipeline(pipeLine);
        }
        else
        {
            sourceNode.addFrontPipe(targetState.getPipeline());
        }
    }

    public ArrayList<Double> runNormal(ArrayList<Double> inputs, boolean returnRaw)
    {
        this.forward(inputs);
        ArrayList<Double> ans = new ArrayList<Double>();

        for (State outputState : this.getOutputLayer())
        {
            if (returnRaw)
            {
                ans.add(outputState.getStateValue());
            }
            else
            {
                ans.add(0.5 <= outputState.getStateValue() ? 1.0 : 0.0);
            }
        }

        return ans;
    }

    public void runForward(ArrayList<Double> inputs)
    {
        this.forward(inputs);
    }

    private void forward(ArrayList<Double> inputs)
    {
        for (int index = 0; index < inputs.size(); index++)
            this.getInputLayer().get(index).loadValue(inputs.get(index));
        for (State inputState : this.getInputLayer())
            inputState.getPipeline().setForwardResult(inputState.getStateValue());
        for (Layer layer : this.getLayers())
            layer.forward();
        for (State outputState : this.getOutputLayer())
            outputState.loadValue(outputState.getPipeline().getForwardResult());
    }

    public void runBackward(ArrayList<Double> expected)
    {
        this.backward(expected);
    }

    private void backward(ArrayList<Double> expected)
    {
        double constant = 1.0 / expected.size();
        for (int index = 0; index < expected.size(); index++)
        {
            double paramValue = (-1.0 * constant * (expected.get(index) - this.getOutputLayer().get(index).getStateValue()));
            this.getOutputLayer().get(index).getPipeline().setBackwardResult(paramValue);
        }
        
        int indexLayer = this.getLayers().size() - 1;
        while (indexLayer >= 0)
        {
            this.getLayers().get(indexLayer--).backward();
        }
    }
}