using System;
using System.Collections.Generic;

namespace Csharp_Src
{
    internal class Program
    {
        private static List<List<double>> Cases {get; set;}
        private const int TRAIN_TIMES = 1000000;

        public static void Main(string[] args)
        {
            for (int flag = 1; flag <= 3; flag++)
            {
                switch (flag)
                {
                    case 1:
                        Console.WriteLine("Xor Model");
                        runXor();
                        break;
                    case 2:
                        Console.WriteLine("Node Tron Model: And");
                        runNodeTron(true);
                        break;
                    case 3:
                        Console.WriteLine("Node Tron Model: Or");
                        runNodeTron(false);
                        break;
                }
                Console.WriteLine();
            }
        }

        private static void runNodeTron(bool isAnd)
        {
            Network caseExample = new NodeTronModel();
            Cases = isAnd ? new List<List<double>>()
            {
                new List<double>() {1.0, 1.0, 1.0},
                new List<double>() {1.0, 0.0, 0.0},
                new List<double>() {0.0, 1.0, 0.0},
                new List<double>() {0.0, 0.0, 0.0},
            } : 
            new List<List<double>>()
            {
                new List<double>() {1.0, 1.0, 1.0},
                new List<double>() {0.0, 1.0, 1.0},
                new List<double>() {0.0, 0.0, 0.0},
                new List<double>() {1.0, 0.0, 1.0},
            };
            caseExample.BuildNetwork();
            caseExample.TrainNetwork(TRAIN_TIMES, Cases);
            foreach (var datCase in Cases)
            {
                var ans = caseExample.RunNormal(new List<double>() { datCase[0], datCase[1] }, true)[0];
                Console.WriteLine($"{string.Join(",", datCase)} result is {ans}");
            }
        }

        private static void runXor()
        {
            Network caseExample = new XorModel();
            Cases = new List<List<double>>()
            {
                new List<double>() {1.0, 1.0, 0.0},
                new List<double>() {0.0, 1.0, 1.0},
                new List<double>() {0.0, 0.0, 0.0},
                new List<double>() {1.0, 0.0, 1.0},
            };
            caseExample.BuildNetwork();
            caseExample.TrainNetwork(TRAIN_TIMES, Cases);
            foreach (var datCase in Cases)
            {
                var ans = caseExample.RunNormal(new List<double>() { datCase[0], datCase[1] }, true)[0];
                Console.WriteLine($"{string.Join(",", datCase)} result is {ans}");
            }
        }
    }
}
