// Packet.h: interface for the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKET_H__0086D72B_3BA5_46C1_A01B_A01D89AD6CDC__INCLUDED_)
#define AFX_PACKET_H__0086D72B_3BA5_46C1_A01B_A01D89AD6CDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WAIT_ON_TIME_OUT				0x12312378
#define STATUS_HOOK_START				1
#define STATUS_HOOK_START1				2
#define STATUS_HOOK_STOP				3
#define STATUS_PRESET					4
#define STATUS_MODEL					5
#define STATUS_LOT_NUMBER				6
#define STATUS_PARAM					7
#define STATUS_MARKING_START			8
#define STATUS_REVIVE_START				15
#define STATUS_REVIVE_END				16


#define NM_MARKING_START				0
#define NM_DATA							1
#define NM_INS_START					2
#define NM_INS_STOP						3
#define NM_EXIT_PGM						4
#define NM_REBOOTING					5
#define NM_SHUTDOWN						6
#define NM_RESET						7	// RESET COMMAND FOR EVERY LOCAL HOST

#define NM_CALIB_START					9
#define NM_CALIB_RESULT					10
#define NM_INS_PRESET					11

#define NM_LOTDATA_CLEAR				12	// 클라이언트의 LotData폴더의 내용을 모두 삭제 한다. 
#define NM_ON_SAVE						13
#define NM_PARAM_INSTANT				14
#define NM_HISTO_EQUA					15

#define NM_REQ_HDD_REMAINING			16
#define NM_CLIENT_SIMULATION_MODE		17

#define NM_ACK_READY					18	// 클라이언트가 정지 상태에서 처음 시작 되는 경우
#define NM_SPLICE						19	// 클라이언트가 동작 상태에서 시작신호를 받은 경우
#define MN_DATA_LOT_NAME				40	// 서버에서 lot name 보내주는 데이터
#define MN_DATA_NEB						41	// 401에서 BROADCASTING
#define MN_DATA_LOT_NAME2				44	// 서버에서 lot name 보내주는 데이터
//#define MN_DATA_NEB2_FROM_SERVER		21
#define NM_ACK_MODEL					22	//Start
#define NM_ACK_LOT_NUMBER				23	//stop
#define NM_ACK_PARAM					24
#define NM_ACK_MARKING_READY_OK			25	//	마킹에 레디를 보냈을때 준비가 되었으면, 받는 피드백
#define NM_ACK_MARKING_READY_NG			26	//	마킹에 레디를 보냈을때 준비가 안되었을때, 받는 피드백
#define NM_ACK_MARKING_RESET			27
#define NM_ACK_REVIVE_START				33
#define NM_ACK_REVIVE_END				34
#define NM_ACK_KBH						49
#define NM_DATA_FRAME					50	//Frame수 Data Receive Packet
#define NM_TAPE2						53
#define NM_ACK_CAM_AVERAGE				54
#define NM_ACK_LIGHT_DATA				56	//Double : AVE	STR : Edge (mm)
#define NM_MOTION_CHECK					58	//Double : AVE	STR : Edge (mm)
//ljh  추가
#define NM_IMAGE_DELETE					70

#define NM_NOT_SAVE					73
#define GM_NOT_INSP					75	//설비 미검사 signal
#define GM_USE_INSP					76	//설비 검사 signal


#define PARAM_NAME_UPDATE				"Update"
#define PARAM_NAME_HDD_REMAINING		"HDD_remaining"

#define PARAM_NAME_ALG1					"Algorithm_Param1"
#define PARAM_NAME_ALG2					"Algorithm_Param2"
#define PARAM_NAME_ALG3					"Algorithm_Param3"
#define PARAM_NAME_ALG4					"Algorithm_Param4"
#define PARAM_NAME_ALG5					"Algorithm_Param5"
#define PARAM_NAME_ALG6					"Algorithm_Param6"
#define PARAM_NAME_ALG7					"Algorithm_Param7"
#define PARAM_NAME_ALG8					"Algorithm_Param8"
#define PARAM_NAME_ALG9					"Algorithm_Param9"
#define PARAM_NAME_ALG10				"Algorithm_Param10"

