#ifndef ELEMENTTEMPLATEMANAGER_H
#define ELEMENTTEMPLATEMANAGER_H

#include <QHash>
#include <QString>
#include <QVariant>
#include <QList>
#include <QPair>
#include <QHashIterator>


#include "elementtemplate.h"

class ElementTemplateManager
{
public:
    ElementTemplateManager();
    unsigned getSize() const;

    void addTemplate(const QString& key, const ElementTemplate& el);
    void addTemplate(const QVariant& key, const ElementTemplate& el);
    ElementTemplate getTemplate(const QString& key) const;
    ElementTemplate getTemplate(const QVariant& key) const;
    QHashIterator<QString, ElementTemplate> getIterator() const;

private:
    static QHash<QString, ElementTemplate> mTemplates;
};

#endif // ELEMENTTEMPLATEMANAGER_H
