//
//  nodetron.swift
//  Swift-Src
//
//  Created by Wesley Webb on 9/29/20.
//

import Foundation

class NodeTron : Network
{
    private var _theCases:[[Double]];
    public var theCases:[[Double]] {
        get { return _theCases; }
        set { _theCases = newValue; }
    }
    
    init(isAndFlag:Bool)
    {
        if (isAndFlag)
        {
            self._theCases = [
                [1.0, 1.0, 1.0],
                [1.0, 0.0, 0.0],
                [0.0, 1.0, 0.0],
                [0.0, 0.0, 0.0]
            ];
        }
        else
        {
            self._theCases = [
                [1.0, 1.0, 1.0],
                [1.0, 0.0, 1.0],
                [0.0, 1.0, 1.0],
                [0.0, 0.0, 0.0]
            ];
        }
        super.init();
    }
    
    override func buildNetwork()
    {
        let mainNode:Node = Node(size: 2, newActiveFlag: 1, name: "mainNode");
        let hiddenLayer:Layer = Layer(learningRate:self.learningRate);
        let inputLayer:[State] = [State(), State()]
        let outputLayer:[State] = [State()]
        
        for state in inputLayer
        {
            self.connectStateToNode(sourceState: state, targetNode: mainNode);
        }
        for state in outputLayer
        {
            self.connectNodeToState(sourceNode: mainNode, targetState: state);
        }
        
        hiddenLayer.addNode(targetNode: mainNode)
        
        self.layers.append(hiddenLayer);
        self.outputLayer = outputLayer;
        self.inputLayer = inputLayer;
    }
    
    override func trainNetwork(iterations:Int, cases:[[Double]])
    {
        var tempIterations:Int = iterations;
        while (tempIterations > 0)
        {
            let inst:[Double] = cases[Int.random(in: 0..<cases.count)];
            self.runFoward(newInputs: [inst[0], inst[1]]);
            self.runBackward(newExpected: [inst[2]]);
            tempIterations -= 1;
        }
    }
    
}
