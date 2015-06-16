#ifndef LITERALNODE_H
#define LITERALNODE_H

#include "GraphNode.h"

class LiteralNode : public GraphNode
{
public:
    LiteralNode(std::string label, GraphNode *low, GraphNode *high) : GraphNode(label, low, high)
    {

    }

    virtual void print(std::ostream& os) const
    {
         os << "\"" << this << "\"" <<  " [label=\"" << label << "\"];" << std::endl;

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
};

#endif // LITERALNODE_H
