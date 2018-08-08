
#pragma once


#include "Device.h"


#define MAX_DEV_CONNECT	8


namespace device
{
	typedef struct tagCONN_INFO {
		tagCONN_INFO()
		{
			dwDevInst = NULL;
			uState = 0;
		}

		DWORD dwDevInst;
		UINT  uState;
	} CONN_INFO;


	enum CONN_INFO_STATE {
		CI_MOUNT	= 1U,
		CI_CONNECT	= 2U,
		CI_REMOVE	= 4U,
		CI_EJECT	= 8U
	};


	class CUsbControl : public CDeviceControl
	{
	public:

		CUsbControl(void)
		{
			m_cpGuid	  = &GUID_DEVCLASS_USB;
			m_uMountCnt	  = 0;
			m_uWaitDevIdx = MAX_DEV_CONNECT;
			m_bRemoveFlag = FALSE;
		}

		void Enable(void);
		void Remove(void);
    
		DEVICE_STATE EnumDevice(LPARAM IN lParam = NULL);

		void ClearState(CONN_INFO_STATE ciState);


	protected:

		virtual DEVICE_STATE EnumProc(PCONN_DEV IN OUT pConnDev, LPARAM IN OUT lParam);


	private:

		UINT m_uMountCnt;
		UINT m_uWaitDevIdx;
		BOOL m_bRemoveFlag;
    
		CONN_INFO m_aConnInfo[MAX_DEV_CONNECT];


		DEVICE_STATE ClearUnmount(void);
		UINT Find(DWORD IN dwDevInst);
	};
}
