LoadAllFiles MACRO
	PUSHA
	
		;; load the intro file to the intro variable 
        LoadFile INTRO_FILE, INTRO
		
		;; LOAD THE FIRST SCREEN OF ASKING PLAYER 1 FOR HIS NAME
		LoadFile OPTIONS_FILE, OPTIONS_SCR
		
		;; LOAD THE FIRST SCREEN OF ASKING PLAYER FOR THE MODE
		LoadFile MODES_FILE, MODES
		
		;; LOAD THE RULES SCREEN
		LoadFile RULES_FILE, RULES
		
		;; LOAD THE SCORE_FILE INTO ITS SCREEN
		LoadFile SCORE_FILE,SCOREBAR
		
		;; PRINT THE CUP 
	    ; LoadFile WINNER_FILE, WIN
		
	POPA
ENDM LoadAllFiles

Redirect MACRO
								; 0 => RULES , 1 => OPTIONS ,  2 => GET LEVEL  
								; 3 => INTRO , 4 => GAMEPLAY 
								; 5 => WIN , 6 => CHAT 
	LOCAL MODE_TEST, OPTIONS_TEST, INTRO_TEST, GAMEPLAY_TEST, WIN_TEST, CHAT_TEST
	
	CMP STATE, 0
	; JNZ RULES_TEST
	; JMP OPTIONS_SCREEN
	JNZ OPTIONS_TEST
	JMP RULES_SCREEN
	
	
	
	OPTIONS_TEST:	
	
		CMP STATE, 1
		JNE MODE_TEST
		; CMP MODE, 0
		; JNZ MODE_NOT_ZERO
		CMP MATCHED, 1
		JZ MODE_TEST
		JMP OPTIONS_SCREEN
		; MODE_NOT_ZERO:
			; MOV STATE, 3
			; JMP INTRO_TEST
			
	
	; RULES_TEST:	
	
		; CMP STATE, 1
		; JNE MODE_TEST
		; CMP MODE, 0
		; JNZ MODE_NOT_ZERO
		; JZ RULES_SCREEN
		; MODE_NOT_ZERO:
			; MOV STATE, 3
			; JMP INTRO_TEST
			
	MODE_TEST:
		CMP STATE, 2
		JNE INTRO_TEST
		CMP MODE, 0
		JNZ MODE_NOT_ZERO
		JMP MODE_SCREEN
		MODE_NOT_ZERO:
			MOV STATE, 3
			JMP INTRO_TEST
			
		
	INTRO_TEST:
		CMP STATE, 3
		JZ INTRO_SCREEN
		CMP STATE, 1
		JZ INTRO_SCREEN
	GAMEPLAY_TEST:
		CMP STATE, 4
		JZ GAMEPLAY_SCREEN
	WIN_TEST:
		CMP STATE, 5
		JZ WIN_SCREEN
	CHAT_TEST:
		CMP STATE, 6
		JZ CHAT_SCREEN



ENDM Redirect


DrawMaze MACRO
    PUSHA    
	
		LOCAL PRINT
		LOCAL NEW_LINE
		LOCAL INCREMENT
		LOCAL CHECK
		
		;; CLEAR THE SCREEN
		ClearScreen
    
		;; MOVE CURSOR TO START OF SCREEN
		MoveCursor 0, 0
	
		;; PRINT THE MAZE TO THE SCREEN WITH A LIGHT BLUE COLOR    
        DrawString MAZE, 33H
    
        ;;DrawScorebar
		
    POPA
                
ENDM DrawMaze   


DrawScorebar MACRO
	PUSHA
	
		MoveCursor 0,22
	
		PrintString SCOREBAR, 0FH
	
	POPA
ENDM DrawScorebar


ClearScreen MACRO
	PUSHA
	
		;; CLEAR THE SCREEN
		MOV AH, 06
		MOV AL, 00
		MOV BH, 07
		MOV CH, 00
		MOV CL, 00
		MOV DH, 24
		MOV DL, 79
		INT 10H	
	
	POPA
ENDM ClearScreen

;; draws a string with colored spaces instead of its letters
DrawString MACRO STRING, COLOR
	PUSHA
		
		LOCAL PRINT
		LOCAL NEW_LINE
		LOCAL INCREMENT
		LOCAL CHECK
		
		MOV BX, OFFSET STRING
		
		PUSH BX
		PRINT:
			
			;; IF IT'S A SPACE JUST INCREMENT THE CURSOR POSITION
			CMP [BX], ' '
			JZ INCREMENT
			
			
			CMP [BX], 13
			JZ INCREMENT
			
			CMP [BX], 9
			JZ INCREMENT
			
			;; IF IT'S A NEW LINE GO TO THE NEXT LINE
			CMP [BX], 10
			JZ NEW_LINE
			
			
			;; PRINT THE CHAR
			mov ah,9 ;;Display
			mov al,' ' ;;SPACE
			mov bh,0 ;;Page 0
			mov cx,1h ;;1 time
			mov bl,COLOR ;; color
			int 10h
			JMP INCREMENT
			
			NEW_LINE:
				mov ah,3h
				mov bh,0h
				int 10h
				MOV DL, 0
				INC DH
				mov ah,2
				int 10h
				JMP CHECK
				
			INCREMENT:
				mov ah,3h
				mov bh,0h
				int 10h
				INC DL
				mov ah,2
				int 10h
				
			CHECK:
				POP BX
				INC BX
				PUSH BX
				CMP [BX], '$'
				JNZ PRINT
		
	
	
	POPA
ENDM DrawString

;; PRINTS A COLORED STRING UNTIL IT REACHES THE '$', JUST LIKE THE INT 21H
PrintString MACRO STRING, COLOR
	PUSHA
		
		LOCAL PRINT
		LOCAL NEW_LINE
		LOCAL INCREMENT
		LOCAL CHECK
		
		MOV BX, OFFSET STRING
		
		PUSH BX
		PRINT:
			
			;; IF IT'S A SPACE JUST INCREMENT THE CURSOR POSITION
			CMP [BX], ' '
			JZ INCREMENT
			
			
			CMP [BX], 13
			JZ INCREMENT
			
			CMP [BX], 9
			JZ INCREMENT
			
			;; IF IT'S A NEW LINE GO TO THE NEXT LINE
			CMP [BX], 10
			JZ NEW_LINE
			
			
			;; PRINT THE CHAR
			mov ah,9 ;;Display
			mov al,[bx] ;;SPACE
			mov bh,0 ;;Page 0
			mov cx,1h ;;1 time
			mov bl,COLOR ;; color
			int 10h
			JMP INCREMENT
			
			NEW_LINE:
				mov ah,3h
				mov bh,0h
				int 10h
				MOV DL, 0
				INC DH
				mov ah,2
				int 10h
				JMP CHECK
				
			INCREMENT:
				mov ah,3h
				mov bh,0h
				int 10h
				INC DL
				mov ah,2
				int 10h
				
			CHECK:
				POP BX
				INC BX
				PUSH BX
				CMP [BX], '$'
				JNZ PRINT
		
	
	
	POPA
ENDM PrintString

;; READS A STRING AND PUTS IT IN THE STRING VARIABLE
ReadString MACRO STRING
	PUSHA
		
		MOV AH, 0AH
		MOV DX, OFFSET STRING
		INT 21H
	
	POPA
ENDM ReadString


GetNames MACRO
	 PUSHA
		
		 ;; CLEAR THE SCREEN
		 ClearScreen
		 ;; MOVE THE CURSOR TO THE START OF THE SCREEN
		 MoveCursor 0,0
		
		 ;; LOAD THE FIRST SCREEN OF ASKING PLAYER 1 FOR HIS NAME
		 LoadFile NAME1_FILE, NAMES
		 ;; PRINT  THE SCREEN WITH A YELLOW COLOR FOR CHARS
		 PrintString NAMES, 0EH
		 ;; MOVE THE CURSOR TO THE NAME LOCATION
		 MoveCursor 30 ,12
		 ;; GET THE NAME OF PLAYER 1
		 ReadString P1_NAME
		
		 ;; CLEAR THE SCREEN
		 ClearScreen
		
		 ;; MOVE THE CURSOR TO THE START OF THE SCREEN
		 MoveCursor 0,0
		
		 ;; LOAD THE SECOND SCREEN OF ASKING PLAYER 2 FOR HIS NAME
		 LoadFile NAME2_FILE, NAMES
		 ;; PRINT  THE SCREEN WITH A YELLOW COLOR FOR CHARS
		 PrintString NAMES, 0EH
		 ;; MOVE THE CURSOR TO THE NAME LOCATION
		 MoveCursor 30 ,12
		 ;; GET THE NAME OF PLAYER 2
		 ReadString P2_NAME
		
		 ;; CLEAR THE SCREEN
		 ClearScreen
		
		 ;; MOVE THE CURSOR TO THE START OF THE SCREEN
		 MoveCursor 0,0
	
	
	 POPA
 ENDM GetNames


