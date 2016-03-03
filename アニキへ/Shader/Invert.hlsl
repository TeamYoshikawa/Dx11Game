Texture2D shaderTexture;
SamplerState SampleType;

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : COLOR;
};

cbuffer Color : register(b0){
	float4 Color;
}

float4 ps_main(PixelInputType input) : SV_TARGET
{
	float4 color = shaderTexture.Sample(SampleType, input.tex);
	float4 invert = 1 - color;

	invert.a = color.a;
	invert.rgb *= invert.a;
	return invert;
}