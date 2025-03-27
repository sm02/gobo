#include "dmx.h"
#include <QCoreApplication>
#include <QHostInfo>

#define LONGUEUR_TRAME_DMX (512)
#define NB_MAX_PARAM (6)

QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}

Dmx::Dmx()
{
    mGateway.clear();
    mGatewayPort = 7755;
    udpSocket = nullptr;

    mDmxFrame.fill(0,NB_MAX_PARAM+2);
}

Dmx::~Dmx()
{
    if (udpSocket) delete udpSocket;
}

bool Dmx::init(QString dmxGatewayAddress, quint16 baseAdr)
// Ouvre la connexion
// Succès : renvoie true
// Echec : renvoie false
{    
    QHostInfo info = QHostInfo::fromName(dmxGatewayAddress);
    if (info.addresses().isEmpty()) {
        qDebug() << QString("Echec: l'adresse %1 ne peut être résolue.").arg(mDmxGatewayAddress);
        return false;
    }
    mBaseAdr = baseAdr;
    mGateway = info.addresses().first();
    udpSocket = new QUdpSocket();
    return true;
}

bool Dmx::sendFrame()
{
    if (mGateway.isNull()) {
        qStdOut() << "Connexion non initialisée."<< Qt::endl;
        return false;
    }
    mDmxFrame[0] = (mBaseAdr >> 8) & 0xff;
    mDmxFrame[1] = (mBaseAdr & 0xff);
    qint64 bytesSent = udpSocket->writeDatagram(mDmxFrame,mGateway,mGatewayPort);
    if (bytesSent != mDmxFrame.length()) {
        qStdOut() << "Echec d'envoi de la trame." << Qt::endl;
        return false;
    }
    return true;
}

void Dmx::setValue(int offset, unsigned char value) {
    if (offset<=NB_MAX_PARAM) mDmxFrame[offset+2]=value;
}
