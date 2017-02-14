#pragma once


// 영상 크기
#define IMAGE_WIDTH								640
#define IMAGE_HEIGHT							480

#define PI										3.141592653

/// Optical flow.cpp
// Optical Flow의 Features 포인트의 Grid 간격, 무조건 짝수여야 함
#define OPTICALfLOW_GRID_INTERVAL				6
// Optical Flow 체크 간격
#define SKIP_FRAME_FOR_ROI						3

// ROI 
#define ROI_START_RATIO_X		0
#define ROI_START_RATIO_Y		0
#define ROI_WIDTH_RATIO			1
#define ROI_HEIGHT_RATIO		1



///==================================================
#define _function_		_T(__FUNCTION__)
#define _line_			__LINE__


void Trace(TCHAR* pszFormat, ...);