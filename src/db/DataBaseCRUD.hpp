/*
 * DataBaseCRUD.hpp
 *
 *  Created on: 07/02/2014
 *      Author: daniel
 */

#ifndef DATABASECRUD_HPP_
#define DATABASECRUD_HPP_

#include <QString>
#include <QtSql/QtSql>
#include <QVariantMap>
#include <QVariantList>

#include "TableDefinitions.hpp"

namespace db {

class DataBaseCRUD {
public:
	DataBaseCRUD();
	virtual ~DataBaseCRUD();
	qlonglong create(const QVariantMap &data) const;
	void deleteRecord(const int &id);
	void deleteRecord(const QVariantMap &arguments, const QString &conditions);
	void update(const QVariantMap &data);
	const QVariantMap read(const int &id) const;
	const QVariantList read() const;
	const QVariantList read(const QVariantMap &arguments, const QString &conditions);
	int count() const;
	int count(const QVariantMap &arguments, const QString &conditions) const;
private:
	int count(QSqlQuery &query) const;
	const QVariantList read(QSqlQuery &query) const;
	void bindValuesOfQuery(QSqlQuery &query, const QVariantMap &arguments) const;
	// specific CRUD interface
	virtual const QString getCRUDName() const = 0;
	virtual const QString getTableName() const = 0;
	virtual void prepareCreateQuery(QSqlQuery &query, const QVariantMap &data) const = 0;
	virtual void prepareUpdateQuery(QSqlQuery &query, const QVariantMap &data) const = 0;
	virtual const QVariantMap createModel(const QSqlQuery &query) const = 0;
	virtual void bindValues(QSqlQuery &query, const QVariantMap &data, const bool &bindId) const = 0;
};

}  /* namespace db */
#endif /* DATABASECRUD_HPP_ */
