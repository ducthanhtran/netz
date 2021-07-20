#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

#include <cstddef>
#include <vector>

namespace netz
{

class AdjacencyList
{
public:

    struct Vertex
    {
        std::size_t id;
        std::vector<std::size_t> neighbors;

        Vertex(const std::size_t id) : id(id) { }
        bool operator==(const Vertex&) const = default;

        struct Hash
        {
            auto operator()(const Vertex& vertex) const
            {
                auto seed = vertex.neighbors.size();
                for(const auto& n : vertex.neighbors)
                {
                    seed ^= std::hash<std::size_t>{}(n) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
                seed ^= std::hash<std::size_t>{}(vertex.id) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                return seed;
            }
        };
    };

    struct Edge
    {
        std::size_t id;
        std::size_t source;
        std::size_t target;

        Edge(const std::size_t id, const std::size_t source, const std::size_t target) : id(id), source(source), target(target) { }
        bool adjacentTo(const std::size_t endpointA, const std::size_t endpointB) const
        {
            return (endpointA == source && endpointB == target) || (endpointA == target && endpointB == source);
        }
        bool operator==(const Edge&) const = default;

        struct Hash
        {
            auto operator()(const Edge& edge) const
            {
                const auto h1 = std::hash<std::size_t>{}(edge.id);
                const auto h2 = std::hash<std::size_t>{}(edge.source);
                const auto h3 = std::hash<std::size_t>{}(edge.target);
                return h1 ^ (h2 << 1) ^ (h3 << 2);
            }
        };
    };

    AdjacencyList() noexcept : m_vertices(), m_edges() { }
    AdjacencyList(const std::size_t numVertices) : m_edges()
    {
        for(auto index = 0u; index < numVertices; ++index)
        {
            m_vertices.emplace_back(Vertex{num_vertices()});
        }
    }

    std::size_t num_vertices() const
    {
        return m_vertices.size();
    }

    std::size_t num_edges() const
    {
        return m_edges.size();
    }

    Vertex add_vertex()
    {
        m_vertices.emplace_back(Vertex{num_vertices()});
        return m_vertices.back();
    }

    std::vector<std::size_t> neighbors(const std::size_t index)
    {
        return m_vertices[index].neighbors;
    }

    Edge add_edge(const std::size_t source, const std::size_t target)
    {
        m_edges.emplace_back(num_edges(), source, target);
        m_vertices[source].neighbors.emplace_back(target);
        m_vertices[target].neighbors.emplace_back(source);
        return m_edges.back();
    }

    void remove_vertex(const std::size_t index)
    {
        for(auto neighbor : neighbors(index))
        {
            std::erase(m_vertices[neighbor].neighbors, index);
            remove_edge(index, neighbor);
        }
        m_vertices.erase(m_vertices.cbegin() + index);
    }

    void remove_edge(const std::size_t source, const std::size_t target)
    {
        std::erase_if(m_edges,
                      [source, target](const Edge& edge){ return edge.adjacentTo(source, target); });
    }

private:
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;
};

} // namespace netz
#endif // ADJACENCY_LIST_HPP
