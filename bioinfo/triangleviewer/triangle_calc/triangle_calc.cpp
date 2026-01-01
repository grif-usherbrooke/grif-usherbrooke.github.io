// ClassifyDuplicationFates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <ostream>
#include <cmath>

using namespace std;


#define M_PI 3.14159265358979323846;
struct point2D {
    float x, y;
public:
    /*point2D();
    point2D(float x1, float y1) {
        x = x1;
        y = y1;
    }*/

    point2D& operator=(point2D const& obj)
    {
        x = obj.x;
        y = obj.y;
        return *this;
    }
    bool operator == (const point2D& Ref) const
    {
        return(this->x == Ref.x && this->y == Ref.y);
    }
};
// note, might as well take p as const-reference
std::ostream& operator<<(std::ostream& o, const point2D& p)
{
    //o << "x: " << p.x << "\ty: " << p.y << std::endl;
    return o;
}
const int   N = 99; // clipped (new) polygon size

/* get quadrant from 12 o'clock*/
int get_quadrant(const point2D& p)
{
    int result = 4; //origin

    if (p.x > 0 && p.y > 0)
        return 1;
    else if (p.x < 0 && p.y > 0)
        return 2;
    else if (p.x < 0 && p.y < 0)
        return 3;
    //else 4th quadrant
    return result;
}

double get_clockwise_angle(const point2D& p)
{
    double angle = 0.0;
    int quadrant = get_quadrant(p);

    /*making sure the quadrants are correct*/
    //cout << "Point: " << p << " is on the " << quadrant << " quadrant" << endl;

    /*calculate angle and return it*/
    angle = -atan2(p.x, -p.y);
    return angle;
}
bool compare_points(const point2D& a, const point2D& b)
{
    return (get_clockwise_angle(a) < get_clockwise_angle(b));
}




// check if a point is on the LEFT side of an edge
bool inside(point2D p, point2D p1, point2D p2)
{
    return (p2.y - p1.y) * p.x + (p1.x - p2.x) * p.y + (p2.x * p1.y - p1.x * p2.y) < 0;
}

// calculate intersection point
point2D intersection(point2D cp1, point2D cp2, point2D s, point2D e)
{
    point2D dc = { cp1.x - cp2.x, cp1.y - cp2.y };
    point2D dp = { s.x - e.x, s.y - e.y };

    float n1 = cp1.x * cp2.y - cp1.y * cp2.x;
    float n2 = s.x * e.y - s.y * e.x;
    float n3 = 1.0 / (dc.x * dp.y - dc.y * dp.x);

    return { (n1 * dp.x - n2 * dc.x) * n3, (n1 * dp.y - n2 * dc.y) * n3 };
}

