#include <iostream>
#include <complex>
using namespace std;

// define X, Y as real(), imag()
typedef complex<double> point;
#define X real()
#define Y imag()

// sample program
int main() {
	point a = 2;
	point b(3, 7);
	cout << a << ' ' << b << endl; // (2, 0) (3, 7)
	cout << a + b << endl;         // (5, 7)
}

/**
1. Vector addition: a + b

2. Scalar multiplication: r * a

3. Dot product: (conj(a) * b).X

4. Cross product: (conj(a) * b).Y
   notice: conj(a) * b = (ax*bx + ay*by) + i (ax*by — ay*bx)

5. Squared distance: norm(a - b)

6 Euclidean distance: abs(a - b)

7. Angle of elevation: arg(b - a)

8. Slope of line (a, b): tan(arg(b - a))

9. Polar to cartesian: polar(r, theta)

10. Cartesian to polar: point(abs(p), arg(p))

11. Rotation about the origin: a * polar(1.0, theta)

12. Rotation about pivot p: (a-p) * polar(1.0, theta) + p

13. Angle ABC: abs(remainder(arg(a-b) - arg(c-b), 2.0 * M_PI))
    remainder normalizes the angle to be between [-PI, PI]. Thus, we can
    get the positive non-reflex angle by taking its abs value.

14. Project p onto vector v: v * dot(p, v) / norm(v);

15. Project p onto line (a, b): a + (b - a) * dot(p - a, b - a) / norm(b - a)

16. Reflect p across line (a, b): a + conj((p - a) / (b - a)) * (b - a)

17. Intersection of line (a, b) and (p, q):

point intersection(point a, point b, point p, point q) {
  double c1 = cross(p - a, b - a), c2 = cross(q - a, b - a);
  return (c1 * q - c2 * p) / (c1 - c2); // undefined if parallel
}

Drawbacks:
-----------
Using std::complex is very advantageous, but it has one disadvantage:
you can't use std::cin or scanf. Also, if we macro x and y, we can't use
them as variables. But that's rather minor, don't you think?

**/


