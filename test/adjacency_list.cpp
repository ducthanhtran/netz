#include "doctest.h"
#include <netz/adjacency_list.hpp>

TEST_CASE("Adjacency list construction with n vertices")
{
    netz::AdjacencyList g{5};
    REQUIRE(g.num_vertices() == 5);
    REQUIRE(g.num_edges() == 0);
}

TEST_CASE("Adjacency list construction with 0 vertices")
{
    netz::AdjacencyList g{};
    REQUIRE(g.num_vertices() == 0);
    REQUIRE(g.num_edges() == 0);
}

TEST_CASE("Add vertices and return vertex index")
{
    netz::AdjacencyList g{};
    const auto numVertices = 12;
    for(auto i = 0; i < numVertices; ++i)
    {
        REQUIRE(i == g.add_vertex());
    }
    REQUIRE(g.num_vertices() == numVertices);
}

TEST_CASE("Add edges to graph")
{
    netz::AdjacencyList g{4};
    const auto edge = g.add_edge(0, 1);
    REQUIRE(edge.source == 0);
    REQUIRE(edge.target == 1);
    REQUIRE(g.num_edges() == 1);
}
