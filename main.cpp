#include <iostream>
#include "ShannonGraphBuilder.h"
#include "ShannonGraph.h"
#include "z3++.h"


using namespace std;
using namespace z3;

void run(char* fileName)
{
    context ctx;

    Z3_ast ast = Z3_parse_smtlib2_file(ctx, fileName, 0, 0, 0, 0, 0, 0);
    expr expression = to_expr(ctx, ast);

    params simplifyParams(ctx);
    simplifyParams.set("flat", true);
    simplifyParams.set(":blast_distinct", true);

    goal g(ctx);
    g.add(expression);
    tactic simplifyTactic =  with(tactic(ctx, "simplify"), simplifyParams);

    apply_result result = simplifyTactic(g);
    goal simplified = result[0];
    expr simplifiedExpr = simplified.as_expr();

    ShannonGraphBuilder builder(ctx);
    ShannonGraph graph = builder.BuildGraphFromExpression(simplifiedExpr);

    cout << graph;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    cout << "Expected file name";
    return 0;
  }

  run(argv[1]);

  return 0;
}

