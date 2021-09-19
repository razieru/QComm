#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include "datagrammodel.h"

class Listener : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY hostNotify)
	Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portNotify)
	Q_PROPERTY(bool active READ getActive WRITE setActive NOTIFY activeNotify)
	Q_PROPERTY(DatagramModel* model READ model WRITE setModel NOTIFY modelChanged)

public:
	explicit Listener(QObject *parent = nullptr);

	const QString &getHost() const;
	void setHost(const QString &newHost);

	int getPort() const;
	void setPort(int newPort);
	Q_INVOKABLE bool reconnect();

	bool getActive() const;
	void setActive(bool newActive);

	DatagramModel *model() const;
	void setModel(DatagramModel *newModel);

signals:

	void hostNotify();
	void portNotify();
	void dataReceived(QByteArray dataString);

	void activeNotify();

	void modelChanged();

private:
	QTcpSocket sucker;
	QString host;
	int port;

	bool m_active;

	DatagramModel *m_model;

private slots:
	void disconnected();
	void readyRead();

};
