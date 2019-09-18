

#ifndef ABSTRACTVM_IVM_H
#define ABSTRACTVM_IVM_H

#define LEXER 0
#define PARSER 1

class IVirtualMachine
{
public:
	virtual void execute(void) = 0;
	~IVirtualMachine() {};
};

#endif //ABSTRACTVM_IVM_H