GetName MACRO P_NAME,NAME_FILE
	 PUSHA
		
		 ;; CLEAR THE SCREEN
		 ClearScreen
		 ;; MOVE THE CURSOR TO THE START OF THE SCREEN
		 MoveCursor 0,0
		
		 ;; LOAD THE FIRST SCREEN OF ASKING PLAYER 1 FOR HIS NAME
		 LoadFile NAME_FILE, NAMES
		 ;; PRINT  THE SCREEN WITH A YELLOW COLOR FOR CHARS
		 PrintString NAMES, 0EH
		 ;; MOVE THE CURSOR TO THE NAME LOCATION
		 MoveCursor 30 ,12
		 ;; GET THE NAME OF PLAYER 1
		 ReadString P_NAME

		 MoveCursor 0,0
	
	
	 POPA
 ENDM GetName

 Options MACRO 
	 PUSHA
	
		LOCAL AGAIN, EXIT, END_IT, CHAT_OPTION, GAME_OPTION

		;; CHECK IF THE INVITATIONS ARE MATCHED
		MOV AL, SENT_INVITATION
		MOV AH, RECEIVED_INVITATION
		CMP AL, AH
		JNZ AGAIN
		AND AH, AL
		JZ AGAIN	
		CMP AL, 1
		JZ TO_CHAT
		
		CMP AL, 2
		JZ TO_GAME		
		
		AGAIN:
			;; CLEAR THE SCREEN
			 ; ClearScreen
			 RemoveCursor
			 ;; MOVE THE CURSOR TO THE START OF THE SCREEN
			 MoveCursor 0,0

			 ;; PRINT  THE SCREEN WITH A YELLOW COLOR FOR CHARS
			 PrintString OPTIONS_SCR, 0FH
			 ;; MOVE THE CURSOR TO THE NAME LOCATION
			
			
			 MOV AH,01
			 INT 16H
			 JZ END_IT
			 
			 CMP AH,3BH
			 JZ CHAT_OPTION
			 
			 CMP AH,3CH
			 JZ GAME_OPTION
			 
			 CMP AH, 01H
			 JZ EXIT
			 
			 JMP END_IT
			 
		EXIT:
				
				TERMINATE
				
			CHAT_OPTION:
		;		MOV STATE, 6
				MOV SENT_INVITATION, 1
				JMP END_IT
				
			GAME_OPTION:
		;		MOV STATE, 1
				MOV SENT_INVITATION, 2
				JMP END_IT
				
			TO_CHAT:
				MOV STATE, 6
			
			TO_GAME:
				MOV STATE, 1
				
	END_IT:
		 FlushBuffer
	
		
		 ;; TO BE CONTINUED
	 POPA
 ENDM Options

 TERMINATE MACRO
	PUSHA
		
		ClearScreen
		MOV AH, 4CH
		INT 21H
	
	POPA
ENDM TERMINATE

 
SetInitials MACRO
	PUSHA
		
		;; SET THE CHAR OF PLAYER1 TO HIS NAME INITIAL 
		MOV BX, 2
		MOV SI, OFFSET P1_NAME
		MOV AL, SI[BX]
		MOV P1_CHAR, AL
		
		;; SET THE CHAR OF PLAYER2 TO HIS NAME INITIAL 
		MOV BX, 2
		MOV SI, OFFSET P2_NAME
		MOV AL, SI[BX]
		MOV P2_CHAR, AL
		
	POPA
ENDM SetInitials

PrintRules MACRO
	PUSHA
		
		;; CLEAR THE SCREEN
		ClearScreen
		;; MOVE THE CURSOR TO THE START OF THE SCREEN
		MoveCursor 0,0

		;; PRINT  THE SCREEN WITH A YELLOW COLOR FOR CHARS
		PrintString RULES, 0CH

		;; WAIT FOR A KEY TO BE PRESSED
		MOV AH, 01
		INT 21H
		
		
	POPA
ENDM PrintRules


GetMode MACRO
	PUSHA
		LOCAL AGAIN
		LOCAL CONTINUE


		AGAIN:
			;; CLEAR THE SCREEN
			ClearScreen
			;; reset the cursor to be visible again
			ResetCursor
			;; MOVE THE CURSOR TO THE START OF THE SCREEN
			MoveCursor 0,0
			
			;; PRINT  THE SCREEN WITH A YELLOW COLOR FOR CHARS
			PrintString MODES, 0EH
			;; MOVE THE CURSOR TO THE NAME LOCATION
			MoveCursor 30 ,12
			;; GET THE CHAR REPRESENTING THE MODE 
			MOV AH, 0
			INT 16H
			
			;; CHECK IF THE CHAR IS '1' OR '2'
			CMP AL, '1'
			JZ CONTINUE
			
			CMP AL, '2'
			JZ CONTINUE
			
			;; IF NOT A VALID MODE, LOOP AGAIN
			JMP AGAIN
			
		CONTINUE:
			
			;; SAVE THE CHAR TO THE MODE
			MOV MODE, AL
			
			;; LOAD THE MAZE
			LoadMaze
			
			
			;; PRINT THE CHAR AGAIN
			MOV AH, 2
			MOV DL, AL
			INT 21H
				
	POPA
ENDM GetMode



LoadMaze MACRO 
    PUSHA
	
		LOCAL ERROR
		LOCAL CONTINUE
		
		;; generates a random number in random variable to indicate which maze will be drawn
        Randomize RANDOM, MAZES_N 
  
        ;; DECIDE WHICH FILE TO OPEN (WHICH MAZE DIFFICULTY)
        CMP MODE, '1'    ;; CHECK IF THE MODE IS EASY
        JNZ H_MAZE  ;; IF NOT GO TO HARD MAZE
        
        E_MAZE:
        
            MOV DX, OFFSET EASY_MAZE
            JMP CONTINUE
        
        H_MAZE:               
        
            MOV DX, OFFSET HARD_MAZE
            JMP CONTINUE
            
        ERROR:
            MOV AH, 4CH
            MOV AL, 0
            INT 21H
                                       
        
        CONTINUE:
            
            ;; OPEN THE MAZE FILE
            MOV AH, 3DH
            MOV AL, 00
            INT 21H
            
            ;; IF FILE COULDN'T BE FOUND, EXIT THE PROGRAM
            JC ERROR
            
            ;; PUSH AX (FILE HANDLE)
            PUSH AX               
            
            ;; CALCULATE THE AMOUNT OF BYTES TO BE SEEKED
            ;; FROM THE MAZE FILE TO REACH THE RANDOM MAZE        
            MOV CL, RANDOM     
            MOV CH, 0
            
            ;; CALCULATE OFFSET OF THE RANDOMLY SELECTED MAZE FROM THE BASE INDEX 
            MOV AX, ROWS
            MOV DX, COLS
            MUL DX                                               
            MUL CX
                  
            
            ;; SEEK THE MAZE FILE TO THE SPECIFIC MAZE
            ;; POP FILE HANDLE INTO BX      
            POP BX
            MOV CX, 0
            MOV DX, AX
            MOV AH, 42H
            MOV AL, 01H
            INT 21H
            
            ;; CALCULATE NUMBER OF BYTES IN THE MAZE 
            MOV AX, ROWS
            MOV DX, COLS
            MUL DX
            
            ;; READ THE MAZE FILE INTO MAZE VARIABLE
            MOV CX, AX
            MOV AH, 3FH
            MOV DX, OFFSET MAZE
            INT 21H  
            
			;; CLOSE THE FILE
			MOV AH, 2EH
			INT 21H
    POPA
        
ENDM LoadMaze



LoadFile MACRO FILE, DEST
    PUSHA
	
		LOCAL ERROR
		LOCAL CONTINUE
  
            MOV DX, OFFSET FILE
            JMP CONTINUE
            
        ERROR:
            MOV AH, 4CH
            MOV AL, 0
            INT 21H
                                       
        
        CONTINUE:
            
            ;; OPEN THE FILE
            MOV AH, 3DH
            MOV AL, 00
            INT 21H
            
            ;; IF FILE COULDN'T BE FOUND, EXIT THE PROGRAM
            JC ERROR
            
            ;; PUSH AX (FILE HANDLE)
            PUSH AX               
            
            MOV AX, 25
            MOV DX, 82
            MUL DX                                               
            
            
            ;; READ THE INTRO FILE INTO THE VARIABLE
            POP BX
            MOV CX, AX
            MOV AH, 3FH
            MOV DX, OFFSET DEST
            INT 21H  
			
			
			;; CLOSE THE FILE
			MOV AH, 2EH
			INT 21H
            
    POPA
        
ENDM LoadFile


