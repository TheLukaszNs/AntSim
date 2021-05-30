/*
 * COPYRIGHT (c) 2021 £UKASZ MYŒLIWIEC (https://github.com/TheLukaszNs)
 *
 * This file is a helper for SFML's vectors math that defines various mathematical functions
 * to help with vector math.
 * It's broadly based on functions used in the Unity Engine.
 *
 * Feel free to copy it, as long as I don't decide otherwise :)
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "random.hpp"

namespace AntMath
{
	constexpr float PI = 3.14159265359f;

	using Random = effolkronium::random_static;
	
	template <typename T>
	T Clamp(T val, T min, T max)
	{
		if (val > max) return max;
		if (val < min) return min;
		return val;
	}
	
	template <typename T>
	float Magnitude(sf::Vector2<T> v)
	{
		return std::sqrt((v.x * v.x) + (v.y * v.y));
	}
	
	template <typename T>
	sf::Vector2<T> NormalizeVector(sf::Vector2<T> v)
	{
		T mag = Magnitude(v);

		if (mag == static_cast<T>(0)) return v;

		return { v.x / mag, v.y / mag };
	}

	template <typename T>
	sf::Vector2<T> ClampMagnitude(sf::Vector2<T> v, T max)
	{
		auto norm = NormalizeVector(v);
		auto clampedMag = Clamp<T>(Magnitude(v), 1, max);
		
		return norm * clampedMag;
	}

	inline sf::Vector2f RandomInUnitCircle()
	{
		float angle = 2.f * PI * Random::get<float>(-1, 1);

		return { std::cos(angle), std::sin(angle) };
	}
}
