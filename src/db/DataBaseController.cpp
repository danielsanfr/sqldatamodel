/*
 * DataBaseController.cpp
 *
 *  Created on: 07/02/2014
 *      Author: daniel
 */

#include "DataBaseController.hpp"

namespace db {

DataBaseController::DataBaseController(QObject *parent) :
		QObject(parent), m_tableName(TEST_TABLE), m_dataBaseCRUD(0) {
	setCRUBInstanceByTableName();
}

DataBaseController::DataBaseController(QString tableName, QObject* parent) :
		QObject(parent) {
	m_tableName = tableName;
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
	QString clientTableQuery = "DROP TABLE IF EXISTS " + TEST_TABLE;
	if (!query.exec(clientTableQuery))
		qDebug()
				<< "DataBaseController::dropTables:Test: Drop table error: "
						+ query.lastError().text();
	database.close();
}

void DataBaseController::setTableName(const QString &tableName) {
	Q_ASSERT(tableName == TEST_TABLE);
	if (m_tableName != tableName) {
		m_tableName = tableName;
		setCRUBInstanceByTableName();
	}
}

const QString& DataBaseController::tableName() {
	return m_tableName;
}

qlonglong DataBaseController::create(const QVariantMap& data) const {
	return m_dataBaseCRUD->create(data);
}

void DataBaseController::deleteRecord(const int& id) {
	m_dataBaseCRUD->deleteRecord(id);
}

void DataBaseController::deleteRecord(const QVariantMap& arguments,
		const QString& conditions) {
	m_dataBaseCRUD->deleteRecord(arguments, conditions);
}

void DataBaseController::update(const QVariantMap& data) {
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

int DataBaseController::count() const {
	return m_dataBaseCRUD->count();
}

int DataBaseController::count(const QVariantMap& arguments,
		const QString& conditions) const {
	return m_dataBaseCRUD->count(arguments, conditions);
}

void DataBaseController::setCRUBInstanceByTableName() {
	if (m_tableName == TEST_TABLE)
		m_dataBaseCRUD = new TestCRUD();
}

} /* namespace db */
