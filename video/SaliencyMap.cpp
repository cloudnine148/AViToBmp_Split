#include "stdafx.h"
#include "SaliencyMap.h"


CSaliencyMap::CSaliencyMap()
{
	
}


CSaliencyMap::~CSaliencyMap()
{
	
}


/// public
void CSaliencyMap::mainProcessing(IplImage* currImg)
{
	IplImage* gaussianImg = NULL;
	IplImage* contrastImg_1 = NULL;
	IplImage* contrastImg_2 = NULL;
	// 1. Gaussian filter 利侩
	gaussianImg = cvCreateImage(cvSize(currImg->width, currImg->height), IPL_DEPTH_8U, 1);
	cvSmooth(currImg, gaussianImg, CV_GAUSSIAN, 5);

	// 2. Contrast map 积己
	contrastImg_1 = cvCreateImage(cvSize(currImg->width, currImg->height), IPL_DEPTH_8U, 1);
	getContrastMap(gaussianImg, contrastImg_1, 5, 1);
	// 3. 2nd Contrast map 积己	
	contrastImg_2 = cvCreateImage(cvSize(currImg->width, currImg->height), IPL_DEPTH_8U, 1);
	getContrastMap(contrastImg_1, contrastImg_2, 6, 1);

	// 4. Saliency map 免仿
	cvNamedWindow("Saliency Map", CV_WINDOW_AUTOSIZE);
	cvShowImage("Saliency Map", contrastImg_2);

	cvCopy(contrastImg_2, m_saliencyMap);
	cvCopy(m_saliencyMap, currImg);

	if (gaussianImg != NULL)
		cvReleaseImage(&gaussianImg);
	if (contrastImg_2 != NULL)
		cvReleaseImage(&contrastImg_2);

	return;
}

void CSaliencyMap::getSaliencyMap(IplImage* img)
{
//	cvEqualizeHist(m_saliencyMap, img);

//	cvNamedWindow("Equalized Saliency Map", CV_WINDOW_AUTOSIZE);
//	cvShowImage("Equalized Saliency Map", dstImg);

	cvCopy(m_saliencyMap, img);
}


void CSaliencyMap::Func_Init(int imgH, int imgW)
{
	m_saliencyMap = NULL;
	m_saliencyMap = cvCreateImage(cvSize(imgW, imgH), IPL_DEPTH_8U, 1);
}

void CSaliencyMap::Func_Destory()
{
	if (m_saliencyMap != NULL)
		cvReleaseImage(&m_saliencyMap);
}

/// protected
void CSaliencyMap::getContrastMap(IplImage* srcImg, IplImage* dstImg, int filterSize, double rate)
{
	double sum = 0;
	int ii, jj, i, j;
	int endx, endy;
	int count = 0;
	int centP, moveP;
	int T = filterSize;

	int new_height = srcImg->height;
	int new_width = srcImg->width;

//	dstImg = cvCreateImage(cvSize(new_width, new_height), IPL_DEPTH_8U, 1);

	for (i = 0; i < new_height; i++)
	{
		for (j = 0; j < new_width; j++)
		{
			dstImg->imageData[j + i * dstImg->widthStep] = 0;
		}
	}

	for (i = 0; i < new_height; i++)
	{
		for (j = 0; j < new_width; j++)
		{
			ii = i - T;
			jj = j - T;
			endx = j + T;
			endy = i + T;

			if (ii<0)
			{
				ii = 0;
			}

			if (jj<0)
			{
				jj = 0;
			}

			if (endx > new_width)
			{
				endx = new_width;
			}

			if (endy > new_height)
			{
				endy = new_height;
			}

			int tem_jj = jj;
			int tem_ii = ii;

			for (ii = tem_ii; ii <endy; ii++)
			{
				for (jj = tem_jj; jj < endx; jj++)
				{					
					centP = srcImg->imageData[j + i * srcImg->widthStep];
					moveP = srcImg->imageData[jj + ii * srcImg->widthStep];

					sum += abs(moveP - centP);

					count++;
				}
			}
			dstImg->imageData[j + i * dstImg->widthStep] = (int)(sum / (double)count);

			sum = count = 0;
		}
	}

	int max = 0;
	for (i = 0; i < new_height; i++)
	{
		for (j = 0; j < new_width; j++)
		{
			if (dstImg->imageData[j + i * dstImg->widthStep] > max)
			{
				max = dstImg->imageData[j + i * dstImg->widthStep];
			}
		}
	}

	for (i = 0; i < new_height; i++)
	{
		for (j = 0; j < new_width; j++)
		{
			dstImg->imageData[j + i * dstImg->widthStep] = (BYTE)(((double)dstImg->imageData[j + i * dstImg->widthStep] / (double)max) * 255);
		}
	}

	return;
}

