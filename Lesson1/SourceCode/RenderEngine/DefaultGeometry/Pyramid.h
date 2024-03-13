#pragma once

#include "../RenderObject.h"

namespace
{
	struct PosColorVertexPyramid
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_abgr;
	};
};

class Pyramid : public RenderObject
{
public:
	Pyramid();

private:
	inline static const PosColorVertexPyramid s_cubeVertices[] =
	{
		{0.0f,  2.0f, 0.0f, 0xff000000 },
		{1.0f, -1.0f,  -1.0f, 0xff00ff00 },
		{ 1.0f, -1.0f,  1.0f, 0xff0000ff },
		{-1.0f, -1.0f, 1.0f, 0xffff0000 },
		{ -1.0f, -1.0f, -1.0f, 0xffffffff },
	};

	inline static const uint16_t s_cubeTriList[] =
	{
		0, 1, 2, // 0
		0, 2, 3,
		0, 3, 4, // 2
		0, 4, 1,
		1, 2, 4, // 4
		4, 2, 3,

	};
};