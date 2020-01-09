#ifndef HH5KDecoder_H
#define HH5KDecoder_H

#include "HHAVDefine.h"

//#ifdef __cplusplus
//extern "C" {
//#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef HHDECODE_INTERFACE
#define DLLDECEXPORT_API __declspec(dllexport)
#else
#define DLLDECEXPORT_API __declspec(dllimport)
#endif

typedef struct _XAV_INFO
{
    //��Ƶ����
	UINT			nVideoEncodeType;		//��Ƶ�����ʽ
    UINT			nVideoHeight;			//��Ƶͼ���
    UINT			nVideoWidth;			//��Ƶͼ���
    //��Ƶ����
	UINT			nAudioEncodeType;		//��Ƶ�����ʽ
    UINT			nAudioChannels;			//ͨ����
    UINT			nAudioBits;				//λ��
    UINT			nAudioSamples;			//������
}XAV_INFO,*PXAV_INFO;

//2007.4.20
//��HH5KDecoder_DecodeOneFrame��HHAV_INFO��nVideoEncodeTypeΪ����ֵʱ��
//����������Ƶͼ���nVideoHeight����Ƶͼ���nVideoWidth
#define	AVFORMAT_IN_MPEG4					0xF000
#define	AVFORMAT_IN_H264					0xF001

#define HH5KDECODER_ERR_INVALID_PARAMETER  -1
#define HH5KDECODER_SUCCESS					0

#define HH5KDECODER_YUV_422					0x01
#define HH5KDECODER_YUV_420					0x02
#define HH5KDECODER_RGB_024					0x03


DLLDECEXPORT_API void* WINAPI HHVideo_InitDecoder();
DLLDECEXPORT_API int   WINAPI HHVideo_ReleaseDecoder(void* pDecoder);
DLLDECEXPORT_API int   WINAPI HHVideo_SelectNewH264( void* pDecoder,  BOOL bNewH264 = TRUE);
DLLDECEXPORT_API int   WINAPI HHVideo_GetVideoInfo(  void* pDecoder,  BYTE* pEncFrame,long lEncFrameSize,HHAV_INFO *pAVInfo,OUT EXT_FRAME_VIDEO *pFrameInfo);
DLLDECEXPORT_API int   WINAPI HHVideo_SetDecoderMode(void* pDecoder,  int Out_Stride, int Out_Format);
DLLDECEXPORT_API int   WINAPI HHVideo_SetDecoderParam(void* pDecoder, BOOL bQulity, BOOL bDoDeInterlace, BOOL bTwoField);
DLLDECEXPORT_API int   WINAPI HHVideo_DecodeOneFrame(void* pDecoder,  BYTE* pEncFrame,long lEncFrameSize, BYTE* pDecBuffer,long &lDecBufSize,HHAV_INFO *pAVInfo = NULL);
DLLDECEXPORT_API void* WINAPI XVideo_InitDecoder();
DLLDECEXPORT_API int   WINAPI XVideo_ReleaseDecoder(void* pDecoder);
DLLDECEXPORT_API int   WINAPI XVideo_SelectNewH264( void* pDecoder,  BOOL bNewH264 = TRUE);
DLLDECEXPORT_API int   WINAPI XVideo_GetVideoInfo(  void* pDecoder,  BYTE* pEncFrame,long lEncFrameSize,HHAV_INFO *pAVInfo,OUT EXT_FRAME_VIDEO *pFrameInfo);
DLLDECEXPORT_API int   WINAPI XVideo_SetDecoderMode(void* pDecoder,  int Out_Stride, int Out_Format);
DLLDECEXPORT_API int   WINAPI XVideo_SetDecoderParam(void* pDecoder, BOOL bQulity, BOOL bDoDeInterlace, BOOL bTwoField);
DLLDECEXPORT_API int   WINAPI XVideo_DecodeOneFrame(void* pDecoder,  BYTE* pEncFrame,long lEncFrameSize, BYTE* pDecBuffer,long &lDecBufSize,HHAV_INFO *pAVInfo = NULL);

DLLDECEXPORT_API void* WINAPI HHAudio_InitDecoder();
DLLDECEXPORT_API int   WINAPI HHAudio_ReleaseDecoder(void* pDecoder);
DLLDECEXPORT_API int   WINAPI HHAudio_GetAudioInfo(  void* pDecoder,BYTE* pEncBuf,long lEncSize,HHAV_INFO *pAVInfo,OUT EXT_FRAME_AUDIO *pFrameInfo);
DLLDECEXPORT_API int   WINAPI HHAudio_DecodeData(    void* pDecoder,BYTE *pEncBuf,long lEncSize,BYTE* pDecBuf,long &lDecSize,HHAV_INFO *pAVInfo = NULL);
DLLDECEXPORT_API void* WINAPI XAudio_InitDecoder();
DLLDECEXPORT_API int   WINAPI XAudio_ReleaseDecoder(void* pDecoder);
DLLDECEXPORT_API int   WINAPI XAudio_GetAudioInfo(  void* pDecoder,BYTE* pEncBuf,long lEncSize,HHAV_INFO *pAVInfo,OUT EXT_FRAME_AUDIO *pFrameInfo);
DLLDECEXPORT_API int   WINAPI XAudio_DecodeData(    void* pDecoder,BYTE *pEncBuf,long lEncSize,BYTE* pDecBuf,long &lDecSize,HHAV_INFO *pAVInfo = NULL);

DLLDECEXPORT_API void* WINAPI HHAudio_InitEncoder();
DLLDECEXPORT_API int   WINAPI HHAudio_ReleaseEncoder(void* pEncoder);
DLLDECEXPORT_API int   WINAPI HHAudio_GetEncodeInfo( void* pEncoder,UINT nAudioEncodeType,HHAV_INFO *pAVInfo,OUT EXT_FRAME_AUDIO *pFrameInfo);
DLLDECEXPORT_API int   WINAPI HHAudio_EncodeData(    void* pEncoder,BYTE *pDecBuf, long lDecSize,BYTE* pEncBuf,long &lEncSize,IN EXT_FRAME_AUDIO *pFrameInfo);
DLLDECEXPORT_API void* WINAPI XAudio_InitEncoder();
DLLDECEXPORT_API int   WINAPI XAudio_ReleaseEncoder(void* pEncoder);
DLLDECEXPORT_API int   WINAPI XAudio_GetEncodeInfo( void* pEncoder,UINT nAudioEncodeType,HHAV_INFO *pAVInfo,OUT EXT_FRAME_AUDIO *pFrameInfo);
DLLDECEXPORT_API int   WINAPI XAudio_EncodeData(    void* pEncoder,BYTE *pDecBuf, long lDecSize,BYTE* pEncBuf,long &lEncSize,IN EXT_FRAME_AUDIO *pFrameInfo);

//#ifdef __cplusplus
//}
//#endif


#endif 
