/*
ADT design Rectangle
characteristics(data): length, width
behaviors(function): area(), perimeter()
*/

class RectangleInterface
{
public:
    virtual int area() const = 0;
    virtual int perimeter() const = 0;
};

class Rectangle : public RectangleInterface
{
private:
    int length = 0;
    int width = 0;
public:
    Rectangle(int len, int wid);
    int area() const;
    int perimeter() const;
};

//setting and retrieving the dimensions of the rectangle
Rectangle::Rectangle(int len, int wid)
{
    length = len;
    width = wid;
};

//finding the area of the rectangle
int Rectangle::area() const
{
    return (length * width);
};

//finding the perimeter of the rectangle
int Rectangle::perimeter() const
{
    return ((length + width) * 2);
};