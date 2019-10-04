/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:58:07 by ablizniu          #+#    #+#             */
/*   Updated: 2019/10/01 17:59:52 by ablizniu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

#define INVALID_NUMBER_OF_ARGS "Error. Invalid number of arguments."

#define BAD_FILE "Error. Unable to open a file."

#define OVERFLOWED "Error: overflowed value"

#define DIVISION_ZERO  "Error: division by zero"

#define MOD_FP_ERROR "Mod instruction on floated point value"

#define INVALID_OPERADN "Error: Invalid Operand type"

#define POP_EMPTY "Error: Pop on empty stack"

#define ASSERT_FAILED "Error: assert failed"

#define ADD_EMPTY "Error: Add instruction on empty stack"

#define SUB_EMPTY "Error: Sub instruction on empty stack"

#define MUL_EMPTY "Error: Mul instruction on empty stack"

#define DIV_EMPTY "Error: Div instruction on empty stack"

#define MOD_EMPTY "Error: Mod instruction on empty stack"

#define PRINT_ERROR "Error: Print only for 8-bit integer value"

#define PRINT_EMPTY "Print on empty stack"

#define NO_EXIT "No exit instructions"

#define NO_ELEMS_CONTAINER "Empty command stack"

#endif //ABSTRACTVM_ERROR_MESSAGES_H
