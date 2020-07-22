using System;
using System.Collections.Generic;

namespace Csharp_Src
{
    internal class Program
    {
        internal static void Main(string[] args)
        {
            int flag = 2;
            Network caseExample;
            switch (flag)
            {
                case 0:
                    caseExample = new NodeTron();
                    var mrCase = ((NodeTron)caseExample).OrCases;
                    caseExample.BuildNetwork();
                    caseExample.TrainNetwork(100000, mrCase);
                    foreach (var datCase in mrCase)
                    {
                        var ans = caseExample.RunNormal(new List<double>() { datCase[0], datCase[1] }, true)[0];
                        Console.WriteLine($"{string.Join(",", datCase)} result is {ans}");
                    }
                    break;
                case 1:
                    caseExample = new XOR();
                    var asdf = ((XOR)caseExample).XorCases;
                    caseExample.BuildNetwork();
                    caseExample.TrainNetwork(1000000, asdf);
                    foreach (var fff in asdf)
                    {
                        var a = caseExample.RunNormal(new List<double>() { fff[0], fff[1] }, true)[0];
                        Console.WriteLine($"{string.Join(",", fff)} result is {a}");
                    }
                    break;
                case 2:
                    caseExample = new AutoEncoder();
                    var fdsa = ((AutoEncoder)caseExample).AutoCases;
                    caseExample.BuildNetwork();
                    caseExample.TrainNetwork(1000000, fdsa);
                    foreach (var fff in fdsa)
                    {
                        var b = caseExample.RunNormal(fff, true);
                        Console.WriteLine($"[{string.Join(",", fff)}] result is [{string.Join(",", b)}]");
                    }
                    break;
            }
        }
    }
}
