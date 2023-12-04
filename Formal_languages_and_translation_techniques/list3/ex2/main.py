import ply.lex as lex
import ply.yacc as yacc

error_code = False

tokens = (
    'INTEGER',
    'PLUS',
    'MINUS',
    'TIMES',
    'DIV',
    'POW',
    'LPAREN',
    'RPAREN',
    'COMM',
    'LINE_CONTINUATION',
    'NEW_LINE'
)

# Regex list

t_ignore = ' \t'

t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_DIV = r'/'
t_POW = r'\^'
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_COMM = r'\#'
t_NEW_LINE = r'\n'
t_LINE_CONTINUATION = r'\\'


def t_INTEGER(t):
    r'[0-9]+'
    t.value = int(t.value)
    return t


def t_error(t):
    global error_code
    error_code = True
    t.lexer.skip(1)


# Parser

BODY = 1234577

operator_occurred = False
unary_operator = False
number_input = False
input_start = False

queue = []
operator_stack = []


def is_operator(op):
    if op == '+' or op == '-' or op == '*' or op == '/' or op == '^' or op == '(' or op == ')':
        return True
    return False


def reset():
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global queue
    global error_code
    global number_input

    queue = []
    operator_stack = []
    error_code = False
    number_input = False
    operator_occurred = False
    unary_operator = False
    input_start = False


def p_program(p):
    """program : sign program
               | sign"""


def p_sign_to_comment(p):
    """sign : COMM comment"""


def p_comment(p):
    """comment : INTEGER comment
               | LINE_CONTINUATION NEW_LINE comment
               | NEW_LINE"""
    if p[1] == '\n' and input_start:
        print("Blad")
        reset()


def p_plus(p):
    """sign : PLUS"""
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global queue
    global error_code

    if error_code:
        return

    operator_occurred = True
    unary_operator = False
    input_start = True
    if len(operator_stack) == 0:
        operator_stack.append('+')
    else:
        while len(operator_stack) > 0 and operator_stack[-1] != '(':
            queue.append(operator_stack.pop())
        operator_stack.append('+')


def p_minus(p):
    """sign : MINUS"""
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global queue
    global error_code

    if error_code:
        return

    if operator_occurred or not number_input:
        unary_operator = True
    elif not error_code:
        operator_occurred = True
        unary_operator = False
        input_start = True
        if len(operator_stack) == 0:
            operator_stack.append('-')
        else:
            while len(operator_stack) > 0 and operator_stack[-1] != '(':
                queue.append(operator_stack.pop())
            operator_stack.append('-')


def p_mult(p):
    """sign : TIMES"""
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global queue
    global error_code

    if error_code:
        return

    operator_occurred = True
    unary_operator = False
    input_start = True
    if len(operator_stack) == 0:
        operator_stack.append('*')
    else:
        if operator_stack[-1] == '+' or operator_stack[-1] == '-':
            operator_stack.append('*')
        else:
            while len(operator_stack) > 0 and operator_stack[-1] != '+' \
                    and operator_stack[-1] != '-' and operator_stack[-1] != '(':
                queue.append(operator_stack.pop())
            operator_stack.append('*')


def p_div(p):
    """sign : DIV"""
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global queue
    global error_code

    if error_code:
        return

    operator_occurred = True
    unary_operator = False
    input_start = True
    if len(operator_stack) == 0:
        operator_stack.append('/')
    else:
        if operator_stack[-1] == '+' or operator_stack[-1] == '-':
            operator_stack.append('/')
        else:
            while len(operator_stack) > 0 and operator_stack[-1] != '+' \
                    and operator_stack[-1] != '-' and operator_stack[-1] != '(':
                queue.append(operator_stack.pop())
            operator_stack.append('/')


def p_lparen(p):
    """sign : LPAREN"""
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global error_code

    if error_code:
        return

    input_start = True
    operator_occurred = True
    unary_operator = False
    operator_stack.append('(')


