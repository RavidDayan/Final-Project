
; Double definition of label
DUPLABEL: clr r1
DUPLABEL: inc r1

; Missing instruction/action after label
EMPTYLABEL: 

; Missing operand
mov r1, 

; Unintended comma placements
B: .data 5,,6
C: .data ,7

; Spaces between '#' and IMM 
mov  r1, # -5

; Too many operands
D: add r1, r2, r3

; Label starting with a number (invalid)
1INVALIDLABEL: hlt

; Floating label without following colon
FLOATLABEL mov r1, r2

; Nested instructions
E: .data 5, .string "hello", 6

; Two instructions/actions on one line
F: clr r1 , hlt

; Exceeding character limit (assuming 81 is the max)
LONG: .string "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopq"

; Label that is an instruction
.string: mov r2, r1

; Label that is an CODE
mov: add r1, r2

; Two colons after a label
H:: clr r3

; Undefined action
J: undefaction r1

; Using a decimal number
L: .data 5.5

; Invalid characters in labels
M@: clr @r1
N$: inc @r2
