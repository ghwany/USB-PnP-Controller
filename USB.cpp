
#include "stdafx.h"
#include "USB.h"


#define CHECK_STATE CHECK_BIT


using namespace device;


DEVICE_STATE CUsbControl::EnumDevice
(
	LPARAM lParam
)
{
	DEVICE_STATE dsRet = DV_DEFAULT;

	ClearState(CI_MOUNT);

	dsRet = CDeviceControl::EnumDevice(lParam);

	if (m_bRemoveFlag || (dsRet == DV_DEFAULT)) {
		dsRet = ClearUnmount();
	}

	return dsRet;
}


DEVICE_STATE CUsbControl::EnumProc
(
	PCONN_DEV	pConnDev,
	LPARAM		lParam
)
{
	TCHAR szBuf[20] = { NULL, };
	DWORD dwSize = 20, dwDataT = NULL;
	DEVICE_STATE dsRet = DV_DEFAULT;


	SetupDiGetDeviceRegistryProperty(pConnDev->hInfo, pConnDev->pInfoData,
		SPDRP_SERVICE,
		&dwDataT, (PBYTE)szBuf, dwSize, &dwSize);

	if (_tcsicmp(szBuf, L"USBSTOR") != ERROR_SUCCESS) {
		return DV_DEFAULT;
	}

	UINT uIdx = Find(pConnDev->pInfoData->DevInst);

	if (uIdx == MAX_DEV_CONNECT) {
		ChangeState(DICS_STOP, pConnDev);
		
		if (m_uMountCnt < MAX_DEV_CONNECT) {
			if (m_uWaitDevIdx == MAX_DEV_CONNECT) {
				m_uWaitDevIdx = m_uMountCnt;
			}

			m_aConnInfo[m_uMountCnt].uState |= CI_MOUNT;
			m_aConnInfo[m_uMountCnt].dwDevInst = pConnDev->pInfoData->DevInst;
			++m_uMountCnt;
			dsRet = DV_MOUNT;
		}
	} else {
		m_aConnInfo[uIdx].uState |= CI_MOUNT;

		if (!CHECK_STATE(m_aConnInfo[uIdx].uState, CI_CONNECT)) {
			ChangeState(DICS_STOP, pConnDev);
		}
	}

	return dsRet;
}


void CUsbControl::Enable()
{
	if (m_uWaitDevIdx == MAX_DEV_CONNECT) {
		return;
	}

	PCONN_DEV pConnDev = new CONN_DEV;
	
	if (Attach(pConnDev) != NO_ERROR) {
		return;
	}
	
	for (UINT i = 0; SetupDiEnumDeviceInfo(pConnDev->hInfo, i, pConnDev->pInfoData); ++i) {
		if (pConnDev->pInfoData->DevInst == m_aConnInfo[m_uWaitDevIdx].dwDevInst) {
			ChangeState(DICS_START, pConnDev);
#ifndef _WIN64
			m_aConnInfo[m_uWaitDevIdx].uState |= (CI_CONNECT + CI_EJECT);
#else
			m_aConnInfo[m_uWaitDevIdx].uState |= CI_CONNECT;
#endif
			m_uWaitDevIdx = MAX_DEV_CONNECT;
			break;
		}
	}

	Detach(pConnDev);
}


void CUsbControl::Remove()
{
	if (m_uWaitDevIdx == MAX_DEV_CONNECT) {
		return;
	}

	m_aConnInfo[m_uWaitDevIdx].uState |= CI_REMOVE;
	m_uWaitDevIdx = MAX_DEV_CONNECT;
	m_bRemoveFlag = TRUE;
}


UINT CUsbControl::Find
(
	DWORD dwDevInst
)
{
	UINT uIdx = MAX_DEV_CONNECT;

	for (UINT i = 0; i < m_uMountCnt; ++i) {
		if (dwDevInst == m_aConnInfo[i].dwDevInst) {
			uIdx = i;
			break;
		}
	}

	return uIdx;
}


DEVICE_STATE CUsbControl::ClearUnmount(void)
{
	DEVICE_STATE dsRet = DV_DEFAULT;

	for (UINT i = 0; i < m_uMountCnt; ++i) {
		if (!CHECK_STATE(m_aConnInfo[i].uState, CI_MOUNT)) {
#ifndef _WIN64
			if (CHECK_STATE(m_aConnInfo[i].uState, CI_EJECT)) {
				continue;
			}
#endif
			if (CHECK_STATE(m_aConnInfo[i].uState, CI_REMOVE)) {
				dsRet = DV_REMOVE;
				m_bRemoveFlag = FALSE;
			} else if (!m_bRemoveFlag) {
				dsRet = DV_UNMOUNT;
			}

			if (CHECK_STATE(m_aConnInfo[i].uState, CI_CONNECT)) {
				dsRet = DV_DISCONNECT;
			}

			--m_uMountCnt;

			for (UINT j = i; j < m_uMountCnt; ++j) {
				m_aConnInfo[j] = m_aConnInfo[j + 1];
			}

			m_aConnInfo[m_uMountCnt].dwDevInst = NULL;
		}
	}

	return dsRet;
}


void CUsbControl::ClearState
(
	CONN_INFO_STATE ciState
)
{
	for (UINT i = 0; i < m_uMountCnt; ++i) {
		m_aConnInfo[i].uState &= ~ciState;
	}
}