DrawIntro MACRO
    PUSHA    
		
		;; CLEAR THE SCREEN
		ClearScreen
		
		;; remove cursor
		RemoveCursor
    
		;; MOVE CURSOR TO START OF SCREEN
		MoveCursor 0, 0
	
		;; PRINT THE INTRO TO THE SCREEN WITH A GREEN COLOR    
        DrawString INTRO, 22H
		
    POPA
                
ENDM DrawIntro  


;; WAITS FOR AN AMOUNT OF TIME
SLEEP MACRO INTERVAL
    PUSHA
        
        MOV AX, 0FFFFH
        MOV BX, INTERVAL
        MUL BX
        MOV CX, AX
        XCHG CX, DX
        MOV AH, 86H
		MOV AL, 0H
        INT 15H
    
    POPA
ENDM


;; GETS THE INDEX OF THE CHAR AT THE X,Y LOCATION INSIDE THE MAZE AND PUT ITI INSIDE THE INDEX VARIABLE
GetIndex MACRO X,Y
    PUSHA
  
		MOV BL,Y
		MOV AL,81
		MUL BL
		MOV BL, X
		MOV BH, 0
		ADD AX, BX
		MOV INDEX, AX
        
    POPA
        
ENDM GetIndex



HandlePlayerMovement MACRO
    PUSHA
		
		LOCAL MOVE_UP1
		LOCAL MOVE_RIGHT1
		LOCAL MOVE_LEFT1
		LOCAL MOVE_DOWN1
		
		LOCAL CONTINUE
		
		;; CHECK IF A KEY WAS PRESSED
		MOV AH, 01
		INT 16H
		JZ CONTINUE
		
		
		;; HANDLE EACH KEY ACCORDING TO ITS SCANCODE
		CMP AH, UP_ARROW1
		JZ MOVE_UP1
		
		CMP AH, LEFT_ARROW1
		JZ MOVE_LEFT1
		
		CMP AH, DOWN_ARROW1
		JZ MOVE_DOWN1
		
		CMP AH, RIGHT_ARROW1
		JZ MOVE_RIGHT1
		
		;; if not caught until here, ignore it because it's a bad key
		JMP CONTINUE
		
		
		MOVE_UP1:
			MOV LOCAL_KEY, AH
		    MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveUp X1, Y1
			JMP CONTINUE

		MOVE_LEFT1:
			MOV LOCAL_KEY, AH
			MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveLeft X1, Y1
			JMP CONTINUE

		MOVE_DOWN1:
			MOV LOCAL_KEY, AH
			MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveDown X1, Y1
			JMP CONTINUE
			
		MOVE_RIGHT1:
			MOV LOCAL_KEY, AH
		    MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveRight X1, Y1
			JMP CONTINUE
    
		CONTINUE:
		
    POPA
ENDM HandlePlayerMovement
    
HandleRemoteMovement MACRO
    PUSHA
		
		LOCAL MOVE_UP2
		LOCAL MOVE_RIGHT2
		LOCAL MOVE_LEFT2
		LOCAL MOVE_DOWN2
		
		
		LOCAL CONTINUE
		
		;; CHECK IF A KEY WAS PRESSED
		CMP REMOTE_KEY, 0
		JZ CONTINUE
		MOV AH, REMOTE_KEY
		
		;; HANDLE EACH KEY ACCORDING TO ITS SCANCODE
		CMP AH, UP_ARROW2
		JZ MOVE_UP2
		
		CMP AH, LEFT_ARROW2
		JZ MOVE_LEFT2
		
		CMP AH, DOWN_ARROW2
		JZ MOVE_DOWN2
		
		CMP AH, RIGHT_ARROW2
		JZ MOVE_RIGHT2
		
		
		;; if not caught until here, ignore it because it's a bad key
		JMP CONTINUE

		MOVE_UP2:
		    MOD_P2_POSTPONE
			ClearPosition X2, Y2
			MoveUp X2, Y2
			JMP CONTINUE

		MOVE_LEFT2:
			MOD_P2_POSTPONE
			ClearPosition X2, Y2
			MoveLeft X2, Y2
			JMP CONTINUE

		MOVE_DOWN2:
		    MOD_P2_POSTPONE
			ClearPosition X2, Y2
			MoveDown X2, Y2
			JMP CONTINUE
			
		MOVE_RIGHT2:
		    MOD_P2_POSTPONE
			ClearPosition X2, Y2
			MoveRight X2, Y2
			JMP CONTINUE

    
		CONTINUE:
		
    POPA
ENDM HandleRemoteMovement

	
	
;; move the player with x,y coordinates upwards    
MoveUp	MACRO	X,Y
	PUSHA
		
		LOCAL MAKE_PEEP
		LOCAL CONTINUE
		
		;; SUBTRACT 1 FROM Y TO REPRESENT GOING UPWARDS
		MOV CL, Y
		SUB CL, 1
		
		;; GET INDEX OF X,Y PLACE IN THE MAZE ARRAY
		GetIndex X, CL
		
		;; CHECK IF THE MAZE IS EMPTY AT THAT INDEX
		MOV BX, INDEX
		CMP MAZE[BX], ' '
		JNZ MAKE_PEEP

		
		;; CHANGE THE Y POSITION OF THE PLAYER TO THE NEW POSITION
		MOV Y, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			MOV AL, X
			MOV AH, Y
			SUB AL, X2
			SUB AH, Y2
			OR AL, AH
			JZ CONTINUE
			Peep
		
		CONTINUE:
			
	
	POPA
ENDM MoveUp

;; move the player with x,y coordinates left
MoveLeft	MACRO	X,Y
	PUSHA
		
		LOCAL MAKE_PEEP
		LOCAL CONTINUE
		
		;; ADD 1 TO X TO REPRESENT GOING RIGHT
		MOV CL, X
		SUB CL, 1
		
		;; GET INDEX OF X,Y PLACE IN THE MAZE ARRAY
		GetIndex CL, Y
		
		;; CHECK IF THE MAZE IS EMPTY AT THAT INDEX
		MOV BX, INDEX
		CMP MAZE[BX], ' '
		JNZ MAKE_PEEP	;; if not valid, make a peep

		;; CHANGE THE X POSITION OF THE PLAYER TO THE NEW POSITION
		MOV X, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			MOV AL, X
			MOV AH, Y
			SUB AL, X2
			SUB AH, Y2
			OR AL, AH
			JZ CONTINUE
			Peep
		
		CONTINUE:
			
	
	POPA
ENDM MoveLeft

;; move the player with x,y coordinates down
MoveDown	MACRO	X,Y
	PUSHA
		
		LOCAL MAKE_PEEP
		LOCAL CONTINUE
		
		;; SUBTRACT 1 FROM Y TO REPRESENT GOING UPWARDS
		MOV CL, Y
		ADD CL, 1
		
		;; GET INDEX OF X,Y PLACE IN THE MAZE ARRAY
		GetIndex X, CL
		
		;; CHECK IF THE MAZE IS EMPTY AT THAT INDEX
		MOV BX, INDEX
		CMP MAZE[BX], ' '
		JNZ MAKE_PEEP	;; if not valid, make a peep

		
		;; CHANGE THE Y POSITION OF THE PLAYER TO THE NEW POSITION
		MOV Y, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			MOV AL, X
			MOV AH, Y
			SUB AL, X2
			SUB AH, Y2
			OR AL, AH
			JZ CONTINUE
			Peep
		
		CONTINUE:
			
	
	POPA
ENDM MoveDown

;; move the player with x,y coordinates right
MoveRight	MACRO	X,Y
	PUSHA
		
		LOCAL MAKE_PEEP
		LOCAL CONTINUE
		
		;; ADD 1 TO X TO REPRESENT GOING RIGHT
		MOV CL, X
		ADD CL, 1
		
		;; GET INDEX OF X,Y PLACE IN THE MAZE ARRAY
		GetIndex CL, Y
		
		;; CHECK IF THE MAZE IS EMPTY AT THAT INDEX
		MOV BX, INDEX
		CMP MAZE[BX], ' '
		JNZ MAKE_PEEP	;; if not valid, make a peep


		;; CHANGE THE X POSITION OF THE PLAYER TO THE NEW POSITION
		MOV X, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			MOV AL, X
			MOV AH, Y
			SUB AL, X2
			SUB AH, Y2
			OR AL, AH
			JZ CONTINUE
			Peep
		
		CONTINUE:
			

	POPA
ENDM MoveRight

ClearPosition MACRO X, Y
    PUSHA
    
        ;; MOVE CURSOR TO X,Y POSITION
		MOV AH, 02
		MOV BH, 00
		MOV DL, X
		MOV DH, Y
		INT 10H
		
		
		; MOV AH,9
		; MOV BH,0
		; MOV AL,44H
		; MOV CX,1H
		; MOV BL,000H
		; INT 10H
		  
		
		;; CLEAR THAT PLACE (print a space at it)
		MOV AH, 02
		MOV DL, ' '
		INT 21H
		
    
    POPA
