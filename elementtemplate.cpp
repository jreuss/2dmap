#include "elementtemplate.h"
#include "element.h"

ElementTemplate::ElementTemplate()
{

}

ElementTemplate::ElementTemplate(QUuid id)
{
    mID = id;
}

QUuid ElementTemplate::getUID() const
{
    return mID;
}

QString ElementTemplate::getStringID() const
{
    return mID.toString();
}

const QVector<cv::Point>& ElementTemplate::contour() const
{
    return mContour;
}

void ElementTemplate::setContour(const QVector<cv::Point>& contour)
{
    mContour = contour;
}

const QVector<cv::Point>& ElementTemplate::fixture() const
{
    return mFixture;
}

void ElementTemplate::setFixture(const QVector<cv::Point>& fixture)
{
    mFixture = fixture;
}

bool ElementTemplate::addElement(Element& elem)
{
    if(!mElements.contains(elem.getStringID()))
    {
        mElements.insert(elem.getStringID(),&elem);
        return true;
    }
    return false;
}

Element* ElementTemplate::getElement(QString ID)
{
    return mElements.value(ID);
}

const QString ElementTemplate::name() const
{
    return mName;
}

void ElementTemplate::setName(const QString &name)
{
    mName = name;
}

const QString ElementTemplate::imgPath() const
{
    return mImgPath;
}

void ElementTemplate::setImgPath(const QString &path)
{
    mImgPath = path;
}

ElementTemplate::~ElementTemplate()
{
    qDeleteAll(mElements);
    mElements.clear();
}
