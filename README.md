# USB-Access-Control
<br>
In a Windows environment, you can choose whether to use the USB before it is recognized.
<br>
윈도우 환경에서 USB를 인식하기 전에 사용 여부를 선택할 수 있습니다.<br>
<h3>Used to MFC
<br>
MFC에서 사용 가능합니다.</h3>
<br>
<br>
<h4>주의사항</h4>
TestDlg.cpp에 있는 OnDeviceChange, RegisterForDeviceNotification 함수를 참고하세요.<br>
USB.cpp의 CUsbControl 클래스를 사용하여 USB를 제어할 수 있습니다.<br>
CUsbControl은 Dlg안에서 사용되기 때문에 Dlg 멤버변수로 선언하여 사용해야 합니다.<br>

