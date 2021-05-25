#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

#include <cstddef>
#include <vector>

namespace netz
{

struct OutEdge
{
    std::size_t target;
};

class AdjacencyList
{
public:
    AdjacencyList() noexcept { }
    AdjacencyList(const std::size_t numVertices) : m_adjList(numVertices) { }

    std::size_t num_vertices() const
    {
        return m_adjList.size();
    }

private:
    std::vector<std::vector<OutEdge>> m_adjList;
};

} // namespace netz

#endif // ADJACENCY_LIST_HPP
