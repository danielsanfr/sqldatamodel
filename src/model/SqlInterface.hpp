/*
 * SqlInterface.hpp
 *
 *  Created on: 25/03/2014
 *      Author: daniel
 */

#ifndef SQLINTERFACE_HPP_
#define SQLINTERFACE_HPP_

#include <QVariant>
#include <QVariantList>

namespace model {

class SqlInterface {
public:
	SqlInterface() {}
	virtual ~SqlInterface() {}
	virtual void append(const QVariant &value) = 0;
	virtual void append(const QVariantList &value) = 0;
	virtual void removeAt(const QVariantList &indexPath) = 0;
	virtual void replace(const int &i, const QVariant &value) = 0;
};

} /* namespace model */
#endif /* SQLINTERFACE_HPP_ */
