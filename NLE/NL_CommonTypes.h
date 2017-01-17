#pragma once

#include <cstdint>
#include "NL_LuaCustomTypes.h"
#include "LuaIntf.h"

namespace NLE
{
	struct Size2D
	{
		Size2D() : width(0), height(0) {}
		Size2D(int_fast32_t width, int_fast32_t height) : width(width), height(height) {}

		uint_fast32_t getWidth()
		{
			return width;
		}

		void setWidth(uint_fast32_t w)
		{
			width = w;
		}

		uint_fast32_t getHeight()
		{
			return height;
		}

		void setHeight(uint_fast32_t h)
		{
			height = h;
		}

		uint_fast32_t width;
		uint_fast32_t height;

		static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
		{
			binding.beginClass<Size2D>("Size2D")
				.addConstructor(LUA_ARGS(int_fast32_t, int_fast32_t))
				.addProperty("width", &Size2D::getWidth, &Size2D::setWidth)
				.addProperty("height", &Size2D::getHeight, &Size2D::setHeight)
				.endClass();
		}
	};

	struct Position2D
	{
		Position2D() : x(0), y(0) {}
		Position2D(int_fast32_t x, int_fast32_t y) : x(x), y(y) {}

		uint_fast32_t getX()
		{
			return x;
		}

		void setX(uint_fast32_t _x)
		{
			x = _x;
		}

		uint_fast32_t getY()
		{
			return y;
		}

		void setY(uint_fast32_t _y)
		{
			y = _y;
		}


		int_fast32_t x;
		int_fast32_t y;

		static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
		{
			binding.beginClass<Position2D>("Position2D")
				.addConstructor(LUA_ARGS(int_fast32_t, int_fast32_t))
				.addProperty("x", &Position2D::getX, &Position2D::setX)
				.addProperty("y", &Position2D::getY, &Position2D::setY)
				.endClass();
		}
	};

	struct Offset2D
	{
		Offset2D() : x(0), y(0) {}
		Offset2D(int_fast32_t x, int_fast32_t y) : x(x), y(y) {}

		uint_fast32_t getX()
		{
			return x;
		}

		void setX(uint_fast32_t _x)
		{
			x = _x;
		}

		uint_fast32_t getY()
		{
			return y;
		}

		void setY(uint_fast32_t _y)
		{
			y = _y;
		}


		int_fast32_t x;
		int_fast32_t y;

		static void attachBindings(LuaIntf::CppBindModule<LuaIntf::LuaBinding>& binding)
		{
			binding.beginClass<Offset2D>("Offset2D")
				.addConstructor(LUA_ARGS(int_fast32_t, int_fast32_t))
				.addProperty("x", &Offset2D::getX, &Offset2D::setX)
				.addProperty("y", &Offset2D::getY, &Offset2D::setY)
				.endClass();
		}
	};
}