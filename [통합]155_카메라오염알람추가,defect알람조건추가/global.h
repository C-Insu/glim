// Global.h

#define MOD_COUNT	8

#define MAX_LENGTH	20

#define	MAX_FRAME	6
#define METER_10	10
#define METER_100	100
#define METER_1		1

#define MAGIMAGE_X	400
#define MAGIMAGE_Y	300


#define PI					3.141592653589793
//--Display Size
#define FORM_IMG_WIDTH			950
#define FORM_IMG_HEIGHT			950

#define BAD_IMG_WIDTH			128
#define BAD_IMG_HEIGHT			128

#define EDGE_IMG_WIDTH			128
#define EDGE_IMG_HEIGHT			128

#define	MAX_ROI					10

#define HDD_PERCENTAGE_LIMIT	10

//--Display Position
#define DEFAULT_POSITION

#define MAX_BADIMAGE_FILENAME	100

#define		MAX_INSPECT_COUNT	10

//--Vision Board
#define MATROX_SOLIOS
//#define MATROX_CL

//--Camera
#define DALSA_2K_LINESCAN
//#define DALSA_1K_LINESCAN
//#define AVIIVA_2K_LINESCAN
//#define AVIIVA_1K_LINESCAN

//--DCF 
#define DCF_FILE				"C:\\Glim\\Glim.dcf"
#define DCF_FILE1			"C:\\Glim\\Glim1.dcf"
#define DCF_FILE2			"C:\\Glim\\Glim2.dcf"

//--Parameter
#define PARAMETER_PATH			"C:\\Glim\\parameter.ini"
#define SHUTTER_PATH			"C:\\Glim\\Gradeparameter.ini"
#define PATH_HISTO_EQUA			"c:\\Glim\\HistoEqua.lut"

//LogData Path
#define PATH_LOG_GRABPROCESS	"c:\\Glim\\LogGrab"
#define PATH_LOG_PACKET			"c:\\Glim\\LogPacket"

#define PATH_IMAGE_EXT				"D:\\Image\\"
#define PATH_IMAGE_EXT1				"D:\\Image1\\"
#define PATH_IMAGE_INSIDE			"C:\\Glim\\Image\\"

#define PATH_DEBUG_LOG			"C:\\LOG\\"


//define Color
#define COLOR_BLACK		RGB(0,0,0)
#define COLOR_TOP_BK	RGB(128,128,255)
#define COLOR_GREEN		RGB(0,255,0)
#define COLOR_RED		RGB(255,0,0)
#define COLOR_BLUE		RGB(0,0,255)
#define COLOR_YELLOW	RGB(255,255,0)
#define	COLOR_WHITE		RGB(255,255,255)
#define COLOR_ORANGE	RGB(255,153,51)
#define COLOR_ORANGE1	RGB(204,102,0)
#define COLOR_ORANGE2	RGB(255,102,0)
#define COLOR_GRAY		RGB(128,128,128)
#define COLOR_GRAY_WHITE1	RGB(192,192,192)


//////////////////////////��ǰ�� Į��
#define COLOR_NULLING1		RGB(204,102,0)	//�ݻ� ����
#define COLOR_NULLING2		RGB(255,255,255)	//���� ���
#define COLOR_COATING		RGB(0,0,0)	//��
#define COLOR_INSULATE		RGB(255,255,0)	//���� ���


#define COLOR_OK		RGB(0,255,0)
#define COLOR_NG		RGB(255,0,0)



//define MAX_buffer
#define MAX_BUFFER		2	//10
#define MAX_DEFECT		10	//10	//15	//chcho
#define MAX_REALDEFECT	16	//4x4 mesh �� 1ea
#define MAX_REALDEFECTNEW	40
#define MAX_DEFECT_COUNT 10		//200625 kjh


#define SKIP_AREA_X		256
#define SKIP_AREA_Y		256
#define SKIP_AREA		512

#define MAX_CAMERAS		3	//2

#define MAX_COMMUTYFRAME	5	//10


//define Com
#define GL1			0	//hitachi area cross
#define GL2			1	//���ݻ�
#define GL3			2	//���� ���ν�ĵ
#define GL4			3	//������,						������
#define GL5			5	//�̺йݻ�,					������ݻ�
#define GL6			6	//���ݻ�,						����Ĺݻ�
#define GL7			7	//������a
#define GL8			8	//Area Slit
#define GL9			9	//Gigan Lan Camera Cross,		ũ�ν�����
#define GLB			4	//2D Barcode
#define GLCIS			11	//2D Barcode