// Sutherland-Hodgman clipping
void SutherlandHodgman(point2D* subjectPolygon, int& subjectPolygonSize, point2D* clipPolygon, int& clipPolygonSize, point2D(&newPolygon)[N], int& newPolygonSize)
{

    int o, k;
    for (o = 0; o < subjectPolygonSize; o++)
        if (subjectPolygon[o].y != 0)
            break;
    for (k = 0; k < clipPolygonSize; k++)
        if (clipPolygon[k].y != 0)
            break;
    bool negativeflag = false;
    if (subjectPolygon[o].y < 0 && clipPolygon[k].y < 0) {
        subjectPolygon[o].y *= -1;
        clipPolygon[k].y *= -1;
        negativeflag = true;
    }


    point2D cp1, cp2, s, e, inputPolygon[N];
    // copy subject polygon to new polygon and set its size
    for (int i = 0; i < subjectPolygonSize; i++)
        newPolygon[i] = subjectPolygon[i];

    newPolygonSize = subjectPolygonSize;

    bool check[3];// = { false, false, false };
    for (int i = 0; i < 3; i++) {
        check[i] = false;
        for (int j = 0; j < 3; j++) {
            if (subjectPolygon[i] == clipPolygon[j])
                check[i] = true;
        }
    }
    if (check[0] && check[1] && check[2]) {
        if (negativeflag) {
            subjectPolygon[2].y *= -1;
            clipPolygon[2].y *= -1;
            for (int i = 0; i < newPolygonSize; i++)
                if (newPolygon[i].y != 0)
                    newPolygon[i].y *= -1;
        }
        return;
    }



    for (int j = 0; j < clipPolygonSize; j++)
    {
        // copy new polygon to input polygon & set counter to 0
        for (int k = 0; k < newPolygonSize; k++) { inputPolygon[k] = newPolygon[k]; }
        int counter = 0;

        // get clipping polygon edge
        cp1 = clipPolygon[j];
        cp2 = clipPolygon[(j + 1) % clipPolygonSize];

        for (int i = 0; i < newPolygonSize; i++)
        {
            // get subject polygon edge
            s = inputPolygon[i];
            e = inputPolygon[(i + 1) % newPolygonSize];

            // Case 1: Both vertices are inside:
            // Only the second vertex is added to the output list
            if (inside(s, cp1, cp2) && inside(e, cp1, cp2))
                newPolygon[counter++] = e;

            // Case 2: First vertex is outside while second one is inside:
            // Both the point of intersection of the edge with the clip boundary
            // and the second vertex are added to the output list
            else if (!inside(s, cp1, cp2) && inside(e, cp1, cp2))
            {
                newPolygon[counter++] = intersection(cp1, cp2, s, e);
                newPolygon[counter++] = e;
            }

            // Case 3: First vertex is inside while second one is outside:
            // Only the point of intersection of the edge with the clip boundary
            // is added to the output list
            else if (inside(s, cp1, cp2) && !inside(e, cp1, cp2))
                newPolygon[counter++] = intersection(cp1, cp2, s, e);

            // Case 4: Both vertices are outside
            else if (!inside(s, cp1, cp2) && !inside(e, cp1, cp2))
            {
                // No vertices are added to the output list
            }
        }
        // set new polygon size
        newPolygonSize = counter;
    }
    if (negativeflag) {
        subjectPolygon[2].y *= -1;
        clipPolygon[2].y *= -1;
        for (int i = 0; i < newPolygonSize; i++)
            if (newPolygon[i].y != 0)
                newPolygon[i].y *= -1;
    }
}


// find equation of a line from two points (y = mx + z)
void findequation(point2D a, point2D b, float mz[])
{
    mz[0] = (b.y - a.y) / (b.x - a.x);
    mz[1] = a.y - (mz[0] * a.x);
}

// sort vertices of triangle based on x
point2D* sorttrianglevertices(point2D a[3])
{
    point2D* sorted = a;
    point2D temp, temp1;
    if (a[0].x < a[1].x && a[0].x < a[2].x)
    {
        sorted[0] = a[0];
        if (a[1].x < a[2].x) {
            sorted[1] = a[1];
            sorted[2] = a[2];
        }
        else {
            temp = a[1];
            sorted[1] = a[2];
            sorted[2] = temp;
        }
    }
    else if (a[1].x < a[0].x && a[1].x < a[2].x)
    {
        temp = a[0];
        sorted[0] = a[1];
        if (a[0].x < a[2].x) {
            sorted[1] = temp;
            sorted[2] = a[2];
        }
        else {
            sorted[1] = a[2];
            sorted[2] = temp;
        }
    }
    else if (a[2].x < a[0].x && a[2].x < a[1].x)
    {
        temp = a[0];
        temp1 = a[1];
        sorted[0] = a[2];
        if (a[0].x < a[1].x) {
            sorted[1] = temp;
            sorted[2] = temp1;
        }
        else {
            sorted[1] = temp1;
            sorted[2] = temp;
        }
    }
    //for (int i = 0; i < 3; i++)
        //cout << "(" << sorted[i].x << ", " << sorted[i].y << ")" << endl;
    return sorted;
}