ENDM ClearPosition

Peep MACRO
	PUSHA
	
		; CX = the frequency of the generated sound
		MOV CX, 1000
		IN AL, 061H
		OR AL, 003H
		DEC AX
		OUT 061H, AL	;;TURN AND GATE ON;; TURN TIMER OFF
		MOV DX, 00012H	;;HIGH WORD OF 1193180
		MOV AX, 034DCH	;;LOW WORD OF 1193180
		DIV CX
		MOV DX, AX
		MOV AL, 0B6H
		PUSHF
		CLI	;;!!!
		OUT 043H, AL
		MOV AL, DL
		OUT 042H, AL
		MOV AL, DH
		OUT 042H, AL
		POPF
		IN AL, 061H
		OR AL, 003H
		OUT 061H, AL
		
		SLEEP 1
		
		MOV CX, 25000
		IN AL, 061H
		OR AL, 003H
		DEC AX
		OUT 061H, AL	;;TURN AND GATE ON;; TURN TIMER OFF
		MOV DX, 00012H	;;HIGH WORD OF 1193180
		MOV AX, 034DCH	;;LOW WORD OF 1193180
		DIV CX
		MOV DX, AX
		MOV AL, 0B6H
		PUSHF
		CLI	;;!!!
		OUT 043H, AL
		MOV AL, DL
		OUT 042H, AL
		MOV AL, DH
		OUT 042H, AL
		POPF
		IN AL, 061H
		OR AL, 003H
		OUT 061H, AL
		
		
		;;DESTROYS AL
				IN AL, 061H
				AND AL, 0FCH
				OUT 061H, AL
		
	POPA

ENDM Peep

PrintPlayers MACRO
    PUSHA
	
		
		;; CLEAR PLAYER2 POSITION
		ClearPosition OLD_X2, OLD_Y2
		
		;; MOVE CURSOR TO X1,Y2 POSITION
		MOV AH, 02
		MOV BH, 00
		MOV DL, X1
		MOV DH, Y1
		INT 10H
		
		;; PRINT PLAYER 1
		MOV AH, 09
		MOV BH, 00
		MOV AL, P1_CHAR
		MOV CX, 01
		MOV BL, 0FH
		INT 10H
		
		;; MOVE CURSOR TO X2,Y2 POSITION
		MOV AH, 02
		MOV BH, 00
		MOV DL, X2
		MOV DH, Y2
		INT 10H
		
		;; PRINT PLAYER 2 
		MOV AH, 09
		MOV BH, 00
		MOV AL, P2_CHAR
		MOV CX, 01
		MOV BL, 0FH
		INT 10H
		
		;;  SAVE THE OLD PLAYER2 POSITION
		MOV AL, X2
		MOV OLD_X2, AL
		MOV AL, Y2
		MOV OLD_Y2, AL
		
		
    POPA
    
ENDM PrintPlayers

RemoveCursor MACRO
	PUSHA

		MOV AH, 01H
		MOV CX, 2607H
		INT 10H
		
	POPA

ENDM RemoveCursor

ResetCursor MACRO
	PUSHA

		MOV AH, 01H
		MOV CX, 0607H
		INT 10H
		
	POPA

ENDM ResetCursor


FlushBuffer MACRO
		PUSHA
		
			LOCAL AGAIN
			LOCAL END

			AGAIN:
				;; CHECK IF A KEY WAS PRESSED
				MOV AH, 01
				INT 16H
				JZ END		;; NO, END THE FUNCTION
				
				;; IF YES, FLUSH IT
				MOV AH, 00
				INT 16H
				JMP AGAIN
			
			END:
		
		POPA
ENDM FlushBuffer



MOD_P1_POSTPONE MACRO
		PUSHA
		LOCAL END_1
		LOCAL END_2
		
			CMP P1_POSTPONE,0
			JNZ END_1
			
			MOV AL,UP_ARROW_PER
			MOV UP_ARROW1,AL
			
			MOV AL,DOWN_ARROW_PER
			MOV DOWN_ARROW1,AL
			
			MOV AL,LEFT_ARROW_PER
			MOV LEFT_ARROW1,AL
			
			MOV AL,RIGHT_ARROW_PER
			MOV RIGHT_ARROW1,AL
			
			JMP END_2
			
			END_1:
			      DEC P1_POSTPONE
                  JMP END_2
				  
	        END_2:	
		POPA
ENDM MOD_P1_POSTPONE


MOD_P2_POSTPONE MACRO
		PUSHA
		LOCAL END_1
		LOCAL END_2
		
			CMP P2_POSTPONE,0
			JNZ END_1
			
			MOV AL,UP_ARROW_PER
			MOV UP_ARROW2,AL
			
			MOV AL,DOWN_ARROW_PER
			MOV DOWN_ARROW2,AL
			
			MOV AL,LEFT_ARROW_PER
			MOV LEFT_ARROW2,AL
			
			MOV AL,RIGHT_ARROW_PER
			MOV RIGHT_ARROW2,AL
			
			JMP END_2
			
			END_1:
				DEC P2_POSTPONE
				JMP END_2
				  
			END_2:	
		POPA
ENDM MOD_P2_POSTPONE


DetectAction MACRO
    PUSHA
     LOCAL CONTINUE
		;; CHECK IF A KEY WAS PRESSED
		MOV AH, 01
		INT 16H
		JZ CONTINUE	;; if no, skip

		HandlePlayerFire
		HandlePlayerMovement
		;;HandleExit
		FlushBuffer
		
		
		
		
		
		JMP CONTINUE
        
CONTINUE:
    POPA
        
ENDM DetectAction

DetectRemoteAction MACRO
    PUSHA
     LOCAL CONTINUE
		;; CHECK IF A REMOTE KEY WAS PRESSED
		CMP REMOTE_KEY, 0
		JZ CONTINUE	;; if no, skip
		        

		HandleRemoteFire
		HandleRemoteMovement
		;;HandleExit
		
		
		
		JMP CONTINUE
        
CONTINUE:
    POPA
        
ENDM DetectRemoteAction




;;------------------------------------------------- 
;;PRINT BOMBS EVERY LOOP IN THE INDEX STORED IN BOMBX AND BOMBY  
PrintBombs MACRO
  PUSHA
	  
	  LOCAL NEXT
	  
	  LEA SI,BOMBX
	  LEA DI,BOMBY
		
	  MOV CX,B_COUNT
	  
	  ;; IF BOMB INDEX IN BOMBX = -1 SKIP IT ELSE PRINT IT
	  LOOP_BOMBS:
		    MOV AH,-1
		    CMP [SI],AH
			JZ NEXT
			
		     MoveCursor [SI],[DI]
		     PlantBomb
             JMP NEXT			
			
			  
		    NEXT:
			  INC SI
		      INC DI
			  LOOP LOOP_BOMBS
			
  POPA
ENDM PrintBombs


;;-------------------------------------------------
;; GET AND IMPLEMENT THE PLAYERS FIRE ACTION
HandlePlayerFire MACRO
    PUSHA
		LOCAL CONTINUE

        ;; GET KEY PRESSED 
		MOV AH, 01
		INT 16H
		JZ CONTINUE
		
		MOV AL,FIRE_DELAY
		
		CMP AH, M_LETTER
		JZ FIRE1
		
		JMP CONTINUE
		
		FIRE1:
			MOV LOCAL_KEY, AH
		    CMP HOLD_FIRE_1,0
			JNZ DEC_HOLD_1 ;; PLAYER 1 CAN'T FIRE AGAIN YET 
			FIRE X1, Y1 , 1
			MOV HOLD_FIRE_1,AL ;; HOLD FIRE THE NEXT "FIRE_DELAY" TIMES
			JMP CONTINUE
			

		;; IGNORE ACTION AND DEC HOLD_FIRE_1 OR HOLD_FIRE_2	
        DEC_HOLD_1:
			DEC HOLD_FIRE_1
            JMP CONTINUE			
        
		CONTINUE:
	
  POPA
        
ENDM HandlePlayerFire


HandleRemoteFire MACRO
    PUSHA
		LOCAL CONTINUE

        ;; GET KEY PRESSED 
		CMP REMOTE_KEY, 0
		JZ CONTINUE
		
		MOV AL,FIRE_DELAY
		
		CMP REMOTE_KEY, M_LETTER
		JZ FIRE2
		
		JMP CONTINUE
			
		FIRE2:
		    CMP HOLD_FIRE_2,0
			JNZ DEC_HOLD_2 ;; PLAYER 2 CAN'T FIRE AGAIN YET
			FIRE X2, Y2 , 2
			MOV HOLD_FIRE_2,AL
			JMP CONTINUE

		;; IGNORE ACTION AND DEC HOLD_FIRE_1 OR HOLD_FIRE_2	
				
		DEC_HOLD_2:
			DEC HOLD_FIRE_2
            JMP CONTINUE
    
    
		CONTINUE:
	
  POPA
        
