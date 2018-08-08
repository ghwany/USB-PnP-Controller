
#pragma once


#include "Usb.h"
#include "afxwin.h"


class CTestDlg : public CDialogEx
{
public:

    CTestDlg(CWnd* pParent = NULL);

    enum { IDD = IDD_TEST_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    
    HICON m_hIcon;

    DECLARE_MESSAGE_MAP()
    afx_msg void OnDestroy();
    afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);

    virtual BOOL OnInitDialog();
    virtual void RegisterForDeviceNotification();

private:
    HDEVNOTIFY m_hDevNotify;
    device::CUsbControl	m_UsbCtrl;
    
    
public:
};