#define PARAM_NAME_IP_CHANGE			"IP change"					// almost not using
#define PARAM_NAME_SHUTTER_CONTROL		"Shutter_Control"			// used for calibration.
#define PARAM_NAME_CAL_X				"Calibration_X_Offset"		// used for calibration.
#define PARAM_NAME_CAL_Y				"Calibration_Y_Offset"		// used for calibration.
#define PARAM_NAME_CAL_FRAME			"Calibration_Frame"			// used for calibration.
#define PARAM_NAME_FRAME_LENGTH			"Frame_Length_in_real"		// used for basic setup.
#define PARAM_NAME_SFY					"Y_Scale_Factor"			// used for basic setup.
#define PARAM_NAME_SFX					"X_Scale_Factor"			// used for basic setup.
#define PARAM_NAME_ALGORITHM_SELECT		"Algorithm_Select"			// used for basic setup.
#define PARAM_NAME_SLY_WAKE_UP			"SLY"


#define PARAM_NAME_MODEL				"Model"
#define PARAM_NAME_LOT_NUMBER			"Lot"
#define PARAM_DUMMY						"NULL"
#define PARAM_RETRY_TIME				"RETRY_TIME"
#define PARAM_CLIENT_MODE				"CLIENT_MODE"

typedef struct tagDEFECT
{
	int			defect_class;
	float		x_pos;
	float		y_pos;
	float		size_x;
	float		size_y;
	char		filename[MAX_BADIMAGE_FILENAME];
}DEFECT;

class CPacket  
{
public:
	CPacket();
	virtual ~CPacket();

	// 수신시에 코드값만 일단 분해.
	int		GetCode(char* buf, int buf_len);
	//----------------------------------------------------------------------------------------------------------------------------------------------

	// Client -> Server
//	void	MakeDataPacket(int frame_num, int defect_cnt, int* defect_class, float* defect_x, float* defect_y, float* size_x, float* size_y, char** defect_image);
	void	MakeDataPacket(int frame_num, int defect_cnt,int lotNo, int* defect_class, float* defect_x, float* defect_y, float* size_x, float* size_y, char** defect_image);
	// Server에서 받은 데이터 분해.
	void	PullDataPacket(char* buf, int buf_len, int& code, int& frame_num, int& defect_cnt);
	//----------------------------------------------------------------------------------------------------------------------------------------------

	// Client -> Server
	void	MakeCalibPacket(int avg_luminousity, int detection_frame, int x_pos_in_pixel, int y_pos_in_pixel);
	// 서버에서 받은 캘리브레이션 데이터 분해. 
	void	PullCalibPacket(char* buf, int buf_len, int& code, int &avg_luminousity, int &detection_frame, int& x_pos_in_pixel, int& y_pos_in_pixel);
	//----------------------------------------------------------------------------------------------------------------------------------------------

	//	Server -> Client
	void	MakeInstantPacket(int code, LPCSTR param_name, double val);
	void	MakeInstantPacket(int code, LPCSTR param_name, LPSTR str_val, int len);
	//  Client에서 데이터 분해.
	void	PullInstantPacket(char* buf, int buf_len, int& code, LPSTR &param_name, double &val, LPSTR &str_val);
	//----------------------------------------------------------------------------------------------------------------------------------------------
	
	char*	m_pBuf;
	int		m_nBuflen;

	int		m_nFull_packet_length;
	int		m_nPacket_code;
	int		m_nFrame_num;
//	int		m_nPacket_type;

	int		m_nDefect;
	DEFECT	*m_pDefect_data;
protected:

};

#endif // !defined(AFX_PACKET_H__0086D72B_3BA5_46C1_A01B_A01D89AD6CDC__INCLUDED_)
