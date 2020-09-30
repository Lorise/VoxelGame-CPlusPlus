//VS
float4x4 matViewProjection;
float4 chunkPosition;

struct VS_INPUT
{
	float4 Position : POSITION0;
	float2 TexCoord : TEXCOORD0;
	float3 Normal : NORMAL0;
};

struct VS_OUTPUT
{
	float4 Position : POSITION0;
	float2 TexCoord : TEXCOORD0;
	float3 Normal : TEXCOORD1;
};

VS_OUTPUT vs_main( VS_INPUT Input )
{
	VS_OUTPUT Output;

	Output.Position = mul( Input.Position + chunkPosition, matViewProjection );

	Output.TexCoord = Input.TexCoord;

	Output.Normal = Input.Normal;

	return Output;
}

//PS
float4 lightDir;
sampler2D diffuseTexture;
sampler2D normalTexture;

struct PS_INPUT
{
	float2 TexCoord : TEXCOORD0;
	float3 Normal : TEXCOORD1;
};

float4 ps_main( PS_INPUT Input ): COLOR0
{
	float4 diffuseColor = tex2D( diffuseTexture, Input.TexCoord );

	float lightPerVertex = dot( Input.Normal, float3( lightDir.x, -lightDir.y, -lightDir.z ) );
	if( lightPerVertex < 0.3 )
		lightPerVertex = 0.3;

	float lightPerPixel = dot( tex2D( normalTexture, Input.TexCoord ).xyz, lightDir.xyz );
	if( lightPerPixel < 0.3 )
		lightPerPixel = 0.3;

	float light = lightPerVertex * lightPerPixel;

	return diffuseColor * light;
}