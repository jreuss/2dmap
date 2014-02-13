#include "elementtemplatemanager.h"
#include <QVariant>


QHash<QString, ElementTemplate> ElementTemplateManager::templates;

ElementTemplateManager::ElementTemplateManager()
{

}

void ElementTemplateManager::addTemplate(const QString &key, const ElementTemplate &el)
{
    templates.insert(key, el);
}

void ElementTemplateManager::addTemplate(const QVariant &key, const ElementTemplate &el)
{

    templates.insert(key.toString(), el);
}

ElementTemplate ElementTemplateManager::getTemplate(const QString &key) const
{
    return templates.value(key);
}

ElementTemplate ElementTemplateManager::getTemplate(const QVariant&key) const
{
    return templates.value(key.toString());
}



