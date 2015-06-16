#ifndef LITERALNODE_H
#define LITERALNODE_H

#include "GraphNode.h"
#include <sstream>

using namespace std;

class LiteralNode : public GraphNode
{
public:
    LiteralNode(std::string label, GraphNode *low, GraphNode *high) : GraphNode(label, low, high)
    {

    }

    virtual void print(std::ostream& os, int boundVars) const
    {
         if (boundVars > 0)
         {
             bool dependsOnQuantifier = false;
             stringstream ss;
             for (int i = 0; i < boundVars; i++)
             {
                ss.str("");
                ss << "(:var " << i << ")";
                std::string str = ss.str();
                if (label.find(str) != string::npos)
                {
                    dependsOnQuantifier = true;
                    break;
                }
             }

             if (dependsOnQuantifier)
             {
                os << "\"" << this << "\"" <<  " [label=\"" << label << "\"];" << std::endl;
             }
             else
             {
                os << "\"" << this << "\"" <<  " [label=\"" << label << "\",color=blue];" << std::endl;
             }
         }

         if (low != NULL)
         {
             if (low->isCluster())
             {
                os << "\"" << this << "\" -> " << low->getRootId() << " [style=dotted, lhead=\"cluster_" << low << "\"];" << std::endl;
             }
             else
             {
                 os << "\"" << this << "\" -> " << low->getRootId() << " [style=dotted];" << std::endl;
             }
         }

         if (high != NULL)
         {
             if (high->isCluster())
             {
                os << "\"" << this << "\" -> " << high->getRootId() << " [lhead=\"cluster_" << high << "\"];" << std::endl;
             }
             else
             {
                 os << "\"" << this << "\" -> " << high->getRootId() << ";" << std::endl;
             }
         }
    }

    virtual void print(std::ostream& os) const
    {
         print(os, 0);
    }
};

#endif // LITERALNODE_H
