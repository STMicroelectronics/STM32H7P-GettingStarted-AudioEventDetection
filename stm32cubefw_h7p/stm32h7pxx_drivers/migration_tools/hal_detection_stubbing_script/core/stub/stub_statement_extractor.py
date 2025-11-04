"""
/**
  *************************************************************************************************
  * @file    stub_statement_extractor.py
  * @brief   provides hal detection stubbing script stub statement extractor services
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

from dataclasses import dataclass, field
from typing import List, Optional, Dict
from collections import defaultdict

@dataclass
class Position:
    """
    Represents the position of a code element within a source file.

    Attributes:
        line_start (int): The starting line number of the element.
        line_end (int): The ending line number of the element.
        column_start (int): The starting column number of the element.
        column_end (int): The ending column number of the element.
    """
    line_start:int
    line_end:int
    column_start:int
    column_end:int

@dataclass
class StatementCondition:
    """
    Represents a condition statement depending on the context:
    - control structures expressions
    - functions names and their parameters
    """

    start_line: int                                                  # Starting line in source of the condition
    end_line: int                                                    # Ending line in source of the condition
    start_column: int                                                # Starting column in source of the condition
    end_column:int                                                   # Ending column in source of condition
    condition: str                                                   # Raw text of the condition
    is_for_stubbing: bool = False                                    # True if the condition should be stubbed
    identifiers_for_stub: List[str] = field(default_factory=list)    # list of identifiers causing the stubbing
    insert_new_line : bool = False                                   # a new line must be inserted after the condition
    insert_line_before : bool = False                                # a new line must be inserted before the condition
    origin_position: Optional[Position] = None                       # in case of line insertions save condition origin
                                                                     # position

    def is_multiline(self) -> bool:
        """
        Checks if the condition spans multiple lines.
        """
        return self.end_line > self.start_line

    def __str__(self) -> str:
        """
        Returns a string representation of the condition.
        """
        return f"Condition: {self.condition} \
                 (Lines {self.start_line}-{self.end_line})"

@dataclass
class Statement:
    """
    Represents a C statement with location and hierarchy.
    """
    start_line: int                                                 # Starting line in source
    end_line: int                                                   # Ending line in source
    start_column: int                                               # Starting column in source
    end_column:int                                                  # Ending column in source
    type: str                                                       # Statement type, e.g., 'if', 'for', 'declaration'
    content: str                                                    # Raw text content of the statement
    is_for_stubbing: bool                                           # True if the statement should be stubbed
    stubbing_condition: Optional[StatementCondition] = None         # Condition for stubbing
    else_stubbing_condition: Optional[StatementCondition] = None    # Condition for stubbing else KW
    identifiers_for_stub: List[str] = field(default_factory=list)   # list of identifiers causing the stubbing
    children: List["Statement"] = field(default_factory=list)       # Nested statements
    chain_with_next : bool = False                                  # Chain a statement with the next one
    chain_with_previous : bool = False                              # Chain a statement with the previous one
    is_struct_member_stmt : bool = False                            # mark the statement as struct member access
    insert_new_line : bool = False                                  # a new line must be inserted after the statement
    insert_line_before : bool = False                               # a new line must be inserted before the statement
    do_stubbing_condition: Optional[StatementCondition] = None      # Condition for stubbing do in do-while statement
    origin_position: Optional[Position] = None                      # in case of line inserttion save the original

    def is_struct_member(self) -> bool:
        """
        Returns True if this statement is a struct member.
        """
        return self.is_struct_member_stmt

    def is_chain_previous(self) -> bool:
        """
        Returns True if this statement is chained with the previous statement.
        """
        return self.chain_with_previous

    def is_chain_next(self) -> bool:
        """
        Returns True if this statement is chained with the next statement.
        """
        return self.chain_with_next

    def print_stmt(self, indent: int = 0, identifiers: bool = False, numbering: Optional[List[int]] = None) -> None:
        """
        Print statement with hierarchical numbering.

        Args:
            indent (int): Indentation level.
            identifiers (bool): Whether to print identifiers.
            numbering (List[int], optional): Hierarchical numbering list.
        """
        if numbering is None:
            numbering = [1]  # Default numbering if none provided

        indent_str = "  " * indent
        number_str = ".".join(str(num) for num in numbering)

        def print_stubbing_status(
                                   is_stub: bool,
                                   is_struct_member_stmt: bool,
                                   is_chain_next: bool, is_chain_previous:bool
                                   ) -> None:

            print(
                    f"{indent_str}  Stubbing: {'Yes' if is_stub else 'No'},\t"
                    f"struc member: {'Yes' if is_struct_member_stmt else 'No'},\t"
                    f"chain previous: {'Yes' if is_chain_previous else 'No'},\t"
                    f"chain next: {'Yes' if is_chain_next else 'No'}"
                )

        def print_insert_line_status(insert_new_line: bool, insert_line_before:bool) -> None:
            print(
                    f"{indent_str}  Insert Line after: {'Yes' if insert_new_line else 'No'},\t"
                    f"Insert Line before: {'Yes' if insert_line_before else 'No'}"
                )

        print(f"{indent_str}{number_str}. {self.type} [({self.start_line},{self.start_column})->"
              f"({self.end_line},{self.end_column})]: {self.content}")

        print_stubbing_status(
                                self.is_for_stubbing,
                                self.is_struct_member(),
                                self.chain_with_next,
                                self.chain_with_previous
                                )
        do_condition = getattr(self, 'do_stubbing_condition', None)
        if do_condition:
            print(f"{indent_str}  do_Condition [({do_condition.start_line},{do_condition.start_column})->"
                f"({do_condition.end_line},{do_condition.end_column})]: {do_condition.condition}")
            print_stubbing_status(
                                    do_condition.is_for_stubbing,
                                    False,
                                    False,
                                    False
                                    )
            print_insert_line_status(do_condition.insert_new_line, do_condition.insert_line_before)

        if self.stubbing_condition:
            cond = self.stubbing_condition
            else_cond = getattr(self, 'else_stubbing_condition', None)

            print(f"{indent_str}  {self.type}_Condition [({cond.start_line},{cond.start_column})->"
                f"({cond.end_line},{cond.end_column})]: {cond.condition}")
            print_stubbing_status(
                                    cond.is_for_stubbing,
                                    False,
                                    False,
                                    False
                                    )
            print_insert_line_status(cond.insert_new_line, cond.insert_line_before)

            if else_cond:
                print(f"{indent_str}  else_Condition [({else_cond.start_line},{else_cond.start_column})->"
                    f"({else_cond.end_line},{else_cond.end_column})]: {else_cond.condition}")
                print_stubbing_status(else_cond.is_for_stubbing, False, False, False)
                print_insert_line_status(else_cond.insert_new_line, else_cond.insert_line_before)

            if identifiers:
                print(f"{indent_str}  condition identifiers:")
                for token in cond.identifiers_for_stub:
                    print(f"{indent_str}    - {token}")

        if identifiers and getattr(self, 'identifiers_for_stub', None):
            print(f"{indent_str}  identifiers:")
            for token in self.identifiers_for_stub:
                print(f"{indent_str}    - {token}")

        children = getattr(self, 'children', [])
        for idx, child in enumerate(children, start=1):
            child.print_stmt(indent + 4, identifiers, numbering + [idx])

@dataclass
class StatementExtractor:
    """
    Extracts and parses C statements from a list of tokens.

    This class processes a tokenized representation of C source code and identifies
    various types of statements, such as declarations, control structures, function
    definitions, and preprocessor directives. It organizes these statements into a
    hierarchical structure for further analysis or transformation.

    Attributes:
        tokens (List[Dict]): A list of token dictionaries representing the source code.
        index (int): The current position in the token list during parsing.
    """

    variables_identifiers_for_stub = {}             # dictionary to save variables declarations

    declarations_identifiers_for_stub = {}          # dictionary to save declarations types

    functions_identifiers_for_stub = {}             # dictionary to save functions types



    def __init__(self, tokens: List[Dict]):
        """
        Initializes the StatementExtractor with a list of tokens.

        Args:
            tokens (List[Dict]): A list of token dictionaries representing the source code.
        """
        self.tokens = tokens
        self.index = 0

    def print_statements(self, statements: List[Statement], identifiers: bool = False) -> None:
        """
        Print multiple top-level statements with numbering 1, 2, 3, ...
        Each statement will handle its own nested numbering.

        Args:
            statements (List[Any]): List of statement objects.
            identifiers (bool): Whether to print identifiers.
        """
        for idx, stmt in enumerate(statements, start=1):
            stmt.print_stmt(indent=0, identifiers=identifiers, numbering=[idx])

    def count_statements(self, stmts: List[Statement], stmt_type: Optional[str] = None) -> int:
        """
        Counts the total number of statements or statements of a specific type.

        Args:
            stmts (List[Statement]): The list of statements to count.
            stmt_type (Optional[str]): The type of statement to count (e.g., 'if', 'for').
                                       If None, counts all statements.

        Returns:
            int: The total number of statements matching the criteria.
        """
        count = 0
        for stmt in stmts:
            if stmt_type is None or stmt.type == stmt_type:
                count += 1
            if stmt.children:
                count += self.count_statements(stmt.children, stmt_type)
        return count

    def get_statement_by_type(self, stmts: List[Statement], stmt_type: str) -> List[Statement]:
        """
        Retrieves all statements of a specific type from the extracted statements.

        Args:
            stmts (List[Statement]): The list of statements to search.
            stmt_type (str): The type of statement to retrieve
            (e.g., 'if', 'for', 'function_definition').

        Returns:
            List[Statement]: A list of statements matching the specified type.
        """
        result = []
        for stmt in stmts:
            if stmt.type == stmt_type:
                result.append(stmt)
            if stmt.children:
                result.extend(self.get_statement_by_type(stmt.children, stmt_type))
        return result

    def extract(self) -> List[Statement]:
        """
        Extracts statements from the token list.

        Returns:
            List[Statement]: A list of parsed Statement objects.
        """
        stmts = []

        while self.index < len(self.tokens):
            tok = self._peek()
            if not tok:
                break

            ttype = tok["type"]
            tval = tok.get("value")

            handler_map = {
                "INCLUDE": self._handle_include,
                "DEFINE": self._handle_define,
                "UNDEF": self._handle_undef,
                "IFDEF": self._handle_ifdef,
                "IFNDEF": self._handle_ifndef,
                "ELIFDEF":self._handle_elifdef,
                "ELIFNDEF":self._handle_elifndef,
                "ELSE": self._handle_preproc_else,
                "IF": self._handle_preproc_if,
                "ELIF": self._handle_preproc_elif,
                "ENDIF": self._handle_preproc_endif,
                "PRAGMA": self._handle_pragma,
                "WARNING": lambda: self._handle_error_warning("WARNING"),
                "ERROR": lambda: self._handle_error_warning("ERROR"),
                "LBRACE": self._handle_compound,
                "RETURN": lambda: self._simple_stmt("return", ";"),
                "IF_KW": lambda: self._handle_control_structure("if"),
                "SWITCH": lambda: self._handle_control_structure("switch"),
                "FOR": lambda: self._handle_control_structure("for"),
                "WHILE": lambda: self._handle_control_structure("while"),
                "DO": self._handle_do_while,
                "BREAK": lambda: self._simple_stmt("jump", ";"),
                "CONTINUE": lambda: self._simple_stmt("jump", ";"),
                "GOTO": lambda: self._simple_stmt("jump", ";"),
                "STRUCT": self._handle_struct,
                "ENUM": self._handle_enum,
                "UNION": self._handle_union,
                "CASE": lambda: self._simple_stmt("case", ":"),
                "DEFAULT": lambda: self._simple_stmt("default", ":"),

            }

            if ttype == "TYPEDEF" and self._peek(1):
                next_type = self._peek(1)["type"]
                typedef_map = {
                    "STRUCT": self._handle_typedef_struct,
                    "ENUM": self._handle_typedef_enum,
                    "UNION": self._handle_typedef_union,
                }
                stmts.append(typedef_map.get(next_type, self._handle_typedef_alias)())
            elif ttype in handler_map:
                stmts.append(handler_map[ttype]())
            elif self._is_function_definition():
                stmts.append(self._handle_function_definition())
            elif self._is_declaration():
                stmts.append(self._simple_stmt("declaration", ";"))
            elif tval == ";":
                stmts.append(self._simple_stmt("empty", ";"))
            else:
                stmts.append(self._simple_stmt("expression", ";"))
                if len(stmts) >= 2:
                    last_stmt = stmts[-1]
                    previous_last_stmt = stmts[-2]
                    if last_stmt.is_struct_member_stmt and previous_last_stmt.is_struct_member_stmt:
                        last_stmt.chain_with_previous = True
                        previous_last_stmt.chain_with_next = True
                    if last_stmt.start_line ==  previous_last_stmt.end_line:
                        last_stmt.chain_with_previous = True
                        previous_last_stmt.chain_with_next = True
        return stmts

    def _peek(self, offset=0) -> Optional[Dict]:
        """
        Returns the token at the current index + offset without advancing.
        """
        idx = self.index + offset
        return self.tokens[idx] if idx < len(self.tokens) else None

    def _advance(self):
        """
        Advances the token index by one.
        """
        self.index += 1

    def _handle_define(self) -> Statement:
        is_for_stubbing = False
        identifiers_for_stub = []
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        content_parts = [start_token["value"]]
        self._advance()  # consume '#define'

        macro_name_token = self._peek()
        if not macro_name_token or macro_name_token["type"] != "IDENTIFIER":
            # Handle error: expected identifier after #define
            raise ValueError(f"Expected identifier after #define at line {start_line}")


        macro_name = macro_name_token["value"]
        content_parts.append(macro_name)
        self._advance()  # consume identifier

        if self._peek() and self._peek()["value"] == "(":
            content_parts.append("(")
            self._advance()
            depth = 1
            while self._peek() and depth > 0:
                tok = self._peek()
                val = tok["value"]
                if tok["type"] == 'IDENTIFIER':
                    if tok.get("for_stub") is True:
                        is_for_stubbing = True
                        # to add the macro name in variables_identifiers_for_stub
                        # should be handled here for macros without arguments
                        self.variables_identifiers_for_stub[macro_name] = (tok["hal_api_type"],tok["variable_type"])
                        self.declarations_identifiers_for_stub[macro_name] = tok
                        identifiers_for_stub.append(tok)
                    if val in self.variables_identifiers_for_stub:
                        tok["for_stub"] = True
                        is_for_stubbing = True
                        macro_hal_api_type, macro_variable_type = self.variables_identifiers_for_stub[val]
                        self.variables_identifiers_for_stub[macro_name] = (macro_hal_api_type,macro_variable_type)
                        if val in self.declarations_identifiers_for_stub:
                            value_declaration = self.declarations_identifiers_for_stub[val]
                            self.declarations_identifiers_for_stub[macro_name] = value_declaration
                        identifiers_for_stub.append(self.declarations_identifiers_for_stub[macro_name])

                content_parts.append(val)
                if val == "(":
                    depth += 1
                elif val == ")":
                    depth -= 1
                self._advance()
            if depth != 0:
                raise ValueError(f"Unmatched parentheses in macro parameters at line {start_line}")

        replacement_parts = []
        while self._peek() and self._peek()["type"] != "END_DEFINE":
            tok = self._peek()
            val = tok["value"]
            replacement_parts.append(tok["value"])
            if tok["type"] == 'IDENTIFIER':

                if tok.get("for_stub") is True:
                    is_for_stubbing = True
                    self.variables_identifiers_for_stub[macro_name] = (tok["hal_api_type"],tok["variable_type"])
                    self.declarations_identifiers_for_stub[macro_name] = tok
                    identifiers_for_stub.append(tok)
                if val in self.variables_identifiers_for_stub:
                    tok["for_stub"] = True
                    is_for_stubbing = True
                    macro_hal_api_type, macro_variable_type = self.variables_identifiers_for_stub[val]
                    self.variables_identifiers_for_stub[macro_name] = (macro_hal_api_type,macro_variable_type)
                    if val in self.declarations_identifiers_for_stub:
                        self.declarations_identifiers_for_stub[macro_name] = self.declarations_identifiers_for_stub[val]
                    identifiers_for_stub.append(self.declarations_identifiers_for_stub[macro_name])
            self._advance()

        if self._peek() and self._peek()["type"] == "END_DEFINE":
            self._advance()

        full_content = " ".join(content_parts + replacement_parts).replace(" \\", "\\") \
                          .replace("\\ ", "\\").replace("\\", "")

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type='define',
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            stubbing_condition=None,
            else_stubbing_condition=None,
            do_stubbing_condition= None,
            identifiers_for_stub=identifiers_for_stub,
            children=[],
        )

    def _handle_undef(self) -> Statement:
        is_for_stubbing = False
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        content_parts = [start_token["value"]]  # e.g., '#undef'
        self._advance()  # consume '#undef'

        # Parse identifier (macro name)
        identifier_token = self._peek()
        if not identifier_token or identifier_token["type"] != "IDENTIFIER":
            # Handle error: expected identifier after #define
            raise ValueError(f"Expected identifier after #undef at line {start_line}")

        identifier = identifier_token["value"]
        content_parts.append(identifier)
        self._advance()  # consume identifier

        # Consume END_DEFINE token if present
        if self._peek() and self._peek()["type"] == "END_UNDEF":
            self._advance()

        # Combine all parts into full content string
        full_content = " ".join(content_parts)

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type='undef',
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            stubbing_condition=None,
            else_stubbing_condition=None,
            identifiers_for_stub=[],
            children=[]
        )



    def _handle_ifdef(self) -> Statement:
        is_for_stubbing = False
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        content_parts = [start_token["value"]]  # e.g., '#undef'
        self._advance()  # consume '#undef'

        # Parse identifier (macro name)
        identifier_token = self._peek()
        if not identifier_token or identifier_token["type"] != "IDENTIFIER":
            # Handle error: expected identifier after #define
            raise ValueError(f"Expected identifier after #undef at line {start_line}")


        identifier = identifier_token["value"]
        content_parts.append(identifier)
        self._advance()  # consume identifier

        # Consume END_DEFINE token if present
        if self._peek() and self._peek()["type"] == "END_IFDEF":
            self._advance()

        # Combine all parts into full content string
        full_content = " ".join(content_parts)

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type='ifdef',
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            stubbing_condition=None,
            else_stubbing_condition=None,
            identifiers_for_stub=[],
            children=[]
        )

    def _handle_ifndef(self) -> Statement:
        is_for_stubbing = False
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        content_parts = [start_token["value"]]  # e.g., '#undef'
        self._advance()  # consume '#undef'

        # Parse identifier (macro name)
        identifier_token = self._peek()
        if not identifier_token or identifier_token["type"] != "IDENTIFIER":
            # Handle error: expected identifier after #define
            raise ValueError(f"Expected identifier after #undef at line {start_line}")

        identifier = identifier_token["value"]
        content_parts.append(identifier)
        self._advance()  # consume identifier

        # Consume END_DEFINE token if present
        if self._peek() and self._peek()["type"] == "END_IFNDEF":
            self._advance()

        # Combine all parts into full content string
        full_content = " ".join(content_parts)

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type='ifndef',
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            stubbing_condition=None,
            else_stubbing_condition=None,
            identifiers_for_stub=[],
            children=[]
        )

    def _handle_elifdef(self) -> Statement:
        return self._handle_preprocessor("eifdef")

    def _handle_elifndef(self) -> Statement:
        return self._handle_preprocessor("eifndef")

    def _handle_preproc_else(self) -> Statement:
        is_for_stubbing = False
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        content_parts = [start_token["value"]]
        self._advance()

        # Consume END_DEFINE token if present
        if self._peek() and self._peek()["type"] == "END_ELSE":
            self._advance()

        # Combine all parts into full content string
        full_content = " ".join(content_parts)

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type='#else',
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            identifiers_for_stub=[],
            children=[]
        )


    def _handle_preproc_if(self) -> Statement:
        is_for_stubbing = False
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        content_parts = [start_token["value"]]  # e.g., '#undef'
        while self._peek() and self._peek()["type"] != "END_IF":
            content_parts.append(self._peek()["value"])
            self._advance()  # consume '#undef'

        # Consume END_IF token if present
        if self._peek() and self._peek()["type"] == "END_IF":
            self._advance()

        # Combine all parts into full content string
        full_content = " ".join(content_parts)

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type='#if',
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            identifiers_for_stub=[],
            children=[]
        )

    def _handle_preproc_elif(self) -> Statement:
        is_for_stubbing = False
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        content_parts = [start_token["value"]]  # e.g., '#undef'
        while self._peek() and self._peek()["type"] != "END_ELIF":
            content_parts.append(self._peek()["value"])
            self._advance()  # consume '#undef'

        # Consume END_IF token if present
        if self._peek() and self._peek()["type"] == "END_ELIF":
            self._advance()
        # Combine all parts into full content string
        full_content = " ".join(content_parts)

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type='#elif',
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            identifiers_for_stub=[],
            children=[]
        )

    def _handle_preproc_endif(self) -> Statement:
        is_for_stubbing = False
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        content_parts = [start_token["value"]]
        self._advance()  # consume '#endif'

        # Consume END_ENDIF token if present
        if self._peek() and self._peek()["type"] == "END_ENDIF":
            self._advance()

        # Combine all parts into full content string
        full_content = " ".join(content_parts)

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type='#endif',
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            identifiers_for_stub=[],
            children=[]
        )

    def _handle_pragma(self) -> Statement:
        return self._handle_preprocessor("pragma")

    def _handle_error_warning(self, typ: str) -> Statement:
        is_for_stubbing = False
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        full_content = [start_token["value"]]  # e.g., '#warning'
        self._advance()  # consume '#warning' or '#error'
        while self._peek() and self._peek()["type"] not in  ["END_WARNING", "END_ERROR"]:
            tok = self._peek()
            full_content.append(tok["value"])
            self._advance()

        # Consume END_WARNING or END_ERROR token if present
        if self._peek() and self._peek()["type"] in  ["END_WARNING", "END_ERROR"]:
            self._advance()

        # Combine all parts into full content string
        full_content = " ".join(full_content)

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type=typ.lower(),
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            identifiers_for_stub=[],
            children=[]
        )

    def _handle_preprocessor(self, typ: str) -> Statement:

        is_for_stubbing = False
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        content_parts = [start_token["value"]]  # e.g., '#undef'
        self._advance()  # consume '#undef'

        # Parse identifier (macro name)
        identifier_token = self._peek()
        if not identifier_token or identifier_token["type"] != "IDENTIFIER":
            # Handle error: expected identifier after #define
            raise ValueError(f"Expected identifier after {typ} at line {start_line}")

        identifier = identifier_token["value"]
        content_parts.append(identifier)
        self._advance()  # consume identifier

        # Consume END_DEFINE token if present
        if self._peek() and self._peek()["type"] == 'END_'+typ.upper():
            self._advance()

        # Combine all parts into full content string
        full_content = " ".join(content_parts)

        return Statement(
            start_line=start_line,
            end_line=self.tokens[self.index - 1]["line"] if self.index > 0 else start_line,
            start_column=start_column,
            end_column=self.tokens[self.index - 1]["column"] if self.index > 0 else start_column,
            type=typ.lower(),
            content=full_content,
            is_for_stubbing=is_for_stubbing,
            identifiers_for_stub=[],
            children=[]
        )

    def _handle_include(self) -> Statement:
        """
        Handles #include preprocessor directive.

        Parses the #include line, capturing the included file or path.
        """
        start_token = self._peek()
        start_line = start_token["line"]
        start_column = start_token["column"] - 1

        # content_parts = [start_token["value"]]  # e.g., '#include'
        content_parts = []
        self._advance()  # consume '#include'
        while self._peek() and self._peek()["type"] not in {"END_INCLUDE"}:
            tok = self._peek()
            content_parts.append(tok["value"])
            self._advance()

        if self._peek() and self._peek()["type"] == "END_INCLUDE":
            content_parts.append(self._peek()["value"])
            self._advance()

        full_content = " ".join(content_parts)

        end_line = self.tokens[self.index - 1]["line"] if self.index > 0 else start_line
        end_column = self.tokens[self.index - 1]["column"] if self.index > 0 else start_column

        return Statement(
            start_line=start_line,
            end_line=end_line,
            start_column=start_column,
            end_column=end_column,
            type="include",
            content=full_content,
            is_for_stubbing=False,
            identifiers_for_stub=[],
            children=[]
        )



    def _simple_stmt(self, typ: str, term: str) -> Statement:
        start_line = self._peek()["line"]
        start_column = self._peek()["column"]
        content = []
        identifiers_for_stub = []
        is_hal_api_type = False
        hal_api_type_name = None
        hal_api_type = None
        hal_api_tok = None
        is_for_stubbing = False
        structure_member_access = False
        function_declaration = self._is_function_declaration()
        if function_declaration:
            function_name, _ = self.get_function_declaration_name()
        function_declaration_hal_api_id_list = []
        if typ == "expression":
            structure_member_access = self._is_structure_member_access()
        while (peek := self._peek()) and peek["value"] != term:
            tok = peek
            # ... handle HAL API type ...
            if tok["type"] == 'IDENTIFIER' and typ == 'declaration' and (
                tok.get("hal_api_type") == 'Typedef structure'
                or tok.get("hal_api_type") == 'Typedef enumeration'
                or tok.get('value') in self.declarations_identifiers_for_stub
            ):
                if tok.get('value') in self.declarations_identifiers_for_stub:
                    tok['for_stub'] = True
                    if not any(
                                    item["value"] == self.declarations_identifiers_for_stub[tok.get('value')]
                                    for item in identifiers_for_stub
                            ):
                        identifiers_for_stub.append(self.declarations_identifiers_for_stub[tok.get('value')])
                else :
                    is_hal_api_type = True
                    hal_api_type_name = tok["value"]
                    hal_api_type = tok.get("hal_api_type")
                    is_for_stubbing = True
                    if not any(item["value"] == tok["value"] for item in identifiers_for_stub):
                        identifiers_for_stub.append(tok)
                    hal_api_tok = tok
            # ... handle regular identifier ...
            elif tok["type"] == 'IDENTIFIER':
                if is_hal_api_type:
                    if not function_declaration:
                        tok["for_stub"] = True
                    tok["variable_type"] = hal_api_type_name
                    self.variables_identifiers_for_stub[tok["value"]] = (hal_api_type,tok["variable_type"])
                    self.declarations_identifiers_for_stub[tok["value"]] = hal_api_tok
                    is_for_stubbing = True
                if tok["value"] in self.declarations_identifiers_for_stub:
                    tok["for_stub"] = True
                    is_for_stubbing = True

                if tok["value"] in self.variables_identifiers_for_stub:
                    tok["for_stub"] = True
                    tok["hal_api_type"],tok["variable_type"] = self.variables_identifiers_for_stub[tok["value"]]
                    is_for_stubbing = True

                if tok.get("for_stub") is True:
                    if function_declaration :
                        if tok not in function_declaration_hal_api_id_list:
                            function_declaration_hal_api_id_list.append(tok)
                        self.functions_identifiers_for_stub[function_name] = function_declaration_hal_api_id_list

                    is_for_stubbing = True
                if typ != 'declaration':
                    if tok["value"] in self.variables_identifiers_for_stub:
                        if tok["value"] in self.declarations_identifiers_for_stub:
                            if not any(
                                        item["value"] == self.declarations_identifiers_for_stub[tok["value"]]
                                        for item in identifiers_for_stub
                                    ):
                                identifiers_for_stub.append(self.declarations_identifiers_for_stub[tok["value"]])
                        else:
                            if not any(item["value"] == tok["value"] for item in identifiers_for_stub):
                                identifiers_for_stub.append(tok)
                    else:
                        if not any(item["value"] == tok["value"] for item in identifiers_for_stub):
                            identifiers_for_stub.append(tok)
                elif (tok.get("hal_api_type") != 'Typedef structure' and
                      tok.get("hal_api_type") != 'Typedef enumeration'):
                    if not function_declaration:
                        if not any(item["value"] == tok["value"] for item in identifiers_for_stub):
                            identifiers_for_stub.append(tok)

            content.append(tok["value"])
            self._advance()

        if self._peek() and self._peek()["value"] == term:
            tok = self._peek()
            content.append(term)
            self._advance()

        end_line = self.tokens[self.index - 1]["line"]
        # to take the semi-colon when new-line insertion
        end_column= self.tokens[self.index - 1]["column"] + 1

        return Statement(
                start_line=start_line,
                end_line=end_line,
                start_column=start_column,
                end_column=end_column,
                type=typ,
                content=" ".join(content),
                is_for_stubbing=is_for_stubbing,
                identifiers_for_stub=identifiers_for_stub,
                is_struct_member_stmt = structure_member_access
            )


    def _handle_compound(self) -> Statement:
        start_line = self._peek()["line"]
        start_column = self._peek()["column"]
        content = []
        identifiers_for_stub = []
        depth = 0

        while self._peek():
            tok = self._peek()
            v = tok["value"]
            if tok["type"] == 'IDENTIFIER':
                if tok not in identifiers_for_stub:
                    identifiers_for_stub.append(tok)
            content.append(v)
            if v == "{":
                depth += 1
            elif v == "}":
                depth -= 1
            self._advance()
            if depth == 0:
                break

        end_line = self.tokens[self.index - 1]["line"]
        end_column = self.tokens[self.index - 1]["column"]
        block_start = self._find_block_start_idx(start_line)
        inner = self.tokens[block_start+1:self.index-1]
        children = StatementExtractor(inner).extract()
        return Statement(
            start_line, end_line, start_column, end_column + 1, "compound", " ".join(content),
            False,
            None,
            None,
            identifiers_for_stub,
            children
        )

    def _handle_struct(self) -> Statement:
        return self._handle_aggregate("struct")

    def _handle_enum(self) -> Statement:
        return self._handle_aggregate("enum")

    def _handle_union(self) -> Statement:
        return self._handle_aggregate("union")

    def _handle_typedef_struct(self) -> Statement:
        return self._handle_typedef_aggregate("typedef_struct", "struct")

    def _handle_typedef_enum(self) -> Statement:
        return self._handle_typedef_aggregate("typedef_enum", "enum")

    def _handle_typedef_union(self) -> Statement:
        return self._handle_typedef_aggregate("typedef_union", "union")

    def _handle_aggregate(self, keyword: str) -> Statement:
        start_line = self._peek()["line"]
        start_column = self._peek()["column"]
        content = [keyword]
        self._advance()  # Move past the keyword

        # Collect the name if present
        if self._peek() and self._peek()["type"] == "IDENTIFIER":
            content.append(self._peek()["value"])
            self._advance()

        # Handle the body
        if self._peek() and self._peek()["value"] == "{":
            body = self._handle_compound()
            content.append(body.content)
            children = body.children
            end_line = body.end_line
            end_column = body.end_column
        else:
            children = []
            end_line = start_line
            end_column = self._peek()["column"]

        return Statement(
                            start_line,
                            end_line,
                            start_column,
                            end_column,
                            keyword,
                            " ".join(content),
                            False,
                            None,
                            None,
                            [],
                            children
                            )

    def _handle_typedef_aggregate(self, stmt_type: str, keyword: str) -> Statement:
        start_line = self._peek()["line"]
        start_column = self._peek()["column"]
        content = ["typedef", keyword]
        self._advance()  # Move past 'typedef'
        self._advance()  # Move past the keyword (e.g., 'struct')

        # Collect the name if present
        if self._peek() and self._peek()["type"] == "IDENTIFIER":
            content.append(self._peek()["value"])
            self._advance()

        # Handle the body (compound statement)
        if self._peek() and self._peek()["value"] == "{":
            body = self._handle_compound()
            content.append(body.content)
            children = body.children
            end_line = body.end_line
            end_column = body.end_column
        else:
            children = []
            end_line = start_line
            end_column = self._peek()["column"] if self._peek() else start_column

        # Collect the typedef alias identifier and mark for stubbing
        if self._peek() and self._peek()["type"] == "IDENTIFIER":
            alias_token = self._peek()
            alias_token["for_stub"] = True
            content.append(alias_token["value"])
            self._advance()

        # Ensure the statement ends with a semicolon
        if self._peek() and self._peek()["value"] == ";":
            content.append(";")
            self._advance()

        return Statement(
            start_line,
            end_line,
            start_column,
            end_column,
            stmt_type,
            " ".join(content),
            False,
            None,
            None,
            [],
            children
        )

    def _handle_function_definition(self) -> Statement:
        start_line = self._peek()["line"]
        start_column = self._peek()["column"]
        content = []
        condition_content = []
        identifiers_for_stub = []
        while self._peek() and self._peek()["value"] != "{":
            v = self._peek()["value"]
            ttoken = self._peek()["type"]
            token =  self._peek()
            if ttoken == "IDENTIFIER":
                if token not in identifiers_for_stub:
                    identifiers_for_stub.append(token)
            content.append(v)
            condition_content.append(v)
            end_column = self._peek()["column"]
            self._advance()
        condition = StatementCondition(
                                        start_line=start_line,
                                        end_line=self._peek()["line"],
                                        start_column=start_column,
                                        end_column=end_column,
                                        condition=" ".join(condition_content),
                                        is_for_stubbing=False,
                                        identifiers_for_stub = [],
                                        insert_new_line = False,
                                        insert_line_before = False
                                      )
        compound_stmt = self._handle_compound()
        content.extend(compound_stmt.content.split())
        end_line = compound_stmt.end_line
        end_colmumn = compound_stmt.end_column
        return Statement(
                            start_line=start_line,
                            end_line= end_line,
                            start_column=start_column,
                            end_column=end_colmumn,
                            type="function_definition",
                            content=" ".join(content),
                            is_for_stubbing=False,
                            stubbing_condition=condition,
                            else_stubbing_condition=None,
                            do_stubbing_condition=None,
                            identifiers_for_stub=identifiers_for_stub,
                            children=compound_stmt.children,
                            chain_with_next = False,
                            chain_with_previous = False,
                            is_struct_member_stmt = False,
                            insert_new_line = False,
                            insert_line_before = False,
                        )

    def _handle_do_while(self) -> Statement:
        """
        Handles the do-while loop.
        """
        start_line = self._peek()["line"]
        start_column = self._peek()["column"]
        content = ["do"]
        self._advance()
        do_while_stubbing_condition = StatementCondition(
                                                            start_line = start_line,
                                                            end_line = start_line,
                                                            start_column= start_column,
                                                            end_column = start_column+len('do'),
                                                            condition= "do",
                                                            is_for_stubbing = False,
                                                            identifiers_for_stub = [],
                                                            insert_new_line = False,
                                                            insert_line_before = False
                                                        )
        # Parse the body
        if self._peek() and self._peek()["value"] == "{":
            body = self._handle_compound()
        else:
            # do_branch
            body = self._simple_stmt("expression", ";")
        content.append(body.content)

        # Parse the while condition, must be a while condition else error
        start_line_condition = self._peek()["line"]
        start_column_condition= self._peek()["column"]
        if self._peek() and self._peek()["value"] == "while":
            content.append("while")
            self._advance()
            condition = self._parse_condition(start_line_condition, start_column_condition,"(", ")")
            content.append(condition.condition)
            if self._peek() and self._peek()["value"] == ";":
                content.append(";")
                self._advance()
        else:
            # Handle error: expected identifier after #define
            raise ValueError(
                            f"Expected while condition at line {start_line_condition}, column {start_column_condition}"
            )

        if condition.is_for_stubbing is True:
            do_while_stubbing_condition.is_for_stubbing = True
            if body.end_line == condition.start_line :
                condition.insert_line_before = True
            if body.start_line == do_while_stubbing_condition.end_line:
                do_while_stubbing_condition.insert_new_line = True

        end_line = body.end_line
        end_column = body.end_column
        return Statement(
                            start_line = start_line,
                            end_line = end_line,
                            start_column = start_column,
                            end_column = end_column,
                            type = "do_while",
                            content = " ".join(content),
                            is_for_stubbing = False,
                            stubbing_condition = condition,
                            else_stubbing_condition= None,
                            do_stubbing_condition = do_while_stubbing_condition,
                            identifiers_for_stub = [],
                            children = [body],
                            chain_with_next = False ,
                            chain_with_previous = False,
                            is_struct_member_stmt = False,
                            insert_new_line = False,
                            insert_line_before = False,
                        )

    def _find_block_start_idx(self, line_no: int) -> int:
        """
        Finds the index of the opening brace '{' that starts a block on the given line number.
        Searches backwards from the current index.

        Args:
            line_no (int): The line number to search for the block start.

        Returns:
            int: The index of the '{' token on the specified line, or self.index - 1 if not found.
        """
        for i in range(self.index - 1, -1, -1):
            token = self.tokens[i]
            if token["line"] == line_no and token["value"] == "{":
                return i
        # If not found, return the previous index as a fallback
        return self.index - 1

    def _is_structure_member_access(self) -> bool:
        """
        Checks if the current token sequence represents a structure member access,
        i.e., uses '.' or '->' operators.

        Returns:
            bool: True if a structure member access operator is found near the current token.
        """
        # Check current and next token for '.' or '->'
        current_token = self._peek()
        next_token = self._peek(1)
        next_next_tok = self._peek(2)

        if current_token and next_token:
            # Check for '.' or '->' operator
            if current_token["type"] == "IDENTIFIER" and next_token["value"] in {".", "->"} \
                    and next_next_tok["type"] == "IDENTIFIER":
                return True

        # Optionally, scan a few tokens ahead if needed
        # For example, look ahead up to 3 tokens
        for offset in range(1, 4):
            tok = self._peek(offset)
            if tok and tok["value"] in {".", "->"}:
                return True

        return False

    def _is_assignment(self) -> bool:
        """
        Checks if the current token sequence represents an assignment expression.

        Returns:
            bool: True if an assignment operator is found before statement terminator, False otherwise.
        """
        assignment_operators = {
            "ASSIGN",      # =
            "PLUS_ASSIGN", # +=
            "MINUS_ASSIGN",# -=
            "MUL_ASSIGN",  # *=
            "DIV_ASSIGN",  # /=
            "MOD_ASSIGN",  # %=
            "AND_ASSIGN",  # &=
            "OR_ASSIGN",   # |=
            "XOR_ASSIGN",  # ^=
            "LSHIFT_ASSIGN", # <<=
            "RSHIFT_ASSIGN"  # >>=
        }

        idx = self.index
        while idx < len(self.tokens):
            tok = self.tokens[idx]
            if tok["type"] in assignment_operators:
                return True
            if tok["value"] == ";":
                # Reached end of statement without assignment
                return False
            idx += 1
        return False

    def _is_declaration(self) -> bool:
        """
        Enhanced: Detects variable and array declarations, including multiple declarations.
        """
        peek = self._peek()
        if not peek:
            return False

        builtins = {"INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "LONG", "SHORT", "BOOL", "SIGNED", "UNSIGNED"}
        compounds = {"ENUM", "STRUCT", "UNION"}
        storage_specs = {"EXTERN", "STATIC", "TYPEDEF", "AUTO", "REGISTER"}
        qualifiers = {
            "CONST", "VOLATILE", "RESTRICT", "THREAD_LOCAL", "ATOMIC",
            "__I", "__O", "__IO", "__IM", "__OM", "__IOM"
        }
        stdint_types = {"uint32_t", "uint16_t", "uint8_t", "int32_t", "int16_t", "int8_t"}

        j = self.index
        # Skip storage specifiers and qualifiers
        while j < len(self.tokens) and (
            self.tokens[j]["type"] in storage_specs or
            self.tokens[j]["type"] in qualifiers or self.tokens[j]["value"] in qualifiers
        ):
            j += 1

        # Check for type
        if j < len(self.tokens):
            token = self.tokens[j]
            if (
                token["type"] in builtins or
                token["type"] in compounds or
                token["type"] in stdint_types or
                (token["type"] == "IDENTIFIER") or  # Accept any identifier as type (for typedefs)
                token.get("hal_api_type") in {"Typedef structure", "Typedef enumeration"}
            ):
                j += 1
                # Support multiple declarations
                while True:
                    # Skip pointer stars
                    while j < len(self.tokens) and self.tokens[j]["value"] == "*":
                        j += 1
                    # Now expect an identifier (variable name)
                    if j < len(self.tokens) and self.tokens[j]["type"] == "IDENTIFIER":
                        j += 1
                        # Check for array brackets: zero or more [ ... ]
                        while j < len(self.tokens) and self.tokens[j]["value"] == "[":
                            j += 1
                            while j < len(self.tokens) and self.tokens[j]["value"] != "]":
                                j += 1
                            if j < len(self.tokens) and self.tokens[j]["value"] == "]":
                                j += 1
                            else:
                                return False
                        # Skip whitespace/comments
                        while j < len(self.tokens) and self.tokens[j]["type"] in {"WHITESPACE", "COMMENT"}:
                            j += 1
                        # Check for end or next variable
                        if j < len(self.tokens):
                            if self.tokens[j]["value"] == ";":
                                return True
                            if self.tokens[j]["value"] == "=":
                                return True
                            if self.tokens[j]["value"] == ",":
                                j += 1
                                continue
                    break
        return False


    def _is_function_definition(self) -> bool:
        """
        Determines if the current token index is at the start of a function definition.
        Returns True if a function definition is detected, otherwise False.
        """
        i = self.index
        while i < len(self.tokens):
            token = self.tokens[i]

            # If a semicolon is found before an opening brace, it's a declaration, not a definition
            if token["value"] == ";":
                return False

            # If an opening brace is found, check if it follows a function signature
            if token["value"] == "{":
                if self._is_function_signature(i - 1) or self._is_macro_prototype(i-1):
                    return True
                return False

            i += 1
        return False

    def _is_function_signature(self, end_index: int) -> bool:
        """
        Checks if the tokens ending at end_index form a function signature.
        """
        # The token before '{' should be ')'
        if end_index < 0 or self.tokens[end_index]["value"] != ")":
            return False

        # Walk backwards to find the matching '('
        depth = 1
        j = end_index - 1
        while j >= 0 and depth > 0:
            value = self.tokens[j]["value"]
            if value == ")":
                depth += 1
            elif value == "(":
                depth -= 1
            j -= 1

        # After matching, the token before '(' should be an identifier (function name)
        if depth == 0 and j >= 0 and self.tokens[j]["type"] == "IDENTIFIER":
            name = self.tokens[j]["value"]
            # Exclude control flow keywords
            if name not in {"if", "while", "for", "switch", "do"}:
                return True
        return False

    def _is_macro_prototype(self, end_index: int) -> bool:
        """
        Checks if the token at end_index is a macro likely used as a function prototype.
        """
        if end_index < 0:
            return False
        token = self.tokens[end_index]
        # Heuristic: macro names are usually all uppercase and not a C keyword
        if (token["type"] == "IDENTIFIER" and
            token["value"].isupper() and
            token["value"] not in {"IF", "WHILE", "FOR", "SWITCH", "DO"}):
            return True
        return False

    def _is_function_declaration(self) -> bool:
        """
        Determines if the current token index is at the start of a function declaration (prototype),
        using logic similar to _is_declaration.
        Returns True if a function declaration is detected, otherwise False.
        """
        builtins = {"INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "LONG", "SHORT", "BOOL", "SIGNED", "UNSIGNED"}
        compounds = {"ENUM", "STRUCT", "UNION"}
        storage_specs = {"EXTERN", "STATIC", "TYPEDEF", "AUTO", "REGISTER"}
        qualifiers = {
            "CONST", "VOLATILE", "RESTRICT", "THREAD_LOCAL", "ATOMIC",
            "__I", "__O", "__IO", "__IM", "__OM", "__IOM"
        }
        stdint_types = {"uint32_t", "uint16_t", "uint8_t", "int32_t", "int16_t", "int8_t"}

        j = self.index
        # Skip storage specifiers and qualifiers
        while j < len(self.tokens) and (
            self.tokens[j]["type"] in storage_specs or
            self.tokens[j]["type"] in qualifiers or self.tokens[j]["value"] in qualifiers
        ):
            j += 1

        # Check for type
        if j < len(self.tokens):
            token = self.tokens[j]
            if (
                token["type"] in builtins or
                token["type"] in compounds or
                token["type"] in stdint_types or
                (token["type"] == "IDENTIFIER") or  # Accept any identifier as type (for typedefs)
                token.get("hal_api_type") in {"Typedef structure", "Typedef enumeration"}
            ):
                j += 1
                # Skip pointer stars
                while j < len(self.tokens) and self.tokens[j]["value"] == "*":
                    j += 1
                # Now expect an identifier (function name)
                if j < len(self.tokens) and self.tokens[j]["type"] == "IDENTIFIER":
                    name = self.tokens[j]["value"]
                    # Exclude control flow keywords
                    if name in {"if", "while", "for", "switch", "do"}:
                        return False
                    j += 1
                    # Skip whitespace/comments
                    while j < len(self.tokens) and self.tokens[j]["type"] in {"WHITESPACE", "COMMENT"}:
                        j += 1
                    # Now expect '(' (start of parameter list)
                    if j < len(self.tokens) and self.tokens[j]["value"] == "(":
                        depth = 1
                        j += 1
                        # Find matching ')'
                        while j < len(self.tokens) and depth > 0:
                            if self.tokens[j]["value"] == "(":
                                depth += 1
                            elif self.tokens[j]["value"] == ")":
                                depth -= 1
                            j += 1
                        if depth == 0:
                            # Skip whitespace/comments
                            while j < len(self.tokens) and self.tokens[j]["type"] in {"WHITESPACE", "COMMENT"}:
                                j += 1
                            # Now expect ';' (declaration) or '{' (definition)
                            if j < len(self.tokens):
                                if self.tokens[j]["value"] == ";":
                                    return True
                                # If '{' comes next, it's a definition, not a declaration
                                if self.tokens[j]["value"] == "{":
                                    return False
        return False

    def get_function_declaration_name(self):
        """
        If the current token index is at the start of a function declaration,
        returns the IDENTIFIER name of the function. Otherwise, returns None.
        """
        builtins = {"INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "LONG", "SHORT", "BOOL", "SIGNED", "UNSIGNED"}
        compounds = {"ENUM", "STRUCT", "UNION"}
        storage_specs = {"EXTERN", "STATIC", "TYPEDEF", "AUTO", "REGISTER"}
        qualifiers = {
            "CONST", "VOLATILE", "RESTRICT", "THREAD_LOCAL", "ATOMIC",
            "__I", "__O", "__IO", "__IM", "__OM", "__IOM"
        }
        stdint_types = {"uint32_t", "uint16_t", "uint8_t", "int32_t", "int16_t", "int8_t"}

        j = self.index
        # Skip storage specifiers and qualifiers
        while j < len(self.tokens) and (
            self.tokens[j]["type"] in storage_specs or
            self.tokens[j]["type"] in qualifiers or self.tokens[j]["value"] in qualifiers
        ):
            j += 1

        # Check for type
        if j < len(self.tokens):
            token = self.tokens[j]
            if (
                token["type"] in builtins or
                token["type"] in compounds or
                token["type"] in stdint_types or
                (token["type"] == "IDENTIFIER") or  # Accept any identifier as type (for typedefs)
                token.get("hal_api_type") in {"Typedef structure", "Typedef enumeration"}
            ):
                j += 1
                # Skip pointer stars
                while j < len(self.tokens) and self.tokens[j]["value"] == "*":
                    j += 1
                # Now expect an identifier (function name)
                if j < len(self.tokens) and self.tokens[j]["type"] == "IDENTIFIER":
                    function_name_token = self.tokens[j]
                    name = self.tokens[j]["value"]
                    # Exclude control flow keywords
                    if name in {"if", "while", "for", "switch", "do"}:
                        return None
                    j += 1
                    # Skip whitespace/comments
                    while j < len(self.tokens) and self.tokens[j]["type"] in {"WHITESPACE", "COMMENT"}:
                        j += 1
                    # Now expect '(' (start of parameter list)
                    if j < len(self.tokens) and self.tokens[j]["value"] == "(":
                        depth = 1
                        j += 1
                        # Find matching ')'
                        while j < len(self.tokens) and depth > 0:
                            if self.tokens[j]["value"] == "(":
                                depth += 1
                            elif self.tokens[j]["value"] == ")":
                                depth -= 1
                            j += 1
                        if depth == 0:
                            # Skip whitespace/comments
                            while j < len(self.tokens) and self.tokens[j]["type"] in {"WHITESPACE", "COMMENT"}:
                                j += 1
                            # Now expect ';' (declaration) or '{' (definition)
                            if j < len(self.tokens) and self.tokens[j]["value"] == ";":
                                return name, function_name_token
        return None, None



    def _handle_typedef_alias(self) -> Statement:
        """
        Handle typedef aliases like 'typedef int alias;'
        """
        start_line = self._peek()["line"]
        start_column = self._peek()["column"]
        content = ["typedef"]
        self._advance()  # Move past 'typedef'
        identifiers_for_stub = []
        is_hal_api_type = False
        hal_api_type_name = None
        hal_api_type = None
        is_for_stubbing = False

        # Collect the type and alias
        while self._peek() and self._peek()["value"] != ";":
            token = self._peek()
            if token["type"] == 'IDENTIFIER':
                # Check for hal_api_type to mark for stubbing
                if token.get("hal_api_type") in ('Typedef structure', 'Typedef enumeration'):
                    is_hal_api_type = True
                    hal_api_type_name = token["value"]
                    hal_api_type = token.get("hal_api_type")
                    is_for_stubbing = True
                if is_hal_api_type:
                    token["for_stub"] = True
                    token["variable_type"] = hal_api_type_name
                    self.variables_identifiers_for_stub[token["value"]] = (hal_api_type,token["variable_type"])
                    is_for_stubbing = True
                if token["value"] in self.variables_identifiers_for_stub:
                    token["for_stub"] = True
                    token["hal_api_type"], token["variable_type"] = self.variables_identifiers_for_stub[token["value"]]
                    is_for_stubbing = True
                if token.get("for_stub") is True:
                    is_for_stubbing = True
                if token not in identifiers_for_stub:
                    identifiers_for_stub.append(token)
            content.append(token["value"])
            self._advance()

        # Mark the alias identifier for stubbing if present (last identifier before ';')
        if identifiers_for_stub:
            alias_token = identifiers_for_stub[-1]
            alias_token["for_stub"] = True
            # to be checked
            if alias_token["value"] not in self.variables_identifiers_for_stub:
                self.variables_identifiers_for_stub[alias_token["value"]] = (
                                                                                alias_token["hal_api_type"],
                                                                                alias_token["variable_type"]
                                                                            )
            is_for_stubbing = True

        # Ensure the statement ends with a semicolon
        if self._peek() and self._peek()["value"] == ";":
            content.append(";")
            self._advance()

        end_line = self.tokens[self.index - 1]["line"]
        end_column = self.tokens[self.index - 1]["column"]
        return Statement(
            start_line=start_line,
            end_line=end_line,
            start_column=start_column,
            end_column=end_column,
            type="typedef_alias",
            content=" ".join(content),
            is_for_stubbing=is_for_stubbing,
            stubbing_condition=None,
            else_stubbing_condition=None,
            do_stubbing_condition=None,
            identifiers_for_stub=identifiers_for_stub,
            children = [],
            chain_with_next = False ,
            chain_with_previous = False,
            is_struct_member_stmt = False,
            insert_new_line = False,
            insert_line_before = False,
        )


    def _parse_condition(self, start_line, start_column, start_token: str, end_token: str) -> StatementCondition:
        """
        Parses a condition enclosed by start_token and end_token (e.g., '(' and ')').

        Args:
            start_token (str): The opening token of the condition (e.g., '(').
            end_token (str): The closing token of the condition (e.g., ')').

        Returns:
            StatementCondition: The parsed condition.
        """

        condition_start_line = start_line
        condition_start_column = start_column
        condition_content = []
        depth = 0
        identifiers_for_stub = []
        is_for_stubbing = False
        is_hal_api_type = False
        hal_api_tok = None
        hal_api_type_name = None
        hal_api_type = None
        while self._peek():
            if self._peek()["for_stub"] is True:
                is_for_stubbing = True
            if( self._peek()["type"] == 'IDENTIFIER' and
                ( self._peek()["hal_api_type"] == 'Typedef structure' or
                 self._peek()["hal_api_type"] == 'Typedef enumeration')
                 ):
                is_hal_api_type = True
                hal_api_type_name = self._peek()["value"]
                hal_api_type = self._peek()["hal_api_type"]
                hal_api_tok = self._peek()
                is_for_stubbing = True
            if self._peek()["type"] == 'IDENTIFIER':
                if self._peek()["for_stub"] is True:
                    self._peek()["for_stub"] = True
                    is_for_stubbing = True
                    if not any(item["value"] == self._peek()["value"] for item in identifiers_for_stub):
                        identifiers_for_stub.append(self._peek())

                if self._peek()["value"] in self.functions_identifiers_for_stub:
                    self._peek()["for_stub"] = True
                    # This logic --> to be discussed
                    identifiers_for_stub.append(self.functions_identifiers_for_stub[self._peek()["value"]][0])
                    # for tok in self.functions_identifiers_for_stub[self._peek()["value"]]:
                    #     if not any(item["value"] == tok["value"] for item in identifiers_for_stub):
                    #         identifiers_for_stub.append(tok)
                    is_for_stubbing = True

                if self._peek()["value"] in self.declarations_identifiers_for_stub:
                    self._peek()["for_stub"] = True
                    is_for_stubbing = True
                    if not any(
                                item["value"] == self.declarations_identifiers_for_stub[self._peek()["value"]]
                                for item in identifiers_for_stub
                            ):
                        identifiers_for_stub.append(self.declarations_identifiers_for_stub[self._peek()["value"]])

                if is_hal_api_type is True:
                    self._peek()["for_stub"] = True
                    self._peek()["variable_type"] = hal_api_type_name
                    self.variables_identifiers_for_stub[self._peek()["value"]] =  \
                                                                      (hal_api_type,self._peek()["variable_type"])
                    self.declarations_identifiers_for_stub[self._peek()["value"]] = hal_api_tok
                    is_for_stubbing = True
                    if self._peek() not in identifiers_for_stub:
                        identifiers_for_stub.append(self._peek())

                if self._peek()["value"] in self.variables_identifiers_for_stub:
                    self._peek()["for_stub"] = True
                    self._peek()["hal_api_type"], self._peek()["variable_type"] = \
                                                            self.variables_identifiers_for_stub[self._peek()["value"]]
                    is_for_stubbing = True
                    if self._peek()["value"] in self.declarations_identifiers_for_stub:
                        if self.declarations_identifiers_for_stub[self._peek()["value"]] not in identifiers_for_stub:
                            identifiers_for_stub.append(self.declarations_identifiers_for_stub[self._peek()["value"]])
                    else:
                        if self._peek() not in identifiers_for_stub:
                            identifiers_for_stub.append(self._peek())

            condition_content.append(self._peek()["value"])
            if self._peek()["value"] == start_token:
                depth += 1
            elif self._peek()["value"] == end_token:
                depth -= 1
                if depth == 0:
                    self._advance()
                    break
            self._advance()

        condition_end_line = self._peek(-1)["line"]
        # must be after ')'
        condition_end_column = self._peek(-1)["column"]+1
        return StatementCondition(
                                    start_line = condition_start_line,
                                    end_line = condition_end_line,
                                    start_column = condition_start_column,
                                    end_column = condition_end_column,
                                    condition = " ".join(condition_content),
                                    is_for_stubbing = is_for_stubbing,
                                    identifiers_for_stub = identifiers_for_stub,
                                    insert_new_line = False,
                                    insert_line_before = False
                                    )


    def _handle_control_structure(self, structure_type: str) -> Statement:
        """
        Handles C flow control statements: if (with else if/else), for, while, switch.

        Args:
            structure_type (str): One of 'if', 'for', 'while', 'switch'.

        Returns:
            Statement: Parsed statement representing the control structure.
        """
        if structure_type == "if":
            return self._handle_if_statement()
        if structure_type == "for":
            return self._handle_loop_statement("for")
        if structure_type == "while":
            return self._handle_loop_statement("while")
        if structure_type == "switch":
            return self._handle_loop_statement("switch")
        raise ValueError(f"Unsupported control structure type: {structure_type}")

    def _handle_if_statement(self) -> Statement:
        """
        Parses an if statement with optional else if/else branches.
        """
        tok = self._peek()
        start_line = tok["line"]
        start_column = tok["column"]
        content = ["if"]
        self._advance()

        # Parse the if condition
        condition = self._parse_condition(start_line, start_column, "(", ")")
        content.append(condition.condition)

        # Parse the if body (compound or simple statement)
        if self._peek() and self._peek()["value"] == "{":
            if_body = self._handle_compound()
            if_body.type = "if_branch"
        else:
            # expression instead of if_branch
            if_body = self._simple_stmt("expression", ";")
            if_body.type = "expression"
        if condition.is_for_stubbing is True:
            if if_body.start_line == condition.end_line :
                condition.insert_new_line = True
            if if_body.children:
                if if_body.children[0].start_line == condition.end_line:
                    if_body.children[0].insert_line_before = True
                if if_body.children[-1].end_line == if_body.end_line:
                    if_body.children[-1].insert_new_line = True
        content.append(if_body.content)
        children = [if_body]

        else_stubbing_condition = None

        # Parse else if / else branches
        while self._peek() and self._peek()["value"] == "else":
            content.append("else")
            else_start_line = self._peek()["line"]
            else_start_column = self._peek()["column"]
            self._advance()

            # Create a stub condition for else keyword
            else_stubbing_condition = StatementCondition(
                                                            start_line=else_start_line,
                                                            end_line=else_start_line,
                                                            start_column=else_start_column,
                                                            end_column=else_start_column+len('else'),
                                                            condition="else",
                                                            is_for_stubbing=condition.is_for_stubbing,
                                                            identifiers_for_stub=[],
                                                            insert_new_line = False,
                                                            insert_line_before= False
                                                        )

            if else_stubbing_condition.is_for_stubbing is True:
                if self._peek()["line"] == else_stubbing_condition.end_line :
                    else_stubbing_condition.insert_new_line = True

            if self._peek() and self._peek()["value"] == "if":
                # else if branch: recursively parse as if statement
                else_if_stmt = self._handle_if_statement()
                content.append(else_if_stmt.content)
                children.append(else_if_stmt)
            else:
                # else branch: parse compound or simple statement
                if self._peek() and self._peek()["value"] == "{":
                    else_body = self._handle_compound()
                    else_body.type = "else_branch"
                    if else_stubbing_condition.is_for_stubbing is True:
                        if else_body.children :
                            if else_body.children[0].start_line == else_stubbing_condition.end_line:
                                else_body.children[0].insert_line_before = True
                            if else_body.children[-1].end_line == else_body.end_line:
                                else_body.children[-1].insert_new_line = True
                else:
                    # else_branch
                    else_body = self._simple_stmt("expression", ";")
                    else_body.type = "expression"
                content.append(else_body.content)
                children.append(else_body)
                break  # else is always last branch

        end_line = children[-1].end_line if children else start_line
        end_column = children[-1].end_column if children else start_column

        return Statement(
                            start_line=start_line,
                            end_line=end_line,
                            start_column=start_column,
                            end_column=end_column,
                            type="if",
                            content=" ".join(content),
                            is_for_stubbing=False,
                            stubbing_condition=condition,
                            else_stubbing_condition=else_stubbing_condition,
                            do_stubbing_condition = None,
                            identifiers_for_stub=[],
                            children=children,
                            chain_with_next = False,
                            chain_with_previous = False,
                            is_struct_member_stmt = False,
                            insert_new_line = False,
                            insert_line_before = False,
                        )


    def _handle_loop_statement(self, loop_type: str) -> Statement:
        """
        Parses for, while, and switch statements.

        Args:
            loop_type (str): 'for', 'while', or 'switch'.

        Returns:
            Statement: Parsed statement representing the loop or switch.
        """
        tok = self._peek()
        start_line = tok["line"]
        start_column = tok["column"]
        content = [loop_type]
        self._advance()

        # Parse condition or control expression
        condition = self._parse_condition(start_line, start_column, "(", ")")
        content.append(condition.condition)

        # Parse body
        if self._peek() and self._peek()["value"] == "{":
            body = self._handle_compound()
            body.type = f"{loop_type}_branch"
        else:
            body = self._simple_stmt(f"{loop_type}_branch", ";")
        content.append(body.content)
        children = [body]
        if condition.is_for_stubbing is True:
            if body.start_line == condition.end_line :
                condition.insert_new_line = True
        end_line = body.end_line
        end_column = body.end_column

        return Statement(
                            start_line=start_line,
                            end_line=end_line,
                            start_column=start_column,
                            end_column=end_column,
                            type=loop_type,
                            content=" ".join(content),
                            is_for_stubbing=False,
                            stubbing_condition=condition,
                            else_stubbing_condition=None,
                            do_stubbing_condition= None,
                            identifiers_for_stub=[],
                            children=children,
                            chain_with_next = False,
                            chain_with_previous = False,
                            is_struct_member_stmt = False,
                            insert_new_line = False,
                            insert_line_before = False,
                        )



def count_insert_lines(statements):
    """
    Counts the number of times insert_new_line or insert_line_before are True
    in both Statement and StatementCondition objects, recursively.

    Args:
        statements (List[Statement]): List of top-level Statement objects.

    Returns:
        int: Total count of insert_new_line or insert_line_before set to True.
    """
    def count_in_condition(cond):
        if cond is None:
            return 0
        return int(getattr(cond, 'insert_new_line', False)) + int(getattr(cond, 'insert_line_before', False))

    def count_in_statement(stmt):
        count = int(getattr(stmt, 'insert_new_line', False)) + int(getattr(stmt, 'insert_line_before', False))
        # Check all StatementCondition fields
        count += count_in_condition(getattr(stmt, 'stubbing_condition', None))
        count += count_in_condition(getattr(stmt, 'else_stubbing_condition', None))
        count += count_in_condition(getattr(stmt, 'do_stubbing_condition', None))
        # Recurse into children
        for child in getattr(stmt, 'children', []):
            count += count_in_statement(child)
        return count

    total = 0
    for stmt in statements:
        total += count_in_statement(stmt)
    return total

def extract_insert_positions(statements):
    """
    Extracts the (line, column) positions for each place where
    insert_new_line or insert_line_before is True in both Statement
    and StatementCondition objects, recursively.

    Args:
        statements (List[Statement]): List of top-level Statement objects.

    Returns:
        List[Dict]: List of dictionaries with insertion info:
            {
                'type': 'statement' or 'condition',
                'field': 'insert_new_line' or 'insert_line_before',
                'line': int,
                'column': int,
                'statement_type': str,  # e.g., 'if', 'for', etc.
                'condition_type': str or None,  # e.g., 'stubbing_condition'
            }
    """
    results = []

    def check_and_add(obj, obj_type, field_name, line, column, statement_type, condition_type=None):
        if getattr(obj, field_name, False):
            results.append({
                'type': obj_type,
                'field': field_name,
                'line': line,
                'column': column,
                'statement_type': statement_type,
                'condition_type': condition_type,
            })

    def process_condition(cond, statement_type, condition_type):
        if cond is None:
            return
        check_and_add(
                        cond, 'condition', 'insert_new_line', cond.end_line,
                        cond.end_column, statement_type, condition_type
                    )
        check_and_add(
                        cond, 'condition', 'insert_line_before', cond.start_line,
                        cond.start_column, statement_type, condition_type
                    )

    def process_statement(stmt):
        # Statement-level insertions
        check_and_add(stmt, 'statement', 'insert_new_line', stmt.end_line, stmt.end_column, stmt.type)
        check_and_add(stmt, 'statement', 'insert_line_before', stmt.start_line, stmt.start_column, stmt.type)
        # Condition fields
        process_condition(getattr(stmt, 'stubbing_condition', None), stmt.type, 'stubbing_condition')
        process_condition(getattr(stmt, 'else_stubbing_condition', None), stmt.type, 'else_stubbing_condition')
        process_condition(getattr(stmt, 'do_stubbing_condition', None), stmt.type, 'do_stubbing_condition')
        # Children
        for child in getattr(stmt, 'children', []):
            process_statement(child)

    for stmt in statements:
        process_statement(stmt)
    return results


def increment_lines_for_insertions(statements: List['Statement']):
    """
    For each Statement and StatementCondition, increment start_line and end_line by the number of insertions
    before or at their original line/column, according to insertion type.
    Before shifting, save the original position in origin_position.
    """

    insert_positions_newline = []
    insert_positions_before = []

    def collect_insert_positions(stmt):
        if getattr(stmt, 'insert_new_line', False):
            insert_positions_newline.append((stmt.end_line, getattr(stmt, 'end_column', 0)))
        if getattr(stmt, 'insert_line_before', False):
            insert_positions_before.append((stmt.start_line, getattr(stmt, 'start_column', 0)))
        for cond_attr in ['stubbing_condition', 'else_stubbing_condition', 'do_stubbing_condition']:
            cond = getattr(stmt, cond_attr, None)
            if cond:
                if getattr(cond, 'insert_new_line', False):
                    insert_positions_newline.append((cond.end_line, getattr(cond, 'end_column', 0)))
                if getattr(cond, 'insert_line_before', False):
                    insert_positions_before.append((cond.start_line, getattr(cond, 'start_column', 0)))
        for child in getattr(stmt, 'children', []):
            collect_insert_positions(child)

    for stmt in statements:
        collect_insert_positions(stmt)

    insert_positions_newline.sort()
    insert_positions_before.sort()

    def shift_for(line, col):
        shift = 0
        shift += sum(
            1 for (ins_line, ins_col) in insert_positions_newline
            if (ins_line < line) or (ins_line == line and ins_col < col)
        )
        shift += sum(
            1 for (ins_line, ins_col) in insert_positions_before
            if (ins_line < line) or (ins_line == line and ins_col <= col)
        )
        return shift

    def save_origin(obj):
        # Save the original position if not already saved
        if getattr(obj, 'origin_position', None) is None:
            obj.origin_position = Position(
                line_start=obj.start_line,
                line_end=obj.end_line,
                column_start=getattr(obj, 'start_column', 0),
                column_end=getattr(obj, 'end_column', 0)
            )

    def update_lines(obj):
        # Shift this node (parent or child)
        if hasattr(obj, 'start_line') and hasattr(obj, 'end_line'):
            save_origin(obj)
            orig_start = obj.origin_position.line_start
            orig_start_col = obj.origin_position.column_start
            orig_end = obj.origin_position.line_end
            orig_end_col = obj.origin_position.column_end
            shift_start = shift_for(orig_start, orig_start_col)
            shift_end = shift_for(orig_end, orig_end_col)
            obj.start_line = orig_start + shift_start
            obj.end_line = orig_end + shift_end

        # Update conditions
        for cond_attr in ['stubbing_condition', 'else_stubbing_condition', 'do_stubbing_condition']:
            cond = getattr(obj, cond_attr, None)
            if cond and hasattr(cond, 'start_line') and hasattr(cond, 'end_line'):
                save_origin(cond)
                orig_start = cond.origin_position.line_start
                orig_start_col = cond.origin_position.column_start
                orig_end = cond.origin_position.line_end
                orig_end_col = cond.origin_position.column_end
                shift_start = shift_for(orig_start, orig_start_col)
                shift_end = shift_for(orig_end, orig_end_col)
                cond.start_line = orig_start + shift_start
                cond.end_line = orig_end + shift_end

        # Recursively update children
        for child in getattr(obj, 'children', []):
            update_lines(child)

    for stmt in statements:
        update_lines(stmt)



def split_lines_at_positions(content, positions):
    """
    Splits lines in the content at the specified (line, column) positions.

    Args:
        content (str): The original text.
        positions (List[Dict]): Each dict must have 'line' and 'column' (both 1-based).

    Returns:
        str: The modified content with newlines inserted at the specified positions.
    """
    lines = content.split('\n')

    # Group columns by line
    line_to_columns = defaultdict(list)
    for pos in positions:
        line_to_columns[pos['line'] - 1].append(pos['column'] - 1)  # convert to 0-based

    # Process each line with insertions, from last to first line to avoid index shifting
    for line_idx in sorted(line_to_columns.keys(), reverse=True):
        columns = sorted(line_to_columns[line_idx], reverse=True)  # rightmost first
        if 0 <= line_idx < len(lines):
            line = lines[line_idx]
            for col_idx in columns:
                if 0 <= col_idx <= len(line):
                    before = line[:col_idx]
                    after = line[col_idx:]
                    # Replace the line with two new lines
                    lines[line_idx:line_idx+1] = [before, after]
                    # After splitting, 'line_idx' now points to 'before', and 'after' is at 'line_idx+1'
                    # For next split, operate on 'before' (which is already split), so no further action needed
                    line = before  # For next split, operate on the left part only

    return '\n'.join(lines)
