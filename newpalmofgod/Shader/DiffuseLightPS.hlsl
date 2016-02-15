//Pixel Shader InputData
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 col2 : COL2;

};
cbuffer Color : register(b0){
	float4 Color;
};

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

float4 ps_main(PixelInputType input) : SV_Target
{
	float4 output;

	output = saturate(input.col2) * txDiffuse.Sample(samLinear, input.tex);

	return output;
}