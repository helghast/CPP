/**
https://www.mathsisfun.com/algebra/vectors-cross-product.html
https://gamedev.stackexchange.com/questions/28565/fastest-solution-to-compute-normal
http://www.cplusplus.com/forum/general/77959/
https://math.stackexchange.com/questions/305642/how-to-find-surface-normal-of-a-triangle
https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal
https://en.wikipedia.org/wiki/Cross_product

The cross product of two sides of the triangle equals the surface normal. So, if V = P2 - P1 and W = P3 - P1, and N is the surface normal, then:
Nx=(Vy∗Wz)−(Vz∗Wy)
Ny=(Vz∗Wx)−(Vx∗Wz)
Nz=(Vx∗Wy)−(Vy∗Wx)
If A is the new vector whose components add up to 1, then (normal can be -1,0,1):
Ax=Nx/(|Nx|+|Ny|+|Nz|)
Ay=Ny/(|Nx|+|Ny|+|Nz|)
Az=Nz/(|Nx|+|Ny|+|Nz|)
*/
#include <iostream>
#include <ostream>
#include <cmath>
using namespace std;

struct Vector3
{
	float x, y, z;
	Vector3(): x(0), y(0), z(0){};
	Vector3(const float x, const float y, const float z):x(x), y(y), z(z){};
	Vector3(const Vector3& Other): Vector3(Other.x, Other.y, Other.z){};
	friend ostream& operator<<(ostream& os, const Vector3& obj)
	{
		os << "[" << obj.x << ", " << obj.y << ", " << obj.z << "]";
		return os;
	}
	const Vector3 operator%(const Vector3& Other) const
	{
		return Vector3((y * Other.z) - (z * Other.y), (z * Other.x) - (x * Other.z), (x * Other.y) - (y * Other.z));
	}
	const double getMagnitude() const
	{
		return sqrt(x * x + y * y + z * z);
	}
	/**	Mathematically speaking, the zero vector cannot be normalized. Its length will always remain 0.
	For given vector v = (v1, v2, ..., vn) we have: ||v|| = sqrt(v1^2 + v2^2 + ... + vn^2). Let us remember that a normalized vector is
	one that has ||v||=1.
	So for v = 0 we have: ||0|| = sqrt(0^2 + 0^2 + ... + 0^2) = 0. You can never normalize that.
	Also important to note that to ensure consistency, you should not return NaN or any other null value.
	The normalized form of v=0 is indeed v=0.
	Then if lenght == 0, cant do a division by x/0 to obtain a normalized vector. */
	const Vector3 Normalize()
	{
		const double lenght = getMagnitude();
		if (lenght == 0)
		{
			cout << "Cannot normalize a vector of lenght/magnitude == 0" << endl;
			x = y = z = 0;
		}
		else
		{
			x = x / lenght;
			y = y / lenght;
			z = z / lenght;
		}
		return *this;
	}
};

const Vector3 CalculateNormals(const Vector3& Point1, const Vector3& Point2, const Vector3& Point3)
{
	// cross product formula: only need two vectors from the surface, whatever of them
	// (u1, u2, u3) x (v1, v2, v3) = (u2*v3 - u3*v2, u3*v1 - u1*v3, u1*v2 - u2*v1)
	// form 1
	/*Vector3 result;
	result.x = (Point1.y * Point2.z) - (Point1.z * Point2.y);
	result.y = (Point1.z * Point2.x) - (Point1.x * Point2.z);
	result.z = (Point1.x * Point2.y) - (Point1.y * Point2.x);
	return result;*/

	// form 2
	//return Vector3((Point1.y * Point2.z) - (Point1.z * Point2.y), (Point1.z * Point2.x) - (Point1.x * Point2.z), (Point1.x * Point2.y) - (Point1.y * Point2.z));

	// form 3
	return Point1 % Point2;
}

int main()
{
	const Vector3 v[3]{{0,0,0}, {3,3,0}, {6,0,0}};
	cout << "u=" << v[0] << ", v=" << v[1] << ", w=" << v[2] << endl;
	Vector3 Normal = CalculateNormals(v[0], v[1], v[2]);
    cout << "Normal: " << Normal << endl;
    cout << "Normalize: " << Normal.Normalize() << endl;
    return 0;
}
