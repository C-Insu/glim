/*

#ifdef PYLON_2_2
	#include <pylonc/PylonC.h>	//2.2
#else
	#include "PylonGenericInterface.h"
#endif

#define AREA_SLIT
//#define DEBUG_MODE

#define MAX_CAM			1		// �� PC�� ����� ī�޶� �� 
#define WIDTH			1392	// ���� Areaī�޶�� Grab�ϴ� ũ�� X
//////////////////////////////////////////////////////////////////////
//BC01/cc01					48-Line	, 8Frame
//BE01/BE02					48-Line , 32Frame
//DE01/DE02					60-Line , 32Frame
//CE01/02/03/04				60-Line , 32Frame
//CC02/CC03/CC04/BC02		320-Line , 2Frame
//DC02/dc01					60-8
//////////////////////////////////////////////////////////////////////
#define NUM_BUFFERS		2		//3	//8	//8	//Default Buffers //BC01 8 , other 8
#define HEIGHT			320		//48//		//Default Height WV 1Frame  ũ�ν� ����.
	
#define YOFFSET			208				//�κ� Grab �� Y���� Offset ��, (0,208)-(639,208+64) ������ Grab�Ѵ�.
#define MAX_FULL_BUF	3				//Buffer �� 

#include "SlitInspect.h"

class CVision1  
{
public:
//l/10
	//-------------------------���� �ִ� �Լ��� ���� ----------------------
	BOOL Open(HWND hWnd);
	void Close();
	CVision1(CWnd* pwnd=NULL);
	virtual ~CVision1();
	void GetExposureTime(double *dValue);
	void HookStart();
	void HookStop();
	unsigned short* GetProcessBufShort();	//������� ����
	LPBYTE GetProcessBuf();

	long m_nSizeX;
	long m_nSizeY;	//����
	long m_nExposure;
	CWnd*	m_pParent;	
	//---------------------------------------------------------------------

	//Scout Camera ���ÿ� ���Ǵ� ����----------
#ifdef PYLON_2_2
	UINT NumOfCams;		//2.2
#else	
	long NumOfCams;
#endif

	CString strError;
	char StrBuffer [100];
	char sCameraSerial[2][80];
	//---------------------------------------------
	bool GetAreaCameraSerialNumber(CString str);		//C:\\nexteye\\AreaSerial.ini ���� ī�޶� Serial��ȣ �о���� �Լ� 
														//str�� "NEL-701"~"NEL-899"���� 	
	int LoadSlitData(CString str);						//Slit����Ÿ�� �о�´�.
};

typedef struct TEMPDATA_
{
	bool m_GRAB1RUN;
	bool m_GRAB1START;
	bool m_GRAB1RUNSUB;
	bool m_GRAB1Done;
	long m_nGrab1Count;
	long m_nBuffer1ID;


	bool m_GRABControlRUN;
	bool m_GRABControlEND;
	bool m_GRABControlSTART;

	bool m_bChangeExposure;
	long m_nExposureData;

	bool m_Inspecting;

}TEMPDATA;

extern TEMPDATA g_Temp;


#define CAMERA_SERIAL_PATH			"C:\\nexteye\\AreaSerial.ini"
#define CAMERA_TEACHDATA_PATH		"C:\\nexteye\\SlitAreaTeachData.ini"

*/