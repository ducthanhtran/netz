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
private:
    std::unordered_map<K,V,typename K::Hash> m_map;
};

template<typename V>
class EdgeMap : PropertyMap<AdjacencyList::Edge, V>
{
public:
    EdgeMap(const AdjacencyList& g) { }
};

template<typename V>
class VertexMap : PropertyMap<AdjacencyList::Vertex, V>
{
public:
    VertexMap(const AdjacencyList& g) { }
};

} // namespace netz
#endif // PROPERTY_MAP_HPP
