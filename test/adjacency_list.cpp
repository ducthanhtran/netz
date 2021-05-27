#include "doctest.h"
#include <netz/adjacency_list.hpp>

TEST_CASE("Adjacency list construction with n vertices")
{
    netz::AdjacencyList g(5);
    REQUIRE(g.num_vertices() == 5);
}

TEST_CASE("Adjacecny list construction with 0 vertices")
{
	netz::AdjacencyList g(0);
	REQUIRE(g.num_vertices() == 0);
}
