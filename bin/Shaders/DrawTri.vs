
cbuffer MatrixBuffer : register(b0)
{
	matrix ModelToWorldMatrix;
	matrix WorldToViewMatrix;
	matrix ProjectionMatrix;
};

cbuffer CameraBuffer : register(b1)
{
	float4 cameraPosition;
};

cbuffer LightBuffer : register(b2)
{
	float4 lightPosition;
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
	float4 CameraPos : CameraPos;
	float4 LightPos : LightPos;
};

//-----------------------------------------------------------------------------------------
// VertexShader: VSScene
//-----------------------------------------------------------------------------------------
PSIn VS_main(VSIn input)
{
	PSIn output = (PSIn)0;
	
	// model-to-view
	//matrix MV = mul(ModelToWorldMatrix, WorldToViewMatrix);
	matrix MV = mul(WorldToViewMatrix, ModelToWorldMatrix);
	matrix VM = mul(ModelToWorldMatrix, WorldToViewMatrix);
	// model-to-projection
	//matrix MVP = mul(MV, ProjectionMatrix);
	matrix MVP = mul(ProjectionMatrix, MV);
	
	//float2 inv = { input.TexCoord.x, -input.TexCoord.y };

	output.Pos = mul(MVP, float4(input.Pos, 1));
	output.Normal = mul(MV, input.Normal);
	output.Tangent = mul(MV, input.Tangent);
	output.Binormal = mul(MV, input.Binormal);
	output.TexCoord = input.TexCoord;
	output.WorldPos = mul(MV, input.Pos);
	output.CameraPos = mul(WorldToViewMatrix, cameraPosition);
	output.LightPos =  mul(WorldToViewMatrix, lightPosition);

	return output;
}