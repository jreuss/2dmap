#ifndef ELEMENTTEMPLATE_H
#define ELEMENTTEMPLATE_H

#include <opencv2/core/core.hpp>
#include <QVector>
#include <QString>
#include <QUuid>
#include <QImage>
#include <QHash>

class Element;

class ElementTemplate
{

public:
    ElementTemplate();

    ElementTemplate(const QString& id);

    ~ElementTemplate();

    const QString getID() const;

    const std::vector<cv::Point>& contour() const;
    void setContour(const std::vector<cv::Point>& contour);

    const std::vector<cv::Point>& fixture() const;
    void setFixture(const std::vector<cv::Point>& fixture);

    const QImage image() const;
    void setImage(QImage img);

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
    QString mID;
    std::vector<cv::Point> mContour;
    std::vector<cv::Point> mFixture;
    QImage mImg;
};

#endif // ELEMENTTEMPLATE_H
