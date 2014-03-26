/*
 * TestCRUD.hpp
 *
 *  Created on: 25/03/2014
 *      Author: daniel
 */

#ifndef TESTECRUD_HPP_
#define TESTECRUD_HPP_

#include "DataBaseCRUD.hpp"
#include "TableDefinitions.hpp"

namespace db {

class TestCRUD : public DataBaseCRUD {
public:
	TestCRUD();
	virtual ~TestCRUD();
private:
	const QString getCRUDName() const;
	const QString getTableName() const;
	void prepareCreateQuery(QSqlQuery &query, const QVariantMap &data) const ;
	void prepareUpdateQuery(QSqlQuery &query, const QVariantMap &data) const ;
	const QVariantMap createModel(const QSqlQuery &query) const;
	void bindValues(QSqlQuery &query, const QVariantMap &data, const bool &bindId) const ;
};

} /* namespace db */
#endif /* TESTECRUD_HPP_ */
