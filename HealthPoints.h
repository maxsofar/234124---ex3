#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H

#include <iostream>

class HealthPoints {
public:
    HealthPoints(int maxHP = 100);

    HealthPoints(const HealthPoints&) = default;

    HealthPoints& operator=(const HealthPoints&) = default;

    ~HealthPoints() = default;

    HealthPoints& operator+=(int x);

    HealthPoints& operator-=(int x);

    HealthPoints operator-(int x);

    bool operator ==(const HealthPoints& rightSide) const;

    bool operator !=(const HealthPoints& rightSide) const;

    bool operator >(const HealthPoints& rightSide) const;

    bool operator >=(const HealthPoints& rightSide) const;

    bool operator <(const HealthPoints& rightSide) const;

    bool operator <=(const HealthPoints& rightSide) const;

    class InvalidArgument {};

private:
    int m_HP, m_maxHP;

    friend HealthPoints operator+(int x, const HealthPoints& hp);

    friend std::ostream& operator<<(std::ostream&, const HealthPoints&);
};

HealthPoints::HealthPoints(int maxHP) {
    if (maxHP <= 0) {
        throw (InvalidArgument());
    }
    m_HP = m_maxHP = maxHP;
}

HealthPoints& HealthPoints::operator+=(int x) {
    if (m_HP + x > m_maxHP) {
        m_HP = m_maxHP;
    } else {
        m_HP = m_HP + x;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(int x) {
    if (m_HP - x < 0) {
        m_HP = 0;
    } else {
        m_HP = m_HP - x;
    }
    return *this;
}

HealthPoints operator+(int x, const HealthPoints& hp) {
    HealthPoints result(hp);
    if (hp.m_HP + x > hp.m_maxHP) {
        result.m_HP = hp.m_maxHP;
    } else {
        result.m_HP += x;
    }
    return result;
}

HealthPoints HealthPoints::operator-(int x) {
    HealthPoints result(*this);
    if (this->m_HP - x  < 0) {
        result.m_HP = 0;
    } else {
        result.m_HP -= x;
    }
    return result;
}

bool HealthPoints::operator==(const HealthPoints& rightSide) const {
    if (this->m_HP == rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator!=(const HealthPoints& rightSide) const {
    if (this->m_HP != rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator>(const HealthPoints& rightSide) const {
    if (this->m_HP > rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator>=(const HealthPoints& rightSide) const {
    if (this->m_HP >= rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator<(const HealthPoints& rightSide) const {
    if (this->m_HP < rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator<=(const HealthPoints& rightSide) const {
    if (this->m_HP <= rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints1) {
    os << healthPoints1.m_HP << '(' << healthPoints1.m_maxHP << ')';
    return os;
}

#endif //HEALTHPOINTS_H
