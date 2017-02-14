#include "StdAfx.h"
#include "common.h"

void Trace(TCHAR* pszFormat, ...)
{    //���������� ���̸� �𸣱⶧���� �������� �����ϱ� ���� ������ ����    
	TCHAR* pBuffer = NULL;    
	va_list args;     
	va_start(args, pszFormat);    
	// �������� ��Ʈ���� ���̸� ���Ѵ�.    
	int nLen = _vsctprintf(pszFormat, args) + sizeof(TCHAR);    
	// �������� ���̸�ŭ ���ڿ��� �����Ѵ�.    
	pBuffer = new TCHAR[nLen];    
	// �����Ѵ�.    
	_vstprintf_s(pBuffer, nLen, pszFormat, args);    
	va_end(args); 
	// Windows������ �ʿ����     
	// ������ش�.   
	::OutputDebugString(pBuffer);    
	if (pBuffer)    
	{       
		delete[] pBuffer;        
		pBuffer = NULL;    
	}
}