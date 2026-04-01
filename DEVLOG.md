# Developer Log (DEVLOG.md)
## Programming Assignment 2
# Jasper McIntyre


Each entry must document learning and reasoning. Fabricated bugs are not expected.



## Allowed Entry Types
Each entry may be one of the following:

1) **Bug Fix Entry**
- The issue encountered.
- Error messages or symptoms.
- Attempts made.
- Final resolution.

2) **Edge Case / Testing Entry**
- A failure discovered through testing.
- The specific input/state that caused it.
- The change you made to handle it correctly.

3) **Engineering Decision Entry (up to 2 allowed)**
- A design decision you made.
- An alternative approach you considered.
- Why you chose one approach over another (tradeoffs).



### Entry 1
3/24
**Entry Type:** 
**Task worked on: Engineering decision **
**Issue or decision: Designing ArrayStack<T> error handling**
**Error message / symptom (if applicable):**
**What I tried: Considered returning a value like T() from top() or throwing an expection. This approach avoids crashing errors but allows incorrect logic**
**Fix / resolution (or final decision): Used throw stf:: out_of_range("Stac is empty") in pop() and top() to make bugs in evaluation and conversion easy to find during testing instead of correctly producing incorrect answers**
**Commit(s):** implement ArrayStack

### Entry 2
3/24
**Entry Type: Bug Fix **
**Task worked on: precedence he;per function**
**Issue or decision:* and / were not higher precendence than + and -. During conversion, 3+4*2 produced incorrect postfix order** 
**Error message / symptom (if applicable): wrong output**
**What I tried: saw printing precedence("*") and precedence ("+") both outputted 2 and found the error in a typing error**
**Fix / resolution (or final decision):typed "+" twice instead of "*" in the high precendence conditional**
**Commit(s):** fix precendence operator

### Entry 3
3/31
**Entry Type:Bug Fix**
**Task worked on: isValidPostfix()**
**Issue or decision:Every expression classified as NEITHER instad of POSTFIX**
**Error message / symptom (if applicable): isValidPostfix always returned false**
**What I tried:tried debugging from inside the loop and saw the function returned after the first token. Noticed return depth ==1 was inside the for loop **
**Fix / resolution (or final decision): moved return depth ==1 to outside the loop and tested 3 4 + and 3 4 2 * +**
**Commit(s):** fixed helper classes

### Entry 4
3/31
**Entry Type: Engineering Decision**
**Task worked on: Outputting format for number results**
**Issue or decision:evalPostfix returns doubles**
**Error message / symptom (if applicable): bad output**
**What I tried: At first I thought cout << fixed << setprecision(0) would work but that makes every result an integer which would break math that results in a double. **
**Fix / resolution (or final decision): I wrote printOut() helper that casts the double into a long long and compares the 2 numbers. If they match it prints as an int else it prints as a decimal**
**Commit(s):** Added helpers
