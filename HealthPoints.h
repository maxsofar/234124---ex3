#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H

#include <iostream>

class HealthPoints {
public:
    /*
     * C'tor of HealthPoints class
     *
     * @param maxHP - The maximal amount of Health Points.
     * @return
     *      A new instance of HealthPoints.
    */
    HealthPoints(int maxHP = DEFAULT_HP);

    /*
     * Default Copy Constructor, Destructor, and Assignment operator overloading
    */
    HealthPoints(const HealthPoints&) = default;

    HealthPoints& operator=(const HealthPoints&) = default;

    ~HealthPoints() = default;

    /*
     * += operator overloading
     *
     * @param hp - The number of Health Points to be added.
     * @return
     *      The instance of HealthPoints that called the operator.
    */
    HealthPoints& operator+=(int hp);

    /*
     * + operator overloading (HealthPoints instance on left side)
     *
     * @param hp - The number of HP to be added.
     * @return
     *      New instance of HealthPoints with HP added.
    */
    HealthPoints operator+(int hp);

    /*
     * -= operator overloading
     *
     * @param hp - The number of Health Points to be subtracted.
     * @return
     *      The instance of HealthPoints that called the operator.
    */
    HealthPoints& operator-=(int hp);

    /*
     * - (minus) operator overloading
     *
     * @param hp - The number of Health Points to be subtracted.
     * @return
     *      New instance of HealthPoints with HP subtracted.
    */
    HealthPoints operator-(int hp);

    /*
     * != operator overloading
     *
     * @param rightSide - The instance of HealthPoints to be compared to.
     * @return
     *      True if HealthPoints instances are not equal
     *      False else
    */
    bool operator !=(const HealthPoints& rightSide) const;

    /*
     * > operator overloading
     *
     * @param rightSide - The instance of HealthPoints to be compared to.
     * @return
     *      True if number of HP is greater in HealthPoints instance that called the operator
     *      False else
    */
    bool operator >(const HealthPoints& rightSide) const;

    /*
     * >= operator overloading
     *
     * @param rightSide - The instance of HealthPoints to be compared to.
     * @return
     *      True if number of HP is greater OR equal in HealthPoints instance that
     *      called the operator
     *      False else
    */
    bool operator >=(const HealthPoints& rightSide) const;

    /*
     * < operator overloading
     *
     * @param rightSide - The instance of HealthPoints to be compared to.
     * @return
     *      True if number of HP is lesser in HealthPoints instance that called the operator
     *      False else
    */
    bool operator <(const HealthPoints& rightSide) const;

    /*
     * <= operator overloading
     *
     * @param rightSide - The instance of HealthPoints to be compared to.
     * @return
     *      True if number of HP is lesser OR equal in HealthPoints instance that
     *      called the operator
     *      False else
    */
    bool operator <=(const HealthPoints& rightSide) const;

    /*
     * InvalidArgument class declaration/empty implementation
     *
     * It is used be thrown as exception in case zero or negative number received in
     * HealthPoints C'tor
    */
    class InvalidArgument {};

private:
    static const int DEFAULT_HP = 100;
    int m_HP, m_maxHP;

    /*
     * + operator overloading (HealthPoints instance on right side)
     *
     * @param hp - The number of HP to be added.
     * @param HealthPoints - instance of the class to which the HP will be added.
     * @return
     *      New instance of HealthPoints with HP added.
    */
    friend HealthPoints operator+(int hp, const HealthPoints& rhs);

    /*
     * == operator overloading
     *
     * @param lhs - The instance of HealthPoints to be compared to on the left side
     * @param rhs - The instance of HealthPoints to be compared to on the right side
     * @return
     *      True if HealthPoints instances are equal
     *      False else
    */
    friend bool operator==(const HealthPoints& lhs, const HealthPoints& rhs);

    /*
     * << operator overloading
     *
     * @param ostream - I/O stream the info will be forwarded to.
     * @param HealthPoints - HealthPoints instance that called the operator.
     * @return
     *      I\O stream
    */
    friend std::ostream& operator<<(std::ostream&, const HealthPoints&);
};

#endif //HEALTHPOINTS_H