ENDM HandleRemoteFire


HandleExit MACRO
    PUSHA
		LOCAL CONTINUE
		LOCAL EXIT

        ;; GET KEY PRESSED 
		MOV AH, 01
		INT 16H
		JZ CONTINUE
		
		CMP AH, 01H
		JZ EXIT
		
		
		JMP CONTINUE
		
		EXIT:
			MOV STATE, 1
		    ;TERMINATE
			
		CONTINUE:
	
  POPA
        
ENDM HandleExit
;;-------------------------------
;; PRINT THE BOMB ON THE SCREEN AND STORE ITS DATA IN BOMBX, BOMBY, BOMB_ACTIVE
Fire MACRO X, Y, P
    PUSHA

		MOV DL,X
		MOV DH,Y
		MOV AL,P

		MoveCursor DL,DH
		PlantBomb ;; PRINT THE BOMB
		AddBomb DL,DH,AL ;; STORE ITS DATA
            
  POPA
        
ENDM Fire

;;-------------------------------
MoveCursor MACRO X,Y
    PUSHA
	
		MOV DL,X
		MOV DH,Y
		MOV AH,02H
		MOV BH,0
		INT 10H 
  
  POPA      
ENDM MoveCursor

;;-------------------------------
;; prints a bomb
PlantBomb MACRO
    PUSHA
	
		MOV AH,9
		MOV BH,0
		MOV AL, BOMB_CHAR
		MOV CX,1H
		MOV BL,004H ;; 04F
		INT 10H
    
	POPA
        
ENDM PlantBomb

;;-------------------------------

 AddBomb MACRO X,Y,P
    PUSHA
   
    StoreX X
    StoreY Y
	StoreCond P 
   
    POPA
 ENDM AddBomb

;;-------------------------------

StoreX MACRO X
   PUSHA
   
   LEA BX,BOMBX
   ADD BX,B_COUNT
   MOV AL,X
   MOV [BX],AL
   
   POPA
   
ENDM StoreX

;;-------------------------------

StoreY MACRO Y
   PUSHA
   
   LEA BX,BOMBY
   ADD BX,B_COUNT
   MOV AL,Y
   MOV [BX],AL
   
   POPA
   
ENDM StoreY

;;-------------------------------
;; INDICATE IF THE BOMB IS PLANTED BY FIRST PLAYER OR SECOND ONE
StoreCond MACRO P
   PUSHA
	
	LEA BX, BOMB_ACTIVE
	ADD BX, B_COUNT
	MOV AL,P
	MOV [BX], AL
	
    INC B_COUNT

   POPA
ENDM StoreCond



;;------------------Explosion---------------------------

;; CHECK IF ANY BOMB GOING TO EXPLODE
TestBombs MACRO S,X,Y
   PUSHA
   LOCAL NEXT
   LOCAL COMPARE_X
   LOCAL COMPARE_Y
   LOCAL EX_1
   LOCAL CHECK
   
      LEA SI,BOMBX
	  LEA DI,BOMBY
	  LEA BX, BOMB_ACTIVE	  
	  
	  MOV CX,B_COUNT
	  
	CHECK:  
	  CMP [BX], 0
	  JNZ NEXT
	  

      COMPARE_X:
			
		   MOV AH,X
		   CMP [SI],AH
		   JZ COMPARE_Y
		   JNZ NEXT
	       
	  COMPARE_Y:
           
		   MOV AL,Y
		   CMP [DI],AL
           JNZ NEXT
		    
		   MOV AL,1	
		   CMP AL,S
		   JZ EX_1
		   
		   Explode CX,2
		   JMP NEXT
		   
		   
        EX_1:   Explode CX,1
		        JMP NEXT
		   
       NEXT:
            
           INC SI
           INC DI
		   INC BX 
           LOOP CHECK		   
   
   POPA  
ENDM TestBombs

;;-------------------------------
;; CHECK FOR ACTIVE BOMBS (READY FOR EXPLOSION)
CheckBombs MACRO
	PUSHA
		
		LOCAL CHECK
		LOCAL NEXT
		LOCAL POS1
		LOCAL POS2
		
		LEA SI, BOMBX
		LEA DI, BOMBY
		LEA BX, BOMB_ACTIVE
		
		
		MOV CX, B_COUNT
		
		CHECK:
		
			CMP [BX], 1
			JZ POS1
			
			CMP [BX], 2
			JZ POS2
			
			JMP NEXT
			
		POS1:
			MOV AH, [SI]
			SUB AH, X1
			
			MOV AL, [DI]
			SUB AL, Y1
			OR AL, AH
			CMP AL, 0
			JZ NEXT
			
			MOV [BX], 0
			
			JMP NEXT
		
		POS2:

			MOV AH, [SI]
			SUB AH, X2
			
			MOV AL, [DI]
			SUB AL, Y2
			OR AL, AH
			JZ NEXT
			
			MOV [BX], 0		
			
			JMP NEXT
		
		NEXT:
			INC SI
			INC DI
			INC BX
			DEC CX
			JNZ CHECK
		
	POPA
ENDM CheckBombs
 
 
;;-------------------------------
;; IMPLEMENT EXPLOSION ACTION 
Explode MACRO COUNT,G
   PUSHA

        MOV AH,G
        MOV DX,B_COUNT
        SUB DX,COUNT
       
        ResetXY DX
		
        Bang AH
      			

   POPA
ENDM Explode

   
;;-------------------------------
;; CLEAR THE COORDINATES OF THE BOMB  
ResetXY MACRO N
  PUSHA

		LEA SI,BOMBX
		ADD SI,N

		LEA DI,BOMBY
		ADD DI,N

		MOV [SI],-1 
		MOV [DI],-1 


  POPA	
ENDM ResetXY



;;--------------------------------------------
;; PERFORM THE AFFECT OF THE BOMB ON THE PLAYERS
Bang MACRO S
  PUSHA
    LOCAL P_2
	LOCAL END_IT
		
		MOV AL, MOTION_DELAY
	    
		CMP S,1
        JNZ P_2
		
		;; SHUFFLE THE CONTROLS OF PLAYER1
		ADD P1_POSTPONE, AL
		Shuffle1
		
		JMP END_IT
        
		;; SHUFFLE THE CONTROLS OF PLAYER2
		P_2:
            ADD P2_POSTPONE,AL
            Shuffle2			 

			JMP END_IT
			
        END_IT:
       
  POPA	
ENDM Bang


;;--------------------------------------------
;; SHUFFLE THE CONTROLS OF THE FIRST PLAYER
Shuffle1 MACRO 
  PUSHA
        

		;; randomize numbers with uniqueness
		
		Select_UP_1 2

		Select_DOWN_1 1

		Select_LEFT_1 4
		  
		Select_RIGHT_1 3	
		
	    
  POPA	
ENDM Shuffle1


;;--------------------------------------------
;; CHANGE THE SCANCODE OF THE UP KEY OF THE FIRST PLAYER (^)
Select_UP_1 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL DOWN_1 
	LOCAL RIGHT_1
	LOCAL LEFT_1
	
        CMP S,1
        JZ END_IT
		
		CMP S,2
		JZ DOWN_1
		
        CMP S,3
        JZ LEFT_1

        CMP S,4
        JZ RIGHT_1
		
        DOWN_1:
		    MOV AL,DOWN_ARROW_PER
            MOV UP_ARROW1,AL
            JMP END_IT
        
        LEFT_1:
		    MOV AL,LEFT_ARROW_PER
            MOV UP_ARROW1,AL
            JMP END_IT
			
		RIGHT_1:
		    MOV AL,RIGHT_ARROW_PER
            MOV UP_ARROW1,AL
            JMP END_IT
        
		END_IT:		
                      
   POPA
ENDM Select_UP_1
;;--------------------------------------------
;; CHANGE THE SCANCODE OF THE DOWN KEY OF THE FIRST PLAYER 
Select_DOWN_1 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_1 
	LOCAL RIGHT_1
	LOCAL LEFT_1
	
        CMP S,1
        JZ UP_1
		
		CMP S,2
		JZ END_IT
		
        CMP S,3
        JZ LEFT_1

        CMP S,4
        JZ RIGHT_1
		
        UP_1:
		    MOV AL,UP_ARROW_PER
            MOV DOWN_ARROW1,AL
            JMP END_IT
        
        LEFT_1:
		    MOV AL,LEFT_ARROW_PER
            MOV DOWN_ARROW1,AL
            JMP END_IT
			
		RIGHT_1:
		    MOV AL,RIGHT_ARROW_PER
            MOV DOWN_ARROW1,AL
            JMP END_IT
        
        END_IT:		
                      
   POPA