// calculate a + b when a and b have intersection ( in this case we have new polygon with 7 vertices)
void calculate_a_plus_b_polygon(point2D* a, point2D* b, point2D(&a_plus_b_polygon)[6])
{
    int size = 0;
    float mz[2];
    //point2D a_plus_b_polygon[7]{};
    point2D* sorted_a = sorttrianglevertices(a);
    point2D* sorted_b = sorttrianglevertices(b);
    point2D temp[3]{};
    if (sorted_a[0].x > sorted_b[0].x)
    {
        for (int i = 0; i < 3; i++) {
            temp[i] = sorted_a[i];
            sorted_a[i] = sorted_b[i];
            sorted_b[i] = temp[i];
        }
    }
    //cout << sorted_a[0] << sorted_a[1] << sorted_a[2] << "**" << endl;
    //cout << sorted_b[0] << sorted_b[1] << sorted_b[2];
    //point2D* sorted_intersection_a_b = sorttrianglevertices(intersection_a_b);
    a_plus_b_polygon[0] = sorted_a[0];

    if (sorted_b[0].x >= sorted_a[1].x) {
        a_plus_b_polygon[1] = sorted_a[1];
        if (sorted_b[0].x >= sorted_a[2].x) {
            a_plus_b_polygon[2] = sorted_a[2];
            a_plus_b_polygon[3] = sorted_b[0];
            a_plus_b_polygon[4] = sorted_b[1];
            a_plus_b_polygon[5] = sorted_b[2];
        }
        else {
            findequation(sorted_a[1], sorted_a[2], mz);
            //cout << "m ,z" << mz[0] << mz[1] << endl;
            a_plus_b_polygon[2] = { sorted_b[0].x , mz[0] * sorted_b[0].x + mz[1] };
            if (sorted_b[1].x >= sorted_a[2].x) {
                findequation(sorted_b[0], sorted_b[1], mz);
                //cout << "m ,z" << mz[0] << mz[1] << endl;
                a_plus_b_polygon[3] = { sorted_a[2].x , mz[0] * sorted_a[2].x + mz[1] };
                a_plus_b_polygon[4] = sorted_b[1];
                a_plus_b_polygon[5] = sorted_b[2];
            }
            else {
                findequation(sorted_a[1], sorted_a[2], mz);
                //cout << "m ,z" << mz[0] << mz[1] << endl;
                a_plus_b_polygon[3] = { sorted_b[1].x , mz[0] * sorted_b[1].x + mz[1] + sorted_b[1].y };
                if (sorted_b[2].x >= sorted_a[2].x) {
                    findequation(sorted_b[1], sorted_b[2], mz);
                    //cout << "m ,z" << mz[0] << mz[1] << endl;
                    a_plus_b_polygon[4] = { sorted_a[2].x , mz[0] * sorted_a[2].x + mz[1] };
                    a_plus_b_polygon[5] = sorted_b[2];
                }
                else {
                    findequation(sorted_a[1], sorted_a[2], mz);
                    //cout << "m ,z" << mz[0] << mz[1] << endl;
                    a_plus_b_polygon[4] = { sorted_b[2].x , mz[0] * sorted_b[2].x + mz[1] };
                    a_plus_b_polygon[5] = sorted_a[2];
                }
            }
        }
    }
    else {
        findequation(sorted_a[0], sorted_a[1], mz);
        //cout << "m ,z" << mz[0] << mz[1] << endl;
        a_plus_b_polygon[1] = { sorted_b[0].x , mz[0] * sorted_b[0].x + mz[1] };
        if (sorted_b[1].x >= sorted_a[1].x) {
            findequation(sorted_b[0], sorted_b[1], mz);
            //cout << "m ,z" << mz[0] << mz[1] << endl;
            a_plus_b_polygon[2] = { sorted_a[1].x , mz[0] * sorted_a[1].x + mz[1] + sorted_a[1].y };
            if (sorted_b[1].x >= sorted_a[2].x) {
                findequation(sorted_b[0], sorted_b[1], mz);
                //cout << "m ,z" << mz[0] << mz[1] << endl;
                a_plus_b_polygon[3] = { sorted_a[2].x , mz[0] * sorted_a[2].x + mz[1] };
                a_plus_b_polygon[4] = sorted_b[1];
                a_plus_b_polygon[5] = sorted_b[2];
            }
            else {
                findequation(sorted_a[1], sorted_a[2], mz);
                a_plus_b_polygon[3] = { sorted_b[1].x , mz[0] * sorted_b[1].x + mz[1] + sorted_b[1].y };
                if (sorted_b[2].x >= sorted_a[2].x) {
                    findequation(sorted_b[1], sorted_b[2], mz);
                    //cout << "m ,z" << mz[0] << mz[1] << endl;
                    a_plus_b_polygon[4] = { sorted_a[2].x , mz[0] * sorted_a[2].x + mz[1] };
                    a_plus_b_polygon[5] = sorted_b[2];
                }
                else {
                    findequation(sorted_a[1], sorted_a[2], mz);
                    //cout << "m ,z" << mz[0] << mz[1] << endl;
                    a_plus_b_polygon[4] = { sorted_b[2].x , mz[0] * sorted_b[2].x + mz[1] };
                    a_plus_b_polygon[5] = sorted_a[2];
                }
            }
        }
        else {
            findequation(sorted_a[0], sorted_a[1], mz);
            //cout << "m ,z" << mz[0] << mz[1] << endl;
            a_plus_b_polygon[2] = { sorted_b[1].x , mz[0] * sorted_b[1].x + mz[1] + sorted_b[1].y };
            if (sorted_a[1].x >= sorted_b[2].x) {
                findequation(sorted_a[0], sorted_a[1], mz);
                //cout << "m ,z" << mz[0] << mz[1] << endl;
                a_plus_b_polygon[3] = { sorted_b[2].x , mz[0] * sorted_b[2].x + mz[1] };
                a_plus_b_polygon[4] = sorted_a[1];
                a_plus_b_polygon[5] = sorted_a[2];
            }
            else {
                findequation(sorted_b[1], sorted_b[2], mz);
                a_plus_b_polygon[3] = { sorted_a[1].x , mz[0] * sorted_a[1].x + mz[1] + sorted_a[1].y };
                if (sorted_b[2].x >= sorted_a[2].x) {
                    findequation(sorted_b[1], sorted_b[2], mz);
                    //cout << "m ,z" << mz[0] << mz[1] << endl;
                    a_plus_b_polygon[4] = { sorted_a[2].x , mz[0] * sorted_a[2].x + mz[1] };
                    a_plus_b_polygon[5] = sorted_b[2];
                }
                else {
                    findequation(sorted_a[1], sorted_a[2], mz);
                    //cout << "m ,z" << mz[0] << mz[1] << endl;
                    a_plus_b_polygon[4] = { sorted_b[2].x , mz[0] * sorted_b[2].x + mz[1] };
                    a_plus_b_polygon[5] = sorted_a[2];
                }
            }
        }
    }

}

