#include "ShannonGraph.h"
#include "LiteralNode.h"
#include <sstream>
#include "algorithm"

using namespace std;

typedef std::map<NodeTriple, GraphNode*> CacheType;

GraphNode* ShannonGraph::InsertNode(string label, GraphNode* low, GraphNode* high)
{
    //CacheType::const_iterator cacheNode = nodeCache.find(tuple<string, GraphNode*, GraphNode*>(label, low, high));

    //if (cacheNode == nodeCache.end())
    //{
        GraphNode *node = new LiteralNode(label, low, high);
        nodes.push_back(node);
        return node;
    //}
    //else
    //{
    //    return (*cacheNode).second;
    //}
}

GraphNode* ShannonGraph::InsertRoot(string label, GraphNode *low, GraphNode *high)
{
    root = InsertNode(label, low, high);
    return root;
}

GraphNode* ShannonGraph::InsertRootGraphNode(GraphNode *node)
{
    root = node;
    nodes.push_back(node);
    return node;
}

void ShannonGraph::Negate()
{
  GraphNode *temp = zero;
  zero = one;
  one = temp;
}

void ShannonGraph::ReplaceZero(ShannonGraph replacement)
{
    for (auto node : nodes)
    {
        if (node->getLow() != NULL && node->getLow() == zero)
        {
            node->setLow(replacement.getRoot());
        }
        else if (node->getHigh() != NULL && node->getHigh() == zero)
        {
            node->setHigh(replacement.getRoot());
        }
        if (node->getLow() != NULL && node->getLow() == one)
        {
            node->setLow(replacement.one);
        }
        else if (node->getHigh() != NULL && node->getHigh() == one)
        {
            node->setHigh(replacement.one);
        }
    }

    nodes.insert(nodes.end(), replacement.nodes.begin(), replacement.nodes.end());

    delete zero;
    delete one;

    one = replacement.one;
    zero = replacement.zero;

}

void ShannonGraph::ReplaceOne(ShannonGraph replacement)
{
    Negate();
    replacement.Negate();
    ReplaceZero(replacement);
    Negate();
}
