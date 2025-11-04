"""
/**
  *************************************************************************************************
  * @file    stub_lexer.py
  * @brief   provides hal detection stubbing script stub lexer services
  *************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root
  * directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *************************************************************************************************
  */
"""

from ply import lex

class StubLexer:
    """
    A lexer for tokenizing C source code using the PLY (Python Lex-Yacc) library.

    The `StubLexer` class is designed to tokenize C source code, including:
    - Preprocessor directives (e.g., `#define`, `#include`, `#ifdef`)
    - C keywords (e.g., `if`, `for`, `while`, `return`)
    - Literals (e.g., integers, floating-point numbers, strings, characters)
    - Operators and punctuation (e.g., `+`, `-`, `*`, `;`, `{`, `}`)
    - Comments (both single-line `//` and multi-line `/* ... */`)

    The lexer supports different C standards (e.g., C89, C99, C23) and can handle
    language-specific features such as digit separators, binary literals, and hexadecimal floats.

    Attributes:
        tokens (list): A list of token names recognized by the lexer.
        states (tuple): A tuple of exclusive lexer states
        (e.g., `preproc` for preprocessor directives).
        keyword_map (dict): A mapping of C keywords to their corresponding token names.
        c_version (str): The C standard version (e.g., 'c89', 'c99', 'c23').
        errors (list): A list to collect error messages encountered during tokenization.
        comment_count (int): A counter for the number of comments encountered.
        lexer (ply.lex.Lexer): The PLY lexer instance.

    Methods:
        input(data): Feeds source code to the lexer for tokenization.
        token(): Returns the next token from the input stream.
        get_errors(): Retrieves the list of collected errors.
    """
    tokens = [
        # Preprocessor directives
        'DEFINE', 'INCLUDE', 'IFDEF', 'IFNDEF', 'IF', 'ELIF', 'ELSE', 'ENDIF',
        'PRAGMA', 'ERROR', 'WARNING', 'UNDEF', 'ELIFDEF', 'ELIFNDEF',
        'PREPROCESSOR',

        # Preprocessor end directives, used for parsing purposes
        'END_DEFINE', 'END_INCLUDE', 'END_IFDEF', 'END_IFNDEF', 'END_IF', 'END_ELIF', 'END_ELSE', 'END_ENDIF',
        'END_PRAGMA', 'END_ERROR', 'END_WARNING', 'END_UNDEF', 'END_ELIFDEF', 'END_ELIFNDEF',
        'END_PREPROCESSOR',

        # C keywords
        'AUTO', 'BREAK', 'CASE', 'CHAR', 'CONST', 'CONTINUE', 'DEFAULT', 'DO',
        'DOUBLE', 'ELSE_KW', 'ENUM', 'EXTERN', 'FLOAT', 'FOR', 'GOTO', 'IF_KW', 'INT',
        'LONG', 'REGISTER', 'RETURN', 'SHORT', 'SIGNED', 'SIZEOF', 'STATIC',
        'STRUCT', 'SWITCH', 'TYPEDEF', 'UNION', 'UNSIGNED', 'VOID', 'VOLATILE', 'WHILE',
        'INLINE', 'BOOL', 'RESTRICT', 'COMPLEX', 'IMAGINARY',
        'ALIGNAS', 'STATIC_ASSERT', 'THREAD_LOCAL',

        # Literals
        'INTEGER', 'FLOAT_LITERAL', 'CHAR_LITERAL', 'STRING_LITERAL',

        # Operators
        'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'MOD', 'INC', 'DEC',
        'EQ', 'NE', 'LT', 'GT', 'LE', 'GE', 'AND', 'OR', 'NOT',
        'BITAND', 'BITOR', 'BITXOR', 'BITNOT', 'LSHIFT', 'RSHIFT',
        'ASSIGN', 'PLUS_ASSIGN', 'MINUS_ASSIGN', 'TIMES_ASSIGN', 'DIVIDE_ASSIGN',
        'MOD_ASSIGN', 'LSHIFT_ASSIGN', 'RSHIFT_ASSIGN', 'BITAND_ASSIGN',
        'BITXOR_ASSIGN', 'BITOR_ASSIGN',

        'QUESTION', 'COLON', 'SEMI', 'COMMA', 'DOT', 'ARROW',
        'LPAREN', 'RPAREN', 'LBRACKET', 'RBRACKET', 'LBRACE', 'RBRACE',
        'ELLIPSIS',

        'IDENTIFIER', 'INVALID',
    ]

    # Inclusive state for preprocessing directives
    states = (('preproc', 'inclusive'),)

    # Mapping of C keywords to token names
    keyword_map = {
        'auto': 'AUTO', 'break': 'BREAK', 'case': 'CASE', 'char': 'CHAR',
        'const': 'CONST', 'continue': 'CONTINUE', 'default': 'DEFAULT', 'do': 'DO',
        'double': 'DOUBLE', 'else': 'ELSE_KW', 'enum': 'ENUM', 'extern': 'EXTERN',
        'float': 'FLOAT', 'for': 'FOR', 'goto': 'GOTO', 'if': 'IF_KW',
        'int': 'INT', 'long': 'LONG', 'register': 'REGISTER', 'return': 'RETURN',
        'short': 'SHORT', 'signed': 'SIGNED', 'sizeof': 'SIZEOF', 'static': 'STATIC',
        'struct': 'STRUCT', 'switch': 'SWITCH', 'typedef': 'TYPEDEF', 'union': 'UNION',
        'unsigned': 'UNSIGNED', 'void': 'VOID', 'volatile': 'VOLATILE', 'while': 'WHILE',
        'inline': 'INLINE', '_Bool': 'BOOL', 'restrict': 'RESTRICT',
        '_Complex': 'COMPLEX', '_Imaginary': 'IMAGINARY', 'alignas': 'ALIGNAS',
        'static_assert': 'STATIC_ASSERT', '_Thread_local': 'THREAD_LOCAL'
    }

    def __init__(self, c_version='c89'):
        # Store the chosen C standard version
        self.c_version = c_version
        # Keywords allowed by this lexer
        self.allowed_keywords = self.keyword_map
        # A list to collect error messages
        self.errors = []
        # Counter of comments seen
        self.comment_count = 0
        # Build the PLY lexer
        self.lexer = lex.lex(module=self, debug = False, optimize= True)

    # Token for '#' starting preprocessor directive
    def t_INITIAL_preprocessor_entry(self, t):   # pylint: disable=invalid-name
        r'\#'
        t.lexer.begin('preproc')
        t.lexer.directive_name = ''
        t.lexer.preproc_data = '#'

    # Match directive keyword and emit token for all directives
    def t_preproc_directive(self, t):
        r'[ \t]*(define|undef|include|ifdef|ifndef|if|elif|else|endif|pragma|error|warning|elifdef|elifndef)\b'
        directive = t.value.strip()
        t.lexer.directive_name = directive.upper()
        t.lexer.preproc_data += t.value + ' '
        t.type = directive.upper()
        return t

    # Handle newlines and end of directive
    def t_preproc_newline(self, t):                     # pylint: disable= inconsistent-return-statements
        r'\\\n|\n'
        if t.value == '\\\n':
            t.lexer.lineno += 1
        else:
            t.lexer.lineno += 1
            t.type = 'END_'+ t.lexer.directive_name if t.lexer.directive_name in self.tokens else 'PREPROCESSOR'
            t.value = t.lexer.preproc_data
            t.lexer.begin('INITIAL')
            return t


    def t_preproc_backslash(self, t):
        r'\\'
        t.lexer.preproc_data += t.value + '\\'
        # pass

    t_preproc_ignore = ' \t'

    def t_preproc_error(self, t):
        """
        Handles illegal characters in preprocessor directives.
        Logs the error and skips the offending character.
        """
        illegal_char = t.value[0] if t.value else ''
        self._add_error(t, f"Illegal character in preprocessor directive: {illegal_char}")
        t.lexer.skip(1)

    def t_DOCCOMMENT(self, t):                                                          # pylint: disable=invalid-name
        r'/\*\*(.|\n)*?\*/'
        self.comment_count += 1
        t.lexer.lineno += t.value.count('\n')

    def t_COMMENT(self, t):                                                             # pylint: disable=invalid-name
        r'/\*(.|\n)*?\*/'
        if '/*' in t.value[2:-2]:
            self._add_error(t, "Nested comment detected")
        self.comment_count += 1
        t.lexer.lineno += t.value.count('\n')

    def t_COMMENT_unclosed(self, t):                                                    # pylint: disable=invalid-name
        r'/\*(.|\n)*'
        self._add_error(t, "Unclosed comment")
        t.lexer.lineno += t.value.count('\n')
        # Skip to end of input or next token

    def t_LINECOMMENT(self, t):                                        # pylint: disable=invalid-name, unused-argument
        r'//.*'
        # Line comment: count as one comment, do not increment line number here
        self.comment_count += 1

    def t_IDENTIFIER(self, t):                                                          # pylint: disable=invalid-name
        r'[a-zA-Z_][a-zA-Z0-9_]*'
        # Check against keyword map
        t.type = self.allowed_keywords.get(t.value, 'IDENTIFIER')
        return t


    def t_FLOAT_LITERAL(self, t):                                                       # pylint: disable=invalid-name
        r'(([0-9]+(\'?[0-9]+)*\.([0-9]*(\'?[0-9]+)*)?|\.[0-9]+(\'?[0-9]+)*)' \
        r'([eE][+-]?[0-9]+(\'?[0-9]+)*)?([fFlL])?|' \
        r'(0[xX][0-9a-fA-F]+(\'?[0-9a-fA-F]+)*(\.[0-9a-fA-F]*(\'?[0-9a-fA-F]+)*)?[pP][+-]?[0-9]+(\'?[0-9]+)*)([fFlL])?)'
        # Hexadecimal floats are only allowed in C99 and later
        if 'x' in t.value.lower() and self.c_version == 'c89':
            self._add_error(t, "Hexadecimal floats not allowed in C89")
            t.type = 'INVALID'
        # Digit separators are only allowed in C23
        if "'" in t.value and self.c_version != 'c23':
            self._add_error(t, "Digit separators not allowed in C89/C99")
            t.type = 'INVALID'
        return t

    def t_INTEGER(self, t):                                                             # pylint: disable=invalid-name
        r'(0[bB][01]+(\'?[01]+)*)|' \
        r'(0[xX][0-9a-fA-F]+(\'?[0-9a-fA-F]+)*)|' \
        r'(0[0-7]+(\'?[0-7]+)*)|' \
        r'([1-9][0-9]*(\'?[0-9]+)*|0)' \
        r'([uU][lL]{0,2}|[lL]{1,2}[uU]?)?'
        # Binary literals only allowed in C23
        if t.value.lower().startswith(('0b', '0B')) and self.c_version != 'c23':
            self._add_error(t, "Binary literals not allowed in C89/C99")
            t.type = 'INVALID'
        # Digit separators only allowed in C23
        if "'" in t.value and self.c_version != 'c23':
            self._add_error(t, "Digit separators not allowed in C89/C99")
            t.type = 'INVALID'
        # Exclude hexadecimal floats
        if 'x' in t.value.lower() and '.' in t.value:
            t.type = 'INVALID'
        return t

    def t_CHAR_LITERAL(self, t):                                                        # pylint: disable=invalid-name
        r'(L)?\'(\\.|[^\\\']+)\''
        return t

    def t_STRING_LITERAL(self, t):                                                      # pylint: disable=invalid-name
        r'(u8|u|U|L)?\"(\\(.|\n)|[^\\\"\n])*\"'
        # This allows escaped characters including escaped newlines inside the string literal
        return t

    t_PLUS           = r'\+'
    t_MINUS          = r'-'
    t_TIMES          = r'\*'
    t_DIVIDE         = r'/'
    t_MOD            = r'%'
    t_INC            = r'\+\+'
    t_DEC            = r'--'
    t_EQ             = r'=='
    t_NE             = r'!='
    t_LT             = r'<'
    t_GT             = r'>'
    t_LE             = r'<='
    t_GE             = r'>='
    t_AND            = r'&&'
    t_OR             = r'\|\|'
    t_NOT            = r'!'
    t_BITAND         = r'&'
    t_BITOR          = r'\|'
    t_BITXOR         = r'\^'
    t_BITNOT         = r'~'
    t_LSHIFT         = r'<<'
    t_RSHIFT         = r'>>'
    t_ASSIGN         = r'='
    t_PLUS_ASSIGN    = r'\+='
    t_MINUS_ASSIGN   = r'-='
    t_TIMES_ASSIGN   = r'\*='
    t_DIVIDE_ASSIGN  = r'/='
    t_MOD_ASSIGN     = r'%='
    t_LSHIFT_ASSIGN  = r'<<='
    t_RSHIFT_ASSIGN  = r'>>='
    t_BITAND_ASSIGN  = r'&='
    t_BITXOR_ASSIGN  = r'\^='
    t_BITOR_ASSIGN   = r'\|='
    t_QUESTION       = r'\?'
    t_COLON          = r':'
    t_SEMI           = r';'
    t_COMMA          = r','
    t_DOT            = r'\.'
    t_ARROW          = r'->'
    t_LPAREN         = r'\('
    t_RPAREN         = r'\)'
    t_LBRACKET       = r'\['
    t_RBRACKET       = r'\]'
    t_LBRACE         = r'\{'
    t_RBRACE         = r'\}'
    t_ELLIPSIS       = r'\.\.\.'

    # Ignore whitespace
    t_ignore = ' \t\r'


    def t_newline(self, t):
        r'\n+'
        # Count line breaks
        t.lexer.lineno += len(t.value)

    def t_error(self, t):
        """
        Handles illegal characters encountered during tokenization.

        This method is called when the lexer encounters a character or sequence
        of characters that do not match any defined token pattern. It performs
        the following actions:
        - If the token has a type of 'INVALID', it skips the character and returns.
        - Otherwise, it logs an error message indicating the illegal character
        and skips the character to continue tokenization.

        Args:
            t (ply.lex.LexToken): The token object representing the illegal character.

        Returns:
            None
        """
        # Handle illegal characters
        if hasattr(t, 'type') and t.type == 'INVALID':
            t.lexer.skip(1)
            return
        self._add_error(t, f"Illegal character '{t.value[0]}'")
        t.lexer.skip(1)

    def _add_error(self, t, message):
        # Append an error message with line number
        self.errors.append(f"Line {t.lineno}: {message}")

    def input(self, data):
        """Feed data to the lexer."""
        self.lexer.input(data)

    def token(self):
        """Return the next token."""
        return self.lexer.token()

    def get_errors(self):
        """Retrieve the list of collected errors."""
        return self.errors

    def reset(self):
        """
        Reset the lexer state for reuse.
        Clears errors, resets comment count, and sets line number to 1.
        """
        self.errors.clear()
        self.comment_count = 0
        if hasattr(self.lexer, 'lineno'):
            self.lexer.lineno = 1
