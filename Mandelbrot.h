#ifndef MANDELBROT_H_
#define MANDELBROT_H_

namespace Fun
{
    class Mandelbrot
    {
        public:
            static const int MAX_ITERATIONS = 1000;
        public:
            Mandelbrot();
            virtual ~Mandelbrot();
            static int s_GetIterations(double x, double y);
    };
}

#endif /* MANDELBROT_H_ */
