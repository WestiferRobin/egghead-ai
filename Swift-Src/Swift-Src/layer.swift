//
//  layer.swift
//  Swift-Src
//
//  Created by Wesley Webb on 9/24/20.
//

import Foundation

class Layer
{
    private var _learningRate:Double;
    var learningRate:Double {
        get { return self._learningRate; }
        set { self._learningRate = newValue; }
    }
    
    private var _layerName:String;
    var layerName:String {
        get { return self._layerName; }
        set { self._layerName = newValue; }
    }
    
    private var _layerNodes:[Node]?;
    var layerNodes:[Node]? {
        get { return self._layerNodes; }
        set { self._layerNodes = newValue; }
    }
    
    init(learningRate:Double, name:String = "")
    {
        self._learningRate = learningRate;
        self._layerName = name;
        self._layerNodes = [Node]();
    }
    
    func forward()
    {
        for node in self.layerNodes!
        {
            node.calculate();
        }
    }
    
    func backward()
    {
        for node in self.layerNodes!
        {
            node.derive(learningRate: self.learningRate);
        }
    }
    
    func addNode(targetNode:Node)
    {
        self.layerNodes?.append(targetNode);
    }
    
    func toString() -> String
    {
        return self.layerName;
    }
}
