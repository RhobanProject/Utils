/*****************************************************************************/
/*! \file    option.hh
 *  \author  AV
 *  \date    2010-03
 *
 *  \brief   A simple template to mimic ML's option/None/Some
 *****************************************************************************/

#ifndef OPTION_HH
#define OPTION_HH

class OptionNoValueExc {};

template <typename T>
class Option
{
  T stored;
  bool isSome;

public:
  /*! \brief Default constructor, similar to None in ML */
  Option()
  {
    isSome = false;
  }
  /*! \brief Constructor with a value, similar to Some in ML */
  Option(T val)
  {
    stored = val;
    isSome = true;
  }

  /*! \brief Copy constructor */
  Option(const Option &other) :
    stored(other.stored),
    isSome(other.isSome)
  {};

  /*! \brief Check if a value is stored */
  bool hasValue() const
  {
    return isSome;
  }

  /*! \brief Get the value if present, throw a dirty exception otherwise */
  T getValue() const
  {
    if (!isSome)
      throw OptionNoValueExc();
    return stored;
  }

  /*! \brief Get the address of the value if present, throw a dirty exception
   *  otherwise */
  T * getValueAddr()
  {
    if (!isSome)
      throw OptionNoValueExc();
    return & stored;
  }
};

#endif /* OPTION_HH */
