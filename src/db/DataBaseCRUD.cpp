/*
 * DataBaseCRUD.hpp
 *
 *  Created on: 07/02/2014
 *      Author: daniel
 */

#include "DataBaseCRUD.hpp"

namespace db {

DataBaseCRUD::DataBaseCRUD() {
}

DataBaseCRUD::~DataBaseCRUD() {
}

qlonglong DataBaseCRUD::create(const QVariantMap& data) const {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	prepareCreateQuery(query, data);
	if (!query.exec())
		qDebug()
				<< getCRUDName() + "::create: Create task error: "
						+ query.lastError().text();
	database.close();
	return query.lastInsertId().toLongLong();
}

void DataBaseCRUD::deleteRecord(const int& id) {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	query.prepare("DELETE FROM " + getTableName() + " WHERE id=:id");
	query.bindValue(":id", id);
	if (!query.exec()) {
		qDebug()
				<< getCRUDName() + "::deleteRecord: Delete task error: "
						+ query.lastError().text();
	}
	database.close();
}

void DataBaseCRUD::deleteRecord(const QVariantMap& arguments,
		const QString& conditions) {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	const QString readQuery = "DELETE FROM " + getTableName() + " WHERE "
			+ conditions;
	query.prepare(readQuery);
	bindValuesOfQuery(query, arguments);
	if (!query.exec()) {
		qDebug()
				<< getCRUDName() + "::deleteRecord: Delete task error: "
						+ query.lastError().text();
	}
	database.close();
}

void DataBaseCRUD::update(const QVariantMap& data) {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	prepareUpdateQuery(query, data);
	if (!query.exec())
		qDebug()
				<< getCRUDName() + "::update: Update task error: "
						+ query.lastError().text();
	database.close();
}

const QVariantMap DataBaseCRUD::read(const int& id) const {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	query.prepare("SELECT * FROM " + getTableName() + " WHERE id=:id");
	query.bindValue(":id", id);
	QVariantMap map = read(query).at(0).toMap();
	database.close();
	return map;
}

const QVariantList DataBaseCRUD::read() const {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	const QString sqlStatement = "SELECT * FROM " + getTableName();
	query.prepare(sqlStatement);
	QVariantList resultList = read(query);
	database.close();
	return resultList;
}

const QVariantList DataBaseCRUD::read(const QVariantMap& arguments,
		const QString& conditions) {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	const QString readQuery = "SELECT * FROM " + getTableName() + " WHERE "
			+ conditions;
	query.prepare(readQuery);
	bindValuesOfQuery(query, arguments);
	QVariantList resultList = read(query);
	database.close();
	return resultList;
}

int DataBaseCRUD::count() const {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	const QString sqlQuery = "SELECT COUNT(1) AS \"size\" FROM "
			+ getTableName();
	query.prepare(sqlQuery);
	int size = count(query);
	database.close();
	return size;
}

int DataBaseCRUD::count(const QVariantMap& arguments,
		const QString& conditions) const {
	QSqlDatabase database = QSqlDatabase::database();
	QSqlQuery query(database);
	const QString countQuery = "SELECT COUNT(1) AS \"size\" FROM "
			+ getTableName() + " WHERE " + conditions;
	query.prepare(countQuery);
	bindValuesOfQuery(query, arguments);
	int size = count(query);
	database.close();
	return size;
}

int DataBaseCRUD::count(QSqlQuery& query) const {
	int size = -1;
	if (query.exec()) {
		while (query.next()) {
			size = query.value(0).toInt();
		}
	} else
		qDebug()
				<< getCRUDName() + "::count: Count table error: "
						+ query.lastError().text();
	return size;
}

const QVariantList DataBaseCRUD::read(QSqlQuery& query) const {
	QVariantList resultList;
	if (query.exec()) {
		while (query.next()) {
			QVariantMap map = createModel(query);
			resultList.append(map);
		}
	} else
		qDebug()
				<< getCRUDName() + "::read: Load table error: "
						+ query.lastError().text();
	return resultList;
}

void DataBaseCRUD::bindValuesOfQuery(QSqlQuery& query,
		const QVariantMap& arguments) const {
	foreach(QString key, arguments.keys()) {
		switch (arguments[key].type()) {
		case QMetaType::Int:
			query.bindValue(key, arguments[key].toInt());
			break;
		case QMetaType::QString:
			query.bindValue(key, arguments[key].toString());
			break;
		case QMetaType::LongLong:
			query.bindValue(key, arguments[key].toLongLong());
			break;
		}
	}
}

} /* namespace db */