def p_rparen(p):
    """sign : RPAREN"""
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global queue
    global error_code

    if error_code:
        return

    operator_occurred = False
    input_start = True
    unary_operator = False
    if len(operator_stack) == 0:
        error_code = True
    else:
        while len(operator_stack) > 0 and operator_stack[-1] != '(':
            queue.append(operator_stack.pop())
        if len(operator_stack) == 0:
            error_code = True
        else:
            operator_stack.pop()


def p_pow(p):
    """sign : POW"""
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global queue
    global error_code

    if error_code:
        return

    input_start = True
    operator_occurred = True
    unary_operator = False
    if len(operator_stack) == 0:
        operator_stack.append('^')
    else:
        if operator_stack[-1] != '^':
            operator_stack.append('^')
        else:
            queue.append(operator_stack.pop())
            operator_stack.append('^')


def p_integer(p):
    """sign : INTEGER"""
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global queue
    global error_code
    global number_input
    global BODY

    if error_code:
        return

    number_input = True
    input_start = True
    num = p[1]
    if unary_operator:
        num *= -1
        while num < 0:
            num += BODY
    queue.append(num % BODY)
    operator_occurred = False
    unary_operator = False


def p_new_line(p):
    """sign : LINE_CONTINUATION NEW_LINE
            | NEW_LINE"""
    global operator_occurred
    global unary_operator
    global input_start
    global operator_stack
    global queue
    global error_code
    global number_input
    global BODY
    if p[1] != '\n':
        return

    if error_code:
        print("Blad")
        reset()
        return
    while len(operator_stack) > 0:
        queue.append(operator_stack.pop())
    result = 0
    calculations_stack = []
    for i in queue:
        if not is_operator(i):
            calculations_stack.append(int(i))
        else:
            if len(calculations_stack) == 0:
                error_code = True
            if i == '+':
                a = calculations_stack.pop()
                if len(calculations_stack) == 0:
                    error_code = True
                else:
                    b = calculations_stack.pop()
                    calculations_stack.append((a + b) % BODY)
            elif i == '-':
                a = calculations_stack.pop()
                if len(calculations_stack) == 0:
                    error_code = True
                else:
                    b = calculations_stack.pop()
                    res = b - a
                    while res < 0:
                        res += BODY
                    calculations_stack.append(res)
            elif i == '*':
                a = calculations_stack.pop()
                if len(calculations_stack) == 0:
                    error_code = True
                else:
                    b = calculations_stack.pop()
                    calculations_stack.append((a * b) % BODY)
            elif i == '/':
                a = calculations_stack.pop()
                if len(calculations_stack) == 0:
                    error_code = True
                else:
                    b = calculations_stack.pop()
                    if b == 0:
                        error_code = True
                    else:
                        rev = 1
                        while (rev * a) % BODY != 1:
                            rev += 1
                        calculations_stack.append((b * rev) % BODY)
            elif i == '^':
                a = calculations_stack.pop()
                if len(calculations_stack) == 0:
                    error_code = True
                else:
                    b = calculations_stack.pop()
                    multiplier = b
                    if a == 0:
                        b = 1
                    else:
                        for _ in range(a - 1):
                            b *= multiplier
                            b %= BODY
                    calculations_stack.append(b)
            else:
                error_code = True
            if error_code:
                break
    if not error_code:
        if len(calculations_stack) > 1:
            error_code = True
        else:
            result = calculations_stack.pop()
    print_equation = ""
    for i in queue:
        print_equation += str(i)
        print_equation += " "
    if not error_code:
        print(print_equation)
        print(f'Wynik: {result}')
    else:
        print("Blad")
    reset()


def p_error(p):
    global error_code
    error_code = True


def main():
    lexer = lex.lex()
    parser = yacc.yacc()
    parser.parse("-2--1\n", lexer=lexer)
    return


if __name__ == '__main__':
    main()
