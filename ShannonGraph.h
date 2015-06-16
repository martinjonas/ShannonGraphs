#ifndef SHANNONGRAPH_H
#define SHANNONGRAPH_H

#include "GraphNode.h"
#include "TerminalNode.h"
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <iostream>

typedef std::tuple<std::string, GraphNode*, GraphNode*> NodeTriple;

class ShannonGraph
{
private:
    std::vector<GraphNode*> nodes;
    std::map<NodeTriple, GraphNode*> nodeCache;

    GraphNode *root;
    GraphNode *zero;
    GraphNode *one;
public:
    ShannonGraph()
    {
        zero = new TerminalNode("0", NULL, NULL);
        one = new TerminalNode("1", NULL, NULL);
        root = one;
    }

    GraphNode* InsertNode(std::string, GraphNode*, GraphNode*);
    GraphNode* InsertRoot(std::string, GraphNode*, GraphNode*);
    GraphNode* InsertRootGraphNode(GraphNode*);
    void ReplaceZero(ShannonGraph replacement);
    void ReplaceOne(ShannonGraph replacement);
    void Negate();

    GraphNode* getZero() const { return zero; }
    GraphNode* getOne() const { return one; }
    GraphNode* getRoot() const { return root; }

    std::vector<GraphNode*> getNodes() const { return nodes; }

    std::ostream& print(std::ostream& os) const
    {
        zero->print(os);
        one->print(os);
        os << "\"" << root << "\" [peripheries=2]; " << std::endl;

        for (auto node : nodes)
        {
            node->print(os);
        }

        return os;
    }
};

inline std::ostream& operator<< (std::ostream& os, const ShannonGraph& g) {
    os << "digraph G {" << std::endl;
    os <<  "compound = true; " << std::endl;
    g.print(os);
    os << "}";
    return os;
}

#endif // SHANNONGRAPH_H
