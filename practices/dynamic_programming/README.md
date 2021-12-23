- **Dynamic programming**, like the **divide-and-conquer** method, solves problems by combining the solutions to subproblems. 
(“Programming” in this context refers to a tabular method, not to writing computer code.)

- **Divide-and-conquer** algorithms partition the problem into disjoint subproblems, solve the subproblems recursively, and then combine their solutions to solve the original problem.

- In contrast, **dynamic programming** applies when the subproblems overlap that is, when subproblems share subsubproblems. in this context, a **divide-and-conquer** algorithm does more work than necessary, repeatedly solving the common subsubproblems. A dynamic-programming algorithm solves each subsubproblem just once and then saves its answer in a table, thereby avoiding the work of recomputing the answer every time it solves each subsubproblem.

- We typically apply dynamic programming to **optimization problems**. Such problems can have many possible solutions. Each solution has a value, and we wish to ﬁnd a solution with the optimal (minimum or maximum) value.

## Developing dynamic programming
When developing a dynamic-programming algorithm, we follow a sequence of four steps:
1. Characterize the structure of an optimal solution.
2. Recursively deﬁne the value of an optimal solution.
3. Compute the value of an optimal solution, typically in a bottom-up fashion.
4. Construct an optimal solution from computed information.

Steps 1–3 form the basis of a dynamic-programming solution to a problem. If we need only the value of an optimal solution, and not the solution itself, then we can omit step 4. When we do perform step 4, we sometimes maintain additional information during step 3 so that we can easily construct an optimal solution.