#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <string>
#include <iostream>
#include <sstream>

class GraphNode
{
protected:
    std::string label;
    GraphNode *low;
    GraphNode *high;

public:
    GraphNode(std::string label, GraphNode *low, GraphNode *high) : label(label), low(low), high(high)
    {

    }

    std::string getLabel() { return label; }
    virtual std::string getRootId()
    {
        std::stringstream ss;
        ss << "\"" << this << "\"";
        return ss.str();
    }

    virtual bool isCluster() { return false; }

    GraphNode* getLow() { return low; }
    GraphNode* getHigh() { return high; }

    void setLow(GraphNode* newValue) { low = newValue; }
    void setHigh(GraphNode* newValue) { high = newValue; }

    virtual void print(std::ostream& os) const = 0;
};

inline std::ostream& operator<< (std::ostream& out, const GraphNode& node) {
    node.print(out);
    return out;
}

#endif // GRAPHNODE_H
