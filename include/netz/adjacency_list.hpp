#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

#include <cstddef>
#include <vector>

namespace netz
{

class AdjacencyList
{
public:

    struct Vertex {};

    struct Edge
    {
        std::size_t source;
        std::size_t target;
        Edge(const std::size_t source, const std::size_t target) : source(source), target(target) { }
    };

    AdjacencyList() noexcept : m_vertices(), m_edges() { }
    AdjacencyList(const std::size_t numVertices) : m_vertices(numVertices), m_edges() { }

    std::size_t num_vertices() const
    {
        return m_vertices.size();
    }

    std::size_t num_edges() const
    {
        return m_edges.size();
    }

    std::size_t add_vertex()
    {
        m_vertices.push_back(Vertex{});
        return m_vertices.size() - 1;
    }

    Edge add_edge(const std::size_t source, const std::size_t target)
    {
        m_edges.emplace_back(source, target);
        return m_edges.back();
    }

private:
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;
};

} // namespace netz

#endif // ADJACENCY_LIST_HPP
