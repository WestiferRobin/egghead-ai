import java.util.*; 

public class Main
{
    private static ArrayList<ArrayList<Double>> cases;
    private static final int TRAIN_TIMES = 1000000;

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
        Network model = new NodeTronModel(0.01, null);
        cases = new ArrayList<ArrayList<Double>>();

        if (isAnd)
        {
            ArrayList<Double> case1 = new ArrayList<Double>(Arrays.asList(1.0, 1.0, 1.0));
            cases.add(case1);
            ArrayList<Double> case2 = new ArrayList<Double>(Arrays.asList(1.0, 0.0, 0.0));
            cases.add(case2);
            ArrayList<Double> case3 = new ArrayList<Double>(Arrays.asList(0.0, 1.0, 0.0));
            cases.add(case3);
            ArrayList<Double> case4 = new ArrayList<Double>(Arrays.asList(0.0, 0.0, 0.0));
            cases.add(case4);
        }
        else
        {
            ArrayList<Double> case1 = new ArrayList<Double>(Arrays.asList(1.0, 1.0, 1.0));
            cases.add(case1);
            ArrayList<Double> case2 = new ArrayList<Double>(Arrays.asList(1.0, 0.0, 1.0));
            cases.add(case2);
            ArrayList<Double> case3 = new ArrayList<Double>(Arrays.asList(0.0, 1.0, 1.0));
            cases.add(case3);
            ArrayList<Double> case4 = new ArrayList<Double>(Arrays.asList(0.0, 0.0, 0.0));
            cases.add(case4);
        }

        model.buildNetwork();
        model.trainNetwork(TRAIN_TIMES, cases);

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

    private static void runXor() 
    {
        Network model = new XorModel(0.01, null);
        cases = new ArrayList<ArrayList<Double>>();

        ArrayList<Double> case1 = new ArrayList<Double>(Arrays.asList(1.0, 1.0, 0.0));
        cases.add(case1);
        ArrayList<Double> case2 = new ArrayList<Double>(Arrays.asList(1.0, 0.0, 1.0));
        cases.add(case2);
        ArrayList<Double> case3 = new ArrayList<Double>(Arrays.asList(0.0, 1.0, 1.0));
        cases.add(case3);
        ArrayList<Double> case4 = new ArrayList<Double>(Arrays.asList(0.0, 0.0, 0.0));
        cases.add(case4);

        model.buildNetwork();
        model.trainNetwork(TRAIN_TIMES, cases);

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