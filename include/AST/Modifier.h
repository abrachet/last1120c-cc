/**
 * @file Modifier.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

class Modifier {
public:
    using Type = int;

    enum Modifiers : Type {
        None     = 0,
        FuncArgs = 1 << 0,
        Register = 1 << 1,
        Auto     = 1 << 2,
        Pointer  = 1 << 3
    };

    constexpr Modifier() : modifiers(None)
    {}

    constexpr Modifier(Modifiers modifiers ) 
    : modifiers(modifiers) 
    {}

    inline Modifiers get()
    {
        return this->modifiers;
    }

    inline int as_int()
    {
        return (int) this->modifiers;
    }

    inline operator Type()
    {
        return (Type) this->modifiers;
    }

    inline Modifier operator|(Modifier other) {
        Type m = (Type) this->modifiers;
        Type o = (Type) other.modifiers;

        return Modifier((Modifiers) (m | o));
    }

    inline void operator|=(Modifier other) {
        Type m = (Type) this->modifiers;
        Type o = (Type) other.modifiers;

        m |= o;

        this->modifiers = (Modifiers) m;
    }

    inline bool is_none() const
    {
        return static_cast<Type>(this->modifiers) == 0;
    }

    inline bool is_func_arg() const
    {
        return this->modifiers & FuncArgs;
    }

    inline bool is_register() const
    {
        return this->modifiers & Register;
    }

    inline bool is_auto() const
    {
        return this->modifiers & Auto;
    }

    inline bool is_pointer() const
    {
        return this->modifiers & Pointer;
    }

    inline bool operator==(Modifier m) const
    {
        return this->modifiers == m.modifiers;
    }

private:
    Modifiers modifiers;
};
