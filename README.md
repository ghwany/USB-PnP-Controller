# USB-Access-Control
<br>
윈도우 환경에서 USB를 인식하기 전에 사용 여부를 선택할 수 있습니다.<br>
In a Windows environment, you can choose whether to use the USB before it is recognized.<br>
<h3>MFC에서 사용 가능합니다.<br>Used to MFC</h3>
<br>
1. 'TestDlg.cpp'에 있는 'OnDeviceChange', 'RegisterForDeviceNotification' 함수를 참고하세요.<br>
&nbsp;&nbsp;&nbsp;Refer the function 'OnDeviceChange', 'RegisterForDeviceNotification' in 'TestDlg.cpp'.<br>
2. 'USB.cpp'에 있는 'CUsbControl' 클래스를 사용하여 USB를 제어할 수 있습니다.<br>
&nbsp;&nbsp;&nbsp;The USB can be controlled using the 'CUsbControl' class located in 'USB.cpp'.<br>
3. 'CUsbControl'은 'Dlg'안에서 사용되기 때문에 'Dlg' 멤버변수로 선언하여 사용해야 합니다.<br>
&nbsp;&nbsp;&nbsp;Since 'CUsbControl' is used within 'Dlg', it must be declared as a 'Dlg' member variable.<br>
<br>
<h3>장치 허용<br>Device Enable</h3>
m_UsbControl.Enable();<br>
<br>
<h3>장치 제거<br>Device Remove</h3>
m_UsbControl.Remove();<br>
<br>
