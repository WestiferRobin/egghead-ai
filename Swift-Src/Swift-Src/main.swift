//
//  main.swift
//  Swift-Src
//
//  Created by Wesley Webb on 9/23/20.
//

import Foundation


func xorRun()
{
    let caseExample:Xor = Xor();
    let cases = caseExample.xorCases;
    caseExample.buildNetwork();
    caseExample.trainNetwork(iterations: 500000, cases: cases);
    for inst in cases
    {
        let ans:Double = caseExample.runNormal(newInputs: [inst[0], inst[1]], returnRaw: true)[0];
        print(String("[\(inst[0]), \(inst[1]), \(inst[2])]") + " Result is " + String(ans));
    }
}

func andRun()
{
    let caseExample:NodeTron = NodeTron(isAndFlag: true);
    let cases = caseExample.theCases;
    caseExample.buildNetwork();
    caseExample.trainNetwork(iterations: 500000, cases: cases);
    for inst in cases
    {
        let ans:Double = caseExample.runNormal(newInputs: [inst[0], inst[1]], returnRaw: true)[0];
        print(String("[\(inst[0]), \(inst[1]), \(inst[2])]") + " Result is " + String(ans));
    }
}

func orRun()
{
    let caseExample:NodeTron = NodeTron(isAndFlag: false);
    let cases = caseExample.theCases;
    caseExample.buildNetwork();
    caseExample.trainNetwork(iterations: 500000, cases: cases);
    for inst in cases
    {
        let ans:Double = caseExample.runNormal(newInputs: [inst[0], inst[1]], returnRaw: true)[0];
        print(String("[\(inst[0]), \(inst[1]), \(inst[2])]") + " Result is " + String(ans));
    }
}

xorRun();
andRun();
orRun();
