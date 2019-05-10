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

    Modifier() : modifiers(None)
    {}

    Modifier(Modifiers modifiers ) 
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

    inline bool is_none()
    {
        return this->modifiers & None;
    }

    inline bool is_func_arg()
    {
        return this->modifiers & FuncArgs;
    }

    inline bool is_register()
    {
        return this->modifiers & Register;
    }

    inline bool is_auto()
    {
        return this->modifiers & Auto;
    }

private:
    Modifiers modifiers;
};
