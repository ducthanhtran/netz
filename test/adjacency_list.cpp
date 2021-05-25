#include "doctest.h"
#include <netz/adjacency_list.hpp>

TEST_CASE("Adjacency list construction with n vertices")
{
    netz::AdjacencyList g(5);
    REQUIRE(g.num_vertices() == 5);
}
