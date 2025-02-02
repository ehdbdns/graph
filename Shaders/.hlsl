
struct vertexin
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 noraml:NORMAL;
};
struct vertexout
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};
Texture2D g_tex : register(t0);

SamplerState g_sampler : register(s0);
cbuffer passcb : register(b0)
{
    float4x4 MVP;
    float3 eyepos;
    float pad1;
    float3 AL;
    float pad2;
    float3 BL;
    float m;
    float3 lightdir;
    float pad3;
    float4 md;
    float3 r0;
}
vertexout VS(vertexin pin)
{
    vertexout pout;
    float4 posmvp = mul(pin.position, MVP);
    pout.position =posmvp;
    pout.uv = pin.uv;
    pout.normal = pin.noraml;
    return pout;
}
float4 PS(vertexout pin):SV_Target
{
    pin.normal = normalize(pin.normal);
   // float mm = (1 - m) * 100.0f;
    float4 texcolor= g_tex.Sample(g_sampler, pin.uv);
    float3 kd = texcolor.xyz / 255.0f;//kd其实就是吸收率
    float3 toeye = normalize(eyepos - pin.position.xyz);
    float3 lightdirnor = normalize(lightdir);
    float3 h = normalize( toeye + lightdirnor); //半程向量
    float3 al = AL * kd;//环境光
    float decfactor = max(0, dot(normalize(lightdir), pin.normal)); //朗播余弦
    float3 diffuse = BL * kd * decfactor;
  // float3 rf = (r0 + (1.0f - r0) * pow(max(0, dot(h, pin.normal)), 5));
    float roughfactor = (400 + 8 / 8)*
    pow(max(0, dot(h, pin.normal)), 400);
    float3 speculous = BL *roughfactor*0.3f ;
    float3 retlit = al + diffuse+speculous;
    return float4(retlit,1.0f);
   
}