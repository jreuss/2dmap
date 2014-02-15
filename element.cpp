#include "element.h"
#include "elementtemplate.h"

Element::Element() {}

Element::Element(const QString& id, ElementTemplate* parent)
{
    mID = id;
    mParent = parent;
}

QString Element::getID() const
{
    return mID;
}

void Element::setName(QString name)
{
    mName = name;
}

float Element::angle() const
{
    return mAngle;
}

void Element::setAngle(const float &angle)
{
    mAngle = angle;
}

cv::Point Element::scale() const
{
    return mScale;
}

void Element::setScale(const cv::Point &scale)
{
    mScale = scale;
}

cv::Point Element::position() const
{
    return mPosition;
}

void Element::setPosition(const cv::Point &position)
{
    mPosition = position;
}

QString Element::name() const
{
    return mName;
}

ElementTemplate* Element::parent() const
{
    return mParent;
}

void Element::setParent(ElementTemplate *parent)
{
    mParent = parent;
}

Element::~Element()
{
    mParent = NULL;
    delete mParent;
}

