/*
 * DataBaseController.cpp
 *
 *  Created on: 07/02/2014
 *      Author: daniel
 */

#include "DataBaseController.hpp"

namespace db {

DataBaseController::DataBaseController(QObject *parent) :
		QObject(parent), m_UUIDs(-1), m_tableName(TEST_TABLE), m_dataBaseCRUD(0) {
	setCRUBInstanceByTableName();
}

DataBaseController::~DataBaseController() {
}

bool DataBaseController::createDB() {
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	bool success = false;
	database.setDatabaseName(DB_PATH);
	if (database.open()) {
		qDebug() << "DataBaseController::createDB: Database created/registered.";
		success = true;
	} else {
		qDebug()
				<< "DataBaseController::createDB: Error opening connection to the database: "
						+ database.lastError().text();
	}
	database.close();
	return success;
}

void DataBaseController::createTables() {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	QString testTableQuery = "CREATE TABLE IF NOT EXISTS " + TEST_TABLE
			+ " (" + TEST_ID + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
			+ TEST_NAME + " TEXT NOT NULL, " + TEST_LAST_NAME + " TEXT)";
	if (!query.exec(testTableQuery))
		qDebug()
				<< "DataBaseController::createTables::Test: Create table error: "
						+ query.lastError().text();
	database.close();
}

void DataBaseController::dropTables() {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	QString testTableQuery = "DROP TABLE IF EXISTS " + TEST_TABLE;
	if (!query.exec(testTableQuery))
		qDebug()
				<< "DataBaseController::dropTables:Test: Drop table error: "
						+ query.lastError().text();
	database.close();
}

void DataBaseController::setTableName(const QString &tableName, int uuid) {
	Q_ASSERT(tableName == TEST_TABLE);
	if (m_tableName != tableName) {
		m_tableName = tableName;
		emit tableNameChanged(uuid, tableName);
		setCRUBInstanceByTableName();
	}
}

const QString& DataBaseController::tableName() {
	return m_tableName;
}

qlonglong DataBaseController::create(const QVariantMap& data, int uuid) {
	qlonglong id =  m_dataBaseCRUD->create(data);
	emit createdRecord(uuid, data, id);
	return id;
}

void DataBaseController::deleteRecord(const int& id, int uuid) {
	emit deletedRecord(uuid, id);
	m_dataBaseCRUD->deleteRecord(id);
}

void DataBaseController::deleteRecord(const QVariantMap& arguments,
		const QString& conditions, int uuid) {
	emit deletedRecord(uuid, arguments, conditions);
	m_dataBaseCRUD->deleteRecord(arguments, conditions);
}

void DataBaseController::update(const QVariantMap& data, int uuid) {
	emit updatedRecord(uuid, data);
	m_dataBaseCRUD->update(data);
}

const QVariantMap DataBaseController::read(const int& id) {
	return m_dataBaseCRUD->read(id);
}

const QVariantList DataBaseController::read() {
	return m_dataBaseCRUD->read();
}

const QVariantList DataBaseController::read(const QVariantMap& arguments,
		const QString& conditions) {
	return m_dataBaseCRUD->read(arguments, conditions);
}

int DataBaseController::count() {
	return m_dataBaseCRUD->count();
}

int DataBaseController::count(const QVariantMap& arguments,
		const QString& conditions) {
	return m_dataBaseCRUD->count(arguments, conditions);
}

int DataBaseController::getUUID() {
	++m_UUIDs;
	return m_UUIDs;
}

void DataBaseController::setCRUBInstanceByTableName() {
	if (m_tableName == TEST_TABLE)
		m_dataBaseCRUD = new TestCRUD();
}

} /* namespace db */
