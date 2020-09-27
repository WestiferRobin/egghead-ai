//
//  pipe.swift
//  Swift-Src
//
//  Created by Wesley Webb on 9/23/20.
//

import Foundation

class Pipe
{
    private var _fowardResult:Double;
    var forwardResult:Double {
        get { return self._fowardResult; }
        set { self._fowardResult = newValue; }
    }
    
    private var _backwardResult:Double;
    var backwardResult:Double {
        get { return self._backwardResult; }
        set { self._backwardResult = newValue; }
    }
    
    init()
    {
        self._fowardResult = 0.0;
        self._backwardResult = 0.0;
    }
}
