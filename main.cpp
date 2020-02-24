#include <iostream>
using namespace std;

//template <typename T>
//void test (T x, T y)   {
//    cout << x << " " << y << endl;
//}


class Exception {
protected:
    string message;
public:
    Exception();
    Exception (string newException);
    string getMessage();
};

Exception::Exception()   {

}

Exception::Exception(string newException) {
    message = newException;
}

string Exception::getMessage() {
    return "\n--=={Exception: " + message + "}==--\n";
}


class LineSegmentException: public Exception {
public:
    LineSegmentException (string newException);
    string getMessage();
};

LineSegmentException::LineSegmentException(string newException) {
    message = newException;
}

string LineSegmentException::getMessage() {
    return "\n--=={Line Segment Exception: " + message + "}==--\n";  //TODO Change this to Exception,line segment not found
}

class SegmentsException: public Exception {
public:
    SegmentsException (string newException);
    string getMessage();
};

SegmentsException::SegmentsException(string newException) {
    message = newException;
}

string SegmentsException::getMessage() {
    return "\n--=={Segments Exception: " + message + "}==--\n";
}


template <class T>
class Point {
protected:
    T x; //x coordinate value
    T y; //y coordinate value
public:
    Point (); //default constructor; x = 0.0 and y = 0.0
    Point (T xvalue, T yvalue); //no-default constructor
    void setLocation (T xvalue, T yvalue); // set x = xvalue and y = yvalue
    double getXValue(); //return x
    double getYValue(); //return y
    void display(); // Print (0.0, 0.0)
    void display(ostream& s);
};

template <class T>
Point<T>::Point() {
    x = 0.0;
    y = 0.0;
}

template <class T>
Point<T>::Point(T xvalue, T yvalue) {
    x = xvalue;
    y = yvalue;
}

template <class T>
void Point<T>::setLocation(T xvalue, T yvalue) { //Originally returned int. I changed it to return nothing(void)
    x = xvalue;
    y = yvalue;
}

template <class T>
double Point<T>::getXValue() {
    return x;
}

template <class T>
double Point<T>::getYValue() {
    return y;
}

template <class T>
void Point<T>::display() {
    cout<< "(" << x << ", " << y << ")" << endl; // Formatted in this manner (x, y)
}

template <class T>
void Point<T>::display(ostream& s) {
    s << "(" << x << ", " << y << ")";
}

template <class T>
ostream& operator<<(ostream& s, Point<T>& p) {
    p.display(s);
    return s;
}

template <class T>
class Math {
public:
    static double squareroot(T number);
    static T round(T var);
    static double abs(double number);
};

template <class T>
double Math<T>::squareroot(T number) {
    double eps = 1e-6;
    double k = number;
    double l = 0.0, r, mid;

    if (k>=1) {
        r = k;
    }
    if (k<1)  {
        r = 1;
    }

    while (l-k/l > eps || l-k/l < -eps)
    {
        mid = l + (r - l) /2 ;
        if (mid<k/mid)
        {
            l = mid;
        }
        else {
            r = mid;
        }
    }
//    cout << "This is a test of squareroot: " << l << endl;
    return l;
}



template <class T>
T Math<T>::round(T var) {
    T value = (int)(var * 100.0);
    T result = (double)value / 100.0;
//    cout << "This is a test of round: " << result << endl;
    return result;
}

template <class T>
double Math<T>::abs(double number) {
    double result = number;
    if (number < 0)   {
        result = (number * -1);
    }
    return result;
}

template <class T>
class LineSegment {
protected:
    Point<T> P1;
    Point<T> P2;
    T x1; // x in P1
    T x2; // x in P2
    T y1; // y in P1
    T y2; // y in P2
public:
    LineSegment (); //default constructor
    LineSegment (Point<T> one, Point<T> two);
    double length(); //return the length of the line segment
    Point<T> midpoint (); //return the midpoint of the line segment
    double xIntercept (); //return the x-intercept of the line segment
    double yIntercept (); //return the y-intercept of the line segment
    double slope (); //return the slope of the line segment
    bool itIntersects (LineSegment L); //returns true if L intersects with the line segment
    Point<T> intersectionPoint (LineSegment L); // returns the point in which two line segments intersect
    bool isParallel (LineSegment L); //check if slopes are same
    void displayEquation (); // Prints in the format y=mx+b
    Point<T> getP1 ();
    Point<T> getP2 ();
    void display(ostream& s);
};

