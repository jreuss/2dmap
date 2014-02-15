#include "elementtemplatemanager.h"
#include <QVariant>


QHash<QString, ElementTemplate> ElementTemplateManager::mTemplates;

ElementTemplateManager::ElementTemplateManager()
{

}

unsigned ElementTemplateManager::getSize() const
{
    return mTemplates.count();
}

void ElementTemplateManager::addTemplate(const QString &key, const ElementTemplate &el)
{
    mTemplates.insert(key, el);
}

void ElementTemplateManager::addTemplate(const QVariant &key, const ElementTemplate &el)
{

    mTemplates.insert(key.toString(), el);
}

ElementTemplate ElementTemplateManager::getTemplate(const QString &key) const
{
    return mTemplates.value(key);
}

ElementTemplate ElementTemplateManager::getTemplate(const QVariant&key) const
{
    return mTemplates.value(key.toString());
}

QHashIterator<QString, ElementTemplate> ElementTemplateManager::getIterator() const
{

    QHashIterator<QString, ElementTemplate> iter(mTemplates);

    return  iter;
}



