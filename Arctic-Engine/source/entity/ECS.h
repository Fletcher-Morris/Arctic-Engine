#pragma once

#include <memory>
#include <vector>
#include <array>
#include <bitset>

class EcsEntity;
class EcsComponent;

using CompID = std::size_t;
constexpr CompID MAX_ENTITY_COMPONENTS = 16;
using CompBits = std::bitset<MAX_ENTITY_COMPONENTS>;
using CompArray = std::array<EcsComponent*, MAX_ENTITY_COMPONENTS>;

inline CompID GetCompID()
{
	static CompID prevId = 0;
	return prevId++;
}
template <typename T>
inline CompID GetCompID() noexcept
{
	static CompID id = GetCompID();
	return id;
}

class EcsComponent
{

};