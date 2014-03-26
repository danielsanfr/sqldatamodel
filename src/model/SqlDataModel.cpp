/*
 * SqlDataModel.cpp
 *
 *  Created on: 06/02/2014
 *      Author: daniel
 */

#include "SqlDataModel.hpp"

using namespace bb::cascades;
using namespace db;

namespace model {

SqlDataModel::SqlDataModel(QObject *parent) :
		ArrayDataModel(parent), m_dataBaseController(
				new DataBaseController(this)) {
}

SqlDataModel::~SqlDataModel() {
}

const QString& SqlDataModel::table() {
	return m_dataBaseController->tableName();
}

void SqlDataModel::setTable(const QString& table) {
	m_dataBaseController->setTableName(table);
	emit tableChanged();
}

qlonglong SqlDataModel::create(const QVariantMap& data) {
	int id = m_dataBaseController->create(data);
	QVariantMap newData = data;
	newData[ID_FIELD] = id;
	append(newData);
	return id;
}

void SqlDataModel::deleteRecordById(const int& id) {
	deleteRecord(getIndexPathByID(id));
}

void SqlDataModel::deleteRecord(const QVariantList& indexPath) {
	m_dataBaseController->deleteRecord(data(indexPath).toMap()[TEST_ID].toInt());
	int index = indexPath.back().toInt();
	if (index != -1)
		removeAt(index);
}

void SqlDataModel::deleteRecord(const QVariantMap& arguments,
		const QString& conditions) {
}

void SqlDataModel::update(const QVariantMap& data) {
	m_dataBaseController->update(data);
	replace(getIndexPathByID(data[ID_FIELD].toInt()).back().toInt(), data);
}

QVariantMap SqlDataModel::read(const int& id) {
	return m_dataBaseController->read(id);
}

QVariantList SqlDataModel::read() {
	return m_dataBaseController->read();
}

QVariantList SqlDataModel::read(const QVariantMap& arguments,
		const QString& conditions) {
	return m_dataBaseController->read(arguments, conditions);
}

int SqlDataModel::count() {
	return m_dataBaseController->count();
}

int SqlDataModel::count(const QVariantMap& arguments,
		const QString& conditions) {
	return m_dataBaseController->count(arguments, conditions);
}

void SqlDataModel::load() {
	int length = size();
	for (int i = 0; i < length; ++i)
		removeAt(0);
	append(m_dataBaseController->read());
}

void SqlDataModel::load(const QVariantMap& arguments,
		const QString& conditions) {
	int length = size();
	for (int i = 0; i < length; ++i)
		removeAt(0);
	append(m_dataBaseController->read(arguments, conditions));
}

void SqlDataModel::clear() {
	int length = size();
	for (int i = 0; i < length; ++i) {
		m_dataBaseController->deleteRecord(value(0).toMap()["id"].toInt());
		removeAt(0);
	}
}

QVariantList SqlDataModel::getIndexPathByID(int id) {
	int length = size();
	for (int i = 0; i < length; ++i) {
		if (value(i).toMap()[ID_FIELD].toInt() == id)
			return QVariantList() << i;
	}
	return QVariantList() << -1;
}

} /* namespace model */
