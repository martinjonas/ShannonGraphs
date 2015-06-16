#include "ShannonGraphBuilder.h"

#include <sstream>
#include "QuantifiedNode.h"

using namespace z3;
using namespace std;

ShannonGraph ShannonGraphBuilder::BuildGraphFromExpression(const z3::expr &e)
{
    if (e.is_app())
    {
        //cout << "APP: " << e << endl;
        func_decl f = e.decl();
        int num = e.num_args();

        string functionName = f.name().str();
        if (functionName == "and")
        {
            ShannonGraph left = BuildGraphFromExpression(e.arg(0));

            for (int i = 1; i < num; i++)
            {
                ShannonGraph right = BuildGraphFromExpression(e.arg(i));

                left.ReplaceOne(right);
            }
            return left;
        }
        else if (functionName == "or")
        {
            ShannonGraph left = BuildGraphFromExpression(e.arg(0));
            for (int i = 1; i < num; i++)
            {
                ShannonGraph right = BuildGraphFromExpression(e.arg(i));

                left.ReplaceZero(right);
            }
            return left;
        }
        else if (functionName == "not")
        {
            ShannonGraph g = BuildGraphFromExpression(e.arg(0));

            g.Negate();
            return g;
        }
    }
    else if (e.is_quantifier())
    {
        Z3_ast ast = (Z3_ast)e;
        int boundVariables = Z3_get_quantifier_num_bound(*context, ast);

        ShannonGraph bodySg = BuildGraphFromExpression(e.body());

        ShannonGraph sg;

        Quantifier quant = Z3_is_quantifier_forall(*context, ast) ? UNIVERSAL : EXISTENTIAL;

        GraphNode *node = new QuantifiedNode(boundVariables, sg.getZero(), sg.getOne(), quant, bodySg);
        sg.InsertRootGraphNode(node);
        return sg;
    }

    stringstream ss;
    ss << e;

    ShannonGraph sg;
    sg.InsertRoot(ss.str(), sg.getZero(), sg.getOne());
    return sg;
}