ENDM Select_DOWN_1
;;--------------------------------------------
;; CHANGE THE SCANCODE OF THE LEFT KEY OF THE FIRST PLAYER (<-)
Select_LEFT_1 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_1 
	LOCAL DOWN_1
	LOCAL RIGHT_1
	
        CMP S,1
        JZ UP_1
		
		CMP S,2
		JZ DOWN_1
		
        CMP S,3
        JZ END_IT

        CMP S,4
        JZ RIGHT_1
		
        UP_1:
		    MOV AL,UP_ARROW_PER
            MOV LEFT_ARROW1,AL
            JMP END_IT
        
        DOWN_1:
		    MOV AL,DOWN_ARROW_PER
            MOV LEFT_ARROW1,AL
            JMP END_IT
			
		RIGHT_1:
		    MOV AL,RIGHT_ARROW_PER
            MOV LEFT_ARROW1,AL
            JMP END_IT
        		
        END_IT:        
		
   POPA
ENDM Select_LEFT_1
;;--------------------------------------------
;; CHANGE THE SCANCODE OF THE RIGHT KEY OF THE FIRST PLAYER (->)
Select_RIGHT_1 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_1 
	LOCAL DOWN_1
	LOCAL LEFT_1
	
        CMP S,1
        JZ UP_1
		
		CMP S,2
		JZ DOWN_1
		
        CMP S,3
        JZ LEFT_1

        CMP S,4
        JZ END_IT
		
        UP_1:
		    MOV AL,UP_ARROW_PER
            MOV RIGHT_ARROW1,AL
            JMP END_IT
        
        DOWN_1:
		    MOV AL,DOWN_ARROW_PER
            MOV RIGHT_ARROW1,AL
            JMP END_IT
			
		LEFT_1:
		    MOV AL,LEFT_ARROW_PER
            MOV RIGHT_ARROW1,AL
            JMP END_IT
        
        END_IT:		
                      
   POPA
ENDM Select_RIGHT_1


;;--------------------------------------------W->1,2->S,3->A,4->D
;; SHUFFLE THE CONTROLS OF THE SECOND PLAYER 
Shuffle2 MACRO 
  PUSHA
        
		Select_UP_2 2

		Select_DOWN_2 1

		Select_LEFT_2 4
		  
		Select_RIGHT_2 3			
	    
  POPA	
ENDM Shuffle2
;---------------------------------------
;;--------------------------------------------
;; CHANGE THE SCANCODE OF THE UP KEY OF THE SECOND PLAYER (^)
Select_UP_2 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL DOWN_2 
	LOCAL RIGHT_2
	LOCAL LEFT_2
	
        CMP S,1
        JZ END_IT
		
		CMP S,2
		JZ DOWN_2
		
        CMP S,3
        JZ LEFT_2

        CMP S,4
        JZ RIGHT_2
		
        DOWN_2:
		    MOV AL,DOWN_ARROW_PER
            MOV UP_ARROW2,AL
            JMP END_IT
        
        LEFT_2:
		    MOV AL,LEFT_ARROW_PER
            MOV UP_ARROW2,AL
            JMP END_IT
			
		RIGHT_2:
		    MOV AL,RIGHT_ARROW_PER
            MOV UP_ARROW2,AL
            JMP END_IT
        
		END_IT:		
                      
   POPA
ENDM Select_UP_2
;;--------------------------------------------
;; CHANGE THE SCANCODE OF THE DOWN KEY OF THE SECOND PLAYER 
Select_DOWN_2 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_2 
	LOCAL RIGHT_2
	LOCAL LEFT_2
	
        CMP S,1
        JZ UP_2
		
		CMP S,2
		JZ END_IT
		
        CMP S,3
        JZ LEFT_2

        CMP S,4
        JZ RIGHT_2
		
        UP_2:
		    MOV AL,UP_ARROW_PER
            MOV DOWN_ARROW2,AL
            JMP END_IT
        
        LEFT_2:
		    MOV AL,LEFT_ARROW_PER
            MOV DOWN_ARROW2,AL
            JMP END_IT
			
		RIGHT_2:
		    MOV AL,RIGHT_ARROW_PER
            MOV DOWN_ARROW2,AL
            JMP END_IT
        
        END_IT:		
                      
   POPA
ENDM Select_DOWN_2
;;--------------------------------------------
;; CHANGE THE SCANCODE OF THE LEFT KEY OF THE SECOND PLAYER
Select_LEFT_2 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_2 
	LOCAL DOWN_2
	LOCAL RIGHT_2
	
        CMP S,1
        JZ UP_2
		
		CMP S,2
		JZ DOWN_2
		
        CMP S,3
        JZ END_IT

        CMP S,4
        JZ RIGHT_2
		
        UP_2:
		    MOV AL,UP_ARROW_PER
            MOV LEFT_ARROW2,AL
            JMP END_IT
        
        DOWN_2:
		    MOV AL,DOWN_ARROW_PER
            MOV LEFT_ARROW2,AL
            JMP END_IT
			
		RIGHT_2:
		    MOV AL,RIGHT_ARROW_PER
            MOV LEFT_ARROW2,AL
            JMP END_IT
        		
        END_IT:        
		
   POPA
ENDM Select_LEFT_2
;;--------------------------------------------
;; CHANGE THE SCANCODE OF THE RIGHT KEY OF THE SECOND PLAYER 
Select_RIGHT_2 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_2 
	LOCAL DOWN_2
	LOCAL LEFT_2
	
        CMP S,1
        JZ UP_2
		
		CMP S,2
		JZ DOWN_2
		
        CMP S,3
        JZ LEFT_2

        CMP S,4
        JZ END_IT
		
        UP_2:
		    MOV AL,UP_ARROW_PER
            MOV RIGHT_ARROW2,AL
            JMP END_IT
        
        DOWN_2:
		    MOV AL,DOWN_ARROW_PER
            MOV RIGHT_ARROW2,AL
            JMP END_IT
			
		LEFT_2:
		    MOV AL,LEFT_ARROW_PER
            MOV RIGHT_ARROW2,AL
            JMP END_IT
        
        END_IT:		
                      
   POPA
ENDM Select_RIGHT_2


;;--------------------------------------------
;; GET A RANDOM NUMBER SMALLER THAN N AND STORE IT IN R
Randomize MACRO R,N
	PUSHA

		;; GET SYSTEM TIME
		MOV AH, 2CH
		INT 21H

		;; MOVE HUNDREDTHS OF SECOND TO AX
		MOV AL, DL
		CBW

		;; TAKE HUNDREDTHS OF SECOND MOD NUMBER OF MAZES TO GET A RANDOM NUMBER
		MOV BL,N
		DIV BL
		MOV R, AH


	POPA
ENDM Randomize

;;---------------------------------------------------------------
;; GENERATE RANDOM FOUR RANDOM NUMBERS BETWEEN 1 AND 4 WITHOUT ANY DUPLICATES (USED IN SHUFFLING THE CONTROLS)			 
RandUnique MACRO
    PUSHA  
        
		LOCAL GENERATE
		LOCAL CHECK
		LOCAL SHIFT
		LOCAL NEXT
		LOCAL RESET
		
        MOV SI, OFFSET RAND_2
        MOV DI, OFFSET RAND_1
        MOV CL, RAND_2_LNS
        MOV CH, 0
        MOV BH, 0
        
        GENERATE:
            RANDOMIZE RANDOM , RAND_2_LNS
            MOV BL, RANDOM
            MOV AL, SI[BX]
            MOV [DI], AL
            INC DI
            
        CHECK:
            INC BL
            CMP BL, RAND_2_LNS
            JZ NEXT
            ;; SHIFT THE ELEMENTS
        SHIFT:
            MOV AL, SI[BX]
            DEC BL
            MOV SI[BX], AL
            INC BL
            JMP CHECK
                 
        NEXT:     
            DEC RAND_2_LNS
            LOOP GENERATE 
		
		;; reset the reference array to its initial values with its length
		MOV SI, OFFSET RAND_2
		MOV CX, 1
		
		RESET:
			MOV [SI], CX
			INC SI
			INC CX
			CMP CX, 5
			JNZ RESET
		
		MOV RAND_2_LNS, 4
		
    
    
    POPA
ENDM	RandUnique

RandInvert MACRO
	PUSHA
				
		MOV RAND_1[0], 2
		MOV RAND_1[1], 1
		MOV RAND_1[2], 4
		MOV RAND_1[3], 3
	
	POPA
ENDM RandInvert

