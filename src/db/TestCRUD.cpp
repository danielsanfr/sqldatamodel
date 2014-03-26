/*
 * TestCRUD.cpp
 *
 *  Created on: 25/03/2014
 *      Author: daniel
 */

#include "TestCRUD.hpp"

namespace db {

TestCRUD::TestCRUD() {
	// TODO Auto-generated constructor stub
}

TestCRUD::~TestCRUD() {
	// TODO Auto-generated destructor stub
}

const QString TestCRUD::getCRUDName() const {
	return QString("TestCRUD");
}

const QString TestCRUD::getTableName() const {
	return TEST_TABLE;
}

void TestCRUD::prepareCreateQuery(QSqlQuery& query,
		const QVariantMap& data) const {
	query.prepare(
			"INSERT INTO " + TEST_TABLE + " (" + TEST_ID + "," + TEST_NAME + ","
					+ TEST_LAST_NAME + ") VALUES (" + ":" + TEST_ID + "," + ":"
					+ TEST_NAME + "," + ":" + TEST_LAST_NAME + ")");
	bindValues(query, data, false);
}

void TestCRUD::prepareUpdateQuery(QSqlQuery& query,
		const QVariantMap& data) const {
	query.prepare(
			"UPDATE " + TEST_TABLE + " SET " + TEST_NAME + " = :" + TEST_NAME
					+ ", " + TEST_LAST_NAME + " = :" + TEST_LAST_NAME
					+ " WHERE " + TEST_ID + " = :" + TEST_ID);
	bindValues(query, data, true);
}

const QVariantMap TestCRUD::createModel(const QSqlQuery& query) const {
	QVariantMap map;
	map.insert(TEST_ID, query.value(0).toInt());
	map.insert(TEST_NAME, query.value(1).toString());
	map.insert(TEST_LAST_NAME, query.value(2).toString());
	return map;
}

void TestCRUD::bindValues(QSqlQuery& query, const QVariantMap& data,
		const bool& bindId) const {
	if (bindId)
		query.bindValue(":" + TEST_ID, data[TEST_ID].toInt());
	query.bindValue(":" + TEST_NAME, data[TEST_NAME].toString());
	query.bindValue(":" + TEST_LAST_NAME, data[TEST_LAST_NAME].toString());
}

} /* namespace db */
