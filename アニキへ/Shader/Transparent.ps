
// Global
Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);
	
// Typedef
struct PixelInputType
{
    float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

cbuffer Color : register(b0){
	float4 Color;
}


float4 ps_main(PixelInputType input) : SV_TARGET
{
	float4 output;
	output = shaderTexture.Sample(SampleType, input.tex);

	float4 add = Color;

	float aDf = add.a;
	float aSf = 0;
	float Sf = 1;
	float Df = 1;

	output.rgb = (add.rgb*add.a*Sf+output.rgb*output.a*Df);

	output.a = (add.a*aSf+output.a*aDf);
	return output;
    
}
