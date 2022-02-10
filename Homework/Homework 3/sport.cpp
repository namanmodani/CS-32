//
// CS 32 Homework 3
// Naman Modani
// Problem 1: sport.cpp
//

class Sport
{
public:
    Sport(string sportName)
    {
        m_name = sportName;
    }
    virtual ~Sport() {};
    string name() const
    {
        return m_name;
    }
    virtual string icon() const = 0;
    virtual bool isOutdoor() const = 0;
private:
    string m_name;
};

class Biathlon: public Sport
{
public:
    Biathlon(string name, double distance): Sport(name)
    {
        m_distance = distance;
    }
    ~Biathlon()
    {
        cout << "Destroying the Biathlon object named " << name() << ", distance " << m_distance << " km." << endl;
    }
    virtual string icon() const
    {
        return "a skier with a rifle";
    }
    virtual bool isOutdoor() const
    {
        return true;
    }
private:
    double m_distance;
};

class Snowboarding: public Sport
        {
public:
    Snowboarding(string name) : Sport(name) {}
    ~Snowboarding()
    {
        cout << "Destroying the Snowboarding object named " << name() << "." << endl;
    }
    virtual string icon() const
    {
        return "a descending snowboarder";
    }
    virtual bool isOutdoor() const
    {
        return true;
    }
};

class FigureSkating: public Sport
{
public:
    FigureSkating(string name): Sport(name) {}
    ~FigureSkating()
    {
        cout << "Destroying the FigureSkating object named " << name() << "." << endl;
    }
    virtual string icon() const
    {
        return "a skater in the Biellmann position";
    }
    virtual bool isOutdoor() const
    {
        return false;
    }
};