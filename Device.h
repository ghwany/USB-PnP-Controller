
#pragma once


#include <SetupAPI.h>


#pragma comment(lib, "setupapi.lib")


#define INSTANCEID_MAXSIZE	50
#define DEVICEID_MAXSIZE	31

#define CHECK_BIT(_value, _bit) ((_value & _bit) == _bit)

// USB 장비의 GUID값 입니다.
DEFINE_GUID(GUID_DEVCLASS_USB, 0x36fc9e60L, 0xc465, 0x11cf, 0x80, 0x56, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);


namespace device {
	// 장치상태 ENUM
	enum DEVICE_STATE {
		DV_DEFAULT	= 0x0000,
		DV_MOUNT	= 0x0001,
		DV_UNMOUNT	= 0x0002,
		DV_REMOVE	= 0x0012,
		DV_DISCONNECT = 0x0022
	};

	typedef struct tagEXC_LISTW {
		TCHAR szHardwareId[DEVICEID_MAXSIZE];
		TCHAR szReqDate[11];
		TCHAR szDesc[131];
		BYTE  uState;
	} EXC_LISTW, *PEXC_LISTW;

	typedef struct tagEXC_INFO {
		ULONG		ulSize;
		PEXC_LISTW	pExcList;
		UINT		uPolicy;
	} EXC_INFO, *PEXC_INFO;

	typedef struct tagCONNECT_DEV {
		HDEVINFO hInfo;
		PSP_DEVINFO_DATA pInfoData;
	} CONN_DEV, *PCONN_DEV;


	class CDeviceControl
	{
	public:

		CDeviceControl()
		{
			m_cpGuid = NULL;
		}


	protected:

		// 장치의 GUID
		// 자식클래스에서 추가로 초기화합니다.
		const GUID *m_cpGuid;


		// 선택한 장치의 상태를 설정합니다.
		BOOL ChangeState(DWORD IN dwState, PCONN_DEV IN OUT pConnDev);
		// 장치정보에 접근하기 위해 핸들에 등록합니다.
		// 등록하기 전 pConnDev에 메모리가 할당되어 있어야 합니다.
		LSTATUS Attach(PCONN_DEV OUT pConnDev);
		// 연결된 장치를 분리합니다.
		void Detach(PCONN_DEV IN pConnDev = NULL);
		// 장치열거 함수입니다.
		DEVICE_STATE EnumDevice(LPARAM IN OUT lParam = NULL);
		// 장치열거 함수에서 수행할 일을 여기에 구현합니다.
		virtual DEVICE_STATE EnumProc(PCONN_DEV IN OUT pConnDev, LPARAM IN OUT lParam) = 0;
	};
}
