/**
https://es.wikipedia.org/wiki/Tronco_de_cono
https://www.youtube.com/watch?v=MeVsF--h7qU

Given a cone with the sectioned tip, knowing radius of the upper section 'r', the base radius 'R' and the height of the
truncated cone 'h', find the Surface Area and Volume of the truncated cone.

Data: r, R, h
Unknown: A, V

Formulas:
Cone Area = Base Area + Surface Area
Base Area = PI * R^2
Surface Area = PI * R * G
Cone Volume = 1/3 * PI * R^2 * h
Generatrix^2 (equals than a triangle hypotenuse) = h^2 + R^2

By Similar triangles (Thales' Theorem) we can find the proportional triangle, that of the truncated cone formed by h, R and G,
being its variables x = height, r = side and g = generatrix.

Example:
If h = 10m, R = 6m, r = 2m, the height of the sectioned triangle is 'x'. The total height 'H' of the truncated cone plus the
sectioned one will be 'h + x'.

Using Tales: A/B=C/D; 10 + x / x = 6 / 2; 20 + 2x = 6x; x = 5 m
Total Height Cone: H = h + x = 10 + 5 = 15 m

With the heights you can already find the volumes:
Cone Section Volume: V1 = 1/3 * PI * 2^2 * 5= 20,9 m^3
Full Cone Volume: VT = 1/3 * PI * 6^2 * 15= 376,9 m^3
Truncated Cone Volume: V2 = VT - V1 = 397,8 m^3

With the heights find the generatrixs of the cones / hypotenuses of both triangles:
Cone Section Generatrix: g^2 = 5^2 + 2^2; g = 5,38m
Total Generatrix: gT^2 = 15^2 + 6^2; gT = 16,15m
G = GT - g = 10,77m

Upper Cone Section Area = PI * 2^2 = 2,5m^2
Truncated Cone Base Area = PI * 6^2 = 13m^2

Cone Section Surface Area: A1 = PI * r * g = PI * 2 * 5,38 = 33,9 m^2
Total Surface Area: AT = PI* R * GT = PI * 6 * 16,15 = 304 m^2
Truncated Cone Surface Area: A = AT - A1 = 270 m^2
*/

#include <iostream>
#include <cmath> //new C++ header
using namespace std;

#define PI 3.1416f
static const string meters = " m";
static const string squareMeters = " m^2";
static const string cubicMeters = " m^3";

int main()
{
    float coneBaseRadius; // cone base radius = R
    cout << "cone Base Radius (use . for floats): ";
    cin >> coneBaseRadius;

    float truncatedConeUpperRadius; // radius of the upper section of the cone = r
    cout << "truncated Cone Upper Radius (use . for floats): ";
    cin >> truncatedConeUpperRadius;

    float truncatedConeHeight;
    cout << "truncated Cone Height (use . for floats): ";
    cin >> truncatedConeHeight;

    if (coneBaseRadius <= 0.f || truncatedConeUpperRadius <= 0.f || truncatedConeHeight <= 0)
    {
        cout << "Do not use values less than or equal to zero!" << endl;
        return 0;
    }

    if (coneBaseRadius <= truncatedConeUpperRadius)
    {
        cout << "cone Base Radius need to be greater than truncated Cone Upper Radius!" << endl;
        return 0;
    }

    /** find height x of the similar triangle using Thales's Theorem (Similar triangles)
    ej: R = 6; r = 2; h = 10; a/b=c/d; 10+x/x=6/2; 20+2x=6x; 20=4x; 5=x */
    const float similarConeHeight = (truncatedConeHeight * truncatedConeUpperRadius) / (coneBaseRadius - truncatedConeUpperRadius);
    const float fullConeHeight = truncatedConeHeight + similarConeHeight;

    cout << endl;

    cout << "height of the similar upper cone: " << similarConeHeight << meters << endl;
    cout << "full Cone Height: " << fullConeHeight << meters << endl;

    /** find bases areas PI*R^2 */
    const float rSquare = pow(truncatedConeUpperRadius, 2);
    const float RSquare = pow(coneBaseRadius, 2);

    const float upperSectionArea = PI * rSquare;
    const float coneBaseArea = PI * RSquare;

    cout << endl;

    cout << "upper Section Area = " << upperSectionArea << squareMeters << endl;
    cout << "cone Base Area = " << coneBaseArea << squareMeters << endl;

    /** find volumes V1, V2, and Vtotal. V=1/3 * PI * R^2 * h.
    Remember AreaBase = PI * R^2 */
    const float oneThird = 1.f / 3.f;
    const float upperConeVolume = (upperSectionArea * similarConeHeight) * oneThird;
    const float fullConeVolume = (coneBaseArea * fullConeHeight) * oneThird;
    //const float truncatedConeVolume = (PI/3)*((pow(coneBaseRadius, 2)*fullConeHeight)-(pow(truncatedConeUpperRadius, 2)*similarConeHeight));
    const float truncatedConeVolume = fullConeVolume - upperConeVolume;

    cout << endl;

    cout << "upper Cone Volume = " << upperConeVolume << cubicMeters << endl;
    cout << "full Cone Volume = " << fullConeVolume << cubicMeters << endl;
    cout << "truncated Cone Volume = " << truncatedConeVolume << cubicMeters << endl;

    /** find Cones Generatrixs (G) / Traingles Hypotenuses */
    const float similarConeGeneratrix = sqrt(pow(similarConeHeight, 2) + rSquare);
    const float fullConeGeneratrix = sqrt(pow(fullConeHeight, 2) + RSquare);
    const float truncatedConeGeneratrix = fullConeGeneratrix - similarConeGeneratrix;

    cout << endl;

    cout << "similar Cone Generatrix = " << similarConeGeneratrix << meters << endl;
    cout << "full Cone Generatrix = " << fullConeGeneratrix << meters << endl;
    cout << "truncated Cone Generatrix = " << truncatedConeGeneratrix << meters << endl;

    /**  find surface areas ALateral = PI * R * G */
    const float similarConeSurfaceArea = PI * truncatedConeUpperRadius * similarConeGeneratrix;
    const float fullConeSurfaceArea = PI * coneBaseRadius * fullConeGeneratrix;
    //const float truncatedConeSurfaceArea = PI*(coneBaseRadius*fullConeGeneratrix-truncatedConeUpperRadius*similarConeGeneratrix);
    const float truncatedConeSurfaceArea = fullConeSurfaceArea - similarConeSurfaceArea;

    cout << endl;

    cout << "similar Cone Surface Area = " << similarConeSurfaceArea << squareMeters << endl;
    cout << "full Cone Surface Area = " << fullConeSurfaceArea << squareMeters << endl;
    cout << "truncated Cone Surface Area = " << truncatedConeSurfaceArea << squareMeters << endl;

    return 0;
}
