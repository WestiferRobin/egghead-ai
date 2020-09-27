import java.util.*;
import java.lang.*;

public class Layer
{
    private double _learningRate;
    private String _layerName;
    private ArrayList<Node> _layerNodes;

    public Layer(double learn_rate, String name)
    {
        this._learningRate = learn_rate;
        this._layerName = name;
        this._layerNodes = new ArrayList<Node>();
    }

    public double getLearningRate()
    {
        return this._learningRate;
    }

    public String getLayerName()
    {
        return this._layerName;
    }

    public ArrayList<Node> getLayerNodes()
    {
        return this._layerNodes;
    }

    public void forward()
    {
        for (Node node : this.getLayerNodes())
            node.calculate();
    }

    public void backward()
    {
        for (Node node : this.getLayerNodes())
            node.derive(this.getLearningRate());
    }

    public void addNode(Node targetNode)
    {
        this.getLayerNodes().add(targetNode);
    }

    public String toString()
    {
        return this.getLayerName();
    }
}