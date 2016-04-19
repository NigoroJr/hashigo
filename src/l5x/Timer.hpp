#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <string>

/**
 * Timer module in an L5X file.
 */
struct Timer {
    /* Constructors, Destructor, and Assignment operators {{{ */
    // Default constructor
    Timer();

    // Copy constructor
    Timer(const Timer& other);

    // Move constructor
    Timer(Timer&& other);

    // Destructor
    ~Timer();

    // Assignment operator
    Timer&
    operator=(const Timer& other);

    // Move assignment operator
    Timer&
    operator=(Timer&& other);
    /* }}} */

    bool
    operator==(const Timer& other) const;

    bool
    operator!=(const Timer& other) const;

    std::string name;

    unsigned PRE;
    unsigned ACC;
    bool EN;
    bool TT;
    bool DN;
};

/* Constructors, Destructor, and Assignment operators {{{ */
// Default constructor
inline
Timer::Timer()
    : name{}
    , PRE{0}
    , ACC{0}
    , EN{false}
    , TT{false}
    , DN{false}
{
}

// Copy constructor
inline
Timer::Timer(const Timer& other)
    : name{other.name}
    , PRE{other.PRE}
    , ACC{other.ACC}
    , EN{other.EN}
    , TT{other.TT}
    , DN{other.DN}
{
}

// Move constructor
inline
Timer::Timer(Timer&& other)
    : name{std::move(other.name)}
    , PRE{std::move(other.PRE)}
    , ACC{std::move(other.ACC)}
    , EN{std::move(other.EN)}
    , TT{std::move(other.TT)}
    , DN{std::move(other.DN)}
{
}

// Destructor
inline
Timer::~Timer()
{
}

// Assignment operator
inline Timer&
Timer::operator=(const Timer& other) {
    name = other.name;
    PRE = other.PRE;
    ACC = other.ACC;
    EN = other.EN;
    TT = other.TT;
    DN = other.DN;
    return *this;
}

// Move assignment operator
inline Timer&
Timer::operator=(Timer&& other) {
    name = std::move(other.name);
    PRE = std::move(other.PRE);
    ACC = std::move(other.ACC);
    EN = std::move(other.EN);
    TT = std::move(other.TT);
    DN = std::move(other.DN);
    return *this;
}
/* }}} */

inline bool
Timer::operator==(const Timer& other) const {
    return name == other.name;
}

inline bool
Timer::operator!=(const Timer& other) const {
    return name != other.name;
}

/**
 * Hash function for the Timer class.
 */
namespace std {
    template<>
    struct hash<Timer> {
        std::size_t
        operator()(const Timer& t) const {
            return std::hash<std::string>()(t.name);
        }
    };
} // namespace std

#endif /* end of include guard */
