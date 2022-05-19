#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H

#include <iostream>

class HealthPoints {
public:
    HealthPoints(int maxHP = 100);

    HealthPoints(const HealthPoints&) = default;

    HealthPoints& operator=(const HealthPoints&) = default;

    ~HealthPoints() = default;

    HealthPoints operator+(int x);

    HealthPoints operator-(int x);

    HealthPoints& operator+=(int x);

    HealthPoints& operator-=(int x);

    bool operator ==(const HealthPoints& rightSideHP) const;

    bool operator !=(const HealthPoints& rightSideHP) const;

    bool operator >(const HealthPoints& rightSideHP) const;

    bool operator >=(const HealthPoints& rightSideHP) const;

    bool operator <(const HealthPoints& rightSideHP) const;

    bool operator <=(const HealthPoints& rightSideHP) const;

    class InvalidArgument {};

    //to be deleted
    int retHP();
private:
    int m_HP, m_maxHP;

    friend std::ostream& operator<<(std::ostream&, const HealthPoints&);
};


#endif //HEALTHPOINTS_H
