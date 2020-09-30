#pragma once

class BasicEffect
{
public:
	BasicEffect();
	virtual ~BasicEffect();

	virtual void Init() = 0;
	virtual void Cleanup();

	virtual void Enable();
	virtual void Disable();

protected:
	void LoadVertexShader( std::string filename );
	void LoadPixelShader( std::string filename );

	LPD3DXCONSTANTTABLE m_vertexShaderConstantTable;
	LPDIRECT3DVERTEXSHADER9 m_vertexShader;

	LPD3DXCONSTANTTABLE m_pixelShaderConstantTable;
	LPDIRECT3DPIXELSHADER9 m_pixelShader;
};