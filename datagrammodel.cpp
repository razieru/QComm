#include "datagrammodel.h"
#include <QString>
#include <QDebug>

DatagramModel::DatagramModel(QObject *parent) : QAbstractListModel(parent)
{

}


int DatagramModel::rowCount(const QModelIndex &parent) const
{
	return dataList.length();
}

QVariant DatagramModel::data(const QModelIndex &index, int role) const
{
	return dataList[index.row()];
}


QModelIndex DatagramModel::index(int row, int column, const QModelIndex &parent) const
{
	return QAbstractItemModel::createIndex(row,0);
}

QModelIndex DatagramModel::parent(const QModelIndex &child) const
{
	return {};
}

int DatagramModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

void DatagramModel::addData(QByteArray data)
{
	auto string = QString(data);
	beginInsertRows({},dataList.length(),dataList.length()+(m_separator.length() ? (string.count(m_separator,Qt::CaseInsensitive)-1) : 0));
	int startIndex = 0;
	bool toParse = true;
	if (m_separator.length())
		while (toParse) {
			auto ind = string.indexOf(m_separator,startIndex+1);
			if (ind != -1) {
				dataList.append(data.mid(startIndex,ind-startIndex));
				startIndex = ind;
			} else {
				dataList.append(data.mid(startIndex,data.length()-startIndex));
				toParse = false;
			}
		}
	else dataList.append(data);
	endInsertRows();
}


const QString &DatagramModel::getSeparator() const
{
	return m_separator;
}

void DatagramModel::setSeparator(const QString &newSeparator)
{
	if (m_separator == newSeparator)
		return;
	m_separator = newSeparator;
	emit separatorChanged();
}

void DatagramModel::clear()
{
	beginResetModel();
	dataList.clear();
	endResetModel();
}
