#ifndef HHREADWRITER_H
#define HHREADWRITER_H

#ifndef HHFILEERROR_H
#define HHFILEERROR_H
#define ERR_FILE_SUCCESS                0
#define ERR_FILE_INVALID_PARAMETER     -1   //��������
#define ERR_FILE_INVALID_FILE          -2   //��Ч���ļ�
#define ERR_FILE_OPEN_FAIL             -3   //�ļ���ʧ��
#define ERR_FILE_INVALID               -4   //�޷�ʶ����ļ�
#define ERR_FILE_NO_OPEN               -5   //�ļ�û�д�
#define ERR_FILE_NO_FRAME              -6   //Ҫȡ��֡����ʧ
#define ERR_FILE_OPER_FAIL             -7   //�ļ�����ʧ��
#define ERR_FILE_START                 -8   //�ļ�ͷ����֡��
#define ERR_FILE_OVER                  -9   //�ļ�ĩβ
#define ERR_FILE_END                   -10   //�ļ�ĩβ���ܲ���
#define ERR_STREAM_NOINI               -11  //��û�г�ʼ��
#endif 

enum eHHFrameType
{
	eType_Frame_A = 0x0d,
	eType_Frame_I = 0x0e,
	eType_Frame_P = 0x0b,
};

typedef struct _tagHHFileFrameInfo
{
	char  cFrameType;
	DWORD dwPlayTime;
	DWORD dwFrameSize;
	union
	{
		DWORD dwAudioEncType;
		DWORD dwVideoEncType;	
	};
	BYTE *pFrameBuffer;
	_tagHHFileFrameInfo()
	{
		memset(this,0,sizeof(_tagHHFileFrameInfo));
	}

	short		m_PlayStatus;	//��ǰ����״̬���������ţ����...��
	short		m_HaveAudio;	//�Ƿ�����Ƶ�ļ�
}HHFILEFRAMEINFO;				//֡BUFF���ڶ�ȡÿ֡����

typedef struct _tagHHFileInfo
{	
	DWORD dwFileSize;
	DWORD dwPlayTime;
    DWORD dwReserve[2];
	_tagHHFileInfo()
	{
		memset(this,0,sizeof(_tagHHFileInfo));
	}
}HHFILEINFO;				//֡BUFF���ڶ�ȡÿ֡����


#define DLLEXPORT_API  extern "C"__declspec(dllexport) 

DLLEXPORT_API HANDLE __stdcall HHFile_InitReader();
DLLEXPORT_API int    __stdcall HHFile_ReleaseReader(HANDLE hReader);
DLLEXPORT_API int    __stdcall HHFile_OpenFile(     HANDLE hReader, LPCTSTR filelist[], int filenum, DWORD &nTimeLength);
DLLEXPORT_API int    __stdcall HHFile_CloseFile(    HANDLE hReader);

DLLEXPORT_API int    __stdcall HHFile_GetFileInfo(   HANDLE hReader, DWORD *dwTimeLength, DWORD *dwFileLength);            //�õ��ļ���Ϣ
DLLEXPORT_API int    __stdcall HHFile_GetFilePal(    HANDLE hReader, DWORD *pdwPal);
DLLEXPORT_API int    __stdcall HHFile_GetNextFrame(  HANDLE hReader, HHFILEFRAMEINFO &xFileFrameInfo);
DLLEXPORT_API int    __stdcall HHFile_GetNextFrame2( HANDLE hReader, char &cFrameType,BYTE **ppFrameBuffer,DWORD &dwFrameSize,DWORD &dwEncType,DWORD &dwPlayTime);

DLLEXPORT_API int    __stdcall HHFile_GetPosition(    HANDLE hReader,DWORD *dwPlayedTime);			//�õ����ŵ�ʱ��
DLLEXPORT_API int    __stdcall HHFile_SetPosition(    HANDLE hReader,float fOffset);				//���ò���λ��
DLLEXPORT_API int    __stdcall HHFile_SeekToSecond(   HANDLE hReader,int nSec);						//�ƶ�����ָ�뵽ָ����
DLLEXPORT_API int    __stdcall HHFile_SetLoop(        HANDLE hReader,bool bIsLoop = true);			//ѭ������ 
DLLEXPORT_API int    __stdcall HHFile_SetReadOrder(   HANDLE hReader,bool bIsOrder = true);			//˳��� 
DLLEXPORT_API int    __stdcall HHFile_SetReadKeyFrame(HANDLE hReader,bool bIsKeyFrame = false);		//ֻȡ�ؼ�֡

enum eWriteFileStatus
{
	eStatus_CreateFileSuccess = 1,
	eStatus_CloseFileSuccess  = 2,
	eStatus_CreateFileError  = -1,
	eStatus_WriteFileError   = -2,
};
typedef int (WINAPI *HHWriteFileCB)(LPCTSTR strFileName,DWORD dwStatus,HHFILEINFO *pFileInfo,void *pContext);

DLLEXPORT_API HANDLE __stdcall HHFile_InitWriter();
DLLEXPORT_API int    __stdcall HHFile_ReleaseWriter( HANDLE hWriter);
DLLEXPORT_API int    __stdcall HHFile_SetCacheBufferSize( HANDLE hWriter,long lBufferSize = 500*1024);
DLLEXPORT_API int    __stdcall HHFile_RegWriteFileCB(HANDLE hWriter,HHWriteFileCB pCBWriteFile,void *pContext = NULL);
DLLEXPORT_API int    __stdcall HHFile_InputFrame(    HANDLE hWriter,BYTE *pFrame,long lFrameSize,DWORD dwEncType = 0);
DLLEXPORT_API int    __stdcall HHFile_StartWrite(    HANDLE hWriter,LPCTSTR strFileName);
DLLEXPORT_API int    __stdcall HHFile_GetWriteInfo(  HANDLE hWriter,HHFILEINFO &xFileInfo);
DLLEXPORT_API int    __stdcall HHFile_StopWrite(     HANDLE hWriter);

#endif  