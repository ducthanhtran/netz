#include "doctest.h"
#include <netz/property_map.hpp>

TEST_CASE("Property map construction")
{
    netz::AdjacencyList g{5};
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);

    netz::EdgeMap<int> edgeMap{g};
    netz::VertexMap<int> vertexMap{g};

    REQUIRE(edgeMap.size() == 3);
    REQUIRE(vertexMap.size() == 5);
}
