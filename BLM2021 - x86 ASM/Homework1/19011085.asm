stackSegment    SEGMENT PARA STACK 'stack'
                DW 32 DUP (?)
stackSegment    ENDS

dataSegment     SEGMENT PARA 'dataSegment'
CR              EQU 13
LF              EQU 10
ERROR_MSG       DB CR, LF, 'Warning! You did not enter a number, please try again.', 0
MAIN_MENU_T     DB CR, LF, '------------------MENU-----------------', 0
MENU_OPTION_1   DB CR, LF, '1-CREATE ARRAY', 0
MENU_OPTION_2   DB CR, LF, '2-DISPLAY ARRAY', 0
MENU_OPTION_3   DB CR, LF, '3-ADD ELEMENT TO ARRAY', 0
MENU_OPTION_4   DB CR, LF, '4-EXIT', 0
SELECTION_MSG   DB CR, LF, 'Please select the operation you want to perform:', 0
selection       DW 0
ARRAY_SIZE_MSG  DB CR, LF, 'Enter the number of elements in the array: ', 0
elementCount    DW 0
ADD_ELEMENT_MSG DB CR, LF, 'Enter the element you want to add: ', 0
currentIndex    DW 0
arrayData       DW 100 DUP(?)
arrayLinks      DW 100 DUP(?)
DISPLAY_ARRAY   DB CR, LF, 'Array: ', 0
DISPLAY_LINKS   DB CR, LF, 'Links: ', 0
DISPLAY_HEAD    DB CR, LF, 'Head: ', 0
EMPTY_ARRAY     DB CR, LF, 'Array is empty!', 0
SPACE_CHAR      DB ' ', 0
USER_INFO       DB CR, LF, '             Osman Yigit Sokel', CR, LF, '                19011085' ,0
dataSegment     ENDS

codeSegment     SEGMENT PARA 'code'
                ASSUME DS:dataSegment, CS:codeSegment, SS:stackSegment
            
MAIN    PROC FAR
        PUSH DS
        XOR AX, AX
        PUSH AX
        MOV AX, dataSegment
        MOV DS, AX
        
        XOR SI, SI
        MOV DI, -1
mainMenu:
        MOV AX, OFFSET USER_INFO
        CALL DISPLAY_STRING
        MOV AX, OFFSET MAIN_MENU_T
        CALL DISPLAY_STRING
        MOV AX, OFFSET MENU_OPTION_1
        CALL DISPLAY_STRING
        MOV AX, OFFSET MENU_OPTION_2
        CALL DISPLAY_STRING
        MOV AX, OFFSET MENU_OPTION_3
        CALL DISPLAY_STRING
        MOV AX, OFFSET MENU_OPTION_4
        CALL DISPLAY_STRING
        MOV AX, OFFSET SELECTION_MSG
        CALL DISPLAY_STRING
        CALL GET_NUMBER
        MOV selection, AX
        
        CMP selection, 1
        JE option1
        CMP selection, 2
        JE option2
        CMP selection, 3
        JE option3
        CMP selection, 4
        JE exitProgram
        JMP mainMenu
        
option1:    CALL CREATE_ARRAY
            JMP mainMenu
        
option2:    CALL SHOW_ARRAY
            JMP mainMenu

option3:    CALL ADD_ELEMENT
            JMP mainMenu
        
exitProgram:    RETF
MAIN        ENDP

INSERT_ELEMENT  PROC NEAR
        PUSH CX
        PUSH AX
        
        MOV BX, DI
        CMP DI, -1
        JNE notFirstElement
        MOV arrayLinks[SI], -1
        MOV DI, 0
        MOV BX, 0
        JMP endInsert
        
notFirstElement:
        SHL BX, 1
        CMP    arrayLinks[BX], -1
        JE checkLargest
        MOV AX, arrayData[BX]    
        CMP AX, arrayData[SI]
        JGE checkLargest
        SHR BX, 1
        MOV CX, BX
        SHL BX, 1
        MOV BX, arrayLinks[BX]
        JMP notFirstElement
        
checkLargest:
        SHR BX, 1
        SHL DI, 1
        MOV AX, arrayData[DI]
        SHR DI, 1
        CMP AX, arrayData[SI]
        JL insertMiddle
        MOV arrayLinks[SI], BX
        SHR SI, 1
        MOV DI, SI
        SHL SI, 1
        JMP endInsert
        
insertMiddle:
        SHL BX, 1            
        CMP    arrayLinks[BX], -1
        JNE continueInsert
        MOV AX, arrayData[SI]
        CMP AX, arrayData[BX]
        JLE continueInsert
        MOV arrayLinks[SI], -1
        SHR SI, 1
        MOV arrayLinks[BX], SI
        SHR BX, 1
        SHL SI, 1
        JMP endInsert
        
continueInsert:
        SHR BX, 1            
        SHL CX, 1
        PUSH DI
        MOV DI, CX
        SHR CX, 1
        MOV AX, arrayLinks[DI]   
        MOV arrayLinks[SI], AX
        SHR SI, 1
        MOV arrayLinks[DI], SI
        SHL SI, 1
        POP DI

endInsert:
        POP AX
        POP CX
        RET
INSERT_ELEMENT  ENDP

CREATE_ARRAY    PROC NEAR
retryInput:
        MOV AX, OFFSET ARRAY_SIZE_MSG
        CALL DISPLAY_STRING
        CALL GET_NUMBER
        CMP AX, 0
        JLE retryInput
        MOV CX, AX
        XOR SI, SI
        MOV DI, -1
