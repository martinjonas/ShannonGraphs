#ifndef TERMINALNODE_H
#define TERMINALNODE_H

#include "GraphNode.h"

class TerminalNode : public GraphNode
{
public:
    TerminalNode(std::string label, GraphNode *low, GraphNode *high) : GraphNode(label, low, high)
    {

    }

    virtual void print(std::ostream& os) const
    {
        os << "\"" << this << "\"" <<  " [shape=box,label=\"" << label << "\"];" << std::endl;
    }

    virtual void print(std::ostream &os, int boundVars) const
    {
        return print(os);
    }
};

#endif // TERMINALNODE_H
