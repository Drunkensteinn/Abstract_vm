#include "../inc/IOperands.h"


CreateOperands::CreateOperands() {
	factory[Int8] = &createInt8;
	factory[Int16] = &createInt16;
	factory[Int32] = &createInt32;
	factory[Float] = &Float;
	factory[Double] = &Double;
}

CreateOperands::~CreateOperands() {

}

CreateOperands &CreateOperands::operator=(CreateOperands const &r) {
	if (this != &r)
	{
		this->_value = c._value;
		this->type_ = c.type_;
	}
	return (*this);
}

CreateOperands::CreateOperands(CreateOperands const &c) {
	this->_value = c._value;
	this->type_ = c.type_;
}

IOperand const *CreateOperands::createOperand(eOperandType type, std::string const &value) const {
	return nullptr;
}


IOperand const *CreateOperands::createDouble(std::string const &value) const {
	return new Operand<double>(value, Double, 7);
}

IOperand const *CreateOperands::createFloat(std::string const &value) const {
	return new Operand<float>(value, Float, 5);
}

IOperand const *CreateOperands::createInt32(std::string const &value) const {
	return new Operand<int32_t>(value, Int32, 0);
}

IOperand const *CreateOperands::createInt16(std::string const &value) const {
	return new Operand<int16_t>(value, Int16, 0);
}

IOperand const *CreateOperands::createInt8(std::string const &value) const {
	return new Operand<int8_t>(value, Int8, 0);
}