template<class T>
LineSegment<T>::LineSegment() {
    //Shouldn't be used.
}

template<class T>
LineSegment<T>::LineSegment(Point<T> one, Point<T> two) {
    P1 = one;
    P2 = two;
    x1 = P1.getXValue();
    x2 = P2.getXValue();
    y1 = P1.getYValue();
    y2 = P2.getYValue();
}

template<class T>
double LineSegment<T>::length() {
    double length;
    length = Math<T>::squareroot(((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2)));
    return length;
}
template<class T>
Point<T> LineSegment<T>::midpoint() {
    try {
        if (length() == 0)   {
            throw LineSegmentException("midpoint of the line segment has a length of 0.");
        }
    }
    catch (LineSegmentException e)   {
        cout << e.getMessage();
    }
    double xValue = Math<T>::round((x1 + x2)/2);
    double yValue = Math<T>::round((y1 + y2)/2);
    Point<T> midPoint(xValue, yValue);
    return midPoint;
}

template<class T>
double LineSegment<T>::xIntercept() {
    double xIntercept;
    xIntercept = x1 - (((x2-x1)/(y2-y1))*(y1));
    return xIntercept;

}

template<class T>
double LineSegment<T>::yIntercept() {
    double yIntercept;
    yIntercept = y1 - (((y2 - y1)/(x2 - x1))*x1);
    return yIntercept;
}

template<class T>
double LineSegment<T>::slope() {
    double slope =(y2 - y1)/(x2-x1);
    return slope;
}

template<class T>
void LineSegment<T>::displayEquation() {
    cout << "y=" << Math<T>::round(slope()) << "*x+" << Math<T>::round(yIntercept()) << endl;
    //Formatted in this manner y=mx+b
}

template<class T>
bool LineSegment<T>::isParallel(LineSegment L) {
    double slopeOne = Math<T>::round(slope());
    double slopeTwo = Math<T>::round(L.slope());
    if ( slopeOne == slopeTwo )   { // If the slopes of the two lines are the same the they are parallel
        return true;
    }
    else   {
        return false;
    }
}

template<class T>
Point<T> LineSegment<T>::intersectionPoint(LineSegment L) {
    double x = Math<T>::round((L.yIntercept() - yIntercept())/(slope() - L.slope()));
    double y = Math<T>::round(((yIntercept()*L.slope())-(L.yIntercept()*slope()))/(L.slope() - slope()));
    Point<T> intersection ( x, y ); //Puts the x and y values in to a point to be returned
    return intersection;
}

template<class T>
bool LineSegment<T>::itIntersects(LineSegment L) {
    bool doesIntersect;

    double d1u1 = getP2().getXValue() - getP1().getXValue();
    double d1v1 = getP2().getYValue() - getP1().getYValue();
    double d1u2 = L.getP1().getXValue() - getP1().getXValue();
    double d1v2 = L.getP1().getYValue() - getP1().getYValue();

    double d1 = (d1u1 * d1v2) - (d1u2 * d1v1); // d1 = P1->P2 x P1->Q1

    double d2u1 = getP2().getXValue() - getP1().getXValue();
    double d2v1 = getP2().getYValue() - getP1().getYValue();
    double d2u2 = L.getP2().getXValue() - getP1().getXValue();
    double d2v2 = L.getP2().getYValue() - getP1().getYValue();

    double d2 = (d2u1 * d2v2) - (d2u2 * d2v1); //d2 = P1->P2 x P1->Q2

    double d3u1 = L.getP2().getXValue() - L.getP1().getXValue();
    double d3v1 = L.getP2().getYValue() - L.getP1().getYValue();
    double d3u2 = getP1().getXValue() - L.getP1().getXValue();
    double d3v2 = getP1().getYValue() - L.getP1().getYValue();

    double d3 = (d3u1 * d3v2) - (d3u2 * d3v1); //d3 = Q1->Q2 x Q1->P1

    double d4u1 = L.getP2().getXValue() - L.getP1().getXValue();
    double d4v1 = L.getP2().getYValue() - L.getP1().getYValue();
    double d4u2 = getP2().getXValue() - getP1().getXValue();
    double d4v2 = getP2().getYValue() - getP1().getYValue();

    double d4 = (d4u1 * d4v2) - (d4u2 * d4v1); //d4 = Q1->Q2 x P1->P2

    if ( ((d1 * d2 ) <= 0 ) && ((d3 * d4) <= 0))   { //Intersects if d1d2 <= 0, d3d4 <= 0
        doesIntersect = true;
    }
    else   {
        doesIntersect = false;
    }
    return doesIntersect;
}

