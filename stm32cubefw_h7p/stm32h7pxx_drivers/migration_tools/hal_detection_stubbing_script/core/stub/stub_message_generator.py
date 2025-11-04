"""
/**
  *************************************************************************************************
  * @file    stub_message_generator.py
  * @brief   Stub Message Generator Module : Provides services for generating stub messages
  *          from extracted statements for HAL detection stubbing script.
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
import re
from dataclasses import dataclass, field
from typing import List, Dict, Optional, Any, Tuple
from enum import Enum
import logging

from hal_detection_stubbing_script.core.log import log
from hal_detection_stubbing_script.core.log.log_messages import warning_log_messages
from hal_detection_stubbing_script.core.stub.stub_statement_extractor import Statement


class StatementType(Enum):
    """
    Enumeration of possible statement types in source code parsing.

    Members:
        EXPRESSION: Represents an expression statement.
        DECLARATION: Represents a variable or type declaration.
        FUNCTION_DEFINITION: Represents a function definition.
        FOR: Represents a 'for' loop statement.
        WHILE: Represents a 'while' loop statement.
        DO_WHILE: Represents a 'do-while' loop statement.
        IF: Represents an 'if' conditional statement.
        SWITCH: Represents a 'switch' statement.
        DEFINE: Represents a preprocessor define statement.
        SWITCH_BRANCH: Represents a branch within a switch statement.
    """
    EXPRESSION = "expression"
    DECLARATION = "declaration"
    FUNCTION_DEFINITION = "function_definition"
    FOR = "for"
    WHILE = "while"
    DO_WHILE = "do_while"
    IF = "if"
    SWITCH = "switch"
    DEFINE = "define"
    SWITCH_BRANCH = "switch_branch"


@dataclass
class StructMember:
    """
    Represents a member of a struct, including its declaration line and associated typedef information.

    Attributes:
        line (str): The source code line representing the struct member.
        typedef_struct (Dict[str, Any]): Additional typedef information for the struct member.
    """
    line: str = ''
    typedef_struct: Dict[str, Any] = field(default_factory=dict)


@dataclass
class StubMessages:
    """
    Represents a block of stub messages generated from a code statement.
    """
    start_stub_line: int
    end_stub_line: int
    warnings_messages: List[str]
    msg_stub_begin: Optional[str] = None
    msg_stub_end: Optional[str] = None
    is_struct: Optional[bool] = False
    is_chain : Optional[bool] = False
    struct_member : Optional[StructMember] = None

    @classmethod
    def construct_from_statement(cls, stmt: 'Statement') -> List['StubMessages']:
        """
        Constructs blocks of stub messages from a statement, handling different statement types.
        Recursively processes child statements.
        """
        block_messages = []
        try:
            statement_type = StatementType(stmt.type)
        except ValueError:
            statement_type = None

        # Select the relevant statement for stubbing
        statement = stmt.stubbing_condition if statement_type in {
            StatementType.FOR, StatementType.WHILE, StatementType.DO_WHILE, StatementType.IF, StatementType.SWITCH
        } else stmt

        active_identifiers = extract_for_stub_elements(statement.identifiers_for_stub)
        start_stub_line = statement.start_line - 1
        end_stub_line = statement.end_line
        lineo_log = get_lineo_log(statement)

        # Handle each statement type
        if statement_type == StatementType.EXPRESSION:
            if stmt.is_struct_member():
                block_messages.extend(
                    handle_struct_member(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log)
                )
            else:
                block_messages.extend(
                    handle_expression(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log)
                )
        elif statement_type == StatementType.DECLARATION:
            block_messages.extend(
                handle_declaration(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log)
            )
        elif statement_type == StatementType.FUNCTION_DEFINITION:
            block_messages.extend(
                handle_function_definition(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log)
            )
        elif statement_type in {StatementType.FOR, StatementType.WHILE, StatementType.IF}:
            block_messages.extend(
                handle_control_flow(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log)
            )
        elif statement_type == StatementType.DO_WHILE:
            block_messages.extend(
                handle_do_while(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log)
            )
        elif statement_type == StatementType.SWITCH:
            block_messages.extend(
                handle_switch(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log)
            )
        elif statement_type == StatementType.DEFINE:
            block_messages.extend(
                handle_define(active_identifiers, start_stub_line, end_stub_line, lineo_log)
            )

        # Recursively process children (except for function definitions, which handle their own children)
        if statement_type != StatementType.FUNCTION_DEFINITION:
            for child in getattr(stmt, "children", []):
                block_messages.extend(cls.construct_from_statement(child))

        return block_messages

def extract_for_stub_elements(data: List[Dict]) -> List[Dict]:
    """Extracts elements from a list of dictionaries where 'for_stub' is True."""
    return [item for item in data if item.get('for_stub') is True]

def extract_not_for_stub_declared_variable(data: List[Dict]) -> List[Dict]:
    """
    Extract up to two declared variables from active identifiers,
    excluding those marked as 'for_stub' or with a non-None 'hal_api_type'.
    Returns a list of up to two matching items.
    """
    filtered = [item for item in data if item.get('for_stub') is False and item.get('hal_api_type') is None]
    return filtered[:2]

def get_log_message(el: Dict, lineo_log: str) -> Tuple[str, str, str, str]:
    """Extracts log message components from an identifier dictionary."""
    try:
        layer = el.get('layer')
        value = el.get('value')
        api_type = el.get('hal_api_type')
        file = el.get('file')
        link = el.get('link')
        return log.create_message(value, api_type, layer, file, link, lineo_log)
    except (TypeError, ValueError) as e:
        logging.error("Error extracting log message: %s",e)
        return "", "", "", ""

def get_lineo_log(statement: Statement) -> str:
    """Returns a formatted line number log string for a statement."""
    try:
        pos = getattr(statement, "origin_position", None)
        if pos is not None:
            if pos.line_start == pos.line_end:
                return str(pos.line_start)
            return f"{pos.line_start}-{pos.line_end}"
        if statement.start_line == statement.end_line:
            return str(statement.start_line)
        return f"{statement.start_line}-{statement.end_line}"
    except AttributeError as e:
        logging.error("Error getting lineo_log: %s",e)
        return ""

def extract_and_log_messages(identifiers: List[Dict], lineo_log: str) -> Tuple[List[str], str, str]:
    """
    Extracts warning messages, logs, and stub begin/end from a list of identifiers.
    Returns a tuple: (list of warning messages, stub_begin, stub_end)
    """
    all_msg_logs = []
    msg_stub_begin, msg_stub_end = "", ""
    for ident in identifiers:
        try:
            msg_warning, msg_log, stub_begin, stub_end = get_log_message(ident, lineo_log)
            all_msg_logs.append(msg_warning)
            log.add_msg_log(msg_log)
            msg_stub_begin = stub_begin
            msg_stub_end = stub_end
        except (TypeError, ValueError, AttributeError) as e:
            logging.error("Error in extract_and_log_messages: %s", e)
    return all_msg_logs, msg_stub_begin, msg_stub_end

def handle_declaration(stmt : Statement, active_identifiers, start_stub_line, end_stub_line, lineo_log):
    """Handles declaration statements for stub message generation."""
    block_messages = []
    warnings_messages = []
    msg_stub_begin, msg_stub_end = "", ""
    checklist_var = None
    checklist_type_var = ""

    found_var = extract_not_for_stub_declared_variable(stmt.identifiers_for_stub)
    if found_var and len(found_var) > 1:
        checklist_var = found_var[1]
        checklist_type_var = found_var[0]

    if active_identifiers:
        all_msg_logs, msg_stub_begin, msg_stub_end = extract_and_log_messages(active_identifiers, lineo_log)

        if checklist_var is not None and checklist_var.get('value') not in msg_stub_begin:
            msg_stub_end = (
                                "#else\n" + checklist_type_var.get('value') + " "
                                + checklist_var.get('value') + ";\n" + msg_stub_end
            )

        warnings_messages.append("\n".join(all_msg_logs))
        block_messages.append(StubMessages(
            start_stub_line=start_stub_line,
            end_stub_line=end_stub_line,
            warnings_messages=warnings_messages,
            msg_stub_begin=msg_stub_begin,
            msg_stub_end=msg_stub_end
        ))
    return block_messages

def handle_struct_member(
        stmt: Statement,
        active_identifiers: list,
        start_stub_line: int,
        end_stub_line: int,
        lineo_log
    ) -> list:
    """
    Handles struct member statements for stub message generation.

    This function processes active identifiers to identify typedef structures,
    extracts and logs warning messages, and constructs a list of StubMessages
    objects representing the stub information for struct members.

    Args:
        stmt (Statement): The statement object representing the struct member.
        active_identifiers (list): List of active identifier dictionaries.
        start_stub_line (int): The starting line number of the stub block.
        end_stub_line (int): The ending line number of the stub block.
        lineo_log: Log information for line numbers (type depends on implementation).

    Returns:
        list: A list of StubMessages objects containing stub and warning information.
    """
    block_messages = []
    warnings_messages = []
    typedef_struct = {}
    struct_member = StructMember()
    if active_identifiers:
        for ident in active_identifiers:
            if ident.get('hal_api_type') == 'Typedef structure':
                typedef_struct[ident.get('value')] = ident.get('hal_api_type')
                struct_member = StructMember(
                    line=lineo_log,
                    typedef_struct=typedef_struct
                )
        all_warning_mgs, msg_stub_begin, msg_stub_end = extract_and_log_messages(active_identifiers, lineo_log)
        warnings_messages.append("\n".join(all_warning_mgs))

        block_messages.append(StubMessages(
            start_stub_line=start_stub_line,
            end_stub_line=end_stub_line,
            warnings_messages=warnings_messages,
            msg_stub_begin=msg_stub_begin,
            msg_stub_end=msg_stub_end,
            is_struct=True,
            is_chain=stmt.is_chain_next() or stmt.is_chain_previous(),
            struct_member=struct_member
        ))

    return block_messages

def handle_expression(
    stmt: Statement,
    active_identifiers: list,
    start_stub_line: int,
    end_stub_line: int,
    lineo_log
) -> list:
    """
    Handles expression statements for stub message generation.

    Args:
        stmt: The statement object.
        active_identifiers: List of active identifier dictionaries.
        start_stub_line: The starting line number for the stub.
        end_stub_line: The ending line number for the stub.
        lineo_log: Log object for line operations.

    Returns:
        List of StubMessages objects.
    """
    block_messages = []
    warnings_messages = []

    if active_identifiers:
        all_msg_logs, msg_stub_begin, msg_stub_end = extract_and_log_messages(active_identifiers, lineo_log)
        warnings_messages.append("\n".join(all_msg_logs))

        block_messages.append(StubMessages(
            start_stub_line=start_stub_line,
            end_stub_line=end_stub_line,
            warnings_messages=warnings_messages,
            msg_stub_begin=msg_stub_begin,
            msg_stub_end=msg_stub_end,
            # is_struct=stmt.is_struct_member(),
            is_chain=stmt.is_chain_next() or stmt.is_chain_previous()
        ))
    return block_messages

def collect_all_msg_logs(identifiers, lineo_log, seen_messages):
    """
    Collects and deduplicates warning messages from a list of identifiers.

    This helper function extracts warning messages, stub begin, and stub end information
    from the provided identifiers. It ensures that only new (not previously seen) messages
    are added to the result and updates the set of seen messages accordingly.

    Args:
        identifiers (list): List of identifier dictionaries to process.
        lineo_log (str): Log information for line numbers.
        seen_messages (set): Set of messages that have already been seen.

    Returns:
        tuple: A tuple containing:
            - new_msgs (list): List of new warning messages not previously seen.
            - stub_begin (str): The beginning part of the stub message.
            - stub_end (str): The ending part of the stub message.
    """

    all_msg_logs, stub_begin, stub_end = extract_and_log_messages(identifiers, lineo_log)
    new_msgs = [msg for msg in all_msg_logs if msg not in seen_messages]
    seen_messages.update(new_msgs)
    return new_msgs, stub_begin, stub_end

def process_children_recursively(children, seen_messages, all_msg_logs):
    """
    Recursively processes child statements to collect and deduplicate warning messages.

    This function traverses the children of a statement, extracting warning messages
    from each child's identifiers and stubbing conditions. It updates the provided
    all_msg_logs list and seen_messages set with any new messages found.

    Args:
        children (list): List of child statement objects to process.
        seen_messages (set): Set of messages that have already been seen.
        all_msg_logs (list): List to accumulate all collected warning messages.

    Returns:
        None
    """
    for child in children:
        child_active_identifiers = extract_for_stub_elements(getattr(child, "identifiers_for_stub", []))
        if child_active_identifiers:
            child_msgs, _, _ = collect_all_msg_logs(
                child_active_identifiers,
                f"{child.start_line}-{child.end_line}",
                seen_messages
            )
            all_msg_logs.extend(child_msgs)

        stubbing_condition = getattr(child, "stubbing_condition", None)
        if stubbing_condition:
            cond_active_identifiers = extract_for_stub_elements(
                getattr(stubbing_condition, "identifiers_for_stub", [])
            )
            if cond_active_identifiers:
                cond_msgs, _, _ = collect_all_msg_logs(
                    cond_active_identifiers,
                    f"{stubbing_condition.start_line}-{stubbing_condition.end_line}",
                    seen_messages
                )
                all_msg_logs.extend(cond_msgs)

        if hasattr(child, "children"):
            process_children_recursively(child.children, seen_messages, all_msg_logs)

def handle_function_definition(stmt: Statement, active_identifiers, start_stub_line, end_stub_line, lineo_log):
    """
    Handles function definition statements for stub message generation.

    This function processes a function definition statement, including special handling
    for HAL MspInit/MspDeInit patterns. It collects and deduplicates warning messages
    from the function's own identifiers and recursively from its children and their
    stubbing conditions. It then generates and returns a list of StubMessages objects
    representing the stub information for the function and its children.

    Args:
        stmt (Statement): The statement object representing the function definition.
        active_identifiers (list): List of active identifier dictionaries for the function.
        start_stub_line (int): The starting line number of the stub block.
        end_stub_line (int): The ending line number of the stub block.
        lineo_log: Log information for line numbers (type depends on implementation).

    Returns:
        list: A list of StubMessages objects containing stub and warning information
              for the function definition and its children.
    """
    block_messages = []
    warnings_messages = []
    msg_stub_begin, msg_stub_end = "", ""
    seen_messages = set()
    all_msg_logs = []
    msp_init_deinit_pattern = r"HAL_[A-Z0-9]+_Msp(?:De)?Init\s*\("

    if re.search(msp_init_deinit_pattern, stmt.stubbing_condition.condition):
        if active_identifiers:
            new_msgs, msg_stub_begin, msg_stub_end = collect_all_msg_logs(active_identifiers, lineo_log, seen_messages)
            all_msg_logs.extend(new_msgs)
            process_children_recursively(getattr(stmt, "children", []), seen_messages, all_msg_logs)

            if all_msg_logs or msg_stub_begin or msg_stub_end:
                warnings_messages.append("\n".join(all_msg_logs))
                block_messages.append(StubMessages(
                    start_stub_line=start_stub_line,
                    end_stub_line=end_stub_line,
                    warnings_messages=warnings_messages,
                    msg_stub_begin=msg_stub_begin,
                    msg_stub_end=msg_stub_end
                ))
            else:
                for child in getattr(stmt, "children", []):
                    block_messages.extend(StubMessages.construct_from_statement(child))
    else:
        if active_identifiers:
            all_msg_logs, msg_stub_begin, msg_stub_end = extract_and_log_messages(active_identifiers, lineo_log)
            warnings_messages.append("\n".join(all_msg_logs))
            block_messages.append(StubMessages(
                start_stub_line=start_stub_line,
                end_stub_line=end_stub_line,
                warnings_messages=warnings_messages,
                msg_stub_begin=msg_stub_begin,
                msg_stub_end=msg_stub_end
            ))

        for child in getattr(stmt, "children", []):
            block_messages.extend(StubMessages.construct_from_statement(child))

    return block_messages

def handle_control_flow(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log):
    """Handles for/while/if control flow statements for stub message generation."""
    block_messages = []
    warnings_messages = []
    msg_stub_begin, msg_stub_end = "", ""
    if active_identifiers:
        all_msg_logs, msg_stub_begin, msg_stub_end = extract_and_log_messages(active_identifiers, lineo_log)
        warnings_messages.append("\n".join(all_msg_logs))
        block_messages.append(StubMessages(
            start_stub_line=start_stub_line,
            end_stub_line=end_stub_line,
            warnings_messages=warnings_messages,
            msg_stub_begin=msg_stub_begin,
            msg_stub_end=msg_stub_end
        ))

    # Special handling for 'if' with else stubbing condition
    if stmt.type == StatementType.IF.value and hasattr(stmt, 'else_stubbing_condition') \
       and stmt.else_stubbing_condition is not None and getattr(stmt.else_stubbing_condition, "is_for_stubbing", False):
        start_line = stmt.else_stubbing_condition.start_line - 1
        end_line = stmt.else_stubbing_condition.start_line
        else_warning = (
            f'{warning_log_messages["WARNING"]}'
            f'{warning_log_messages["ADDITIONAL_COMPILATION_FLAG"]} '
            f'{start_line}-{end_line} {warning_log_messages["MODIFIED_LINE"]}"'
        )
        block_messages.append(StubMessages(
            start_stub_line=start_line,
            end_stub_line=end_line,
            warnings_messages=[else_warning],
            msg_stub_begin=f'{msg_stub_begin}_ELSE',
            msg_stub_end=msg_stub_end
        ))
    return block_messages

def handle_do_while(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log):
    """Handles do-while statements for stub message generation."""
    block_messages = []
    warnings_messages = []
    msg_stub_begin, msg_stub_end = "", ""
    if active_identifiers:
        all_msg_logs, msg_stub_begin, msg_stub_end = extract_and_log_messages(active_identifiers, lineo_log)
        warnings_messages.append("\n".join(all_msg_logs))
        block_messages.append(StubMessages(
            start_stub_line=start_stub_line,
            end_stub_line=end_stub_line,
            warnings_messages=warnings_messages,
            msg_stub_begin=msg_stub_begin,
            msg_stub_end=msg_stub_end
        ))

        # Add additional warning for do-while
        start_stub_line = stmt.start_line - 1
        end_stub_line = stmt.start_line
        warnings_messages = (
            f'{warning_log_messages["WARNING"]} '
            f'{warning_log_messages["ADDITIONAL_COMPILATION_FLAG"]} '
            f'{start_stub_line}-{end_stub_line}'
        )
        block_messages.append(StubMessages(
            start_stub_line=start_stub_line,
            end_stub_line=end_stub_line,
            warnings_messages=warnings_messages,
            msg_stub_begin=msg_stub_begin,
            msg_stub_end=msg_stub_end
        ))
    return block_messages

def handle_switch(stmt, active_identifiers, start_stub_line, end_stub_line, lineo_log):
    """
    Handles switch statements for stub message generation.

    Processes the main switch statement and its branches (cases), generating
    stub messages and warnings for each relevant code block.

    Args:
        stmt: The statement object representing the switch.
        active_identifiers: List of active identifier dictionaries.
        start_stub_line: The starting line number of the switch stub block.
        end_stub_line: The ending line number of the switch stub block.
        lineo_log: Log information for line numbers.

    Returns:
        list: A list of StubMessages objects containing stub and warning information.
    """
    block_messages = []
    warnings_messages = []
    msg_stub_begin, msg_stub_end = "", ""
    if active_identifiers:
        all_msg_logs, msg_stub_begin, msg_stub_end = extract_and_log_messages(active_identifiers, lineo_log)
        warnings_messages.append("\n".join(all_msg_logs))
        block_messages.append(StubMessages(
            start_stub_line=start_stub_line,
            end_stub_line=end_stub_line,
            warnings_messages=warnings_messages,
            msg_stub_begin=msg_stub_begin,
            msg_stub_end=msg_stub_end
        ))

        # Handle switch branches (cases)
        for child in getattr(stmt, "children", []):
            if getattr(child, "type", None) == StatementType.SWITCH_BRANCH.value:
                try:
                    branch_start = (child.children[0].start_line - 1
                                    if hasattr(child, "children") and child.children
                                    else child.start_line - 1)
                    branch_end = child.children[-1].end_line if getattr(child, "children", []) else child.end_line
                    branch_warning = (
                        f'{warning_log_messages["WARNING"]} '
                        f'{warning_log_messages["ADDITIONAL_COMPILATION_FLAG"]} '
                        f'{branch_start}-{branch_end} '
                        f'{warning_log_messages["MODIFIED_LINE"]}'
                    )
                    block_messages.append(StubMessages(
                        start_stub_line=branch_start,
                        end_stub_line=branch_end,
                        warnings_messages=[branch_warning],
                        msg_stub_begin=msg_stub_begin + '_SWITCH_CASE',
                        msg_stub_end=msg_stub_end
                    ))
                except (AttributeError, IndexError, KeyError) as e:
                    logging.error("Error in handle_switch (branch): %s", e)
    return block_messages

def handle_define(active_identifiers, start_stub_line, end_stub_line, lineo_log):
    """Handles define statements for stub message generation."""
    block_messages = []
    warnings_messages = []
    msg_stub_begin, msg_stub_end = "", ""
    if active_identifiers:
        all_msg_logs, msg_stub_begin, msg_stub_end = extract_and_log_messages(active_identifiers, lineo_log)
        warnings_messages.append("\n".join(all_msg_logs))
        block_messages.append(StubMessages(
            start_stub_line=start_stub_line,
            end_stub_line=end_stub_line,
            warnings_messages=warnings_messages,
            msg_stub_begin=msg_stub_begin,
            msg_stub_end=msg_stub_end
        ))
    return block_messages
