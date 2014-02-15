#include "elementtemplate.h"
#include "element.h"

ElementTemplate::ElementTemplate()
{

}

ElementTemplate::ElementTemplate(const QString& id)
{
    mID = id;
}

const QString  ElementTemplate::getID() const
{
    return mID;
}

const std::vector<cv::Point>& ElementTemplate::contour() const
{
    return mContour;
}

void ElementTemplate::setContour(const std::vector<cv::Point>& contour)
{
    mContour = contour;
}

const std::vector<cv::Point>& ElementTemplate::fixture() const
{
    return mFixture;
}

void ElementTemplate::setFixture(const std::vector<cv::Point>& fixture)
{
    mFixture = fixture;
}

const QImage ElementTemplate::image() const
{
    return mImg;
}

void ElementTemplate::setImage(QImage img)
{
    mImg = img;
}

bool ElementTemplate::addElement(Element& elem)
{
    if(!mElements.contains(elem.getID()))
    {
        mElements.insert(elem.getID(), &elem);
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
