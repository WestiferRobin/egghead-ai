import java.util.*;

public class Main
{
    private static ArrayList<ArrayList<Double>> cases;
    private final int TRAIN_TIMES = 1000000;

    public static void main(String[] args) 
    {
        for (int flag = 1; flag <= 3; flag++)
        {
            switch (flag)
            {
                case 1:
                    System.out.println("Xor Model");
                    runXor();
                    break;
                case 2:
                    System.out.println("Node Tron Model: And");
                    runNodeTron(true);
                    break;
                case 3:
                    System.out.println("Node Tron Model: Or");
                    runNodeTron(false);
                    break;
            }
            System.out.println();
        }
    }

    private static void runNodeTron(boolean isAnd) 
    {
        Network caseExample = new NodeTronModel();
        cases = isAnd ? new ArrayList<ArrayList<Double>>()
        {
            new ArrayList<Double>() {1.0, 1.0, 1.0},
            new ArrayList<Double>() {1.0, 0.0, 0.0},
            new ArrayList<Double>() {0.0, 1.0, 0.0},
            new ArrayList<Double>() {0.0, 0.0, 0.0},
        } : 
        new ArrayList<ArrayList<Double>>()
        {
            new ArrayList<Double>() {1.0, 1.0, 1.0},
            new ArrayList<Double>() {0.0, 1.0, 1.0},
            new ArrayList<Double>() {0.0, 0.0, 0.0},
            new ArrayList<Double>() {1.0, 0.0, 1.0},
        };
        caseExample.BuildNetwork();
        caseExample.TrainNetwork(TRAIN_TIMES, Cases);
        foreach (var datCase in Cases)
        {
            var ans = caseExample.RunNormal(new ArrayList<Double>() { datCase[0], datCase[1] }, true)[0];
            Console.WriteLine($"{string.Join(",", datCase)} result is {ans}");
        }
    }

    private static void runXor() 
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