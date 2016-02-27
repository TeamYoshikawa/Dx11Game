

// Global //
cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer LightBuffer : register(b1)
{
	float3 Light;
	float Padding;
};


//Vertex Shader InputData
struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL0;

};

//Pixel Shader InputData
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 col2 : COL2;

};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType vs_main(VertexInputType input)
{

	PixelInputType output;
	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.tex = input.tex;


	float3 normal;
	normal = mul(input.normal, (float3x3)worldMatrix);
	normal = normalize(normal);


	float3 light = normalize(Light.xyz);

	// Store the input color for the pixel shader to use.
	output.col2 = dot(normal, light);
	output.col2.a = 1.0f;

	return output;
}

