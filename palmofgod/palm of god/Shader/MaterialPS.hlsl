//Pixel Shader InputData
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;
};
cbuffer LightDirection:register(b2)
{
	float3 _lightDirection;
	float Padding2;
};

cbuffer MaterialBuffer :register(b1)
{
	float4 _diffuse;
	float4 _specular;
	float4 _ambient;
	float4 _emissive;
	float _specularPower;
	float _shininess;
	float _transparencyFactor;
	float Padding;
};


Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

float4 ps_main(PixelInputType input) : SV_Target
{
	float4 output;
	float4 texcolor = txDiffuse.Sample(samLinear, input.tex);
	float3 light;
	float4 specularColor = float4(0, 0, 0, 0);

		float3 lightdir = normalize(_lightDirection);
		float4	lightvec = dot(lightdir,input.normal);
		lightvec.a = 1;
		lightvec = saturate(lightvec);
		
		float4 ambient_col = _ambient;
		float4 diffuse_col =  _diffuse*lightvec;

		light = -_lightDirection;
		float lightintensity = saturate(dot(input.normal,_lightDirection));

		if (lightintensity > 0.0f){
		//	output += diffuse_col*lightintensity;
		//	output = saturate(output);

		float3 reflection = reflect(-lightdir, input.normal);
		specularColor = lightintensity * _specular * pow(saturate(dot(reflection, input.viewDirection)), _specularPower);
		}
		output = ambient_col;
//		output = output * texcolor;
		output = diffuse_col + output;
//	output = saturate(output + specularColor);
	output.a = 1;
	return output;
}