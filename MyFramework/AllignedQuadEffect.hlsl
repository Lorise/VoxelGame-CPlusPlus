//vs

struct VS_INPUT
{
	float4 position : POSITION0;
	float3 normal : NORMAL0;
	float2 texCoord : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 position : POSITION0;
	float4 diffuse : COLOR0;
	float2 texCoord : TEXCOORD0;
};

PS_OUTPUT vs_main( VS_INPUT input )
{
	PS_OUTPUT output;

	output.position = float4( input.position.xy, 0, 1 );

	output.diffuse = float4( 1, 1, 1, 0 );

	output.texCoord = input.texCoord;

	return output;
}

//ps
sampler2D myTexture;

static const float4 sampleGausianBlur[ 49 ] =
{
	float4( -3, -3, 0, 0.00000067 ), float4( -2, -3, 0, 0.00002292 ), float4( -1, -3, 0, 0.00019117 ), float4( 0, -3, 0, 0.00038771 ), float4( 1, -3, 0, 0.00019117 ), float4( 2, -3, 0, 0.00002292 ), float4( 3, -3, 0, 0.00000067 ),
	float4( -3, -2, 0, 0.00002292 ), float4( -2, -2, 0, 0.00078634 ), float4( -1, -2, 0, 0.00655965 ), float4( 0, -2, 0, 0.01330373 ), float4( 1, -2, 0, 0.00655965 ), float4( 2, -2, 0, 0.00078633 ), float4( 3, -2, 0, 0.00002292 ),
	float4( -3, -1, 0, 0.00019117 ), float4( -2, -1, 0, 0.00655965 ), float4( -1, -1, 0, 0.05472157 ), float4( 0, -1, 0, 0.11098164 ), float4( 1, -1, 0, 0.05472157 ), float4( 2, -1, 0, 0.00655965 ), float4( 3, -1, 0, 0.00019117 ),
	float4( -3,  0, 0, 0.00038771 ), float4( -2,  0, 0, 0.01330373 ), float4( -1,  0, 0, 0.11098164 ), float4( 0,  0, 0, 0.22508352 ), float4( 1,  0, 0, 0.11098164 ), float4( 2,  0, 0, 0.01330373 ), float4( 3,  0, 0, 0.00038771 ),
	float4( -3,  1, 0, 0.00019117 ), float4( -2,  1, 0, 0.00655965 ), float4( -1,  1, 0, 0.05472157 ), float4( 0,  1, 0, 0.11098164 ), float4( 1,  1, 0, 0.05472157 ), float4( 2,  1, 0, 0.00655965 ), float4( 3,  1, 0, 0.00019117 ),
	float4( -3,  2, 0, 0.00002292 ), float4( -2,  2, 0, 0.00078633 ), float4( -1,  2, 0, 0.00655965 ), float4( 0,  2, 0, 0.01330373 ), float4( 1,  2, 0, 0.00655965 ), float4( 2,  2, 0, 0.00078633 ), float4( 3,  2, 0, 0.00002292 ),
	float4( -3,  3, 0, 0.00000067 ), float4( -2,  3, 0, 0.00002292 ), float4( -1,  3, 0, 0.00019117 ), float4( 0,  3, 0, 0.00038771 ), float4( 1,  3, 0, 0.00019117 ), float4( 2,  3, 0, 0.00002292 ), float4( 3,  3, 0, 0.00000067 )
};

static const float4 sampleNegative[ 16 ] =
{
	float4( -2, -2, 0, -1 ), float4( -1, -2, 0,  0 ), float4( 1, -2, 0,  0 ), float4( 2, -2, 0, 1 ),
	float4( -2, -1, 0,  0 ), float4( -1, -1, 0, -1 ), float4( 1, -1, 0,  0 ), float4( 2, -1, 0, 1 ),
	float4( -2,  1, 0,  0 ), float4( -1,  1, 0,  0 ), float4( 1,  1, 0, -1 ), float4( 2,  1, 0, 1 ),
	float4( -2,  2, 0,  0 ), float4( -1,  2, 0,  0 ), float4( 1,  2, 0,  0 ), float4( 2,  2, 0, 1 )
};


struct PS_INPUT
{
	float4 diffuse : COLOR0;
	float2 texCoord : TEXCOORD0;
};

float4 ps_main( PS_INPUT input ): COLOR0
{
	/*float4 color = 0;

	for( int i = 0; i < 49; i++ )
	{
		float2 offset = float2( sampleGausianBlur[ i ].x * 0.001, sampleGausianBlur[ i ].y * 0.001 );

		color += sampleGausianBlur[ i ].w * tex2D( myTexture, input.texCoord + offset );
	}*/

	return tex2D( myTexture, input.texCoord );
	//return color * input.diffuse;
}