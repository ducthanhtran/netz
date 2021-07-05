#include "doctest.h"
#include <netz/adjacency_list.hpp>

TEST_CASE("Adjacency list construction with n initial vertices")
{
    netz::AdjacencyList g{5};
    REQUIRE(g.num_vertices() == 5);
    REQUIRE(g.num_edges() == 0);
}

TEST_CASE("Adjacency list construction with zero initial vertices")
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
        REQUIRE(g.neighbors(i).size() == 0);
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
    
    SUBCASE("Neighbor indices")
    {
        for (auto index = 0u; index < 2u; ++index)
        {
            const auto neighbors = g.neighbors(index);
            REQUIRE(neighbors.size() == 1);
            REQUIRE(neighbors.front() == (1 - index));
        }
    }
}

TEST_CASE("Remove undirected edge")
{
    netz::AdjacencyList g{3};
    const auto edge = g.add_edge(1, 2);

    SUBCASE("Undirected case A")
    {
        g.remove_edge(edge.source, edge.target);
        REQUIRE(g.num_edges() == 0);
    }

    SUBCASE("Undirected case B")
    {
        g.remove_edge(edge.target, edge.source);
        REQUIRE(g.num_edges() == 0);
    }
}

TEST_CASE("Remove vertex")
{
    netz::AdjacencyList g{4};
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(0, 3);
    g.remove_vertex(0);

    for(auto i = 1u; i < 4u; ++i)
    {
        REQUIRE(g.neighbors(i).size() == 0);
    }

    REQUIRE(g.num_vertices() == 3);
    REQUIRE(g.num_edges() == 0);
}
