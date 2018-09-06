#pragma once

#include <memory>
#include <vector>
#include <array>
#include <bitset>

class Entity;
class Component;

constexpr std::size_t MAX_ENTITY_COMPONENTS = 16;
using CompID = std::size_t;

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