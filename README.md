# USB-Access-Control


윈도우 환경에서 USB를 인식하기 전에 사용 여부를 선택할 수 있습니다.


In a Windows environment, you can choose whether to use the USB before it is recognized.



## MFC에서 사용 가능합니다.

## Used to MFC


1. 'TestDlg.cpp'에 있는 'OnDeviceChange', 'RegisterForDeviceNotification' 함수를 참고하세요.


Refer the function 'OnDeviceChange', 'RegisterForDeviceNotification' in 'TestDlg.cpp'.


2. 'USB.cpp'에 있는 'CUsbControl' 클래스를 사용하여 USB를 제어할 수 있습니다.


The USB can be controlled using the 'CUsbControl' class located in 'USB.cpp'.


3. 'CUsbControl'은 'Dlg'안에서 사용되기 때문에 'Dlg' 멤버변수로 선언하여 사용해야 합니다.


Since 'CUsbControl' is used within 'Dlg', it must be declared as a 'Dlg' member variable.




### 장치 허용<br>Device Enable
```c++
m_UsbControl.Enable();
```



### 장치 제거<br>Device Remove
```c++
m_UsbControl.Remove();
```



