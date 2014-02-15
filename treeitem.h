#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QString>
#include <opencv2/core/core.hpp>
#include <QImage>
#include <QTreeWidgetItem>

struct TreeItem
{
    QImage img;
    QList<QList<unsigned> > matchList;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Point> fixture;
    QString path, name, itemType;
    QTreeWidgetItem* parent = NULL;
};

#endif // TREEITEM_H
