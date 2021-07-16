#ifndef PROPERTY_MAP_HPP
#define PROPERTY_MAP_HPP

#include "adjacency_list.hpp"
#include <unordered_map>

namespace netz
{

template<typename K, typename V>
class PropertyMap
{
public:
    auto size() const
    {
        return m_map.size();
    }

protected:
    std::unordered_map<K,V,typename K::Hash> m_map;
};

template<typename V>
class EdgeMap : public PropertyMap<AdjacencyList::Edge, V>
{
public:
    EdgeMap(const AdjacencyList& g) 
    {
        for(const auto edge : g.m_edges)
        {
            this->m_map.try_emplace(edge, V{});
        }
    }
};

template<typename V>
class VertexMap : public PropertyMap<AdjacencyList::Vertex, V>
{
public:
    VertexMap(const AdjacencyList& g)
    {
        for(const auto vertex : g.m_vertices)
        {
            this->m_map.try_emplace(vertex, V{});
        }
    }
};

} // namespace netz
#endif // PROPERTY_MAP_HPP
