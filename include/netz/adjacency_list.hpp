#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

#include <cstddef>
#include <functional>
#include <vector>

namespace netz
{

class AdjacencyList
{
public:

    struct Vertex
    {
        std::vector<std::size_t> neighbors;

        struct Hash
        {
            auto operator()(const Vertex& vertex) const
            {
                // Hash combination from https://stackoverflow.com/a/27216842/605338.
                // Using bit shifts and multiplicative inverse of the golden ratio as a
                // constant (https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine).
                auto hash = vertex.neighbors.size();
                for(const auto& n : vertex.neighbors)
                {
                    hash ^= std::hash<std::size_t>{}(n) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
                }
                return hash;
            }
        };
    };

    struct Edge
    {
        std::size_t source;
        std::size_t target;
        Edge(const std::size_t source, const std::size_t target) : source(source), target(target) { }
        bool operator<=>(const Edge&) const = default;

        struct Hash
        {
            auto operator()(const Edge& edge) const
            {
                const auto h1 = std::hash<std::size_t>{}(edge.source);
                const auto h2 = std::hash<std::size_t>{}(edge.target);
                // Hash combination from https://en.cppreference.com/w/cpp/utility/hash
                return h1 ^ (h2 << 1);
            }
        };
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

    std::vector<std::size_t> neighbors(const std::size_t index)
    {
        return m_vertices[index].neighbors;
    }

    Edge add_edge(const std::size_t source, const std::size_t target)
    {
        m_edges.emplace_back(source, target);
        m_vertices[source].neighbors.push_back(target);
        m_vertices[target].neighbors.push_back(source);
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
                      [source, target](const Edge& edge){ return edge == Edge{source, target} 
                                                              || edge == Edge{target, source}; });
    }

private:
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;
};

} // namespace netz

#endif // ADJACENCY_LIST_HPP
