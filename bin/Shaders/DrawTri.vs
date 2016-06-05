
cbuffer MatrixBuffer : register(b0)
{
	matrix ModelToWorldMatrix;
	matrix WorldToViewMatrix;
	matrix ProjectionMatrix;
};

struct VSIn
{
	float3 Pos : POSITION;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float2 TexCoord : TEX;
};

struct PSIn
{
	float4 Pos  : SV_Position;
	float3 Normal : NORMAL;
	float2 TexCoord : TEX;
	float4 WorldPos : WorldPos;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
};

//-----------------------------------------------------------------------------------------
// VertexShader: VSScene
//-----------------------------------------------------------------------------------------
PSIn VS_main(VSIn input)
{
	PSIn output = (PSIn)0;
	
	// model-to-view
	matrix MV = mul(WorldToViewMatrix, ModelToWorldMatrix);
	// model-to-projection
	matrix MVP = mul(ProjectionMatrix, MV);
	
	output.Pos = mul(MVP, float4(input.Pos, 1));
	output.Normal = mul(ModelToWorldMatrix, input.Normal);
	output.Tangent = mul(ModelToWorldMatrix, input.Tangent);
	output.Binormal = mul(ModelToWorldMatrix, input.Binormal);
	output.TexCoord = float2(input.TexCoord.x, 1-input.TexCoord.y);
	output.WorldPos = mul(ModelToWorldMatrix, input.Pos);

	return output;
}