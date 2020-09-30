#pragma once

struct CUBE
{
	enum Type
	{
		AIR = 0,
		DIRT,
		GRASS,
		STONE,
		COBBLESTONE,
		BEDROCK,
		END
	};

	bool m_bCube;
	Type m_typeCube;
};