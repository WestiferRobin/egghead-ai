//
//  state.swift
//  Swift-Src
//
//  Created by Wesley Webb on 9/23/20.
//

import Foundation

class State
{
    private var _stateValue:Double;
    var stateValue:Double {
        get { return self._stateValue; }
        set { self._stateValue = newValue; }
    }
    
    private var _pipeline:Pipe?;
    var pipeline: Pipe? {
        get { return self._pipeline;}
        set { self._pipeline = newValue; }
    }
    
    init()
    {
        self._stateValue = 0.0;
        self._pipeline = nil;
    }
    
    func loadValue(stateValue:Double)
    {
        self._stateValue = stateValue;
    }
    
    func addPipeLine(pipeLine:Pipe)
    {
        self._pipeline = pipeLine;
    }
}
