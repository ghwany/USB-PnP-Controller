
#include "stdafx.h"
#include "Device.h"


using namespace device;


/*///////////////////////////////////////////////////////////////////////////////////

	· 장치정보에 접근하기 위해 핸들을 등록합니다.
	· 열거전에 이 함수를 호출해야 합니다.
	· 모든 사용을 마친 후 Detach를 호출하여 리소스를 반환해야합니다.

/*///////////////////////////////////////////////////////////////////////////////////
LSTATUS CDeviceControl::Attach
(
	PCONN_DEV pConnDev
)
{
	LSTATUS lsRet = NO_ERROR;

	if (!pConnDev) {
		return lsRet;
	}

	pConnDev->hInfo = SetupDiGetClassDevs(m_cpGuid, 0, 0, DIGCF_PRESENT);

	if (pConnDev->hInfo == INVALID_HANDLE_VALUE) {
		Detach(pConnDev);
		return lsRet;
	}

	pConnDev->pInfoData = new SP_DEVINFO_DATA;
	
	if (!pConnDev->pInfoData) {
		Detach(pConnDev);
		return lsRet;
	}

	pConnDev->pInfoData->cbSize = sizeof(SP_DEVINFO_DATA);

	return lsRet;
}


/*///////////////////////////////////////////////////////////////////////////////////

	 · 장치열거를 사용한 후 리소스를 반환할 때 이 함수를 호출합니다.

/*///////////////////////////////////////////////////////////////////////////////////
void CDeviceControl::Detach
(
	PCONN_DEV pConnDev
)
{
	if (pConnDev) {
		if ((pConnDev->hInfo) &&
			pConnDev->hInfo != INVALID_HANDLE_VALUE) {
			SetupDiDestroyDeviceInfoList(pConnDev->hInfo);
			pConnDev->hInfo = NULL;
		}

		if (pConnDev->pInfoData) {
			delete pConnDev->pInfoData;
			pConnDev->pInfoData = NULL;
		}

		delete pConnDev;
		pConnDev = NULL;
	}
}


/*///////////////////////////////////////////////////////////////////////////////////

	 · 장치 사용/미사용으로 설정할 수 있습니다.
	 · DICS_START/DICS_STOP

/*///////////////////////////////////////////////////////////////////////////////////
BOOL CDeviceControl::ChangeState
(
	DWORD		dwState,
	PCONN_DEV	pConnDev
)
{
	BOOL				 bSuccess = TRUE;
	SP_PROPCHANGE_PARAMS param;


	param.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
	param.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;	// 속성 변경 함수를 사용
	param.Scope = DICS_FLAG_CONFIGSPECIFIC;	// 현재 지정 장치에만 적용
	param.StateChange = dwState;			// 장치 상태 변경
	param.HwProfile = 0;

	if (!SetupDiSetClassInstallParams(
		pConnDev->hInfo, pConnDev->pInfoData,
		(PSP_CLASSINSTALL_HEADER)&param, sizeof(param))) {
		bSuccess = FALSE;
	}

	// 변경내용 적용
	if (!SetupDiCallClassInstaller(
		DIF_PROPERTYCHANGE,
		pConnDev->hInfo, pConnDev->pInfoData)) {
		// 0xE0000235 64bit용 프로그램으로 재설치 후 사용
		// 0xE000020B 잘못된 핸들 값
		// 0xE0000215 잘못된 파라미터 값
		bSuccess = FALSE;
	}
	
	return bSuccess;
}


/*///////////////////////////////////////////////////////////////////////////////////

	 · 장치를 열거합니다.
	 · 열거 후 얻은 정보로 수행할 일은 EnumProc에 구현합니다.
		EnumProc은 CDeviceControl의 순수가상함수로 상속받은 자식클래스에서 추가로
		구현해야 합니다.

/*///////////////////////////////////////////////////////////////////////////////////
DEVICE_STATE CDeviceControl::EnumDevice
(
	LPARAM lParam
)
{
	PCONN_DEV	 pConnDev = new CONN_DEV;
	DEVICE_STATE dsRet = DV_DEFAULT;


	if (Attach(pConnDev) != NO_ERROR) {
		return DV_DEFAULT;
	}

	// 클래스 목록중 i번째 정보 저장
	for (UINT i = 0; SetupDiEnumDeviceInfo(pConnDev->hInfo, i, pConnDev->pInfoData); ++i) {
		DEVICE_STATE dvStt = EnumProc(pConnDev, lParam);

		if (dvStt != DV_DEFAULT) {
			dsRet = dvStt;
		}
	}

	Detach(pConnDev);

	return dsRet;
}
