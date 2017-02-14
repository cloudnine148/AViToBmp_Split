#pragma once


// ���� ũ��
#define IMAGE_WIDTH								640
#define IMAGE_HEIGHT							480

#define PI										3.141592653

/// Optical flow.cpp
// Optical Flow�� Features ����Ʈ�� Grid ����, ������ ¦������ ��
#define OPTICALfLOW_GRID_INTERVAL				6
// Optical Flow üũ ����
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