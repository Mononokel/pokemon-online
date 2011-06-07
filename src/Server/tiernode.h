#ifndef TIERNODE_H
#define TIERNODE_H

#include <QtCore>
#if !defined(PO_NO_GUI)
#include <QtGui>
#endif

class QDomElement;

struct TierNode
{
    TierNode() : displayOrder(0) {

    }

    virtual void changeName(const QString &name) {
        m_name = name;
    }
    QString name() const {
        return m_name;
    }
    virtual bool isTier() const {
        return false;
    }
    virtual bool isCategory() const {
        return false;
    }

    virtual void loadFromXml(const QDomElement &){}
    virtual QDomElement &toXml(QDomElement &p) const = 0;
    virtual TierNode *dataClone() const = 0;
#if !defined(PO_NO_GUI)
    virtual QTreeWidgetItem *buildGui() const {
        return new QTreeWidgetItem(QStringList() << name());
    }
#endif
    virtual void serialize(QDataStream &stream, int level) {
        stream << uchar (level) << name();
    }

    int displayOrder;
    QString m_name;
};

#endif // TIERNODE_H
