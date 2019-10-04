/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IVm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:59:14 by ablizniu          #+#    #+#             */
/*   Updated: 2019/10/01 17:59:52 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IVM_H
#define IVM_H

#define LEXER 0
#define PARSER 1

class IVirtualMachine
{
public:
	virtual void execute(void) = 0;
	~IVirtualMachine() {};
};

#endif //ABSTRACTVM_IVM_H
