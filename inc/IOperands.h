//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#ifndef ABSTRACTVM_IOPERANDS_H
#define ABSTRACTVM_IOPERANDS_H

#include <iostream>

#include "Error.h"
#include <boost/lexical_cast.hpp>

static const char * str_repr[5] = {"Int8", "Int16", "Int32", "Float", "Double"};

enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double,
};

class IOperand {
public:
	virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
	virtual eOperandType getType( void ) const = 0; // Type of the instance
//	virtual IOperand const * operator+(IOperand const & rhs) const = 0; // Sum
//	virtual IOperand const * operator-(IOperand const & rhs) const = 0; // Difference
//	virtual IOperand const * operator*(IOperand const & rhs) const = 0; // Product
//	virtual IOperand const * operator/(IOperand const & rhs) const = 0; // Quotient
//	virtual IOperand const * operator%(IOperand const & rhs) const = 0; // Modulo
	virtual std::string const & toString(void) const = 0; // String representation of the instance
	virtual ~IOperand( void ) {}
};

template <typename T>
class Operand:IOperand
{
public:
	Operand(std::string const & v, eOperandType type, size_t precision): _type(type), _precision(precision) {
		try {
			if (_type >= Float)
				floated_point_value(v);
			else
			{
				if (_type <= Int8)
				{
					int32_t v_ = boost::lexical_cast<int32_t>(v);

					if (v_	> static_cast<int32_t>(std::numeric_limits<char>::max()) or
						v_	< static_cast<int32_t>(std::numeric_limits<char>::min()))
						throw Error(std::string("Error: Overflowing operand ") + _str_repr);
					_value = static_cast<int8_t>(v_);
				}
				else
				{
					int64_t v_ = boost::lexical_cast<int64_t>(v);

					if (v_  > static_cast<T>(std::numeric_limits<T>::max()) or
						v_  < static_cast<T>(std::numeric_limits<T>::min()))
						throw Error(std::string("Error: Overflowing operand ") + _str_repr);
					_value = static_cast<T>(v_);
				}
			}
		}
		catch (boost::bad_lexical_cast &e){
			throw Error(std::string("Error: unknown error"));
		}
	}

	void floated_point_value(std::string v)
	{

	}


	std::string const & toString(void) const 		{ return this->_str_repr; }
	int 				getPrecision( void ) const 	{ return this->_precision; }
	eOperandType		getType(void) const 		{ return this->_type; }
	T const &			get_value(void) const 		{ return this->_value; }



//	IOperand const * operator+(IOperand const & rhs);
//	IOperand const * operator-(IOperand const & rhs);
//	IOperand const * operator*(IOperand const & rhs);
//	IOperand const * operator/(IOperand const & rhs);
//	IOperand const * operator%(IOperand const & rhs);

	~Operand() {};
private:
	eOperandType	_type;
	std::string		_str_repr = str_repr[_type];
	T				_value;
	size_t			_precision;
};

template <typename T>
std::ostream &operator<<(std::ostream &stream, Operand<T> const &op)
{
	stream << "The value is  - " << op.get_value();
	return stream;
}



class CreateOperands
{
public:

	IOperand const * createOperand(eOperandType type, std::string const & value) const;

private:
	std::string type_;

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;
};


#endif //ABSTRACTVM_IOPERANDS_H
