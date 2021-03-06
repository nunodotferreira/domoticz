#pragma once

#include "DomoticzHardware.h"
#include "ASyncSerial.h"
#include <iosfwd>

enum _eDenkoviUSBDevice
{
	DDEV_USB_16R = 0,						//0
	DDEV_USB_16R_Modbus,						//1
	DDEV_DAEnet_IP40
};

class CDenkoviUSBDevices : public CDomoticzHardwareBase, AsyncSerial
{
public:
	CDenkoviUSBDevices(const int ID, const std::string& comPort, const int model);
	~CDenkoviUSBDevices(void);
	bool WriteToHardware(const char *pdata, const unsigned char length) override;
private:
	void Init();
	bool StartHardware() override;
	bool StopHardware() override;
	void Do_Work();
	void GetMeterDetails();
	void readCallBack(const char * data, size_t len);
private:
	std::string m_szSerialPort;
	int m_baudRate;
	int m_pollInterval;
	volatile bool m_stoprequested;
	int m_iModel;
	std::shared_ptr<std::thread> m_thread;
	//boost::shared_ptr<boost::thread> m_thread;
	int m_Cmd;
	bool readingNow = false;
	bool updateIo = false;

protected:
	void OnData(const unsigned char *pData, size_t length);
	void OnError(const std::exception e);
};
