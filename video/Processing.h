#pragma once

#include "Dib.h"
#include "RGBBYTE.h"
#include "DibCv.h"
#include "DibColor.h"
#include "common.h"

#include "OpticalFlow.h"
#include "SaliencyMap.h"

struct sROI{
	int x;	// roi 시작 좌표
	int y;	// roi 시작 좌표 		
};

class CProcessing
{
public:
	CProcessing();
	~CProcessing();

public:
	void main(CDib &dib, int nCurrentFrame);


protected:
	void getOpticalFlow(CDib &dib, sROI& roi, int nCurrentFrame);
	void getSaliencyMap(CDib &dib);
	void getCandidateMap();
	void getSumImg(CDib& dib1, CDib& dib2, CDib& dib3);


protected:
	int m_nCurrentFrame;			// 현재 frame Num
	int m_nPrevFrameNum;			// 이전 frame Num

	// Optical Flow 클래스 
	COpticalFlow m_opticalFlow;

	// Saliency Map 클래스
	CSaliencyMap m_saliencyMap;
};

