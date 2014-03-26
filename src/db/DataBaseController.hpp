/*
 * DataBaseController.hpp
 *
 *  Created on: 07/02/2014
 *      Author: daniel
 */

#ifndef DATABASECONTROLLER_HPP_
#define DATABASECONTROLLER_HPP_

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QtSql/QtSql>

#include "TestCRUD.hpp"
#include "DataBaseCRUD.hpp"
#include "TableDefinitions.hpp"

namespace db {

class DataBaseController: public QObject{
	Q_OBJECT
public:
	DataBaseController(QObject *parent = 0);
	DataBaseController(QString tableName, QObject *parent = 0);
	virtual ~DataBaseController();
	static DataBaseController *getInstance(QObject *parent = 0) {
		static DataBaseController *m_dataBaseController;
		if (!m_dataBaseController) {
			m_dataBaseController = new DataBaseController(parent);
		}
		return m_dataBaseController;
	}
	static bool createDB();
	static void createTables();
	static void dropTables();
	Q_INVOKABLE void setTableName(const QString &tableName);
	Q_INVOKABLE const QString &tableName();
	Q_INVOKABLE qlonglong create(const QVariantMap &data) const;
	Q_INVOKABLE void deleteRecord(const int &id);
	Q_INVOKABLE void deleteRecord(const QVariantMap &arguments, const QString &conditions);
	Q_INVOKABLE void update(const QVariantMap &data);
	Q_INVOKABLE const QVariantMap read(const int &id);
	Q_INVOKABLE const QVariantList read();
	Q_INVOKABLE const QVariantList read(const QVariantMap &arguments, const QString &conditions);
	Q_INVOKABLE int count() const;
	Q_INVOKABLE int count(const QVariantMap &arguments, const QString &conditions) const;
private:
	void setCRUBInstanceByTableName();
	QString m_tableName;
	DataBaseCRUD *m_dataBaseCRUD;
	QVariantMap m_references;
};

} /* namespace db */
#endif /* DATABASECONTROLLER_HPP_ */
