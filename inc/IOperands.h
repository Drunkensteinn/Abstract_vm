//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#ifndef ABSTRACTVM_IOPERANDS_H
#define ABSTRACTVM_IOPERANDS_H

#include <iostream>

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
	virtual IOperand const * operator+(IOperand const & rhs) const = 0; // Sum
	virtual IOperand const * operator-(IOperand const & rhs) const = 0; // Difference
	virtual IOperand const * operator*(IOperand const & rhs) const = 0; // Product
	virtual IOperand const * operator/(IOperand const & rhs) const = 0; // Quotient
	virtual IOperand const * operator%(IOperand const & rhs) const = 0; // Modulo
	virtual std::string const & toString(void) const = 0; // String representation of the instance
	virtual ~IOperand( void ) {}
};



template <typename T>
class Operand:IOperand
{
public:
	Operand(std::string const & v, eOperandType type, size_t precision): _type(type), _precision(precision) {
	switch(type) {
		case (Int8):
			_value = std::stoi(v);
	}
	}
	~Operand() {};

	std::string const & toString(void) const { return this->_type; }

private:
	eOperandType	_type;
	T				_value;
	size_t			_precision;
};





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
