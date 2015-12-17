//Pixel Shader InputData
struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD0;
	float4 col2 : COL2;

};

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

float4 ps_main(PixelInputType input) : SV_Target
{
	PixelInputType output;

	output.color = input.color;
	output.color.w /= 2;

	output.color = saturate(input.col2) * txDiffuse.Sample(samLinear, input.tex);

	return output.color;
}