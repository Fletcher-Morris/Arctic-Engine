#pragma once

#include <memory>
#include <vector>
#include <array>
#include <bitset>

class Entity;
class Component;

inline std::size_t GetComponentID()
{
	static std::size_t prevId = 0;
	return prevId++;
}