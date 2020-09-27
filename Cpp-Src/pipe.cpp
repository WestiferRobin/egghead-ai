#include "egghead_comp.hpp"

Pipe::Pipe()
{
    forwardResult = new double(0.0);
    backwardResult = new double(0.0);
}

Pipe::~Pipe()
{
    delete forwardResult;
    delete backwardResult;
}

double Pipe::getForwardResult()
{
    return *forwardResult;
}

void Pipe::setForwardResult(double newForwardResult)
{
    forwardResult = &newForwardResult;
}

double Pipe::getBackwardResult()
{
    return *backwardResult;
}

void Pipe::setBackwardResult(double newBackwardResult)
{
    backwardResult = &newBackwardResult;
}