point2D* ret(point2D* a) {
    point2D* b = a;
    return b;
}

// calculate area of triangle using the coordinates 
double trianglearea(point2D a[3])
{
    double dArea = ((a[1].x - a[0].x) * (a[2].y - a[0].y) - (a[2].x - a[0].x) * (a[1].y - a[0].y)) / 2.0;
    return (dArea > 0.0) ? dArea : -dArea;
}

double polygonArea(point2D* polygon, int n)
{
    vector<double> X;
    vector<double> Y;

    for (int i = 0; i < n; i++) {
        X.push_back(polygon[i].x);
        Y.push_back(polygon[i].y);
    }

    // Initialize area
    double area = 0.0;

    // Calculate value of shoelace formula
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (X[j] + X[i]) * (Y[j] - Y[i]);
        j = i;  // j is previous vertex to i
    }
    // Return absolute value
    return abs(area / 2.0);
}

float min(float a, float b) {
    return (a > b) ? b : a;
}

float max(float a, float b) {
    return (a > b) ? a : b;
}

vector<point2D> remove_duplicate_vertices(point2D(&a_plus_b_polygon)[6]) {
    vector<point2D> polygon_a_plus_b_uni;
    polygon_a_plus_b_uni.reserve(6);
    bool flag;
    for (int i = 0; i < 6; i++) {
        flag = false;
        for (int j = 0; j < polygon_a_plus_b_uni.size(); j++) {
            if (polygon_a_plus_b_uni[j] == a_plus_b_polygon[i]) {
                flag = true;
            }
        }
        if (!flag)
            polygon_a_plus_b_uni.push_back(a_plus_b_polygon[i]);
    }
    return polygon_a_plus_b_uni;
}

