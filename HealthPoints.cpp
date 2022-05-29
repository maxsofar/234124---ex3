#include "HealthPoints.h"

HealthPoints::HealthPoints(int maxHP)
{
    if (maxHP <= 0) {
        throw (InvalidArgument());
    }
    m_HP = m_maxHP = maxHP;
}

HealthPoints& HealthPoints::operator+=(int hp)
{
    if(m_HP + hp < 0) {
        m_HP = 0;
    } else if (m_HP + hp > m_maxHP) {
        m_HP = m_maxHP;
    } else {
        m_HP = m_HP + hp;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(int hp) {
    if (m_HP - hp > m_maxHP) {
        m_HP = m_maxHP;
    } else if (m_HP - hp < 0) {
        m_HP = 0;
    } else {
        m_HP = m_HP - hp;
    }
    return *this;
}

HealthPoints HealthPoints::operator+(int hp)
{
    HealthPoints result(*this);
    if (result.m_HP + hp < 0) {
        result.m_HP = 0;
    } else if (result.m_HP + hp > result.m_maxHP) {
        result.m_HP = result.m_maxHP;
    } else {
        result.m_HP += hp;
    }
    return result;
}

HealthPoints operator+(int hp, const HealthPoints& healthPoints)
{
    HealthPoints result(healthPoints);
    if (healthPoints.m_HP + hp < 0) {
        result.m_HP = 0;
    } else if (healthPoints.m_HP + hp > healthPoints.m_maxHP) {
        result.m_HP = healthPoints.m_maxHP;
    } else {
        result.m_HP += hp;
    }
    return result;
}

HealthPoints HealthPoints::operator-(int hp)
{
    HealthPoints result(*this);
    if (this->m_HP - hp > this->m_maxHP) {
        result.m_HP = this->m_maxHP;
    } else if (this->m_HP - hp  < 0) {
        result.m_HP = 0;
    } else {
        result.m_HP -= hp;
    }
    return result;
}

bool HealthPoints::operator!=(const HealthPoints& rightSide) const
{
    if (this->m_HP != rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator>(const HealthPoints& rightSide) const
{
    if (this->m_HP > rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator>=(const HealthPoints& rightSide) const
{
    if (this->m_HP >= rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator<(const HealthPoints& rightSide) const
{
    if (this->m_HP < rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool HealthPoints::operator<=(const HealthPoints& rightSide) const
{
    if (this->m_HP <= rightSide.m_HP) {
        return true;
    } else {
        return false;
    }
}

bool operator==(const HealthPoints& lhs, const HealthPoints& rhs)
{
    if (lhs.m_HP == rhs.m_HP) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints1)
{
    os << healthPoints1.m_HP << '(' << healthPoints1.m_maxHP << ')';
    return os;
}
