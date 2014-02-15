#ifndef MATCHGROUP_H
#define MATCHGROUP_H

#include <QList>
#include <QString>
#include <opencv2/core/core.hpp>

struct MatchGroup {
    QList<QList<unsigned> > matchList;
    std::vector<std::vector<cv::Point> > contours;
    QString path, name;
};

#endif // MATCHGROUP_H
