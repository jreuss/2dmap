#ifndef ELEMENT_H
#define ELEMENT_H

#include <opencv2/core/core.hpp>
#include <QVector>
#include <QString>
#include <QUuid>

class ElementTemplate;

class Element
{
public:

    Element();

    Element(const QString &id, ElementTemplate* parent);

    ~Element();

    ElementTemplate* parent() const;
    void setParent(ElementTemplate* parent);

    QString getID() const;

    QString name() const;
    void setName(QString name);

    float angle() const;
    void setAngle(const float& angle);

    cv::Point scale() const;
    void setScale(const cv::Point &scale);

    cv::Point position() const;
    void setPosition(const cv::Point& position);

private:
    ElementTemplate* mParent;
    QString mID;
    QString mName;
    float mAngle;
    cv::Point mScale;
    cv::Point mPosition;
};

#endif // ELEMENT_H
