
struct VSoutput
{
    float4 position : SV_POSITIONT;
    float4 color : COLOR;
};
VSoutput VS(VSoutput pin)
{
    VSoutput pout;
    pout.position = pin.position;
    pout.color = pin.color;
    return pout;
}
float4 PS(VSoutput pin):SV_TARGET
{
    return pin.color;
}