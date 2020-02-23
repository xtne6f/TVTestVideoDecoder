//------------------------------------------------------------------------------
// File: streams_mingw.h
//
// Desc: DirectShow base classes - MinGW patches for "streams.h".
//
// Public domain.
//------------------------------------------------------------------------------

#define BASECLASSES_RENAME_COM_ENTRYPOINTS

#ifndef STREAMS_MINGW_NOMINMAX
#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#endif

// <sal.h> additional definitions
#define __in
#define __out
#define __deref_in
#define __deref_out
#define __deref_out_opt
#define __deref_inout_opt
#ifndef __success
#define __success(e)
#endif
#ifndef __in_bcount_opt
#define __in_bcount_opt(s)
#endif
#ifndef __in_ecount_opt
#define __in_ecount_opt(s)
#endif
#ifndef __field_ecount_opt
#define __field_ecount_opt(s)
#endif
#ifndef __control_entrypoint
#define __control_entrypoint(c)
#endif
#ifndef __range
#define __range(x, y)
#endif
#ifndef __out_range
#define __out_range(x, y)
#endif
#ifndef __deref_out_range
#define __deref_out_range(x, y)
#endif

#define AM_NOVTABLE

#include <amvideo.h>

// <amvideo.h> additional definitions
#ifndef DIBWIDTHBYTES
#define DIBWIDTHBYTES(b) ((DWORD)((DWORD)(((DWORD)(b).biWidth * (DWORD)(b).biBitCount + 31) & ~31) / 8))
#endif
#ifndef DIBSIZE
#define DIBSIZE(b) ((b).biHeight < 0 ? -1 * (DIBWIDTHBYTES(b) * (DWORD)(b).biHeight) : DIBWIDTHBYTES(b) * (DWORD)(b).biHeight)
#endif
#ifndef SIZE_PREHEADER
#define SIZE_PREHEADER (FIELD_OFFSET(VIDEOINFOHEADER, bmiHeader))
#endif
#ifndef SIZE_VIDEOHEADER
#define SIZE_VIDEOHEADER (sizeof(BITMAPINFOHEADER) + SIZE_PREHEADER)
#endif
#ifndef SIZE_MASKS
#define SIZE_MASKS (iMASK_COLORS * sizeof(DWORD))
#endif
#ifndef SIZE_PALETTE
#define SIZE_PALETTE (iPALETTE_COLORS * sizeof(RGBQUAD))
#endif
#ifndef PALETTISED
#define PALETTISED(p) ((p)->bmiHeader.biBitCount <= iPALETTE)
#endif
#ifndef BITMASKS
#define BITMASKS(p) ((DWORD*)((LPBYTE)&(p)->bmiHeader + (p)->bmiHeader.biSize))
#endif
#ifndef COLORS
#define COLORS(p) ((RGBQUAD*)((LPBYTE)&(p)->bmiHeader + (p)->bmiHeader.biSize))
#endif
#ifndef TRUECOLOR
#define TRUECOLOR(p) ((TRUECOLORINFO*)((LPBYTE)&(p)->bmiHeader + (p)->bmiHeader.biSize))
#endif
#ifndef PALETTE_ENTRIES
#define PALETTE_ENTRIES(p) ((DWORD)1 << (p)->bmiHeader.biBitCount)
#endif
#ifndef HEADER
#define HEADER(p) (&((VIDEOINFOHEADER*)(p))->bmiHeader)
#endif
#ifndef SAFE_DIBSIZE
#define SAFE_DIBSIZE STREAMS_MINGW_SAFE_DIBSIZE
#endif

inline HRESULT STREAMS_MINGW_SAFE_DIBSIZE(const BITMAPINFOHEADER *pb, DWORD *pdwSize)
{
    if (pb->biWidth < 0 || pb->biHeight == 0x80000000 || pb->biBitCount <= 0)
        return E_INVALIDARG;
    DWORD dwBit;
    HRESULT hr = DWordMult((DWORD)pb->biWidth, (DWORD)pb->biBitCount, &dwBit);
    if (FAILED(hr)) return hr;
    DWORD dwB = (dwBit & 7) ? (dwBit >> 3) + 1 : (dwBit >> 3);
    if (dwB & 3) dwB += 4 - (dwB & 3);

    DWORD dwH = pb->biHeight < 0 ? (DWORD)-(pb->biHeight) : (DWORD)pb->biHeight;
    DWORD dwS;
    hr = DWordMult(dwH, dwB, &dwS);
    if (FAILED(hr)) return hr;
    *pdwSize = dwS;
    return S_OK;
}

// "wxutil.h" refers this.
#define __AMVIDEO__
