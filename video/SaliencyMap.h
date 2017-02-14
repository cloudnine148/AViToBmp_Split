#pragma once
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/highgui.h>
#include <opencv2/legacy/legacy.hpp>

#include "Dib.h"
#include "RGBBYTE.h"
#include "DibCv.h"
#include "common.h"


class CSaliencyMap
{
public:
	CSaliencyMap();
	~CSaliencyMap();

public:
	void mainProcessing(IplImage* currImg);
	void getSaliencyMap(IplImage* img);

	void Func_Init(int imgH, int imgW);
	void Func_Destory();

protected:
	void getContrastMap(IplImage* srcImg, IplImage* dstImg, int filterSize, double rate);


protected:
	IplImage* m_saliencyMap;
	
};