;-------------------------------------------
;; CHECK IF THERE IS A WINNER OR NOT YET
Winner MACRO 
	PUSHA
	
	LOCAL P1_WIN
	LOCAL P2_WIN
	LOCAL ANNOUNCE
	LOCAL END_IT
		;; SEE IF PLAYER ONE REACH THE END
		CMP X1,78
		JZ P1_WIN
		
		;; SEE IF PLAYER TWO REACH THE END			
		CMP X2,78
		JZ P2_WIN
		
		JMP END_IT
		
		P1_WIN:
			MOV AL,1
			MOV X1, 5
			JMP ANNOUNCE
			
		P2_WIN:
			MOV AL,2
			MOV X2, 5
			JMP ANNOUNCE
			
		ANNOUNCE:
			MOV END_GAME,1
            MOV WINNER_NO,AL
			MOV STATE, 5
                 		

	END_IT:	
		
	
	POPA
ENDM Winner


;; CLEAR THE MAZE AND ANNOUNCE THE WINNER
DrawWinScreen MACRO
	PUSHA
	
	LOCAL END_IT, LOAD_1, CONTINUE
		
		CMP WINNER_NO, 1
		JZ LOAD_1
		
		LoadFile LOSER_FILE, WIN
		JMP CONTINUE
		
		LOAD_1:
			LoadFile WINNER_FILE, WIN
		
		CONTINUE:
		
		ClearScreen
		
		MoveCursor 0, 0
	 
        DrawString WIN, 0E0H
		
		;; PRINT THE WINNER NAME ON THE CUP
		MoveCursor 33,20
		MOV XP,33
		MOV YP,20
		
		PrintName P1_NAME
	
	POPA
ENDM DrawWinScreen 



;; PRINT THE NAME OF THE WINNER
PrintName MACRO P_NAME
	PUSHA
	

	LOCAL PRINT_NAME
	LOCAL PRINT_CHAR
	LOCAL NEXT
	
		LEA SI,P_NAME
		;; SKIP FIRST TWO CHAR 
		ADD SI,2
		MOV CX,20
		
		PRINT_NAME:
			CMP [SI],'$'
			JZ NEXT
			
			CMP [SI],65
			JL NEXT
			
			JMP PRINT_CHAR
			
		PRINT_CHAR:
			MOV AH,9
			MOV BH,0
			MOV AL,[SI]
			PUSH CX
			MOV CX,1H
			MOV BL,00EH
			INT 10H
			POP CX
			INC XP
			MoveCursor XP,YP
			JMP NEXT
			
		NEXT:
			INC SI
			LOOP PRINT_NAME
		
	
	POPA
ENDM PrintName


;; SET PLAYERS NAMES IN SCOREBAR
SetNames MACRO
	PUSHA
	
		MoveCursor 0,21
		MOV XP,0
		MOV YP,21
		
		PrintName P1_NAME
		
		MoveCursor 40,21
		MOV XP,40
		MOV YP,21		
		
		PrintName P2_NAME
		
		
		
	POPA
ENDM SetNames


;; DISPLAY PLAYERS SCORES
SetScore MACRO
	PUSHA
	
	
	    MOV CL,X1
		ToAscii CL
		MoveCursor 21,21
        
		;; PRINT PLAYER1 SCORE (X1)
		MOV AH,9
		LEA DX,ASCII_RESULT	
		INT 21H
		
		MOV CL,X2
		ToAscii CL
		MoveCursor 61,21
        
		;; PRINT PLAYER2 SCORE (X2)
		MOV AH,9
		LEA DX,ASCII_RESULT	
		INT 21H
		
	
	POPA
ENDM SetScore


;; CONVERT INTEGER TO ASCII CODE AND STORE IT IN ASCII_RESULTS
ToAscii MACRO HEX
    PUSHA
        
        MOV SI, OFFSET ASCII_RESULT
        MOV AL, HEX
		MOV AH,00
        MOV BL, 10
        DIV BL
        ADD AL, '0'
        ADD AH, '0'
        MOV [SI], AL
        INC SI
        MOV [SI], AH
        
    POPA
ENDM ToAscii

InitializeVars MACRO
	PUSHA
		
		LOCAL CLEAR
		
		MOV X1, 0
		MOV Y1, 1
		MOV X2, 0
		MOV Y2, 1
		
		MOV CX, B_COUNT
		MOV SI, OFFSET BOMBX
		MOV DI, OFFSET BOMBY
		MOV BP, OFFSET BOMB_ACTIVE
		CLEAR:
			MOV [SI], -1
			MOV [DI], -1
			MOV [BP], 3
			LOOP CLEAR
		
		MOV B_COUNT, 1
		MOV P1_POSTPONE, 0
		MOV P2_POSTPONE, 0
		MOV HOLD_FIRE_1, 0
		MOV HOLD_FIRE_2, 2
		MOV END_GAME, 0
		
		MOV UP_ARROW,48H
		MOV DOWN_ARROW,50H
		MOV RIGHT_ARROW,4DH
		MOV LEFT_ARROW,4BH
		MOV W_LETTER,11H
		MOV A_LETTER,1EH
		MOV S_LETTER,1FH
		MOV D_LETTER,20H	
	
	
	POPA
ENDM InitializeVars


;; configures serial port connection
ConfigureSerial MACRO
    PUSHA
        
        ;; Set Divisor Latch Access Bit
        mov dx,3fbh 			;; Line Control Register
        mov al,10000000b		;; Set Divisor Latch Access Bit
        out dx,al			;; Out it
        ;; Set LSB byte of the Baud Rate Divisor Latch register.
        mov dx,3f8h			
        mov al,0ch			
        out dx,al
        ;; Set MSB byte of the Baud Rate Divisor Latch register.
        mov dx,3f9h
        mov al,00h
        out dx,al
        ;; Set port configuration
        mov dx,3fbh
        mov al,00011011b
        out dx,al 
    
    POPA
ENDM ConfigureSerial


;; send a byte over serial
Send MACRO LETTER
    PUSHA
	
		LOCAL AGAIN

        ;Check that Transmitter Holding Register is Empty
		mov dx , 3FDH		; Line Status Register
        AGAIN:  In al , dx 			;Read Line Status
          		AND al , 00100000b
          		JZ AGAIN			;; wait until receiver can receive
	
        ;If empty put the VALUE in Transmit data register
  		mov dx , 3F8H		; Transmit data register
  		mov  al,LETTER
  		out dx , al 
	 
    POPA
ENDM Send


;; receive a byte over serial
Receive MACRO STORAGE_ADDRESS
    PUSHA 
    
    LOCAL CHK
	
        ;Check that Data Ready
    	mov dx , 3FDH		; Line Status Register
    	CHK:
			in al , dx 
			AND al , 1
			JZ CHK

        ;If Ready read the VALUE in Receive data register
  		mov dx , 03F8H
  		in al , dx 
		MOV DI, STORAGE_ADDRESS
  		mov [DI] , al

    POPA
ENDM Receive


ExchangeNames MACRO
	LOCAL START_AGAIN
	mov bx,0
	START_AGAIN:
		Send P1_NAME[BX]
		LEA DI, P2_NAME[BX]
		Receive DI  
		INC BX
		CMP BX,23
		JNE START_AGAIN
               
ENDM ExchangeNames


SendMaze MACRO
	PUSHA
		
		LOCAL SEND_MAZE
		
		MOV SI, OFFSET MAZE
		MOV CX, 2100	;; MAXIMUM NUMBER OF CHARS IN A MAZE
		
		SEND_MAZE:
			Send [SI]
			INC SI
			LOOP SEND_MAZE
	
	POPA
ENDM SendMaze

ReceiveMaze MACRO
	PUSHA
		
		LOCAL RECEIVE_MAZE
		
		MOV DI, OFFSET MAZE
		MOV CX, 2100	;; MAXIMUM NUMBER OF CHARS IN A MAZE
		Receive DI	
		RECEIVE_MAZE:
			Receive DI
			INC DI
			LOOP RECEIVE_MAZE
	
	POPA
ENDM ReceiveMaze

ExchangeMazes MACRO
	PUSHA
	
		LOCAL END_IT, RECEIVE_MAZE
		
		CMP GOT_INVITED, 0
		JNE RECEIVE_MAZE
		
		SendMaze
		JMP END_IT
		
		RECEIVE_MAZE:
			ReceiveMaze
		
		END_IT:
	
	POPA
ENDM ExchangeMazes

