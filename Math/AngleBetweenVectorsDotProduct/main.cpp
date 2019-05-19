/**
https://www.mathsisfun.com/algebra/vectors-dot-product.html
https://en.wikipedia.org/wiki/Dot_product
https://onlinemschool.com/math/assistance/vector/projection/


ej: u(4,4) v(6,0).
-dot product between u and v -> u*u = |u||v|*cos(θ). It means the product of two nonzero vectors is equal to the module of one
of them by the projection of the other on it.
-Get proyection of u over v: proyU_V = |U|*cos(θ) -> u*v = |v|*proyU_V.
-If you havent the (θ) angle, you can calculate dotproduct thus: u*v = ux*vx + uy*vy
-Get angle between u and v. |u| = module of u, |v| = module of v. then u*v = |u|*|v|*cos(θ). Then cos(θ)=u*v/|u|*|v|.
Then (θ) = arc_cos(u*v/|u|*|v|)
*/

#include <iostream>
#include <ostream>
#include <cmath>
using namespace std;
#define PI 3.14159265

struct Vector2
{
private:
	float x, y;
public:
	Vector2(): x(0), y(0){};
	Vector2(const float x, const float y):x(x), y(y){};
	/** they are private members of your class, therefore only a method of your class can access and/or modify them.
	Copy-construct from reference can use private member variables:
	https://stackoverflow.com/questions/4117002/why-can-i-access-private-variables-in-the-copy-constructor */
	Vector2(const Vector2& Other): Vector2(Other.x, Other.y){};
	friend ostream& operator<<(ostream& os, const Vector2& obj)
	{
		os << "[" << obj.x << ", " << obj.y << "]";
		return os;
	}
	const double getMagnitude() const
	{
		return sqrt((x * x) + (y * y));
	}
	const double getDotProduct(const Vector2& A) const
	{
		return ((A.x * x) + (A.y * y));
	}
	const double getDotProduct(const Vector2& A, const float Angle) const
	{
		return (A.getMagnitude() * getMagnitude() * (cos(Angle * (PI / 180.0))));
	}
	const double getAngle(const Vector2& A) const
	{
		// cos(θ)= u*v/|u|*|v| -> arc_cos(θ). c++ acos function return radians. use acos(value)*(180/PI) to get degrees
		return acos(getDotProduct(A) / (getMagnitude() * A.getMagnitude())) * (180.0 / PI);
	}
	const double getScalarProyection(const Vector2& A, const float Angle) const
	{
		// using angle: proj_v_u = |u|*cos(θ)
		return getMagnitude() * (cos(Angle * (PI / 180.0)));
	}
	const double getScalarProyection(const Vector2& A) const
	{
		// without angle: proj_v_u = ((u*v)/|v^2|)*v = (u*v)/|v|
		return getDotProduct(A) / getMagnitude();
	}
	const Vector2 getVectorProyection(const Vector2& A) const
	{
		// proj_v_u = ((u*v)/|v^2|)*v
		const double proj = getDotProduct(A) / pow(A.getMagnitude(), 2);
		return Vector2(proj * A.x, proj * A.y);
	}
};

int main()
{
    const Vector2 v[2]{{4,4}, {6,0}};
    cout << "u = " << v[0] << ", v = " << v[1] << endl;
    cout << "Magnitude |u| = " << v[0].getMagnitude() << endl;
    cout << "Magnitude |v| = " << v[1].getMagnitude() << endl;
    cout << "DotProduct u*v = " << v[0].getDotProduct(v[1]) << endl;
    cout << "Angle between acos(u,v) = " << v[0].getAngle(v[1]) << endl;
    cout << "ScalarProyection proy_u_v = " << v[0].getScalarProyection(v[1], v[0].getAngle(v[1]))<< endl;
    cout << "ScalarProyection proy_v_u = " << v[1].getScalarProyection(v[0], v[1].getAngle(v[0]))<< endl;
    cout << "VectorProyection proy_u_v = " << v[0].getVectorProyection(v[1]) << endl;
    cout << "VectorProyection proy_v_u = " << v[1].getVectorProyection(v[0]) << endl;
    return 0;
}
