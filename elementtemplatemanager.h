#ifndef ELEMENTTEMPLATEMANAGER_H
#define ELEMENTTEMPLATEMANAGER_H

#include <QHash>
#include <QString>
#include <QVariant>

#include "elementtemplate.h"

class ElementTemplateManager
{
public:
    ElementTemplateManager();

    void addTemplate(const QString& key, const ElementTemplate& el);
    void addTemplate(const QVariant& key, const ElementTemplate& el);
    ElementTemplate getTemplate(const QString& key) const;
    ElementTemplate getTemplate(const QVariant& key) const;

private:
    static QHash<QString, ElementTemplate> templates;
};

#endif // ELEMENTTEMPLATEMANAGER_H
