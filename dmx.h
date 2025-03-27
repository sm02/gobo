#ifndef DMX_H
#define DMX_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class Dmx : QObject
{
    Q_OBJECT

public:
    Dmx();
    ~Dmx();
    bool init(QString dmxGatewayAddress, quint16 base);
    bool sendFrame();
    void setValue(int offset, unsigned char value);
private:
    QUdpSocket* udpSocket;
    QString mDmxGatewayAddress;
    QHostAddress mGateway;
    quint16 mGatewayPort;
    quint16 mBaseAdr;
    QByteArray mDmxFrame;
};

#endif // DMX_H
