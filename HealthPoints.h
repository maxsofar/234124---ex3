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

HealthPoints::HealthPoints(int maxHP) {
    if (maxHP <= 0) {
        throw InvalidArgument();
    }
    m_HP = m_maxHP = maxHP;
}

HealthPoints HealthPoints::operator+(int x) {
    HealthPoints result(*this);
    if (this->m_HP + x > this->m_maxHP) {
        result.m_HP = this->m_maxHP;
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

bool HealthPoints::operator==(const HealthPoints &rightSideHP) const {
    if (this->m_HP == rightSideHP.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator!=(const HealthPoints &rightSideHP) const {
    if (this->m_HP != rightSideHP.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator>(const HealthPoints &rightSideHP) const {
    if (this->m_HP > rightSideHP.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator>=(const HealthPoints &rightSideHP) const {
    if (this->m_HP >= rightSideHP.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator<(const HealthPoints &rightSideHP) const {
    if (this->m_HP < rightSideHP.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator<=(const HealthPoints &rightSideHP) const {
    if (this->m_HP <= rightSideHP.m_HP) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints1) {
    os << healthPoints1.m_HP << "(" << healthPoints1.m_maxHP << ")" << std::endl;
    return os;
}


int HealthPoints::retHP() {return m_HP;};

int main() {
    HealthPoints healthPoints2(120);
    healthPoints2 -= 100;
    std::cout << "You have: " << healthPoints2.retHP() << "HP" << std::endl;
    healthPoints2 = healthPoints2 + 5;
    std::cout << "You have: " << healthPoints2.retHP() << "HP" << std::endl;
};


#endif //HEALTHPOINTS_H