//double g[3]: g[0](m), g[1](h), g[2](w)
double* ProbabilitiesCalculation(float g[3], float a[3], float b[3]) {
    // convert m, h, w to three vertices
    std::vector <point2D> points;
    point2D g2d[3]{}, a2d[3]{}, b2d[3]{};
    g2d[0] = { g[0] - g[2], 0 };
    g2d[1] = { g[0] + g[2], 0 };
    g2d[2] = { g[0] , g[1] };
    points.push_back(g2d[0]);
    points.push_back(g2d[1]);
    points.push_back(g2d[2]);
    std::sort(points.begin(), points.end(), compare_points);
    for (int i = 0; i < 3; i++) {
        g2d[i] = points[i];
    }
    points.clear();

    a2d[0] = { a[0] - a[2], 0 };
    a2d[1] = { a[0] + a[2], 0 };
    a2d[2] = { a[0] , a[1] };
    points.push_back(a2d[0]);
    points.push_back(a2d[1]);
    points.push_back(a2d[2]);
    std::sort(points.begin(), points.end(), compare_points);
    for (int i = 0; i < 3; i++) {
        a2d[i] = points[i];
    }
    points.clear();

    b2d[0] = { b[0] - b[2], 0 };
    b2d[1] = { b[0] + b[2], 0 };
    b2d[2] = { b[0] , b[1] };
    points.push_back(b2d[0]);
    points.push_back(b2d[1]);
    points.push_back(b2d[2]);
    std::sort(points.begin(), points.end(), compare_points);
    for (int i = 0; i < 3; i++) {
        b2d[i] = points[i];
    }
    points.clear();

    //for (int i = 0; i < 3; i++)
    //    cout << g2d[i];
    //area of g, a ,b
    float area_g = polygonArea(g2d, 3);
    float area_a = polygonArea(a2d, 3);
    float area_b = polygonArea(b2d, 3);

    //cout << "area g: " << area_g << endl;
    //cout << "area a: " << area_a << endl;
    //cout << "area b: " << area_b << endl;

    //point2D subjectPolygon[] = { g1, g2, g3 };
    int gPolygonSize = sizeof(g2d) / sizeof(g2d[0]);
    int aPolygonSize = sizeof(a2d) / sizeof(a2d[0]);
    int bPolygonSize = sizeof(b2d) / sizeof(b2d[0]);

    // define the new clipped polygon (empty)
    int newPolygonSize = 0;
    point2D newPolygon[N] = { 0 };

    // apply clipping
    SutherlandHodgman(g2d, gPolygonSize, a2d, aPolygonSize, newPolygon, newPolygonSize);
    float inersection_area_g_a;
    float inersection_area_g_b;
    float area_a_plus_b;
    float intersection_area_g_a_plus_b;
    // calculate intersection area
    /*point2D a2 = newPolygon[2];
    newPolygon[2] = newPolygon[3];
    newPolygon[3] = a2;*/
    //for (int i = 0; i < 3; i++)
    //    cout << "(" << newPolygon[i].x << ", " << newPolygon[i].y << ")" << endl;
    if (newPolygonSize != 0)
        inersection_area_g_a = polygonArea(newPolygon, newPolygonSize);
    else
        inersection_area_g_a = 0;

    SutherlandHodgman(g2d, gPolygonSize, b2d, bPolygonSize, newPolygon, newPolygonSize);
    if (newPolygonSize != 0)
        inersection_area_g_b = polygonArea(newPolygon, newPolygonSize);
    else
        inersection_area_g_b = 0;
    //cout << "area of intersection of a , g: " << inersection_area_g_a << endl;
    //cout << "area of intersection of b , g: " << inersection_area_g_b << endl;

    SutherlandHodgman(a2d, aPolygonSize, b2d, bPolygonSize, newPolygon, newPolygonSize);
    if (newPolygonSize == 0) {
        //cout << "a and b are separte. " << endl;
        area_a_plus_b = area_a + area_b;
        intersection_area_g_a_plus_b = inersection_area_g_b + inersection_area_g_a;
    }
    else {
        //cout << "a and b have intersection. " << endl;
        point2D polygon_a_plus_b[6]{};
        vector<point2D> polygon_a_plus_b_uni;
        calculate_a_plus_b_polygon(b2d, a2d, polygon_a_plus_b);
        polygon_a_plus_b_uni = remove_duplicate_vertices(polygon_a_plus_b);
        /*for (int i = 0; i < 6; i++) {
            polygon_a_plus_b_uni.push_back(polygon_a_plus_b[i]);
        }*/
        int polygon_a_plus_bSize = polygon_a_plus_b_uni.size();
        std::sort(polygon_a_plus_b_uni.begin(), polygon_a_plus_b_uni.end(), compare_points);
        for (int k = 0; k < polygon_a_plus_b_uni.size(); k++)
            polygon_a_plus_b[k] = polygon_a_plus_b_uni[k];
        polygon_a_plus_b_uni.clear();
        //cout << "a + b polygon:" << endl;
        //for (int i = 0; i < polygon_a_plus_bSize; i++)
        //    cout << "(" << polygon_a_plus_b[i].x << ", " << polygon_a_plus_b[i].y << ")" << endl;
        area_a_plus_b = polygonArea(polygon_a_plus_b, polygon_a_plus_bSize);
        SutherlandHodgman(polygon_a_plus_b, polygon_a_plus_bSize, g2d, gPolygonSize, newPolygon, newPolygonSize);
        //cout << "g inter a + b: " << endl;
        //for (int i = 0; i < newPolygonSize; i++)
        //    cout << "(" << newPolygon[i].x << ", " << newPolygon[i].y << ")" << endl;
        intersection_area_g_a_plus_b = polygonArea(newPolygon, newPolygonSize);
    }
    //ycout << "area of intersection of g, a + b: " << intersection_area_g_a_plus_b << endl;

    float threshold = 0.7;
    float ig_a = (inersection_area_g_a / area_g);
    cout << "ig_a=" << ig_a << endl;
    float ig_b = (inersection_area_g_b / area_g);
    cout << "ig_b=" << ig_b << endl;
    float ia_g = (inersection_area_g_a / area_a);
    cout << "ia_g=" << ia_g << endl;
    float ib_g = (inersection_area_g_b / area_b);
    cout << "ib_g=" << ib_g << endl;
    float ig_a_plus_b = (intersection_area_g_a_plus_b / area_g);
    cout << "ig_a_plus_b=" << ig_a_plus_b << endl;
    //cout << "intersection_area_g_a_plus_b: " << intersection_area_g_a_plus_b << endl;
    //cout << "area_a_plus_b: " << area_a_plus_b << endl;
    float ia_plus_b_g = (intersection_area_g_a_plus_b / area_a_plus_b);
    cout << "ia_plus_b_g=" << ia_plus_b_g << endl;
    float pa = 1 - min(abs(a[1] / (g[1] * threshold)), 1);
    cout << "pa=" << pa << endl;
    float pb = 1 - min(abs(b[1] / (g[1] * threshold)), 1);
    cout << "pb=" << pb << endl;

    
    float P_conservation = ig_a * ig_b;
    float P_newfunctionlizatoin = max(ig_b * (1 - ia_g) * (1 - pa), ig_a * (1 - ib_g) * (1 - pb));
    float P_specialization = (1 - pa) * (1 - pb) * (1 - ig_a_plus_b);
    float P_pseudogenization = max(pa, pb);
    float P_subfunctionlization = ig_a * ib_g * ig_a_plus_b * ia_plus_b_g * (1 - pa) * (1 - pb);
    double fates_probablities[5];
    fates_probablities[0] = P_subfunctionlization;
    fates_probablities[1] = P_conservation;
    fates_probablities[2] = P_newfunctionlizatoin;
    fates_probablities[3] = P_pseudogenization;
    fates_probablities[4] = P_specialization;
    cout << "P_subfunctionlization: " << P_subfunctionlization << " P_conservation: " << P_conservation << " P_newfunctionlizatoin " << P_newfunctionlizatoin << " P_pseudogenization " << P_pseudogenization << " P_specialization " << P_specialization << endl;

    
    return fates_probablities;
}