//#define NEL1			0	//hitachi area cross
//#define NEL2			1	//���ݻ�
//#define NEL3			2	//���� ���ν�ĵ
//#define NEL5			5	//�̺йݻ�
//#define NEL7			7	//������a
//#define NEL8			8	//Area Slit
//#define NEL9			9	//Gigan Lan Camera Cross
//#define NEB				4	//2D Barcode

#define	CAM_PATIAL		320	//320
#define CAM_PATIAL_FRAME	3//2//1//2//1
 
#define CAM_WIDTH_4096	4096
#define CAM_WIDTH_8192	8192
#define CAM_WIDTH_16384	16384
#define CAM_WIDTH_2048	2048
#define CAM_HEIGHT_4096	4096
#define CAM_HEIGHT_8192	8192
#define CAM_HEIGHT_2048	2048
#define CAM_HEIGHT_3072	3072


#define CAM_WIDTH_CIS	7296 //7320 //7296	 
#define CAM_HEIGHT_CIS	3072

#define CAM_FULL_WIDTH_CIS	CAM_WIDTH_CIS*3

//#define IMAGE_X			4096//8192	//4096
//#define IMAGE_Y			2048
#define MAX_IMG_WIDTH	IMAGE_X
#define	CAM_WIDTH		2048		//2048
#define	CAM_HEIGHT		CAM_PATIAL*CAM_PATIAL_FRAME

//#define	CAM_HEIGHT_2048		2048
//#define	CAM_HEIGHT_4096		4096

#define	UM_GRID_DBCLIK		WM_USER+1
#define UM_GRID_EDIT_END	WM_USER+2
#define UM_GRID_CLICK		WM_USER+3
#define UM_GRID_ENDSELECT	WM_USER+4
#define UM_GRID_COMMAND		WM_USER+5

#define WM_RECEIVE			WM_USER+6
#define WM_SENDDONE			WM_USER+7
#define WM_DISCONNECTED		WM_USER+8
#define WM_ACCEPT			WM_USER+9
#define WM_SIMULATE			WM_USER+10
#define	WM_CONNECT			WM_USER+11
#define	WM_SHUTTER			WM_USER+12
#define	WM_CAMYPOS			WM_USER+13
#define WM_RESTART			WM_USER+14
#define WM_SIMULATEMARK		WM_USER+15
#define WM_SIMULATE1		WM_USER+16	//���cross
#define WM_SIMULATEMARK1		WM_USER+17

#define		WM_UPDATEDLG	WM_USER+23	//dlg Updatedata

//�ҷ� Ÿ�Կ� ���� �з� ����
#define DT_DOT				0x00000001	//�ҷ� ���°� ���� ���			AG����,SENI
#define DT_LINE				0x00000002	//�ҷ� ���°� ���� ���			�����׽���,�÷ν���,���ڷ�����,��ν���,AG����
#define DT_CIRCLE			0x00000004	//�ҷ� ���°� ���� ���			������,���ڷ�,��δ���,AG����	
#define DT_WHITE			0x00000008	//�ҷ��� ����� ���[TRUE]		�̺����� : AG����,SENI,������,���ڷ�,�����׽���,�÷ν���,���ڷ�����
										//�ҷ��� ����� ���[FALSE]		�̺����� : ��δ���,AG����,��ν���,AG����
										//								���������� ��� �ݴ�, AG�⽺�� ������ ������ ����

#define DT_MURA				0x00000010	//�ҷ��� ������ ���
#define DT_YOKODAN			0x00000020	//�ҷ��� ���ڴ��� ���

//-------------------------------------------------
#include "Shutdown_Library.h"
#include "SystemClock.h"
//-------------------------------------------------



//udp network
#define		DEFAULT_PORT		10000
#define		MARKING_PORT		20000
#define		NEB_PORT			8000
#define		WM_XDATARRECIEVED	(WM_USER+100+2)
//-------------------------------------------------
//packet data
#define		PD_LEN			30		//charactor Length
#define		PD_FRAME		300		//frame
//-------------------------------------------------

#define		CROSSLINE		320		//Cross Image merging Line
#define		CROSSIMGCOUNT	2

