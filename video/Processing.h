#pragma once

#include "Dib.h"
#include "RGBBYTE.h"
#include "DibCv.h"
#include "DibColor.h"
#include "common.h"

#include "OpticalFlow.h"
#include "SaliencyMap.h"

struct sROI{
	int x;	// roi ���� ��ǥ
	int y;	// roi ���� ��ǥ 		
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
	int m_nCurrentFrame;			// ���� frame Num
	int m_nPrevFrameNum;			// ���� frame Num

	// Optical Flow Ŭ���� 
	COpticalFlow m_opticalFlow;

	// Saliency Map Ŭ����
	CSaliencyMap m_saliencyMap;
};

