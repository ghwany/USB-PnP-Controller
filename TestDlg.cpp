
#include "stdafx.h"
#include "USBw.h"
#include "USBwDlg.h"
#include "MsgboxDlg.h"
#include "afxdialogex.h"
#include <Dbt.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUSBwDlg::CUSBwDlg(CWnd* pParent /*=NULL*/)
    : CDlgDraw(CUSBwDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_bShowWndFlag = FALSE;
}


void CUSBwDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUSBwDlg, CDialogEx)
    ON_WM_DEVICECHANGE()
    ON_WM_DESTROY()
END_MESSAGE_MAP()


BOOL CUSBwDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    return TRUE;
}


void CUSBwDlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    UnregisterDeviceNotification(m_hDevNotify);
}


void CUSBwDlg::RegisterForDeviceNotification()
{
    DEV_BROADCAST_DEVICEINTERFACE devInterface;
    devInterface.dbcc_size = sizeof(devInterface);
    devInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    devInterface.dbcc_classguid = GUID_DEVCLASS_USB;
    m_hDevNotify = RegisterDeviceNotification(m_hWnd, &devInterface, DEVICE_NOTIFY_WINDOW_HANDLE);
}


BOOL CUSBwDlg::OnDeviceChange
(
    UINT      nEventType,
    DWORD_PTR dwData
)
{
    if (nEventType == DBT_DEVNODES_CHANGED) {
        DWORD dwRet = m_UsbCtrl.EnumDevice();
        
        if (dwRet == device::DV_MOUNT) {
            // USB를 PC에 장착했을 때 수행할 역할
        } else if (dwRet & device::DV_UNMOUNT) {
            // USB를 탈착했을 때 수행할 역할
            
            if (dwRet == device::DV_REMOVE) {
                // USB를 m_UsbCtrl.Remove()로 장치를 탈착했을 때 수행할 역할
            }
        }
    }
    else if (nEventType == DBT_DEVICEARRIVAL) {
#ifndef _WIN64
        m_UsbCtrl.ClearState(device::CI_EJECT);
        // 윈도우 64bit 환경에서 장치 Eject 됐을 때 장치 정보 초기화
        // 탈착했을 때와 같은 소스를 여기에 구현하세요.
#endif
    }
    
    return TRUE;
}