#define		DCLASS_NEL9_SPOT			0x0101	//���� 257
#define		DCLASS_NEL9_KUNIC			0x0102	//��� 258
#define		DCLASS_NEL9_LOW_SPOT		0x10101
#define		DCLASS_NEL9_LOW_KUNIC		0x10102
#define		DCLASS_NEL9_SCRATCH			0x0103	//��ŹScratch
#define		DCLASS_NEL9_CYCLE			0x01000	

////////////////////////////////////////////////////////////Mismatch Code
#define		LCLASS_TOP_EDGE						601
#define		LCLASS_TOP_WB							602
#define		LCLASS_TOP_BW							603
#define		LCLASS_TOP_DUMMY					604

#define		LCLASS_BOTTOM_EDGE				611
#define		LCLASS_BOTTOM_WB					612
#define		LCLASS_BOTTOM_BW					613
#define		LCLASS_BOTTOM_DUMMY			614
////////////////////////////////////////////////////////////Mismatch Code


#define		DCLASS_NEL8_PUSHIMUL		0x0801	//�̹�����
#define		DCLASS_NEL8_LOW_PUSHIMUL	0x1801

#define		DCLASS_NEL5_PIMUL			0x0501	//���̹�
#define		DCLASS_NEL5_LOW_PIMUL		0x10501
#define		DCLASS_NEL5_LIMUL			0x0502	//���̹�
#define		DCLASS_NEL5_LOW_LIMUL		0x10502
#define		DCLASS_NEL5_CIMUL			0x0503	//���̹�
#define		DCLASS_NEL5_LOW_CIMUL		0x10503
#define		DCLASS_NEL5_SCRATCH			0x05000	//0x0504	//��ũ��ġ
#define		DCLASS_NEL5_LOW_SCRATCH		0x10504

//ĳ���� 1ȣ��, 2ȣ��
#define		DCLASS_GBR_PIMUL			0x0307	//��Ȧ//��ȦS
#define		DCLASS_GBR_LOW_PIMUL		0x10307
#define		DCLASS_GBR_LIMUL			0x0302	//�̹�
#define		DCLASS_GBR_LOW_LIMUL		0x10302
#define		DCLASS_GBR_CIMUL			0x0303	//����
#define		DCLASS_GBR_LOW_CIMUL		0x10303
#define		DCLASS_GBR_SCRATCH			0x0304	//��ħ
#define		DCLASS_GBR_LOW_SCRATCH		0x10304
#define		DCLASS_GBR_CYCLE			0x03000	//0x0605	
#define		DCLASS_GBR_FMARK			0x0306
#define		DCLASS_GBR_PINHOLE_L		0x0301	//����//��Ȧ��1//��ȦL
#define		DCLASS_GBR_LOW_PINHOLE_L	0x10301	//������
#define		DCLASS_GBR_PINHOLE_C_L		0x0308	//���ĵ����̹�
#define		DCLASS_GBR_LOW_PINHOLE_C_L	0x10308	//���ĵ����̹�
#define		DCLASS_GBR_PINHOLE_BIT		0x0310	//�����
#define		DCLASS_GBR_LOW_PINHOLE_BIT	0x10310	//�����

#define		DCLASS_GBR_BACKDENT			0x0311	//�ĸ鵹��
#define		DCLASS_GBR_WATERDROP		0x0312	//�����

#define		DCLASS_GBR_GROUP_PINHOLE		0x0313	//������Ȧ



#define		DCLASS_GSR_SCRATCH			0x0201	//scratch
#define		DCLASS_GSR_LOW_SCRATCH		0x10201
#define		DCLASS_GSR_CIMUL			0x0202	//dye-spot  514
#define		DCLASS_GSR_LOW_CIMUL		0x10202
#define		DCLASS_GSR_PIMUL			0x0203	//ds ���� ������
#define		DCLASS_GSR_LOW_PIMUL		0x10203  //�̻��
#define		DCLASS_GSR_LIMUL			0x0204	//��ħ
#define		DCLASS_GSR_LOW_LIMUL		0x10204
#define		DCLASS_GSR_NOTDRY			0x0205	//�� ����
#define		DCLASS_GSR_SKIP				0x0210	//SKIP	(0.1���ϰ� �ټ��϶�)	//170307	bh
#define		DCLASS_GSR_CYCLE			0x04000	//0x0405	
#define		DCLASS_GSR_FMARK			0x0406	//F- Mark

