#ifndef SHANNONGRAPHBUILDER_H
#define SHANNONGRAPHBUILDER_H

#include "ShannonGraph.h"
#include "z3++.h"

class ShannonGraphBuilder
{
private:
    //ShannonGraph sg;
    z3::context *context;

public:
    ShannonGraphBuilder(z3::context &ctx)
    {
        context = &ctx;
    }

    ShannonGraph BuildGraphFromExpression(const z3::expr&);

    //ShannonGraph GetGraph() { return sg; }
};

#endif // SHANNONGRAPHBUILDER_H