inputLoop:
        MOV AX, OFFSET ADD_ELEMENT_MSG
        CALL DISPLAY_STRING
        CALL GET_NUMBER
        MOV arrayData[SI], AX
        CALL INSERT_ELEMENT
        ADD SI, 2
        LOOP inputLoop
        RET
CREATE_ARRAY    ENDP

SHOW_ARRAY  PROC NEAR
        PUSH SI
        PUSH CX
        PUSH DI
        CMP DI, -1
        JNE arrayNotEmpty
        MOV AX, OFFSET EMPTY_ARRAY
        CALL DISPLAY_STRING
        JMP endDisplay
        
arrayNotEmpty:
        MOV AX, OFFSET DISPLAY_ARRAY
        CALL DISPLAY_STRING
        SHR SI, 1
        MOV CX, SI
        PUSH DI
        XOR DI, DI
displayArrayLoop:
        MOV AX, arrayData[DI]
        CALL DISPLAY_NUMBER
        MOV AX, OFFSET SPACE_CHAR
        CALL DISPLAY_STRING
        ADD DI, 2
        LOOP displayArrayLoop
        MOV AX, OFFSET DISPLAY_LINKS
        CALL DISPLAY_STRING
        MOV CX, SI
        XOR DI, DI
displayLinksLoop:
        MOV AX, arrayLinks[DI]
        CALL DISPLAY_NUMBER
        MOV AX, OFFSET SPACE_CHAR
        CALL DISPLAY_STRING
        ADD DI, 2
        LOOP displayLinksLoop
        POP DI
        MOV AX, OFFSET DISPLAY_HEAD
        CALL DISPLAY_STRING
        MOV AX, DI
        CALL DISPLAY_NUMBER
                    
endDisplay:
        POP DI
        POP CX
        POP SI
        RET
SHOW_ARRAY  ENDP

ADD_ELEMENT PROC NEAR
        MOV AX, OFFSET ADD_ELEMENT_MSG
        CALL DISPLAY_STRING
        CALL GET_NUMBER
        MOV arrayData[SI], AX
        CALL INSERT_ELEMENT
        ADD SI, 2
        RET
ADD_ELEMENT ENDP    

GET_CHAR    PROC NEAR
        MOV AH, 1h
        INT 21H
        RET 
GET_CHAR    ENDP 

DISPLAY_CHAR    PROC NEAR
        PUSH AX
        PUSH DX
        MOV DL, AL
        MOV AH, 2
        INT 21H
        POP DX
        POP AX
        RET 
DISPLAY_CHAR    ENDP 

GET_NUMBER  PROC NEAR
        PUSH BX
        PUSH CX
        PUSH DX
GET_NUMBER_START:
        MOV DX, 1
        XOR BX, BX
        XOR CX, CX
NEW_CHAR:
        CALL GET_CHAR
        CMP AL, CR 
        JE FINISH_READ
        CMP AL, '-'
        JNE CHECK_DIGIT
HANDLE_NEGATIVE:
        MOV DX, -1
        JMP NEW_CHAR
CHECK_DIGIT:
        CMP AL, '0'
        JB HANDLE_ERROR 
        CMP AL, '9'
        JA HANDLE_ERROR
        SUB AL, '0'     
        MOV BL, AL     
        MOV AX, 10 
        PUSH DX    
        MUL CX    
        POP DX    
        MOV CX, AX    
        ADD CX, BX 
        JMP NEW_CHAR     
HANDLE_ERROR:
        MOV AX, OFFSET ERROR_MSG 
        CALL DISPLAY_STRING
        JMP GET_NUMBER_START 
FINISH_READ:
        MOV AX, CX
        CMP DX, 1
        JE FINISH_GET_NUMBER
        NEG AX
FINISH_GET_NUMBER:
        POP DX
        POP CX
        POP DX
        RET 
GET_NUMBER  ENDP 

DISPLAY_NUMBER  PROC NEAR
        PUSH CX
        PUSH DX     
        XOR DX, DX     
        PUSH DX    
        MOV CX, 10    
        CMP AX, 0
        JGE CALCULATE_DIGITS    
        NEG AX     
        PUSH AX    
        MOV AL, '-'    
        CALL DISPLAY_CHAR
        POP AX
        
CALCULATE_DIGITS:
        DIV CX      
        ADD DX, '0'    
        PUSH DX    
        XOR DX, DX    
        CMP AX, 0    
        JNE CALCULATE_DIGITS
        
DISPLAY_DIGITS:
        POP AX                               
        CMP AX, 0
        JE END_DISPLAY_DIGITS 
        CALL DISPLAY_CHAR 
        JMP DISPLAY_DIGITS  
        
END_DISPLAY_DIGITS:
        POP DX 
        POP CX
        RET
DISPLAY_NUMBER  ENDP 

DISPLAY_STRING  PROC NEAR
        PUSH BX 
        MOV BX, AX                    
        MOV AL, BYTE PTR [BX]                    
DISPLAY_LOOP:   
        CMP AL, 0        
        JE  END_DISPLAY             
        CALL DISPLAY_CHAR                 
        INC BX                        
        MOV AL, BYTE PTR [BX]
        JMP DISPLAY_LOOP                 
END_DISPLAY:
        POP BX
        RET 
DISPLAY_STRING  ENDP

codeSegment     ENDS
                END MAIN