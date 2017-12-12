
#include <cmath>
#include <cstdlib>
#include "rom.h"
#include "transform.h"

#define PI M_PI

void fill(Pel * buf, int N, int k)
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            float val = 127 * cos((j+0.5) * k * PI/N) ;//* cos(j * 5*PI/N);
            buf[i*N+j]=val;
        }
    }
}

template<typename T, typename Idx = size_t>
void print_m(T m[], Idx N, const char * fmt)
{
    for(Idx i=0; i<N; ++i)
    {
        for(Idx j=0; j<N; ++j)
        {
            printf(fmt, m[i*N+j]);
        }
        printf("\n");
    }
}

template<typename T, typename S = T, typename Idx = size_t>
S distance(T a[], T b[], Idx N)
{
    S d = 0;
    
    for(Idx i=0; i<N; ++i)
        d += std::abs(a[i] - b[i]);
    return d;
}

int main()
{
    const int N = 128;
    const int N2 = N*N;
    const int maxLog2TrDynamicRange = 15;
    const int bitdepth = 10;

    Pel buf[N2], rec[N2];
    float coefs_f[N2];
    TCoeff coef[N2];
    
    init_rom();
    
    //std::fill(buf, buf + N2, N);
    fill(buf, N, 5);
    
    //print_m(buf, N, "%3d ");
    
    xTrMxN(bitdepth, buf, N, coef, N, N, 0, maxLog2TrDynamicRange);
    xITrMxN(bitdepth, coef, rec, N, N, N, 0, maxLog2TrDynamicRange);
    
    int shift = maxLog2TrDynamicRange - bitdepth - ( ( g_aucLog2[N] + g_aucLog2[N] ) >> 1 );
    float den = 1 << shift;

    for(int i=0; i<N2; ++i)
    {
        coefs_f[i] = coef[i] / den;
    }

#if 0
    printf("coefs: \n");
    print_m(coefs_f, N, "%.2f ");
    
    printf("rec: \n");
    print_m(rec, N, "%3d ");
#endif
    
    auto err = distance(buf, rec, N2);
    printf("err: %d (%.5f)\n", err, err/float(N2));
}
