#ifndef _PATTERNS_VALUE_H
#define _PATTERNS_VALUE_H

template<typename T>
class Value
{
    public:
        void set(T value_) {
            value = value_;
            defined = true;
        }

        T &get() {
            return value;
        }

        bool isDefined() {
            return defined;
        }

        void define() {
            defined = true;
        }

        void undefine() {
            defined = false;
        }

    protected:
        bool defined;
        T value;
};

#endif
