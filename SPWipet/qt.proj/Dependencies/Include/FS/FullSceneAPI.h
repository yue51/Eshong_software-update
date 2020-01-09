#ifndef FULLSCENEAPI_H_
#define FULLSCENEAPI_H_	1

#ifdef WIN32
#include <Windows.h>
#endif

#ifdef __cplusplus
extern "C" 
{
#endif
    
namespace FS
    {
        typedef enum _PhotoShowTypeOut{
            PSTO_PLANE = 0,
            PSTO_SPHERE_OUT,
            PSTO_SPHERE_IN,
            PSTO_SPHERE_RECT,
            PSTO_CYLINDER,
            PSTO_PLANE_INV
        }PhotoShowTypeOut;
        
        typedef enum _PhotoDrawType{
            PDT_CIRCLE = 0,
            PDT_PLANE360
        }PhotoDrawType;
        
#if defined (WIN32) && (defined USE_WIN32_DC)
	bool Initialize(HDC dc,const char* strPath);
#endif
	long InitializeEx(const char* path, const char* CachePath=0);
	

	void SetViewport(long handle, int width,int height);
	void Render(long handle);
	void Destroy(long handle);
	void ChangeCurFScene(long handle, const char* _ID);

	void MakeVisible(long handle, int n, bool bVisible);
	void MakeViewPort(long handle, int n, bool bVisible, int l, int t, int w, int h);
	void MakeCurrent(long handle, int n);
	int  GetCurrent(long handle);

	//float GetViewRadius();
    //Camera
	void MoveCamera(long handle, float fPitch, float fYaw, float fRoll);
    void MoveCameraDelta(long handle, float dPitch, float dYaw, float dRoll);
    bool GetCameraParam(long handle, float *pPitch, float* pYaw, float* pRoll);
    float GetCameraFov(long handle);

	void MoveTarget(long handle, float x, float y, float z);
	void GetTargetPos(long handle, float *px, float* py, float* pz);

	void GetTargetScale(long handle, float *px, float *py, float *pz);
	void ScaleTarget(long handle, float x, float y, float z);

	void SetCameraPos(long handle, float x, float y, float z);
	void GetCameraPos(long handle, float *px, float* py, float* pz);
	void SetCameraLookAt(long handle, float x, float y, float z);

	bool  SetCameraParamLimited(long handle, float fPitchMin, float fPitchMax, float fYawMin, float fYawMax, float fRollMin, float fRollMax);
	bool  GetCameraParamLimited(long handle, float* pPitchMin, float* pPitchMax, float* pYawMin, float* pYawMax, float* pRollMin, float* pRollMax);

    //Scale
    void Scale(long handle, float _fScale);
    float GetScale(long handle);
	bool SetCameraScaleLimited(long handle, float fScaleMin, float fScaleMax);
    
    void  SetShowType(long handle, unsigned int type); //Image Show Type
    void  SetDx(long handle, float dx);       //Image Center Coord X  0.5
    void  SetDy(long handle, float dy);       //Image Center Coord Y  0.5
    void  SetSr(long handle, float sr);       //Image Radius = 0.5
    void  SetAg(long handle, float ag);       //360 X 230, Ag = 230
	void  SetOrth(long handle, bool orth);

	void  SetBr(long handle, float dLeft, float dTop, float dRight, float dBottom, float imgW, float imgH);	//Eye's border at Image
    void  SetInv(long handle, bool inv);      //inv
    void  SetPow(long handle, bool pow);      //update
    
    unsigned int GetShowType(long handle); //Image Show Type
    float GetDx(long handle);       //Image Center Coord X  0.5
    float  GetDy(long handle);       //Image Center Coord Y  0.5
    float  GetSr(long handle);       //Image Radius = 0.5
    float  GetAg(long handle);       //360 X 230, Ag = 230
    bool  GetInv(long handle);

	void  SetStep(long handle, float step);
	float GetStep(long handle);

	void  SetOutXY(long handle, float OutXY);
	float GetOutXY(long handle);

	void  SetSpanAg(long handle, float spanAg);
	float GetSpanAg(long handle);

	void  SetOutRotAg(long handle, float outRotAg);
	float GetOutRotAg(long handle);
}
	
#ifdef __cplusplus
}
#endif

#endif
