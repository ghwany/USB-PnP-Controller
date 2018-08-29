# USB-Access-Control


윈도우 환경에서 USB를 인식하기 전에 사용 여부를 선택할 수 있습니다.


### MFC에서 사용 가능합니다.


1. **'TestDlg.cpp'** 에 있는 **'OnDeviceChange'** , **'RegisterForDeviceNotification'** 함수를 참고하세요.


2. **'USB.cpp'** 에 있는 **'CUsbControl'** 클래스를 사용하여 USB를 제어할 수 있습니다.


3. **'CUsbControl'** 은 **'Dlg'** 안에서 사용되기 때문에 **'Dlg'** 멤버변수로 선언하여 사용해야 합니다.


### 장치 허용
```cpp
m_UsbControl.Enable();
```


### 장치 제거
```cpp
m_UsbControl.Remove();
```
