#include <iostream>
#include "Bitmap.h"
using namespace std;
using namespace Fun;

int main(void)
{
    Bitmap bitmap(800, 600);
    bitmap.Write("test.bmp");
    cout << "Finished" << endl;
    return 0;
}