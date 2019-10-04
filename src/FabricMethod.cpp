/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FabricMethod.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:59:00 by ablizniu          #+#    #+#             */
/*   Updated: 2019/10/01 17:59:00 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IOperands.h"

CreateOperands::CreateOperands() {
	factory.push_back(&CreateOperands::createInt8);
	factory.push_back(&CreateOperands::createInt16);
	factory.push_back(&CreateOperands::createInt32);
	factory.push_back(&CreateOperands::createFloat);
	factory.push_back(&CreateOperands::createDouble);
}

CreateOperands::~CreateOperands() {

}

CreateOperands &CreateOperands::operator=(CreateOperands const &r) {
	if (this != &r)
	{
		this->type_ = r.type_;
		this->factory = r.factory;
	}
	return (*this);
}

CreateOperands::CreateOperands(CreateOperands const &c) {
	this->type_ = c.type_;
	this->factory = c.factory;
}

IOperand const *CreateOperands::createOperand(eOperandType type, std::string const &value) const {
	const IOperand *(CreateOperands::*pFunction)(std::string const &) const;

	pFunction = this->factory.at(type);
	return (*this.*pFunction)(value);
}

IOperand const *CreateOperands::createDouble(std::string const &value) const {
	return new Operand<double>(value, Double, 7, this);
}

IOperand const *CreateOperands::createFloat(std::string const &value) const {
	return new Operand<float>(value, Float, 5, this);
}

IOperand const *CreateOperands::createInt32(std::string const &value) const {
	return new Operand<int32_t>(value, Int32, 0, this);
}

IOperand const *CreateOperands::createInt16(std::string const &value) const {
	return new Operand<int16_t>(value, Int16, 0, this);
}

IOperand const *CreateOperands::createInt8(std::string const &value) const {
	return new Operand<int8_t>(value, Int8, 0, this);
}