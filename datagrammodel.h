#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QByteArray>

class DatagramModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit DatagramModel(QObject *parent = nullptr);
	Q_PROPERTY(QString separator READ getSeparator WRITE setSeparator NOTIFY separatorChanged)

public:
	virtual int rowCount(const QModelIndex &parent) const override;
	virtual QVariant data(const QModelIndex &index, int role) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
	virtual QModelIndex parent(const QModelIndex &child) const override;
	virtual int columnCount(const QModelIndex &parent) const override;

	const QString &getSeparator() const;
	void setSeparator(const QString &newSeparator);
	Q_INVOKABLE void clear();

signals:
	void separatorChanged();

private:
	QList<QByteArray> dataList;

	QString m_separator;
public slots:
	void addData(QByteArray data);
};
