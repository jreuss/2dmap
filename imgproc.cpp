#include "imgproc.h"

const int ALPHA_THRESSHOLD = 1;

ImgProc::ImgProc() {}

void ImgProc::cvtAlphaToBinary(const cv::Mat &src, cv::Mat &out) const
{
    int nl= src.rows; // number of lines
    int nc= src.cols * src.channels();
    out = cv::Mat(src.rows, src.cols, CV_8UC1);

    if (src.isContinuous())
    {
        // then no padded pixels
        nc= nc*nl;
        nl= 1; // it is now a 1D array
    }

    // this loop is executed only once
    // in case of continuous images
    for (int j=0; j<nl; j++) {

        const uchar* data= src.ptr<uchar>(j);
        uchar * out_data = out.ptr<uchar>(j);

        for (int i=3; i<nc; i+=4) {
            *out_data++ = data[i] < ALPHA_THRESSHOLD ? 0 : 255;
        }

        data = NULL; delete data;
        out_data = NULL; delete out_data;
    }
}

QImage ImgProc::compare_test(std::vector<std::vector<cv::Point> > &contours,
                           const QString &path, const float& shape_thress)
{
    cv::Mat img = cv::imread(path.toStdString(), cv::IMREAD_UNCHANGED);

    int max = contours.size();
    cv::Scalar default_color = cv::Scalar(255,255,255, 255);
    std::vector<cv::Scalar> colors;

    colors.resize(max, default_color);
    cv::RNG rng(12345);

    for(int i=0; i<max; i++)
    {
       cv::Scalar col = cv::Scalar(rng.uniform(0,255),
                                   rng.uniform(0, 255),
                                   rng.uniform(0, 255),
                                   255);

       for(int j=i+1; j<max; j++)
       {
           double match = cv::matchShapes(contours[i], contours[j], CV_CONTOURS_MATCH_I1, 0);
           if(match < shape_thress)
           {

               if(colors[j] == default_color)
               {
                    colors[j] = col;
                    colors[i] = col;
               }
           }
           else continue;
       }
    }

    for(unsigned i = 0; i< contours.size(); i++ )
    {
        cv::drawContours( img, contours,i,colors[i],5);
    }

    return toQImage(img);
}

std::vector<std::vector<cv::Point> > ImgProc::findContours(const QString &path) const
{
    cv::Mat img = cv::imread(path.toStdString(), cv::IMREAD_UNCHANGED);
    cv::Mat img_out;

    std::vector<std::vector<cv::Point> > contours;

    if (! img.data )
    {
        qDebug() << "No image recieved!";
        return contours;
    }

    cvtAlphaToBinary(img, img_out);
    cv::findContours(img_out,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    return contours;
}

QImage ImgProc::toQImage(const cv::Mat &img)
{
    cv::Mat temp;
    cv::cvtColor(img, temp,CV_BGRA2RGBA);

    QImage dest((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGBA8888);
    QImage dest2(dest);
    dest2.detach(); // enforce deep copy
    return dest2;
}




