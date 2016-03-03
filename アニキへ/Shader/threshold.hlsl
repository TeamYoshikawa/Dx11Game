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

	float4 color = shaderTexture.Sample(SampleType, input.tex.xy);
	float4 gray = color.r * 0.299 + color.g * 0.587 + color.b * 0.114;
	color.r = step(color.r,gray);
	//color.g = step(color.g,gray);
	//color.b = step(color.b,gray);
	return color;
}