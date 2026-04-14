struct VS_INPUT
{
    float3 pos : POSITION;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
};

PS_INPUT VSMain(VS_INPUT input)
{
    PS_INPUT output;
    output.pos = float4(input.pos, 1.0f);
    return output;
}

float4 PSMain(PS_INPUT input) : SV_TARGET
{
    return float4(0.0f, 1.0f, 0.3f, 1.0f);

}