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
	/// It's just a PI 
	constexpr static float PI = 3.14159265359f;
	
	/// Degrees-to-radians conversion constant 
	constexpr static float Deg2Rad = (2.f * PI) / 360.f;
	
	/// Radians-to-degrees conversion constant
	constexpr static float Rad2Deg = 360.f / (PI * 2.f);

	using Random = effolkronium::random_static;

	template <typename T>
	T Clamp(T val, T min, T max)
	{
		if (val > max) return max;
		if (val < min) return min;
		return val;
	}

	template <typename T>
	float Distance(sf::Vector2<T> v1, sf::Vector2<T> v2)
	{
		return std::sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
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

	template <typename T>
	T Dot(sf::Vector2<T> v1, sf::Vector2<T> v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	template <typename T>
	float Angle(sf::Vector2<T> vec1, sf::Vector2<T> vec2)
	{
		float mag1 = Magnitude(vec1);
		float mag2 = Magnitude(vec2);

		return std::acos(Dot<T>(vec1, vec2) / (mag1 + mag2));
	}

	// Copyright 2021 Kacper Grabiec
	inline sf::Color ConvertColor(float color[4])
	{
		return sf::Color(static_cast<sf::Uint32>(color[0] * 255), static_cast<sf::Uint32>(color[1] * 255), static_cast<sf::Uint32>(color[2] * 255), 255);
	}
}
