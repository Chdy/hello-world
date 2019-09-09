//
// Created by 邓岩 on 2018/11/25.
//

# include <iostream>
# include <vector>
# include <algorithm>
# include <numeric>


using std::cout;
using std::endl;

int main(void)
{
    std::vector<int> x(12);
    std::iota(x.begin(),x.end(),18);
    std::vector<int> z(12);
    std::vector<double> y = {76.1, 77, 78.1, 78.2, 78.8, 79.7, 79.9, 81.1, 81.2, 81.8, 82.8, 83.5};
    double xsum = std::accumulate(x.begin(), x.end(), 0);
    double xaver = xsum/x.size();
    std::transform(x.begin(), x.end(), y.begin(), z.begin(), [xaver](int xi, double yi) { return yi*(xi - xaver); });
    double xqu = std::accumulate(x.begin() + 1, x.end(), x[0] * x[0], [] (int l,int r) { return l + r*r; });
    double w = std::accumulate(z.begin(), z.end(), 0) / (xqu - xsum * xsum/x.size());
    std::transform(x.begin(), x.end(), y.begin(), z.begin(), [w](int xi, double yi) { return yi - w*xi; });
    double b = std::accumulate(z.begin(), z.end(), 0.) / z.size();

    cout << "y = " << w << "x + " << b << endl;
}