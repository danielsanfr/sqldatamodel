/*
 * SqlDataModel.hpp
 *
 *  Created on: 06/02/2014
 *      Author: daniel
 */

#ifndef SQLDATAMODEL_HPP_
#define SQLDATAMODEL_HPP_

#include <QDebug>
#include <QObject>
#include <QString>
#include <QtSql/QtSql>
#include <QVariantMap>
#include <QVariantList>
#include <QSharedPointer>

#include <bb/cascades/ArrayDataModel>

#include "SqlInterface.hpp"
#include "db/DataBaseController.hpp"

namespace model {

#define FIELD_ID "id"

class SqlDataModel: public bb::cascades::ArrayDataModel /*, model::SqlInterface */  {
	Q_OBJECT
	Q_PROPERTY(QString table  READ table WRITE setTable NOTIFY tableChanged FINAL)
public:
	SqlDataModel(QObject *parent = 0);
	virtual ~SqlDataModel();
	static void registerQmlTypes() {
		qmlRegisterType<SqlDataModel>("model.custom", 1, 0, "SqlDataModel");
	}
	Q_INVOKABLE const QString &table();
	Q_INVOKABLE void setTable(const QString &table);
	Q_INVOKABLE qlonglong create(const QVariantMap &data);
	Q_INVOKABLE void deleteRecordById(const int &id);
	Q_INVOKABLE void deleteRecord(const QVariantList &indexPath);
	Q_INVOKABLE void deleteRecord(const QVariantMap &arguments, const QString &conditions);
	Q_INVOKABLE void update(const QVariantMap &data);
	Q_INVOKABLE QVariantMap read(const int &id);
	Q_INVOKABLE QVariantList read();
	Q_INVOKABLE QVariantList read(const QVariantMap &arguments, const QString &conditions);
	Q_INVOKABLE int count();
	Q_INVOKABLE int count(const QVariantMap &arguments, const QString &conditions);
	Q_INVOKABLE void load();
	Q_INVOKABLE void load(const QVariantMap &arguments, const QString &conditions);
	Q_INVOKABLE void clearRecords();
	Q_SIGNAL void tableChanged();
private:
	Q_SLOT void onTableNameChanged(int uuid, const QString &tableName);
	Q_SLOT void onCreatedRecord(int uuid, const QString &tableName, const QVariantMap &data, const qlonglong &id);
	Q_SLOT void onDeletedRecord(int uuid, const QString &tableName, const int &id);
	Q_SLOT void onDeletedRecord(int uuid, const QString &tableName, const QVariantMap &arguments, const QString &conditions);
	Q_SLOT void onUpdatedRecord(int uuid, const QString &tableName, const QVariantMap &data);
	QVariantList getIndexPathByID(const int &id);
	QString m_table;
	db::DataBaseController * m_dataBaseController;
	int m_dbAccessUUID;
	QString m_lastLoadConditions;
	QVariantMap m_lastLoadArguments;
};

} /* namespace model */
#endif /* SQLDATAMODEL_HPP_ */
