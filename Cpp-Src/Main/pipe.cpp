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