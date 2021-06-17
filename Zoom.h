#ifndef ZOOM_H_
#define ZOOM_H_

namespace Fun
{
    struct Zoom
    {
        int iX{0};
        int iY{0};
        double dScale{0.0};

        Zoom(int x, int y, double scale) : iX(x), iY(y), dScale(scale){};
    };
} // namespace Fun

#endif /* ZOOM_H_ */
