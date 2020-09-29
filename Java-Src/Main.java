import java.util.*;

public class Main
{
    public static void main(String[] args) 
    {
        runXorModel();
        runNodeModel(true);
        runNodeModel(false);
    }

    private static void runNodeModel(boolean flag) 
    {
        NodeTronModel model = new NodeTronModel(0.01, null, flag);
        ArrayList<ArrayList<Double>> cases = model.nodeCases;
        model.buildNetwork();
        model.trainNetwork(10000000, cases);
        for (ArrayList<Double> inst : cases)
        {
            ArrayList<Double> inputs = new ArrayList<Double>();
            inputs.add(inst.get(0));
            inputs.add(inst.get(1));
            double result = model.runNormal(inputs, true).get(0);
            String example = inst.get(0) + " " + inst.get(1) + " " + inst.get(2);
            System.out.println(example + " result is " + result);
        }
        System.out.println();
    }

    private static void runXorModel() 
    {
        XorModel model = new XorModel(0.01, null);
        ArrayList<ArrayList<Double>> cases = model.xorCases;
        model.buildNetwork();
        model.trainNetwork(1000000, cases);
        for (ArrayList<Double> inst : cases)
        {
            ArrayList<Double> inputs = new ArrayList<Double>();
            inputs.add(inst.get(0));
            inputs.add(inst.get(1));
            double result = model.runNormal(inputs, true).get(0);
            String example = inst.get(0) + " " + inst.get(1) + " " + inst.get(2);
            System.out.println(example + " result is " + result);
        }
        System.out.println();
    }
}