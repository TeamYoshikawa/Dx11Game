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

float4 main(PixelInputType input) : SV_TARGET
{

	float frequency = 0.3 * 100;
	float amount = 0.5 / 10;

	input.tex.x += sin(input.tex.y*frequency)*amount;

	float4 final = shaderTexture.Sample(SampleType, input.tex);
	return final;
}