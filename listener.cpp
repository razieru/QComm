#include "listener.h"
#include <QDebug>

Listener::Listener(QObject *parent) : QObject(parent)
{
	connect(&sucker, SIGNAL(readyRead()), SLOT(readyRead()));
	connect(&sucker, SIGNAL(disconnected()), SLOT(disconnected()));
}

const QString &Listener::getHost() const
{
	return host;
}

void Listener::setHost(const QString &newHost)
{
	if (host == newHost)
		return;
	host = newHost;
	emit hostNotify();
}

int Listener::getPort() const
{
	return port;
}

void Listener::setPort(int newPort)
{
	if (port == newPort)
		return;
	port = newPort;
	emit portNotify();
}

bool Listener::reconnect()
{
	sucker.connectToHost(host,port,QTcpSocket::OpenMode::enum_type::ReadOnly);
	return sucker.waitForConnected(1000);
}

void Listener::disconnected()
{
	setActive(false);
}

void Listener::readyRead()
{
	while (sucker.bytesAvailable() > 0)
	{
		auto buffer = sucker.readAll().toHex();
		emit dataReceived(buffer);
//		m_model->addData(buffer);
	};
}

bool Listener::getActive() const
{
	return m_active;
}

void Listener::setActive(bool newActive)
{
	if (m_active == newActive)
		return;
	if (newActive)
		m_active = reconnect();
	else {
		sucker.close();
		m_active = false;
	}
	emit activeNotify();
}

DatagramModel *Listener::model() const
{
	return m_model;
}

void Listener::setModel(DatagramModel *newModel)
{
	if (m_model == newModel)
		return;
	m_model = newModel;
	emit modelChanged();
	connect(this,SIGNAL(dataReceived(QByteArray)),m_model,SLOT(addData(QByteArray)));
}
