#ifndef TIERTREE_H
#define TIERTREE_H

#if !defined(PO_NO_GUI)
#include <QtCore>
#endif
#include "tiernode.h"

class Tier;
class TierMachine;
class QDomElement;
class QTreeWidget;
class QTreeWidgetItem;

struct TierCategory : public TierNode
{
    QList<TierNode *> subNodes;
    bool root;

    ~TierCategory();
    void loadFromXml(const QDomElement &xmldata, TierMachine *boss, bool root=false);
    QDomElement &toXml(QDomElement &xml) const;

    QList<Tier *> gatherTiers();
    QList<TierCategory *> gatherCategories();
    QList<Tier *> firstLevelTiers();
    QList<TierCategory *> firstLevelCategories();
    void cleanCategories();
    void clear();
    void clearWithoutDeleting();
    void kill(TierNode *t);
    TierCategory *dataClone() const;

    void serialize(QDataStream &stream, int level = -1);

    TierNode *getNode(const QString &name);
    TierCategory *getParentCategory(TierNode *t);
    void appendChild(TierNode *t);
    void removeChild(TierNode *t);

    void reorder();
    QTreeWidgetItem *buildGui() const;
    void buildRootGui(QTreeWidget *tree);

    bool isCategory() const { return true; }
};

class TierTree
{
    friend class TierMachine;
#if !defined(PO_NO_GUI)
    friend class TierWindow;
#endif
public:
    void loadFromXml(const QString &xmldata, TierMachine *boss);
    QString toXml() const;
    QList<Tier *> gatherTiers();
    QList<TierCategory *> gatherCategories();
    /* Removing branches without leafs */
    void cleanCategories();
    /* Building the tier list as sent over network */
    QByteArray buildTierList();
    /* Returns a copy, but that has no effect on ratings, just used to represent and touch
       the structure of tiers without harming the real one */
    TierTree *dataClone() const;

    TierNode *getNode(const QString &name);
    TierCategory *getParentCategory(TierNode *c);

#if !defined(PO_NO_GUI)
    void buildTreeGui(QTreeWidget *tree);
#endif
    /* Reorder tiers / categories with the right display order */
    void reorder();
private:
    TierCategory root;
};

#endif // TIERTREE_H