#define		DCLASS_GSR_NOTCOATING		0x0206	//������
#define		DCLASS_GSR_SURFACE_DEFECT	0x0207	//ǥ���̹�
#define		DCLASS_GSR_LOW_SURFACE_DEFECT	0x10207	//ǥ���̹�


//�̰����ҷ�
#define		DCLASS_NEL7_PIMUL			0x0201
#define		DCLASS_NEL7_LOW_PIMUL		0x10201
#define		DCLASS_NEL7_LIMUL			0x0202
#define		DCLASS_NEL7_LOW_LIMUL		0x10202
#define		DCLASS_NEL7_CIMUL			0x0203
#define		DCLASS_NEL7_LOW_CIMUL		0x10203
#define		DCLASS_NEL7_SCRATCH			0x0204
#define		DCLASS_NEL7_LOW_SCRATCH		0x10204
#define		DCLASS_NEL7_CYCLE			0x2000	//0x0705

#define		DCLASS_NEL3_PIMUL			0x0301	//���̹�	//769	//����
#define		DCLASS_NEL3_LOW_PIMUL		0x10301
#define		DCLASS_NEL3_LIMUL			0x0302	//���̹�	//770	//�̹�
#define		DCLASS_NEL3_LOW_LIMUL		0x10302
#define		DCLASS_NEL3_CIMUL			0x0303	//���̹�
#define		DCLASS_NEL3_LOW_CIMUL		0x10303
#define		DCLASS_NEL3_SCRATCH			0x0304	//��ũ��ġ
#define		DCLASS_NEL3_LOW_SCRATCH		0x10304
#define		DCLASS_NEL3_CYCLE			0x03000	//0x0605	


// 0x3xxx �ְ�. xxx = Roll Pi
#define		DCLASS_DEFAULT_CYCLE		3000
#define		MAX_CYCLE_COUNT				14	//15	15���� ���� ����. ������

#define		MAXLIGHTCOUNT	2//12
#define		DEFAULTPORT		7	//4	//6
#define		PARAMETER_PATH1			"C:\\Glim\\Visweb.ini"
#define	CYCLELENGTH		10000

#define WIDTH			CAM_WIDTH	//1392	// ���� Areaī�޶�� Grab�ϴ� ũ�� X
#define HEIGHT			CAM_PATIAL*CAM_PATIAL_FRAME//320
#define	NUM_BUFFERS		CAM_PATIAL_FRAME//1	//CAM_PATIAL_FRAME	//1


#define LIGHT_COM			"COM7"			//���� com port


// ENG/KOR
#define ENG	1
#define KOR 0 

// parameter send & receive
#define MAX_NUM_SERVER_PARAM 80
#define WM_TIMER_CHECK_SERVER_INI_RECEIVE 200
#define FOLDER_PATH_SERVER_PARAMETER _T("D:\\Data\\Parameter")
#define FOLDER_PATH_SERVER_INI_CHECK FOLDER_PATH_SERVER_PARAMETER _T("\\Check")
#define FOLDER_PATH_SERVER_INI FOLDER_PATH_SERVER_PARAMETER _T("\\INI")
static CString g_strServerParamName_KOR[MAX_NUM_SERVER_PARAM] = {
	"��ȦValue",
	"��ȦSize X",
	"��ȦSize Y",
	"����Value",
	"����Size X",
	"����Size Y",
	"���ú�����Value",
	"���ú�����Size X",
	"���ú�����Size Y",
	"ǥ�� �ҷ�Value",
	"ǥ�� �ҷ�Size X",
	"ǥ�� �ҷ�Size Y",
	"��ȭ��Value",
	"��ȭ��Size X",
	"��ȭ��Size Y",
	"��Ȧ�� ��ȭ��Value",
	"��Ȧ�� ��ȭ��Size X",
	"��Ȧ�� ��ȭ��Size Y",
	"��� ���κҷ�Value",
	"��� ���κҷ�Size X",
	"��� ���κҷ�Size Y",
	"���κҷ�Value",
	"���κҷ�Size X",
	"���κҷ�Size Y",
	"�Ŵ���κҷ�Value",
	"�Ŵ���κҷ�Size X",
	"�Ŵ���κҷ�Size Y",
	"���ú� �ָ�Value",
	"���ú� �ָ�Size X",
	"���ú� �ָ�Size Y",
	"�� �ָ�Value",
	"�� �ָ�Size X",
	"�� �ָ�Size Y",
	"����Value",
	"����Size X",
	"����Size Y",
	"ũ��Value",
	"ũ��Size X",
	"ũ��Size Y",
	"�����úҷ�Value",
	"�����úҷ�Size X",
	"�����úҷ�Size Y",
	"���Ϸ���Value",
	"���Ϸ���Size X",
	"���Ϸ���Size Y",
	"�ָ�Value",
	"�ָ�Size X",
	"�ָ�Size Y",
	"DragValue",
	"DragSize X",
	"DragSize Y",
	"Scale Xmm",
	"Scale Ymm",
	"���� THValue",
	"���� 1min",
	"���� 1max",
	"���� 1min",
	"���� 1max",
	"���� 2min",
	"���� 2max",
	"���� 2min",
	"���� 2max",
	"���� 3min",
	"���� 3max",
	"���� 3min",
	"���� 3max",
	"���� 4min",
	"���� 4max",
	"���� 4min",
	"���� 4max",
	"���� 5min",
	"���� 5max",
	"�̽���ġmin",
	"�̽���ġmax",
	"������Meter",
	"�̽���ġ ����Meter",
	"�����̹�Meter",
	"�����̹�EA",
	"�̹� ����Meter",
	"�̹� ����EA"
};

