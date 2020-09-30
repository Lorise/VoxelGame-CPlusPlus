//vs
float4x4 matViewProj;
float4 viewPosition;

struct VS_INPUT
{
	float4 position : POSITION0;
};

struct PS_OUTPUT
{
	float4 position : POSITION0;
	float3 dir : TEXCOORD0;
};

PS_OUTPUT vs_main( VS_INPUT input )
{
	PS_OUTPUT output;

	output.position = mul( float4( input.position.xyz + viewPosition.xyz, 1 ), matViewProj );
	output.dir = input.position.xyz;

	return output;
}

//ps
samplerCUBE cubeTexture;

struct PS_INTPUT
{
	float3 dir : TEXCOORD0;
};

float4 ps_main( PS_INTPUT input ): COLOR0
{
	float4 color = texCUBE( cubeTexture, input.dir );

	return color;
	//return float4( 1, 1, 0, 0 );
}