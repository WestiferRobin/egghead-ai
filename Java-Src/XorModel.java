import java.util.*;

public class XorModel extends Network
{
    public XorModel(double learningRate, ArrayList<Layer> layers)
    {
        super(learningRate, layers);
    }

    @Override
    public void buildNetwork()
    {
        System.out.println("Starting to build XOR Model");

        ArrayList<State> inputLayer = new ArrayList<State>();
        inputLayer.add(new State());
        inputLayer.add(new State());

        ArrayList<State> outputLayer = new ArrayList<State>();
        outputLayer.add(new State());
        
        this.setInputLayer(inputLayer);
        this.setOutputLayer(outputLayer);

        Layer hiddenLayer1 = new Layer(this.getLearningRate(), "layer1");
        hiddenLayer1.addNode(new Node(2, 1, "n11", true));
        hiddenLayer1.addNode(new Node(2, 1, "n12", true));

        Layer hiddenLayer2 = new Layer(this.getLearningRate(), "layer2");
        hiddenLayer2.addNode(new Node(2, 1, "n12", true));

        for (State state : this.getInputLayer())
        {
            for (Node node : hiddenLayer1.getLayerNodes())
            {
                this.connectStateToNode(state, node);
            }
        }

        for (Node node1 : hiddenLayer1.getLayerNodes())
        {
            for (Node node2 : hiddenLayer2.getLayerNodes())
            {
                this.connectPipeline(node1, node2);
            }
        }

        this.connectNodeToState(hiddenLayer2.getLayerNodes().get(0), this.getOutputLayer().get(0));

        this.getLayers().add(hiddenLayer1);
        this.getLayers().add(hiddenLayer2);

        System.out.println("Finished building XOR model");
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