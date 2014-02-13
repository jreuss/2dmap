#ifndef ELEMENTTEMPLATE_H
#define ELEMENTTEMPLATE_H

#include <opencv2/core/core.hpp>
#include <QVector>
#include <QString>
#include <QUuid>
#include <QHash>

class Element;

class ElementTemplate
{

public:
    ElementTemplate();

    ElementTemplate(QUuid id);

    ~ElementTemplate();

    QUuid getUID() const;
    QString getStringID() const;

    const QVector<cv::Point>& contour() const;
    void setContour(const QVector<cv::Point>& contour);

    const QVector<cv::Point>& fixture() const;
    void setFixture(const QVector<cv::Point>& fixture);

    bool addElement(Element &elem);

    Element* getElement(QString getStringID);

    const QString name() const;
    void setName(const QString& name);

    const QString imgPath() const;
    void setImgPath(const QString& path);


private:
    QHash<QString, Element*> mElements;
    QString mName;
    QString mImgPath;
    QUuid mID;
    QVector<cv::Point> mContour;
    QVector<cv::Point> mFixture;
};

#endif // ELEMENTTEMPLATE_H
