cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-s,--dynamicbase,--nxcompat,--kill-at")

project(BaseClasses CXX)

add_library(${PROJECT_NAME} STATIC
  BaseClasses/amextra.cpp
  BaseClasses/amfilter.cpp
  BaseClasses/amvideo.cpp
  BaseClasses/arithutil.cpp
  BaseClasses/combase.cpp
  BaseClasses/cprop.cpp
  BaseClasses/ctlutil.cpp
  BaseClasses/ddmm.cpp
  BaseClasses/dllentry.cpp
  BaseClasses/dllsetup.cpp
  BaseClasses/mtype.cpp
  BaseClasses/outputq.cpp
  BaseClasses/perflog.cpp
  BaseClasses/pstream.cpp
  BaseClasses/pullpin.cpp
  BaseClasses/refclock.cpp
  BaseClasses/renbase.cpp
  BaseClasses/schedule.cpp
  BaseClasses/seekpt.cpp
  BaseClasses/source.cpp
  BaseClasses/strmctl.cpp
  BaseClasses/sysclock.cpp
  BaseClasses/transfrm.cpp
  BaseClasses/transip.cpp
  BaseClasses/videoctl.cpp
  BaseClasses/vtrans.cpp
  BaseClasses/winctrl.cpp
  BaseClasses/winutil.cpp
  BaseClasses/wxdebug.cpp
  BaseClasses/wxlist.cpp
  BaseClasses/wxutil.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE UNICODE)
target_include_directories(${PROJECT_NAME} PRIVATE BaseClasses)

project(libmpeg2 C)

add_library(${PROJECT_NAME} STATIC
  libmpeg2/libmpeg2/alloc.c
  libmpeg2/libmpeg2/cpu_accel.c
  libmpeg2/libmpeg2/cpu_state.c
  libmpeg2/libmpeg2/decode.c
  libmpeg2/libmpeg2/header.c
  libmpeg2/libmpeg2/idct.c
  libmpeg2/libmpeg2/idct_sse2.c
  libmpeg2/libmpeg2/motion_comp.c
  libmpeg2/libmpeg2/motion_comp_sse2.c
  libmpeg2/libmpeg2/slice.c
  libmpeg2/libmpeg2/thread_win.c
)

target_include_directories(${PROJECT_NAME} PRIVATE libmpeg2/include libmpeg2/vc++)

project(TVTestVideoDecoder CXX)

add_library(${PROJECT_NAME} SHARED
  Acceleration.cpp
  BaseVideoFilter.cpp
  ColorAdjustment.cpp
  Deinterlace.cpp
  DeinterlacerSet.cpp
  Deinterlace_DXVA.cpp
  Deinterlace_Yadif.cpp
  DllMain.cpp
  DXVA2Allocator.cpp
  FrameBuffer.cpp
  FrameCapture.cpp
  Mpeg2Decoder.cpp
  Mpeg2DecoderDXVA2.cpp
  PixelFormatConvert.cpp
  stdafx.cpp
  TVTestVideoDecoder.cpp
  TVTestVideoDecoderProp.cpp
  TVTestVideoDecoderStat.cpp
  Util.cpp
  VideoFrameDecoder.cpp
  TVTestVideoDecoder.rc
)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.16)
  target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)
endif()
target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE UNICODE)
target_include_directories(${PROJECT_NAME} PRIVATE BaseClasses libmpeg2/include)
target_link_libraries(${PROJECT_NAME} -static BaseClasses libmpeg2 winmm strmiids)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".ax")
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
