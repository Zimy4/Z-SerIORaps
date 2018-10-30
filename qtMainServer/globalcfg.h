#ifndef GLOBALCFG_H
#define GLOBALCFG_H

#include <QString>
#include <QDataStream>

#define VERSION 0.1
#define BUILD_DATE 11112016

class CSettingsDevice {
public:
    CSettingsDevice(): _name(""), _baudRate(9600), _dataBits(8), _parity(0), _stopBits(1), _flowControl(0), _bIsOpen(false) {}
    CSettingsDevice(const QString &name, qint32 baudRate, qint32 dataBits, qint32 parity, qint32 stopBits, qint32 flowControl, bool IsOpen ) :
    _name(name), _baudRate(baudRate), _dataBits(dataBits), _parity(parity), _stopBits(stopBits), _flowControl(flowControl), _bIsOpen(IsOpen) {}

    CSettingsDevice& operator=(const CSettingsDevice &cfg)
    {
        if( this != &cfg)
        {
            this->_name = cfg._name;
            this->_baudRate = cfg._baudRate;
            this->_dataBits = cfg._dataBits;
            this->_parity = cfg._parity;
            this->_stopBits = cfg._stopBits;
            this->_flowControl = cfg._flowControl;
            this->_bIsOpen = cfg._bIsOpen;
        }
        return *this;
    }

    friend QDataStream &operator>>(QDataStream &stream, CSettingsDevice &A){
        stream >> A._name;
        stream >> A._baudRate;
        stream >> A._dataBits;
        stream >> A._parity;
        stream >> A._stopBits;
        stream >> A._flowControl;
        stream >> A._bIsOpen;
        return stream;
    }

    friend QDataStream &operator<<(QDataStream &stream, const CSettingsDevice &A){
        stream << A._name;
        stream << A._baudRate;
        stream << A._dataBits;
        stream << A._parity;
        stream << A._stopBits;
        stream << A._flowControl;
        stream << A._bIsOpen;
        return stream;
    }

public:
    QString _name;
    qint32 _baudRate;
    qint32 _dataBits;
    qint32 _parity;
    qint32 _stopBits;
    qint32 _flowControl;

/*    QSerialPort::DataBits _dataBits;
    QSerialPort::Parity _parity;
    QSerialPort::StopBits _stopBits;
    QSerialPort::FlowControl _flowControl;*/

    bool    _bIsOpen;

};



enum SERVER_MSG_CMD {
    cmdAutchReq = 1,    // Сообщение успешного соединения ( на самом деле можно все это делать на сервере и не сообщать )
    cmdGetDeviceParam,  // Запрос параметров устройства
    cmdSetDeviceParam,  // Установка параметров устройства
    cmdGetDeviceData,   // От устройства получены данные
    cmdSendDeviceData,  // Данные для устройства
    cmdGetDeviceList,   // Команда получения списка устройств    
    cmdMsgFromClient,   // Сообщение содержит сообщение от клиента
    cmdMsgInfoToClient, // Сообщение содержит сообщение для клиента
    cmdMsgErrorToClient,// Сообщение содержит сообщение об ошибке для клиента
    cmdFileFromClient  // Файл от клиента для передачи на устройство
    };

#endif // GLOBALCFG_H
