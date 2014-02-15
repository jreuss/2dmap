#ifndef IMGPROC_H
#define IMGPROC_H

#include <QString>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QDebug>
#include <QPair>
#include <QList>

#include "matchgroup.h"
#include "elementtemplate.h"
#include "elementtemplatemanager.h"

class ImgProc
{
public:
    ImgProc();

    std::vector<std::vector<cv::Point> >  findContours(const QString &path) const;
    QImage toQImage(const cv::Mat &img);

    QImage compare_test(std::vector<std::vector<cv::Point> > &contours,
                        const QString &path, const float& shape_thress);

    void create_templates (MatchGroup group);

    QList<QList<unsigned> > get_matches(
            std::vector<std::vector<cv::Point> > &contours,
            const float& shape_thress);
private:
    void cvtAlphaToBinary(const cv::Mat &src, cv::Mat &out) const;
};

#endif // IMGPROC_H