//double g[3]: g[0](m), g[1](h), g[2](w)
int main(int argc, char** argv) {

    if (argc != 10)
    {
        cout << "You must provide 9 arguments: mg, hg, wg, ma, ha, wa, mb, hb, wb" << endl;
        return 0;
    }

    float g[3]{};
    float a[3]{};
    float b[3]{};

    g[0] = atof(argv[1]) + 10;
    g[1] = atof(argv[2]);
    g[2] = atof(argv[3]);
    a[0] = atof(argv[4]) + 10;
    a[1] = atof(argv[5]);
    a[2] = atof(argv[6]);
    b[0] = atof(argv[7]) + 10;
    b[1] = atof(argv[8]);
    b[2] = atof(argv[9]);
    


    // convert m, h, w to three vertices
    std::vector <point2D> points;
    point2D g2d[3]{}, a2d[3]{}, b2d[3]{};
    g2d[0] = { g[0] - g[2], 0 };
    g2d[1] = { g[0] + g[2], 0 };
    g2d[2] = { g[0] , g[1] };
    points.push_back(g2d[0]);
    points.push_back(g2d[1]);
    points.push_back(g2d[2]);
    std::sort(points.begin(), points.end(), compare_points);
    for (int i = 0; i < 3; i++) {
        g2d[i] = points[i];
    }
    points.clear();

    a2d[0] = { a[0] - a[2], 0 };
    a2d[1] = { a[0] + a[2], 0 };
    a2d[2] = { a[0] , a[1] };
    points.push_back(a2d[0]);
    points.push_back(a2d[1]);
    points.push_back(a2d[2]);
    std::sort(points.begin(), points.end(), compare_points);
    for (int i = 0; i < 3; i++) {
        a2d[i] = points[i];
    }
    points.clear();

    b2d[0] = { b[0] - b[2], 0 };
    b2d[1] = { b[0] + b[2], 0 };
    b2d[2] = { b[0] , b[1] };
    points.push_back(b2d[0]);
    points.push_back(b2d[1]);
    points.push_back(b2d[2]);
    std::sort(points.begin(), points.end(), compare_points);
    for (int i = 0; i < 3; i++) {
        b2d[i] = points[i];
    }
    points.clear();

    for (int i = 0; i < 3; i++)
        cout << g2d[i];
    //area of g, a ,b
    float area_g = polygonArea(g2d, 3);
    float area_a = polygonArea(a2d, 3);
    float area_b = polygonArea(b2d, 3);

    //cout << "area g: " << area_g << endl;
    //cout << "area a: " << area_a << endl;
    //cout << "area b: " << area_b << endl;

    //point2D subjectPolygon[] = { g1, g2, g3 };
    int gPolygonSize = sizeof(g2d) / sizeof(g2d[0]);
    int aPolygonSize = sizeof(a2d) / sizeof(a2d[0]);
    int bPolygonSize = sizeof(b2d) / sizeof(b2d[0]);

    // define the new clipped polygon (empty)
    int newPolygonSize = 0;
    point2D newPolygon[N] = { 0 };

    // apply clipping
    SutherlandHodgman(g2d, gPolygonSize, a2d, aPolygonSize, newPolygon, newPolygonSize);
    float inersection_area_g_a;
    float inersection_area_g_b;
    float area_a_plus_b;
    float intersection_area_g_a_plus_b;
    // calculate intersection area
    /*point2D a2 = newPolygon[2];
    newPolygon[2] = newPolygon[3];
    newPolygon[3] = a2;*/
    //for (int i = 0; i < 3; i++)
    //    cout << "(" << newPolygon[i].x << ", " << newPolygon[i].y << ")" << endl;
    if (newPolygonSize != 0)
        inersection_area_g_a = polygonArea(newPolygon, newPolygonSize);
    else
        inersection_area_g_a = 0;

    SutherlandHodgman(g2d, gPolygonSize, b2d, bPolygonSize, newPolygon, newPolygonSize);
    if (newPolygonSize != 0)
        inersection_area_g_b = polygonArea(newPolygon, newPolygonSize);
    else
        inersection_area_g_b = 0;
    //cout << "area of intersection of a , g: " << inersection_area_g_a << endl;
    //cout << "area of intersection of b , g: " << inersection_area_g_b << endl;

    SutherlandHodgman(a2d, aPolygonSize, b2d, bPolygonSize, newPolygon, newPolygonSize);
    if (newPolygonSize == 0) {
        //cout << "a and b are separte. " << endl;
        area_a_plus_b = area_a + area_b;
        intersection_area_g_a_plus_b = inersection_area_g_b + inersection_area_g_a;
    }
    else {
        //cout << "a and b have intersection. " << endl;
        point2D polygon_a_plus_b[6]{};
        vector<point2D> polygon_a_plus_b_uni;
        calculate_a_plus_b_polygon(b2d, a2d, polygon_a_plus_b);
        polygon_a_plus_b_uni = remove_duplicate_vertices(polygon_a_plus_b);
        /*for (int i = 0; i < 6; i++) {
            polygon_a_plus_b_uni.push_back(polygon_a_plus_b[i]);
        }*/
        int polygon_a_plus_bSize = polygon_a_plus_b_uni.size();
        std::sort(polygon_a_plus_b_uni.begin(), polygon_a_plus_b_uni.end(), compare_points);
        for (int k = 0; k < polygon_a_plus_b_uni.size(); k++)
            polygon_a_plus_b[k] = polygon_a_plus_b_uni[k];
        polygon_a_plus_b_uni.clear();
        //cout << "a + b polygon:" << endl;
        //for (int i = 0; i < polygon_a_plus_bSize; i++)
        //    cout << "(" << polygon_a_plus_b[i].x << ", " << polygon_a_plus_b[i].y << ")" << endl;
        area_a_plus_b = polygonArea(polygon_a_plus_b, polygon_a_plus_bSize);
        SutherlandHodgman(polygon_a_plus_b, polygon_a_plus_bSize, g2d, gPolygonSize, newPolygon, newPolygonSize);
        //cout << "g inter a + b: " << endl;
        ///for (int i = 0; i < newPolygonSize; i++)
        //    cout << "(" << newPolygon[i].x << ", " << newPolygon[i].y << ")" << endl;
        intersection_area_g_a_plus_b = polygonArea(newPolygon, newPolygonSize);
    }
    //cout << "area of intersection of g, a + b: " << intersection_area_g_a_plus_b << endl;

    float threshold = 0.7;
    float ig_a = (inersection_area_g_a / area_g);
    cout << "ig_a=" << ig_a << endl;
    float ig_b = (inersection_area_g_b / area_g);
    cout << "ig_b=" << ig_b << endl;
    float ia_g = (inersection_area_g_a / area_a);
    cout << "ia_g=" << ia_g << endl;
    float ib_g = (inersection_area_g_b / area_b);
    cout << "ib_g=" << ib_g << endl;
    float ig_a_plus_b = (intersection_area_g_a_plus_b / area_g);
    cout << "ig_a_plus_b=" << ig_a_plus_b << endl;
    //cout << "intersection_area_g_a_plus_b: " << intersection_area_g_a_plus_b << endl;
    //cout << "area_a_plus_b: " << area_a_plus_b << endl;
    float ia_plus_b_g = (intersection_area_g_a_plus_b / area_a_plus_b);
    cout << "ia_plus_b_g=" << ia_plus_b_g << endl;
    float pa = 1 - min(abs(a[1] / (g[1] * threshold)), 1);
    cout << "pa=" << pa << endl;
    float pb = 1 - min(abs(b[1] / (g[1] * threshold)), 1);
    cout << "pb=" << pb << endl;
}