template<class T>
Point<T> LineSegment<T>::getP1() {
    return P1;
}

template<class T>
Point<T> LineSegment<T>::getP2() {
    return P2;
}

template <class T>
void LineSegment<T>::display(ostream& s) {
    s << "(" << Math<T>::round(getP1().getXValue()) << ", " << Math<T>::round(getP1().getYValue()) << "),(" <<
      Math<T>::round(getP2().getXValue()) << ", " << Math<T>::round(getP2().getYValue()) << ")\n" <<
      "Slope:" << Math<T>::round(slope()) << "\n" << "Midpoint:" << "(" << midpoint().getXValue() << ", " <<
      midpoint().getYValue() << ")\n" << "X Intercept:" << Math<T>::round(xIntercept()) << "\n" <<
      "Y Intercept:" << Math<T>::round(yIntercept()) << "\n" << "Length:" << Math<T>::round(length()) << "\n" <<
      "y=" << Math<T>::round(slope()) << "*x+" << Math<T>::round(yIntercept());
}

template <class T>
ostream& operator<<(ostream& s, LineSegment<T>& p) {
    p.display(s);
    return s;
}



template<class T>
class Segments {
protected:
    LineSegment<T>* segments;
    int count;
    int maxSize;
public:
    Segments (); //Defualt constructor
    Segments (int size); //non-default constructor
    ~Segments();
    void addLineSegment (LineSegment<T> L);
    void removeLineSegment (LineSegment<T> L);
    void display();
    LineSegment<T> getLine (int arrayIndex);
    Segments<T> &findAllIntersection(LineSegment<T> ls);
    double distance (Point<T> P, LineSegment<T> L);
    LineSegment<T>& findClosest (Point<T>& aPoint);
    void display(ostream& s);
    int getCount();
};

template<class T>
Segments<T>::Segments () {
    segments = NULL;
    count = 0;
    maxSize = 0;
}

template<class T>
Segments<T>::Segments (int size) {
    segments = new LineSegment<T> [size]; //Assigns an array to the pointer segments.
    count = 0;
    maxSize = size;
}

template<class T>
void Segments<T>::addLineSegment(LineSegment<T> L) {
    segments[count] = L; //Adds a new line segment in the array at index count.
    count = count + 1; //Increases count by 1.
}

template <class T>
void Segments<T>::removeLineSegment(LineSegment<T> L) {
    LineSegment<T>* newArray = new LineSegment<T> [maxSize];
    int newCount = 0;

    for ( int i = 0; i < count; i++ )   {
        newArray[i] = segments[i];
    }
    segments = new LineSegment<T> [maxSize];

    for ( int i = 0; i < count; i++ )   {
        if (!((L.getP1().getYValue() == newArray[i].getP1().getYValue() &&
               L.getP1().getXValue() == newArray[i].getP1().getXValue()) &&
               (L.getP2().getYValue() == newArray[i].getP2().getYValue() &&
               L.getP2().getXValue() == newArray[i].getP2().getXValue())))   {
            segments[newCount] = newArray[i];
            newCount = newCount + 1;
        }
    }
    count = newCount;
}