;; SEND PLAYER UPDATES AND MOVEMENTS ALONGSIDE WITH BOMBS
SendPlayerData MACRO
	PUSHA
	
		LOCAL SEND_X, SEND_Y, SEND_ACTIVE
	
		;; SEND FF TO INDICATE STARTING OF SENDING PLAYER UPDATES
		; Send 0FFH
		
		;; START BY UPDATING PLAYER LOCATION
		
		; LEA SI, X1
		; LEA DI, Y1
		; SEND X1
		; VERIFY SENDING BY RECEIVING IT
		; Receive SI
		
		; SEND Y1
		; VERIFY SENDING BY RECEIVING IT
		; Receive DI
		
		SEND LOCAL_KEY
		LEA SI, LOCAL_KEY
		RECEIVE SI
		MOV LOCAL_KEY, 0
		
		
		; THEN SEND BOMBS COUNT
		; MOV AX, B_COUNT
		; SEND AL
		
		; THEN SEND ALL X'S OF BOMBS
		; MOV CX, B_COUNT
		; LEA SI, BOMBX
		
		; SEND_X:
			; SEND [SI]
			; INC SI
			; LOOP SEND_X
			
		; THEN SEND ALL Y'S OF BOMBS
		; MOV CX, B_COUNT
		; LEA SI, BOMBY
		
		; SEND_Y:
			; SEND [SI]
			; INC SI
			; LOOP SEND_Y
			
		; THEN SEND ALL ACTIVE BOMBS DATA
		; MOV CX, B_COUNT
		; LEA SI, BOMB_ACTIVE
		
		; SEND_ACTIVE:
			; SEND [SI]
			; INC SI
			; LOOP SEND_ACTIVE
	
	POPA
ENDM SendPlayerData


;; SEND PLAYER UPDATES AND MOVEMENTS ALONGSIDE WITH BOMBS
ReceivePlayerData MACRO
	PUSHA
		
		LEA DI, REMOTE_KEY
		RECEIVE DI
		SEND REMOTE_KEY
		; LOCAL CONTINUE
		
		; START BY RECEIVING PLAYER X, Y
		; LEA SI, X2
		; LEA DI, Y2
		; Receive SI
		; Receive SI
		; VERIFY RECEIVING BY RESENDING IT
		; Send X2
		; Receive DI
		; VERIFY RECEIVING BY RESENDING IT
		; Send Y2
		
		; VALIDATE NEW COORDINATES
		; MOV AL, X2
		; SUB AL, OLD_X2
		; MOV AH, Y2
		; SUB AH, OLD_Y2
		; AND AL, AH
		; JZ CONTINUE
		; Receive SI
		; MOV AL, OLD_X2
		; MOV X2, AL
		; MOV AH, OLD_Y2
		; MOV Y2, AH
		
		; CONTINUE:
		; THEN RECEIVE BOMBS COUNT
		; LEA SI, B_COUNT
		; Receive SI
		
		; THEN RECEIVE ALL X'S OF BOMBS
		; MOV CX, B_COUNT
		; LEA SI, BOMBX
		
		; RECEIVE_X:
			; Receive [SI]
			; INC SI
			; LOOP RECEIVE_X
			
		; THEN RECEIVE ALL Y'S OF BOMBS
		; MOV CX, B_COUNT
		; LEA SI, BOMBY
		
		; RECEIVE_Y:
			; Receive [SI]
			; INC SI
			; LOOP RECEIVE_Y
			
		; THEN RECEIVE ALL ACTIVE BOMBS DATA
		; MOV CX, B_COUNT
		; LEA SI, BOMB_ACTIVE
		
		; RECEIVE_ACTIVE:
			; Receive [SI]
			; INC SI
			; LOOP RECEIVE_ACTIVE
		
	POPA
ENDM ReceivePlayerData

ExchangePlayerData MACRO
	PUSHA
		
		LOCAL END_IT, RECEIVE_FIRST
		
		CMP GOT_INVITED, 0
		JNE RECEIVE_FIRST
		
		; else, send first
		SendPlayerData
		ReceivePlayerData
		
		JMP END_IT
		
		RECEIVE_FIRST:
			ReceivePlayerData
			SendPlayerData
		
		END_IT:
	
	POPA
ENDM ExchangePlayerData

PrintWaiting MACRO
	PUSHA
		MOV XP, 0
		MOV YP, 23
		PrintStr WAITING, XP , YP
	
	POPA
ENDM PrintWaiting

SendInvitation MACRO
	PUSHA
	
		;; sends an invitation to the other player with the name in it
		;SendName
		Send SENT_INVITATION
		; ReceiveName
		;SendName
	
	POPA
ENDM SendInvitation

ReceiveInvitation MACRO
	PUSHA
	
		LOCAL RECEIVE_INV, END_IT, COMPARE_INV
		;; receives an invitation to the other player with the name in it
		;ReceiveName
		;; CHECK IF INVITATIONS ARE MATCHED
		MOV AL, SENT_INVITATION
		MOV AH, RECEIVED_INVITATION
		CMP AL, AH
		JNZ RECEIVE_INV
		;; MAKE SURE THEY ARE NOT ZEROS
		CMP AH, 0
		JE RECEIVE_INV
		MOV GOT_INVITED, 1
		MOV MATCHED, 1
		MOV MODE, '3'
		MOV STATE, 2
		; PRINT IN THE NOTIFICATION BAR THAT I ACCEPTED THE INVITATION

		JMP END_IT


		RECEIVE_INV:
			MOV DL, RECEIVED_INVITATION
			MOV SI, OFFSET RECEIVED_INVITATION
			Receive SI
			; SendName
			;ReceiveName
			CMP RECEIVED_INVITATION, 0
			JNE COMPARE_INV
			MOV RECEIVED_INVITATION, DL
			
	;		JZ PRINT IN THE NOTIFICATIONS THAT SECOND PLAYER ACCEPTED THE INVITATION
		COMPARE_INV:
			MOV AH, RECEIVED_INVITATION
			CMP AL, AH
			JNZ END_IT
			CMP AH, 0
			JE END_IT
			MOV MATCHED, 1
			MOV STATE, 2
		
		END_IT:
	
	POPA
ENDM ReceiveInvitation

 
PrintStr MACRO STRING, X, Y
    PUSHA
        
            
    LOCAL PRINT_STR, PRINT_CHAR, NEXT, END_IT
	
		LEA SI,STRING
		MOV CX, 100
		               
		MOV DL,0
		MOV DH,Y
		
		MOV AH,2H
        MOV BH,0
        INT 10H 
		
		PRINT_STR:
			CMP [SI],'$'  
			
			JZ END_IT
			
			
		PRINT_CHAR:
		    CMP [SI],1CH
			JZ NEXT
			
		    MOV AH,2
		    MOV DL,[SI]
		    INT 21H
		    INC X
		    
			JMP NEXT
			
		NEXT:
			INC SI
			LOOP PRINT_STR 
			
		END_IT:
			
        
    POPA
ENDM PrintStr     
     
 

NotificationBar MACRO
	PUSHA
		
		LOCAL SENT_CHAT, SENT_GAME, REC_CHAT, REC_GAME, END_IT, CONTINUE
		MOV XP, 0
		MOV YP, 23
		ClearLine YP
		CMP SENT_INVITATION, 1
		JE SENT_CHAT
		CMP RECEIVED_INVITATION, 1
		JE REC_CHAT
		JMP CONTINUE
		
		SENT_CHAT:
			; MoveCursor XP, YP
			; MOV AH,9H
			; MOV DX,OFFSET SENT_CHAT_MESSAGE
			; INT 21H  

			PrintStr SENT_CHAT_MESSAGE, XP, YP
			MOV AH,9H
			MOV DX,OFFSET P2_NAME[2]
			INT 21H  
			JMP CONTINUE
		
		REC_CHAT:
			; MoveCursor XP, YP
			; MOV AH,9H
			; MOV DX,OFFSET P2_NAME[2]
			; INT 21H  

			PrintStr REC_CHAT_MESSAGE, XP, YP
			MOV AH,9H
			MOV DX,OFFSET P2_NAME[2]
			INT 21H  
		
		
		CONTINUE:
			MOV XP, 0
			MOV YP, 24
			ClearLine YP
			CMP SENT_INVITATION, 2
			JE SENT_GAME
			CMP RECEIVED_INVITATION, 2
			JE REC_GAME
			JMP END_IT

			
		SENT_GAME:
			; MoveCursor XP, YP
			; MOV AH,9H
			; MOV DX,OFFSET SENT_GAME_MESSAGE
			; INT 21H  
			PrintStr SENT_GAME_MESSAGE, XP, YP
			MOV AH,9H
			MOV DX,OFFSET P2_NAME[2]
			INT 21H  
			JMP END_IT
		
		REC_GAME:
			; MoveCursor XP, YP
			; MOV AH,9H
			; MOV DX,OFFSET P2_NAME[2]
			; INT 21H 
			PrintStr REC_GAME_MESSAGE, XP, YP
			MOV AH,9H
			MOV DX,OFFSET P2_NAME[2]
			INT 21H  
		
		
		END_IT:
	
	POPA
ENDM NotificationBar

ClearLine MACRO Y
	PUSHA
	
		; LOCAL CLEAR
		; MOV AL, Y
		MoveCursor 0, Y 
		
			mov ah,9 ;Display
			mov bh,0 ;Page 0
			mov al,' ' ;Letter D
			mov cx,80 ;5 times
			mov bl,0Fh ;Green (A) on white(F) background
			int 10h
		
	
	POPA
ENDM ClearLine
