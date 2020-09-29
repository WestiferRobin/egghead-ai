import java.util.*;

public class NodeTronModel extends Network
{
    public ArrayList<ArrayList<Double>> nodeCases = new ArrayList<ArrayList<Double>>();

    public NodeTronModel(double learningRate, ArrayList<Layer> layers, boolean isAnd)
    {
        super(learningRate, layers);

        if (isAnd)
        {
            initAndCases();
        }
        else
        {
            initOrCases();
        }
    }

    private void initAndCases()
    {
        nodeCases.add(new ArrayList<Double>(Arrays.asList(1.0, 1.0, 1.0)));
        nodeCases.add(new ArrayList<Double>(Arrays.asList(0.0, 1.0, 0.0)));
        nodeCases.add(new ArrayList<Double>(Arrays.asList(1.0, 0.0, 0.0)));
        nodeCases.add(new ArrayList<Double>(Arrays.asList(0.0, 0.0, 0.0)));
    }

    private void initOrCases()
    {
        nodeCases.add(new ArrayList<Double>(Arrays.asList(1.0, 1.0, 1.0)));
        nodeCases.add(new ArrayList<Double>(Arrays.asList(0.0, 1.0, 1.0)));
        nodeCases.add(new ArrayList<Double>(Arrays.asList(1.0, 0.0, 1.0)));
        nodeCases.add(new ArrayList<Double>(Arrays.asList(0.0, 0.0, 0.0)));
    }

    @Override
    public void buildNetwork()
    {
        System.out.println("Starting to build NodeTronModel");
        Node mainNode = new Node(2, 1, "mainNode", true);
        Layer hiddenLayer = new Layer(this.getLearningRate(), "hiddenlayer1");
        ArrayList<State> inputLayer = new ArrayList<State>();
        inputLayer.add(new State());
        inputLayer.add(new State());
        ArrayList<State> outputLayer = new ArrayList<State>();
        outputLayer.add(new State());

        for (State state : inputLayer)
        {
            this.connectStateToNode(state, mainNode);
        }
        for (State state : outputLayer)
        {
            this.connectNodeToState(mainNode, state);
        }

        hiddenLayer.addNode(mainNode);

        this.getLayers().add(hiddenLayer);

        this.setOutputLayer(outputLayer);
        this.setInputLayer(inputLayer);

        System.out.println("Finished building NodeTronModel");
    }

    @Override
    public void trainNetwork(int iterations, ArrayList<ArrayList<Double>> cases)
    {
        Random rand = new Random();
        while (iterations > 0)
        {
            ArrayList<Double> inst = cases.get(rand.nextInt(cases.size()));
            ArrayList<Double> forwardList = new ArrayList<Double>();
            forwardList.add(inst.get(0));
            forwardList.add(inst.get(1));
            
            ArrayList<Double> backwardList = new ArrayList<Double>();
            backwardList.add(inst.get(2));

            this.runForward(forwardList);
            this.runBackward(backwardList);
            iterations--;
        }
    }
}