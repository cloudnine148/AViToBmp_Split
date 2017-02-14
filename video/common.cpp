#include "StdAfx.h"
#include "common.h"

void Trace(TCHAR* pszFormat, ...)
{    //가변인자의 길이를 모르기때문에 동적으로 생성하기 위한 포인터 변수    
	TCHAR* pBuffer = NULL;    
	va_list args;     
	va_start(args, pszFormat);    
	// 가변인자 스트링의 길이를 구한다.    
	int nLen = _vsctprintf(pszFormat, args) + sizeof(TCHAR);    
	// 가변인자 길이만큼 문자열을 생성한다.    
	pBuffer = new TCHAR[nLen];    
	// 복사한다.    
	_vstprintf_s(pBuffer, nLen, pszFormat, args);    
	va_end(args); 
	// Windows에서는 필요없음     
	// 출력해준다.   
	::OutputDebugString(pBuffer);    
	if (pBuffer)    
	{       
		delete[] pBuffer;        
		pBuffer = NULL;    
	}
}