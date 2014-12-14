#ifndef BEZIER_H
#define BEZIER_H

typedef struct Bezier{

    double m_x;
    double m_y;
} Bezier;

// Combine two Bezier curves of degree n-1 to another degree-n curve
Bezier Combine(const Bezier &b1, const Bezier &b2, double t)
{
    Bezier out1, out2;
    out1.m_x = (1.0 - t) * b1.m_x;
    out1.m_y = (1.0 - t) * b1.m_y;
    out2.m_x = (t) * b2.m_x;
    out2.m_y = (t) * b2.m_y;
    Bezier out;
    out.m_x = out1.m_x + out2.m_x;
    out.m_y = out1.m_y + out2.m_y;
    return out;
}    
#endif