template <class T>  //Finish
Segments<T>& Segments<T>::findAllIntersection(LineSegment<T> ls) {
    Segments<T> intersectingSegments(count);
    for ( int i = 0; i < count; i++ )   {
//        cout << "TESTING: ";
//        cout << ls.itIntersects(segments[i]) << endl;
        if (ls.itIntersects(segments[i]) && !((ls.getP1().getYValue() == segments[i].getP1().getYValue() &&
        ls.getP1().getXValue() == segments[i].getP1().getXValue()) && (ls.getP2().getYValue() == segments[i].getP2().getYValue() &&
        ls.getP2().getXValue() == segments[i].getP2().getXValue())))   {
            // &&'s are to make sure segment[i] does not equal ls by comparing all of its given points
//            cout<< "What line segment: " << i << endl;
            intersectingSegments.addLineSegment(segments[i]);
//            cout << "Count " << intersectingSegments.count << endl;
        }
    }
//    cout << "HIT";
    return intersectingSegments;
}

template <class T>
double Segments<T>::distance(Point<T> P, LineSegment<T> L) {
    double x0, y0, m, c;
    double temp, denominator, numerator;
    double distance;
    x0 = P.getXValue();
    y0 = P.getYValue();
    m = L.slope();
    c = L.yIntercept();//Assume yIntercept function returns double value. If yIntercept function returns Point, c = L.yIntercept().getYvalue(); Just be consistent with the function in Project 1.
    denominator = Math<T>::squareroot(1 + (m * m));
    double pre = m*x0 - y0 + c;
    numerator = Math<T>::abs(pre);

    distance = numerator/denominator;
    return distance;
}

template <class T>
LineSegment<T> & Segments<T>::findClosest(Point<T> &aPoint) {  // TODO BROKEN NEEDS TO BE FIXED
    double closestDistance = distance(aPoint, segments[0]);
    LineSegment<T> closestSegment = segments[0];
//    cout << closestSegment << endl;
    double fightingDisctance = distance(aPoint, segments[1]);
    LineSegment<T> fightingSegment = segments[1];

    for ( int i = 1; i < count; i++ )   {
        fightingDisctance = distance(aPoint, segments[i]);
        fightingSegment = segments[i];
        if ( fightingDisctance < closestDistance )   {
//            cout << "Fighter: \n" << segments[i] << endl;
            closestDistance = fightingDisctance;
            closestSegment = segments[i];
//            cout << "Winner: \n" << closestSegment << endl;
        }
    }

    return closestSegment;

}



template<class T>
void Segments<T>::display() {
    int segmentCounter = 1; // Keeps count of what line segment is being displayed
    for ( int i = 0; i < count; i++ )   {
        cout << "Line Segment " << segmentCounter << ":" << endl; // Line Segment #:
        cout << segments[i] << endl;
//        cout << "(" << Math<T>::round(segments[i].getP1().getXValue()) << ", " << Math<T>::round(segments[i].getP1().getYValue()) << "),(" <<
//             Math<T>::round(segments[i].getP2().getXValue()) << ", " << Math<T>::round(segments[i].getP2().getYValue()) << ")" << endl;
//        // (x, y),(x, y)
//
//        cout << "Slope:" << Math<T>::round(segments[i].slope()) << endl; // Slope:m
//
//        cout << "Midpoint:";
//        segments[i].midpoint().display(); //Midpoint:(x, y)
//
//        cout << "X Intercept:" << Math<T>::round(segments[i].xIntercept()) << endl; // X Intercept:x
//        cout << "Y Intercept:" << Math<T>::round(segments[i].yIntercept()) << endl; // Y Intercept:y
//
//        cout << "Length:" << Math<T>::round(segments[i].length()) << endl; // Length:#
//
//        segments[i].displayEquation(); // y=mx+b
        segmentCounter = segmentCounter + 1;
    }
}

template<class T>
LineSegment<T> Segments<T>::getLine(int arrayIndex) {
    return segments[arrayIndex];
}

template <class T>
Segments<T>::~Segments() {
    cout << "Destructor Called" << endl;
//    delete []segments;
}

template <class T>
void Segments<T>::display(ostream &s) {
    display();
    s << "";
}

template <class T>
int Segments<T>::getCount() {
    
}

template <class T>
ostream& operator<<(ostream& s, Segments<T>& p) {
    p.display(s);
    return s;
}




