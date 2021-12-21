// cutting a rod into rods of smaller length in way that maximizes their total value.
/*
Serling Enterprises buys long steel rods and cuts them into shorter rods, 
which it then sells. Each cut is free. The management of Serling Enterprises 
wants to know the best way to cut up the rods.

for i = 1, 2, ... the price "pi" in dollars that Serling Enterprises 
charges for a rod of length i inches. Rod lengths are always an integral number of inches.

Given a rod of length "n" inches and a table of prices "pi" for i = 0, 1, ..., n - 1, 
determine the maximum revenue "rn" obtainable by cutting up the rod and selling the pieces. 

Note that if the price "pn" for a rod of length n is large enough, an optimal solution may require no cutting at all.
length i |  1   2   3   4   5   6   7   8   9   10
price pi |  1   5   8   9   10  17  17  20  24  30

example:
    input:
        n = 4
    putput:
        10
Explain: We see that cutting a 4-inch rod into two 2-inch pieces produces revenue p1 + p1 = 5 + 5 = 10,
which is optimal.

We can cut up a rod of length n in 2^(n - 1) different ways, since we have an independent option of cutting,
or not cutting, at distance i inches from the left end.
*/

#include <iostream>
#include <vector>

int cut_rod(const std::vector<int> &prices, int length);

int main()
{
    std::vector<int> i{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> pi{1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    std::cout << cut_rod(pi, 4) << "\n";

    return 0;
}

int cut_rod(const std::vector<int> &prices, int length)
{
    if (0 == length)
        return 0;

    int max_revenue = INT32_MIN;

    for (int i = 0; i < length; ++i)
        max_revenue = std::max(max_revenue, prices[i] + cut_rod(prices, length - i - 1));

    return max_revenue;
}