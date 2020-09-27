//
//  node.swift
//  Swift-Src
//
//  Created by Wesley Webb on 9/23/20.
//

import Foundation

class Node
{
    private var _nodeName:String;
    var nodeName:String {
        get { return self._nodeName; }
        set { self._nodeName = newValue; }
    }
    
    private var _activeFlag:Int;
    var activeFlag:Int {
        get { return self._activeFlag; }
        set { self._activeFlag = newValue; }
    }
    
    private var _weights:[Double];
    var weights:[Double] {
        get { return self._weights; }
        set { self._weights = newValue}
    }
    
    private var _basis:Double;
    var basis:Double {
        get { return self._basis; }
        set { self._basis = newValue; }
    }
    
    private var _frontPipes:[Pipe];
    var frontPipes:[Pipe] {
        get { return self._frontPipes; }
        set { self._frontPipes = newValue; }
    }
    
    private var _backPipes:[Pipe];
    var backPipes:[Pipe] {
        get { return self._backPipes; }
        set { self._backPipes = newValue; }
    }
    
    init(size:Int, newActiveFlag:Int=1, name:String = "", isRandom:Bool=true)
    {
        self._nodeName = name;
        self._activeFlag = newActiveFlag;
        self._weights = [Double]();
        self._basis = isRandom ? Double.random(in: 0...1) : 0.5;
        for _ in 0...size
        {
            let element = isRandom ? Double.random(in: 0...1) : 0.5;
            self._weights.append(element);
        }
        self._frontPipes = [Pipe]();
        self._backPipes = [Pipe]();
    }
    
    func derive(learningRate:Double)
    {
        let tValue = self.calculateT();
        var outterDer = self.deriveActive(paramValue:tValue);
        var paramDer = 0.0;
        
        for pipe in self.frontPipes
        {
            paramDer += pipe.backwardResult;
        }
        
        outterDer *= paramDer;
        
        for index in 0...weights.count
        {
            let innerDer = self.backPipes[index].forwardResult;
            self.weights[index] = (Double)(learningRate * outterDer * innerDer);
        }
        self.basis -= (learningRate * outterDer);
    }
    
    func calculate()
    {
        let tValue = self.calculateT();
        for pipe in self.frontPipes
        {
            pipe.forwardResult += self.active(paramValue: tValue);
        }
    }
    
    private func calculateT() -> Double
    {
        var ans = self.basis;
        for index in 0...self.weights.count
        {
            ans += backPipes[index].forwardResult * weights[index];
        }
        return ans;
    }
    
    private func active(paramValue:Double) -> Double
    {
        switch (self.activeFlag)
        {
            case 1:
                return (Double)(1.0 / (1.0 + exp(-paramValue)));
            default:
                return 0.0;
        }
    }
    
    private func deriveActive(paramValue:Double) -> Double
    {
        switch (self.activeFlag)
        {
            case 1:
                let activeResult = self.active(paramValue:paramValue);
                return (activeResult * (1.0 - activeResult));
            default:
                return 0.0;
        }
    }
    
    func addFrontPipe(pipe:Pipe)
    {
        self.frontPipes.append(pipe);
    }
    
    func addBackPipe(pipe:Pipe)
    {
        self.backPipes.append(pipe);
    }
}
