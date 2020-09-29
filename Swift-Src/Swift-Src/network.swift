//
//  network.swift
//  Swift-Src
//
//  Created by Wesley Webb on 9/23/20.
//

import Foundation

// Figure out ambstraction in Swift
class Network
{
    private var _learningRate:Double;
    var learningRate:Double {
        get { return self._learningRate; }
        set { self._learningRate = newValue; }
    }
    
    private var _layers:[Layer];
    var layers:[Layer] {
        get { return self._layers; }
        set { self._layers = newValue; }
    }
    
    private var _inputLayer:[State]?;
    var inputLayer:[State]? {
        get { return self._inputLayer; }
        set { self._inputLayer = newValue; }
    }
    
    private var _outputLayer:[State]?;
    var outputLayer:[State]? {
        get { return self._outputLayer; }
        set { self._outputLayer = newValue; }
    }
    
    init(newLayers:[Layer] = [Layer](), newLearningRate:Double = 0.01)
    {
        self._learningRate = newLearningRate;
        self._layers = newLayers;
        self._inputLayer = nil;
        self._outputLayer = nil;
    }
    
    func buildNetwork()
    {
        print("asdf");
    }
    
    func trainNetwork(iterations:Int, cases:[[Double]])
    {
        print("fdsa");
    }
    
    func connnectPipeline(sourceNode:Node, targetNode:Node)
    {
        let newPipe:Pipe = Pipe();
        sourceNode.addFrontPipe(pipe: newPipe);
        targetNode.addBackPipe(pipe: newPipe);
    }
    
    func connectStateToNode(sourceState:State, targetNode:Node)
    {
        if (sourceState.pipeline == nil)
        {
            let pipeline:Pipe = Pipe();
            sourceState.addPipeLine(pipeLine: pipeline);
            targetNode.addBackPipe(pipe: pipeline);
        }
        else
        {
            targetNode.addBackPipe(pipe: sourceState.pipeline!);
        }
    }
    
    func connectNodeToState(sourceNode:Node, targetState:State)
    {
        if (targetState.pipeline == nil)
        {
            let pipeline:Pipe = Pipe();
            sourceNode.addFrontPipe(pipe: pipeline);
            targetState.addPipeLine(pipeLine: pipeline);
        }
        else
        {
            sourceNode.addFrontPipe(pipe: targetState.pipeline!);
        }
    }
    
    func runNormal(newInputs:[Double], returnRaw:Bool = false) -> [Double]
    {
        self.foward(newInputs: newInputs);
        var ans:[Double] = [Double]();
        
        for outputState in self.outputLayer!
        {
            if (returnRaw)
            {
                ans.append(outputState.stateValue);
            }
            else
            {
                ans.append(0.5 <= outputState.stateValue ? 1.0 : 0.0);
            }
        }
        
        return ans;
    }
    
    func runFoward(newInputs:[Double])
    {
        self.foward(newInputs: newInputs)
    }
    
    private func foward(newInputs:[Double])
    {
        for index in 0..<newInputs.count
        {
            self.inputLayer![index].loadValue(stateValue: newInputs[index]);
        }
        for state in self.inputLayer!
        {
            state.pipeline?.forwardResult = state.stateValue;
        }
        for layer in self.layers
        {
            layer.forward();
        }
        for state in self.outputLayer!
        {
            state.loadValue(stateValue: state.pipeline!.forwardResult)
        }
    }
    
    func runBackward(newExpected:[Double])
    {
        self.backward(newExpected: newExpected);
    }
    
    private func backward(newExpected:[Double])
    {
        let constant:Double = 1.0 / Double(newExpected.count);
        for index in 0..<newExpected.count
        {
            let paramValue:Double = (-1.0 * constant * (newExpected[index] - self.outputLayer![index].stateValue));
            self.outputLayer?[index].pipeline?.backwardResult = paramValue;
        }
        
        var indexLayer:Int = self.layers.count - 1;
        while (indexLayer >= 0)
        {
            self.layers[indexLayer].backward();
            indexLayer -= 1;
        }
    }
}
