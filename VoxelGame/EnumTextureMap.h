#pragma once

const static std::string DiffuseTextureMap[]
{
	"notexture.png",
	"dirt.png",
	"grass.png",
	"grass_side.png",
	"stone.png",
	"cobblestone.png",
	"bedrock.png"
};


const static std::string NormalTextureMap[]
{
	"notexture.png",
	"dirt_normal.png",
	"grass_normal.png",
	"grass_side_normal.png",
	"stone_normal.png",
	"cobblestone_normal.png",
	"bedrock_normal.png"
};

enum TEXTURE_MAP
{
	NO_TEXTURE = 0,
	DIRT,
	GRASS,
	GRASS_SIDE,
	STONE,
	COBBLESTONE,
	BEDROCK,
	END
};