static CString g_strServerParamName_ENG[MAX_NUM_SERVER_PARAM] = {
	"Pinhole Value",
	"Pinhole Size X",
	"Pinhole Size Y",
	"Protrusion Value",
	"Protrusion Size X",
	"Protrusion Size Y",
	"Chipping Pinhole Value",
	"Chipping Pinhole Size X",
	"Chipping Pinhole Size Y",
	"Surface Defect Value",
	"Surface Defect Size X",
	"Surface Defect Size Y",
	"Crater Value",
	"Crater Size X",
	"Crater Size Y",
	"Pinhole Crater Value",
	"Pinhole Crater Size X",
	"Pinhole Crater Size Y",
	"Edge Line Value",
	"Edge Line Size X",
	"Edge Line Size Y",
	"Line Value",
	"Line Size X",
	"Line Size Y",
	"Big Line Value",
	"Big Line Size X",
	"Big Line Size Y",
	"Coating Wrinkle Value",
	"Coating Wrinkle Size X",
	"Coating Wrinkle Size Y",
	"Heating Wrinkle Value",
	"Heating Wrinkle Size X",
	"Heating Wrinkle Size Y",
	"Scratch Value",
	"Scratch Size X",
	"Scratch Size Y",
	"Crack Value",
	"Crack Size X",
	"Crack Size Y",
	"None Coating Value",
	"None Coating Size X",
	"None Coating Size Y",
	"Island Value",
	"Island Size X",
	"Island Size Y",
	"Wrinkle Value",
	"Wrinkle Size X",
	"Wrinkle Size Y",
	"Drag Value",
	"Drag Size X",
	"Drag Size Y",
	"Scale Xmm",
	"Scale Ymm",
	"Threshold Value",
	"Non-Coating1 min",
	"Non-Coating1 max",
	"Coating1 min",
	"Coating1 max",
	"Non-Coating2 min",
	"Non-Coating2 max",
	"Coating2 min",
	"Coating2 max",
	"Non-Coating3 min",
	"Non-Coating3 max",
	"Coating3 min",
	"Coating3 max",
	"Non-Coating4 min",
	"Non-Coating4 max",
	"Coating4 min",
	"Coating4 max",
	"Non-Coating5 min",
	"Non-Coating5 max",
	"Mismatch min",
	"Mismatch max",
	"Width Size NG Meter",
	"Mismatch NG Meter",
	"Non-Continuous Meter",
	"Non-Continuous Defect Count",
	"Continuous Meter",
	"Continuous Defect Count"
};

// ip
#define IP_ADDRESS_CMI_ANODE_SURFACE _T("100.0.0.31")
#define IP_ADDRESS_CMI_CATHODE_SURFACE _T("100.0.0.36")
#define IP_ADDRESS_OCH_ANODE_SURFACE_1 _T("100.0.0.46")
#define IP_ADDRESS_OCH_CATHODE_SURFACE_1 _T("100.0.0.41")
#define IP_ADDRESS_OCH_ANODE_SURFACE_2 _T("100.0.0.47")
#define IP_ADDRESS_OCH_CATHODE_SURFACE_2 _T("100.0.0.42")