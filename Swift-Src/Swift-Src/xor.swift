//
//  xor.swift
//  Swift-Src
//
//  Created by Wesley Webb on 9/29/20.
//

import Foundation

class Xor : Network
{
    var xorCases:[[Double]];
    
    init()
    {
        self.xorCases = [
            [1.0, 1.0, 0.0],
            [0.0, 1.0, 1.0],
            [1.0, 0.0, 1.0],
            [0.0, 0.0, 0.0]
        ];
        super.init();
    }
    
    override func buildNetwork()
    {
        print("Starting to build XOR Model");
        self.inputLayer = [State(), State()];
        self.outputLayer = [State()];
        
        let hiddenLayer1:Layer = Layer(learningRate: self.learningRate, name:"layer1");
        hiddenLayer1.addNode(targetNode: Node(size: 2, newActiveFlag: 1, name: "n11"));
        hiddenLayer1.addNode(targetNode: Node(size: 2, newActiveFlag: 1, name:"n12"));
        
        let hiddenLayer2:Layer = Layer(learningRate: self.learningRate, name:"layer2");
        hiddenLayer2.addNode(targetNode: Node(size: 2, newActiveFlag: 1, name: "n21"));
        
        for state in self.inputLayer!
        {
            for node in hiddenLayer1.layerNodes!
            {
                self.connectStateToNode(sourceState: state, targetNode: node);
            }
        }
        
        for node1 in hiddenLayer1.layerNodes!
        {
            for node2 in hiddenLayer2.layerNodes!
            {
                self.connnectPipeline(sourceNode: node1, targetNode: node2);
            }
        }
        
        self.connectNodeToState(sourceNode: hiddenLayer2.layerNodes![0], targetState: self.outputLayer![0]);
        
        self.layers.append(hiddenLayer1);
        self.layers.append(hiddenLayer2);
    }
    
    override func trainNetwork(iterations:Int, cases:[[Double]])
    {
        var tempIterations:Int = iterations;
        while (tempIterations > 0)
        {
            let inst:[Double] = cases[Int.random(in: 0...cases.count - 1)];
            self.runFoward(newInputs: [inst[0], inst[1]]);
            self.runBackward(newExpected: [inst[2]]);
            tempIterations -= 1;
        }
    }
}
