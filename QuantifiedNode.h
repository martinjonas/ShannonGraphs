#ifndef QUANTIFIEDNODE_H
#define QUANTIFIEDNODE_H

#include <string>
#include <sstream>
#include "GraphNode.h"
#include "ShannonGraph.h"

enum Quantifier {EXISTENTIAL, UNIVERSAL};

class QuantifiedNode : public GraphNode
{
private:
    Quantifier quantifier;
    int boundVariables;

    ShannonGraph body;

public:
    QuantifiedNode(int boundVariables, GraphNode *low, GraphNode *high, Quantifier quantifier, ShannonGraph body) :
        GraphNode("quantifier", low, high)
    {
        this->boundVariables = boundVariables;
        this->quantifier = quantifier;
        this->body = body;
    }

    virtual std::string getRootId()
    {
        std::stringstream ss;
        ss << "\"" << body.getRoot() << "\"";
        return ss.str();
    }

    virtual bool isCluster() { return true; }

    virtual void print(std::ostream& os, int boundVars) const
    {
        print(os);
    }

    virtual void print(std::ostream& os) const
    {
        os << "subgraph \"cluster_" << this << "\" {" << std::endl;

        os << "label = \"";
        os << (quantifier == UNIVERSAL ? "forall: " : "exists: ");
        os << boundVariables << "\";" << std::endl;

        body.print(os, boundVariables);

        os << "}" << std::endl;

        os << "\"" << body.getZero() << "\" -> \"" << low << "\" [style=dotted, ltail=\"cluster_" << this << "\"];" << std::endl;
        os << "\"" << body.getOne() << "\" -> \"" << high << "\" [ltail=\"cluster_" << this << "\"];" << std::endl;
    }
};

#endif // QUANTIFIEDNODE_H
