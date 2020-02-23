/*
 *  TVTest DTV Video Decoder
 *  Copyright (C) 2015-2018 DBCTRADO
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once


#ifndef WINVER
#define WINVER 0x0600
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#define WIN32_LEAN_AND_MEAN

#define _USE_MATH_DEFINES

#ifndef _DEBUG
#define _SECURE_SCL 0
#endif

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

#define TVTVIDEODEC_IMPL

#ifdef _MSC_VER

#if defined(_M_IX86) || defined(_M_AMD64)
#define TVTVIDEODEC_SSE_SUPPORT
#define TVTVIDEODEC_SSE2_SUPPORT
#define TVTVIDEODEC_SSE3_SUPPORT
#define TVTVIDEODEC_SSSE3_SUPPORT
#define TVTVIDEODEC_SSE4_1_SUPPORT
#define TVTVIDEODEC_SSE4_2_SUPPORT
#define TVTVIDEODEC_AVX_SUPPORT
#define TVTVIDEODEC_AVX2_SUPPORT
#endif

#else

#if defined(_X86_) || defined(__x86_64)
#ifdef __SSE__
#define TVTVIDEODEC_SSE_SUPPORT
#ifdef __SSE2__
#define TVTVIDEODEC_SSE2_SUPPORT
#ifdef __SSE3__
#define TVTVIDEODEC_SSE3_SUPPORT
#ifdef __SSSE3__
#define TVTVIDEODEC_SSSE3_SUPPORT
#ifdef __SSE4_1__
#define TVTVIDEODEC_SSE4_1_SUPPORT
#ifdef __SSE4_2__
#define TVTVIDEODEC_SSE4_2_SUPPORT
#ifdef __AVX__
#define TVTVIDEODEC_AVX_SUPPORT
#ifdef __AVX2__
#define TVTVIDEODEC_AVX2_SUPPORT
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif

// Avoid VC++ header warnings
#pragma warning(disable: 4995)	// name was marked as #pragma deprecated

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <shellapi.h>
#define STRSAFE_NO_DEPRECATE
#include <dshow.h>
#include <mmsystem.h>
#include <dvdmedia.h>
#include <inttypes.h>
#if defined(_M_IX86) || defined(_M_AMD64)
#include <intrin.h>
#if defined(TVTVIDEODEC_SSE_SUPPORT)
#include <xmmintrin.h>	// SSE
#endif
#if defined(TVTVIDEODEC_SSE2_SUPPORT)
#include <emmintrin.h>	// SSE2
#endif
#if defined(TVTVIDEODEC_SSE3_SUPPORT)
#include <pmmintrin.h>	// SSE3
#endif
#if defined(TVTVIDEODEC_SSSE3_SUPPORT)
#include <tmmintrin.h>	// SSSE3
#endif
#if defined(TVTVIDEODEC_SSE4_1_SUPPORT)
#include <smmintrin.h>	// SSE4.1
#endif
#if defined(TVTVIDEODEC_SSE4_2_SUPPORT)
#include <nmmintrin.h>	// SSE4.2
#endif
#if defined(TVTVIDEODEC_AVX_SUPPORT) || defined(TVTVIDEODEC_AVX2_SUPPORT)
#include <immintrin.h>	// AVX/AVX2
#endif
#endif
#include <new>
#ifdef __MINGW32__
#define STREAMS_MINGW_NOMINMAX
#endif
#include "BaseClasses/streams.h"
#ifdef __MINGW32__
#undef __in
#endif

#include <crtdbg.h>
#ifdef _DEBUG
#define DNew ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define DNew_nothrow DNew
#else
#define DNew new
#define DNew_nothrow new(std::nothrow)
#endif

#ifdef _DEBUG
#ifndef NO_BASECLASSES_DBG
#define DBG_TRACE(...) DbgLog((LOG_TRACE, 5, __VA_ARGS__))
#define DBG_ERROR(...) DbgLog((LOG_ERROR, 5, __VA_ARGS__))
#else
#define DBG_TRACE ::DebugTrace
#define DBG_ERROR ::DebugTrace
void DebugTrace(LPCTSTR pszFormat, ...);
#endif
#else
#define DBG_TRACE(fmt, ...) static_cast<void>(0)
#define DBG_ERROR(fmt, ...) static_cast<void>(0)
#endif

#define restrict __restrict

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
#pragma comment(lib, "strmbasd.lib")
#else
#pragma comment(lib, "strmbase.lib")
#endif
#pragma comment(lib, "libmpeg2.lib")

#ifdef _MSC_VER
#ifdef _WIN64
#pragma comment(linker, "/export:DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/export:DllGetClassObject,PRIVATE")
#pragma comment(linker, "/export:DllRegisterServer,PRIVATE")
#pragma comment(linker, "/export:DllUnregisterServer,PRIVATE")
#endif
#else
STDAPI BASECLASSES_DllCanUnloadNow();
STDAPI BASECLASSES_DllGetClassObject(REFCLSID rClsID, REFIID riid, void **pv);
STDAPI __declspec(dllexport) DllCanUnloadNow();
STDAPI __declspec(dllexport) DllGetClassObject(REFCLSID rClsID, REFIID riid, void **pv);
STDAPI __declspec(dllexport) DllRegisterServer();
STDAPI __declspec(dllexport) DllUnregisterServer();
#endif
