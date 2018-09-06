#pragma once

#include <memory>
#include <vector>
#include <array>
#include <bitset>

class Entity;
class Component;

constexpr std::size_t MAX_ENTITY_COMPONENTS = 16;

inline std::size_t GetCompId()
{
	static std::size_t prevId = 0;
	return prevId++;
}
template <typename T>
inline std::size_t GetCompId() noexcept
{
	static std::size_t id = GetCompId();
	return id;
}