int main() {
    double linePoint1; // x value of a point
    double linePoint2; // y value of a point
    double linePoint3; // x value of a point
    double linePoint4; // y value of a point
    char command;
    int noOfSegments;
    cin >> noOfSegments;
    Segments<double> segments (noOfSegments); // Constructor for Segments
    while (!cin.eof()) {
        cin >> command;
        switch (command) {
            case 'A': {
                cin >> linePoint1 >> linePoint2 >> linePoint3 >> linePoint4; // Inputs the x and y values of a line segment
                Point<double> pointOne (linePoint1, linePoint2);
                Point<double> pointTwo (linePoint3, linePoint4);
                LineSegment<double> line (pointOne, pointTwo);
                segments.addLineSegment(line); // Adds the new line segment to the Segments class's array
                break;
            }
            case 'R': {
                cin >> linePoint1 >> linePoint2 >> linePoint3 >> linePoint4; // Inputs the x and y values of a line segment
                Point<double> pointOne (linePoint1, linePoint2);
                Point<double> pointTwo (linePoint3, linePoint4);
                LineSegment<double> line (pointOne, pointTwo);
                segments.removeLineSegment(line);
                break;
            }
            case 'D': {
                for ( int i = 0; )
            }
            case 'P': {}
            case 'I': {}
            case 'C': {}
            default: cout << "Invalid command" << endl;
        }
    }

















//    double linePoint1; // x value of a point
//    double linePoint2; // y value of a point
//    double linePoint3; // x value of a point
//    double linePoint4; // y value of a point
//    int numberOfLines; // Number of line segments to be input
//
//    cin >> numberOfLines; // Inputs the number of line segments to be input
//
//    Segments<double> interval (numberOfLines); // Constructor for Intervals
//
//    for ( int i = 0; i < numberOfLines; i++ )   {
//        cin >> linePoint1 >> linePoint2 >> linePoint3 >> linePoint4; // Inputs the x and y values of a line segment
//        Point<double> pointOne (linePoint1, linePoint2);
//        Point<double> pointTwo (linePoint3, linePoint4);
////        cout << "TEST OF POINT COUT: " << pointOne << endl; // TESTING CODE SDOJHFDISOHF
//        LineSegment<double> line (pointOne, pointTwo);
////        cout << "TESTING LINESEGMENT COUT: \n" << line << endl;
//        interval.addLineSegment(line); // Adds the new line segment to the Interval class's array
//    }
//    cout << "Testing <<: \n" << interval << endl;
//    interval.display(); // Displays the information about the line segments
//
//
//    cout << "\n\n\n\n\n\n\n" << "findAllInterects:" << endl;
//    Segments<double> newarray = interval.findAllIntersection(interval.getLine(3));
//    newarray.display();
//
//    cout << "\n\n\n\n\n" << "findClosest: " << endl;  //Finish
//    Point<double> closest(1,3);
//    LineSegment<double> newSegment = interval.findClosest(closest);
//    cout << newSegment;



//
//    bool doesIntersect = false;
//    int jCounter = 1; /* Keeps track of j so that every time j's for loop is called
// * it starts 1 higher than the previous time */
//
//    for ( int i = 0; i < numberOfLines; i++ )   {
//        for ( int j = jCounter; j < numberOfLines; j++ )   { // j's for loop compares line segments to i's line segment
//            if (!(i == j))   {
//                doesIntersect = interval.getLine(i).itIntersects(interval.getLine(j));
//                if (doesIntersect)   {
//                    cout << "The line segments compared are segments[" << i << "] and segments[" << j <<
//                         "]: Intersection Point :";
//                    interval.getLine(i).intersectionPoint(interval.getLine(j)).display();
//                }
//                else if (!doesIntersect && !interval.getLine(i).isParallel(interval.getLine(j)))   {
//                    cout << "The line segments compared are segments[" << i << "] and segments[" << j <<
//                         "]: Not Parallel and not Intersecting" << endl;
//                }
//                else {
//                    cout << "The line segments compared are segments[" << i << "] and segments[" << j <<
//                         "]: Lines are Parallel" << endl;
//                }
//            }
//        }
//        jCounter = jCounter + 1;
//    }
    return 0;
}
