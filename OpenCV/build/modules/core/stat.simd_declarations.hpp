#define CV_CPU_SIMD_FILENAME "/home/yukiorigane/catkin_kurione_ws/src/2021_Clione/OpenCV/modules/core/src/stat.simd.hpp"
#define CV_CPU_DISPATCH_MODE SSE4_2
#include "opencv2/core/private/cv_cpu_include_simd_declarations.hpp"

#define CV_CPU_DISPATCH_MODE AVX2
#include "opencv2/core/private/cv_cpu_include_simd_declarations.hpp"

#define CV_CPU_DISPATCH_MODES_ALL AVX2, SSE4_2, BASELINE

#undef CV_CPU_SIMD_FILENAME
