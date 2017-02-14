#include "stdafx.h"
#include "Processing.h"


CProcessing::CProcessing()
{
	m_nCurrentFrame = 0;
	m_nPrevFrameNum = 0;

	// Setting ROI : optical Flow�� ���õ� ���� ����	
	m_opticalFlow.Func_Init(IMAGE_HEIGHT, IMAGE_WIDTH, OPTICALfLOW_GRID_INTERVAL, 1., -1./*0.3*/);
	m_nPrevFrameNum = 9999999;

	m_saliencyMap.Func_Init(IMAGE_HEIGHT, IMAGE_WIDTH);
}


CProcessing::~CProcessing()
{
	m_opticalFlow.Func_Destory();
	m_saliencyMap.Func_Destory();
}

/// public

void CProcessing::main(CDib &dib, int nCurrentFrame)
{
	m_nCurrentFrame = nCurrentFrame;

	CDib cpyDib;
	CDib saliencyMapDib;

	cpyDib.Copy(&dib);
	DibGrayscale(cpyDib);
	saliencyMapDib.Copy(&cpyDib);
	
	// 1. saliency map ����
	getSaliencyMap(saliencyMapDib);

	// 2. saliency map�� original img ���ϱ�
	//Saliency map on/off
	//getSumImg(cpyDib, saliencyMapDib, dib);

	// 3. ��� ���� ����


}







/// protected
void CProcessing::getOpticalFlow(CDib &dib, sROI& roi, int nCurrentFrame)
{
	IplImage* img = NULL;
	IplImage* opticalFlowMap = NULL;

	// ���� �����Ӱ� ���ӵ� �������� �ƴϸ� Optical Flow�� ���� ���� �缳��
	if (nCurrentFrame == 1)
	{
		GetIplImageFromDib(dib, &img);
		m_opticalFlow.SetPreviousImg(img);
		m_nPrevFrameNum = nCurrentFrame;

		// ���� ��ü���� ����
		roi.x = 0;
		roi.y = 0;
	}
	else if (abs(nCurrentFrame - m_nPrevFrameNum) >= SKIP_FRAME_FOR_ROI)			// 3������ �������� Optical Flow üũ
	{
		GetIplImageFromDib(dib, &img);
		// Optical Flow ȣ�� //////////////////////////////////////////
		m_opticalFlow.mainProcessing(img, nCurrentFrame);
		
		/// 20170203 KJY
		// optical flow map ����
//		opticalFlowMap = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
//		m_opticalFlow.getOpticalFlowMap(opticalFlowMap);



		m_opticalFlow.GetROIvalues(roi.x, roi.y);
		m_nPrevFrameNum = nCurrentFrame;
	}

	if (img != NULL)
		cvReleaseImage(&img);
	if (opticalFlowMap != NULL)
		cvReleaseImage(&opticalFlowMap);

	return;
}

void CProcessing::getSaliencyMap(CDib &dib)
{
	IplImage* img = NULL;
	IplImage* saliencyMap = NULL;

	GetIplImageFromDib(dib, &img);

	// saliency map ����
	m_saliencyMap.mainProcessing(img);

	GetDibFromIplImage(img, dib);

	// saliency map �յ�ȭ
//	saliencyMap = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
//	m_saliencyMap.getSaliencyMap(img, saliencyMap);

	if (img != NULL)
		cvReleaseImage(&img);
	if (saliencyMap != NULL)
		cvReleaseImage(&saliencyMap);

	return;
}

void CProcessing::getCandidateMap()
{
	register int i, j;

	IplImage* candidateMap = NULL;
	IplImage* opticalFlowMap = NULL;
	IplImage* saliencyMap = NULL;

	candidateMap = cvCreateImage(cvSize((int)(IMAGE_WIDTH * 0.5), (int)(IMAGE_HEIGHT * 0.5)), IPL_DEPTH_8U, 1);
	opticalFlowMap = cvCreateImage(cvSize((int)(IMAGE_WIDTH * 0.5), (int)(IMAGE_HEIGHT * 0.5)), IPL_DEPTH_8U, 1);
	saliencyMap = cvCreateImage(cvSize((int)(IMAGE_WIDTH * 0.5), (int)(IMAGE_HEIGHT * 0.5)), IPL_DEPTH_8U, 1);

	m_opticalFlow.getOpticalFlowMap(opticalFlowMap);
	m_saliencyMap.getSaliencyMap(saliencyMap);


	for (i = 0; i < (int)(IMAGE_HEIGHT * 0.5); i++)
	{
		for (j = 0; j < (int)(IMAGE_WIDTH * 0.5); j++)
		{
			candidateMap->imageData[j + i * candidateMap->widthStep] = (0.5 * opticalFlowMap->imageData[j + i * opticalFlowMap->widthStep]) + (0.5 * saliencyMap->imageData[j + i * saliencyMap->widthStep]);
		}
	}

	cvNamedWindow("CandidateMap", CV_WINDOW_AUTOSIZE);
	cvShowImage("CandidateMap", candidateMap);

	if (candidateMap != NULL)
		cvReleaseImage(&candidateMap);
	if (opticalFlowMap != NULL)
		cvReleaseImage(&opticalFlowMap);
	if (saliencyMap != NULL)
		cvReleaseImage(&saliencyMap);
}

void CProcessing::getSumImg(CDib& dib1, CDib& dib2, CDib& dib3)
{
	register int i, j;

	int w = dib1.GetWidth();
	int h = dib1.GetHeight();

	BYTE** ptr1 = dib1.GetPtr();
	BYTE** ptr2 = dib2.GetPtr();
	RGBBYTE** ptr3 = dib3.GetRGBPtr();

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			ptr3[i][j].r = limit((ptr1[i][j] + ptr2[i][j])/2);
			ptr3[i][j].g = limit((ptr1[i][j] + ptr2[i][j])/2);
			ptr3[i][j].b = limit((ptr1[i][j] + ptr2[i][j])/2);
		}
	}
}