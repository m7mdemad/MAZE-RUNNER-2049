DrawMaze MACRO
    PUSHA    
	
		LOCAL PRINT
		LOCAL NEW_LINE
		LOCAL INCREMENT
		LOCAL CHECK
		
        RandomizeMaze 
        LoadMaze
		
		;; SET CURSOR TO INVISIBLE
		RemoveCursor
		
		;; CLEAR THE SCREEN
		MOV AH, 06
		MOV AL, 00
		MOV BH, 07
		MOV CH, 00
		MOV CL, 00
		MOV DH, 24
		MOV DL, 79
		INT 10H
    
		;; MOVE CURSOR TO START OF SCREEN
		MOV AH, 02
		MOV BH, 00
		MOV DL, 00
		MOV DH, 00
		INT 10H
		
		
        MOV BX, OFFSET MAZE
		PUSH BX
                         
                         
        ;; PRINT AS LONG AS IT DIDN'T REACH '$' (SAME AS INT 21H , AH = 9)    
        PRINT:
			CMP [BX], ' '
			JZ INCREMENT
			
			CMP [BX], 13
			JZ INCREMENT
			
			
			CMP [BX], 10
			JZ NEW_LINE
			
			
			mov ah,9 ;;Display
			mov al,' ' ;;SPACE
			mov bh,0 ;;Page 0
			mov cx,1h ;;1 time
			mov bl,033H ;;
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
                
ENDM DrawMaze      


RandomizeMaze MACRO 
    PUSHA
  
        ;; GET SYSTEM TIME
        MOV AH, 2CH
        INT 21H
        
        ;; MOVE HUNDREDTHS OF SECOND TO AX
        MOV AL, DL
        CBW
        
        ;; TAKE HUNDREDTHS OF SECOND MOD NUMBER OF MAZES TO GET A RANDOM NUMBER
        DIV MAZES_N
        MOV RANDOM, AH

        
    POPA
        
ENDM RandomizeMaze


LoadMaze MACRO 
    PUSHA
	
		LOCAL ERROR
		LOCAL CONTINUE
  
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
            
    POPA
        
ENDM LoadMaze



LoadIntro MACRO 
    PUSHA
	
		LOCAL ERROR
		LOCAL CONTINUE
  
            MOV DX, OFFSET INTRO_FILE
            JMP CONTINUE
            
        ERROR:
            MOV AH, 4CH
            MOV AL, 0
            INT 21H
                                       
        
        CONTINUE:
            
            ;; OPEN THE INTRO FILE
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
            
            
            ;; READ THE INTRO FILE INTO INTRO VARIABLE
            POP BX
            MOV CX, AX
            MOV AH, 3FH
            MOV DX, OFFSET INTRO
            INT 21H  
            
    POPA
        
ENDM LoadIntro


DrawIntro MACRO
    PUSHA    
		
		LOCAL PRINT
		LOCAL NEW_LINE
		LOCAL INCREMENT
		LOCAL CHECK
		
        LoadIntro
		
		;; SET CURSOR TO INVISIBLE
		RemoveCursor
		
		;; CLEAR THE SCREEN
		MOV AH, 06
		MOV AL, 00
		MOV BH, 07
		MOV CH, 00
		MOV CL, 00
		MOV DH, 24
		MOV DL, 79
		INT 10H
    
		;; MOVE CURSOR TO START OF SCREEN
		MOV AH, 02
		MOV BH, 00
		MOV DL, 00
		MOV DH, 00
		INT 10H
		
		
        MOV BX, OFFSET INTRO
		PUSH BX
                         
                         
        ;; PRINT AS LONG AS IT DIDN'T REACH '$' (SAME AS INT 21H , AH = 9)    
        PRINT:
			CMP [BX], ' '
			JZ INCREMENT 
			
			CMP [BX], 9
			JZ INCREMENT
			
			CMP [BX], 13
			JZ INCREMENT
			
			
			CMP [BX], 10
			JZ NEW_LINE
			
			
			mov ah,9 ;;Display
			mov al,' ' ;;SPACE
			mov bh,0 ;;Page 0
			mov cx,1h ;;1 time
			mov bl,022H ;;
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
				
				
		SLEEP 100
    
    POPA
                
ENDM DrawIntro  


SLEEP MACRO INTERVAL
    PUSHA
        
        MOV AX, 0FFFFH
        MOV BX, INTERVAL
        MUL BX
        MOV CX, AX
        XCHG CX, DX
        MOV AH, 86H
        INT 15H
    
    POPA
ENDM



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
		
		LOCAL MOVE_UP2
		LOCAL MOVE_RIGHT2
		LOCAL MOVE_LEFT2
		LOCAL MOVE_DOWN2
		
		
		LOCAL CONTINUE
		
		;; CHECK IF A KEY WAS PRESSED
		MOV AH, 01
		INT 16H
		JZ CONTINUE
		
		FlushBuffer
		
		CMP AH, UP_ARROW
		JZ MOVE_UP1
		
		CMP AH, LEFT_ARROW
		JZ MOVE_LEFT1
		
		CMP AH, DOWN_ARROW
		JZ MOVE_DOWN1
		
		CMP AH, RIGHT_ARROW
		JZ MOVE_RIGHT1
		
		CMP AH, W_LETTER
		JZ MOVE_UP2
		
		CMP AH, A_LETTER
		JZ MOVE_LEFT2
		
		CMP AH, S_LETTER
		JZ MOVE_DOWN2
		
		CMP AH, D_LETTER
		JZ MOVE_RIGHT2
		
		JMP CONTINUE
		
		
		MOVE_UP1:
		    MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveUp X1, Y1
			JMP CONTINUE

		MOVE_LEFT1:
			MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveLeft X1, Y1
			JMP CONTINUE

		MOVE_DOWN1:
			MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveDown X1, Y1
			JMP CONTINUE
			
		MOVE_RIGHT1:
		    MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveRight X1, Y1
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
ENDM HandlePlayerMovement
    
    
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
			Peep
		
		CONTINUE:
			
	
	POPA
ENDM MoveUp

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
		JNZ MAKE_PEEP

		;; CHANGE THE X POSITION OF THE PLAYER TO THE NEW POSITION
		MOV X, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			Peep
		
		CONTINUE:
			
	
	POPA
ENDM MoveLeft

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
		JNZ MAKE_PEEP

		
		;; CHANGE THE Y POSITION OF THE PLAYER TO THE NEW POSITION
		MOV Y, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			Peep
		
		CONTINUE:
			
	
	POPA
ENDM MoveDown

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
		JNZ MAKE_PEEP


		;; CHANGE THE X POSITION OF THE PLAYER TO THE NEW POSITION
		MOV X, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
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
		
		
		MOV AH,9
		MOV BH,0
		MOV AL,44H
		MOV CX,1H
		MOV BL,000H
		INT 10H
		  
		
		;; CLEAR THAT PLACE 
		MOV AH, 02
		MOV DL, ' '
		INT 21H
		
    
    POPA
ENDM ClearPosition

Peep MACRO
	PUSHA
	
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
	
		;; MAKE PEEP SOUND
		MOV AH, 02H
		MOV DL, 07H
		INT 21H
		
	POPA

ENDM Peep

PrintPlayers MACRO
    PUSHA
	
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


		
    POPA
    
ENDM PrintPlayers

RemoveCursor MACRO
	PUSHA

		MOV AH, 01H
		MOV CX, 2607H
		INT 10H
		
	POPA

ENDM RemoveCursor


FlushBuffer MACRO
		PUSHA
			
			MOV AH, 00
			INT 16H
		
		POPA
ENDM FlushBuffer



MOD_P1_POSTPONE MACRO
		PUSHA
		LOCAL END_1
		LOCAL END_2
		
			CMP P1_POSTPONE,0
			JNZ END_1
			
			MOV AL,UP_ARROW_PER
			MOV UP_ARROW,AL
			
			MOV AL,DOWN_ARROW_PER
			MOV DOWN_ARROW,AL
			
			MOV AL,LEFT_ARROW_PER
			MOV LEFT_ARROW,AL
			
			MOV AL,RIGHT_ARROW_PER
			MOV RIGHT_ARROW,AL
			
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
			
			MOV AL,W_LETTER_PER
			MOV W_LETTER,AL
			
			MOV AL,S_LETTER_PER
			MOV S_LETTER,AL
			
			MOV AL,A_LETTER_PER
			MOV A_LETTER,AL
			
			MOV AL,D_LETTER_PER
			MOV D_LETTER,AL
			
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
		JZ CONTINUE
		        

		HandlePlayerFire
		HandlePlayerMovement
		
		
		
		JMP CONTINUE
        
CONTINUE:
    POPA
        
ENDM DetectAction




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



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
		
		CMP AH, F_LETTER
		JZ FIRE2
		
		JMP CONTINUE
		
		FIRE1:
		    CMP HOLD_FIRE_1,0
			JNZ DEC_HOLD_1 ;; PLAYER 1 CAN'T FIRE AGAIN YET 
			FIRE X1, Y1 , 1
			MOV HOLD_FIRE_1,AL ;; HOLD FIRE THE NEXT "FIRE_DELAY" TIMES
			JMP CONTINUE
			
		FIRE2:
		    CMP HOLD_FIRE_2,0
			JNZ DEC_HOLD_2 ;; PLAYER 2 CAN'T FIRE AGAIN YET
			FIRE X2, Y2 , 2
			MOV HOLD_FIRE_2,AL
			JMP CONTINUE

		;; IGNORE ACTION AND DEC HOLD_FIRE_1 OR HOLD_FIRE_2	
        DEC_HOLD_1:
			DEC HOLD_FIRE_1
            JMP CONTINUE			
		
		
		DEC_HOLD_2:
			DEC HOLD_FIRE_2
            JMP CONTINUE
    
    
		CONTINUE:
	
  POPA
        
ENDM HandlePlayerFire

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
PlantBomb MACRO
    PUSHA
	
  MOV AH,9
  MOV BH,0
  MOV AL, BOMB_CHAR
  MOV CX,1H
  MOV BL,04fH
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
		
		LEA SI,BOMBX
		ADD SI,COUNT 

		LEA DI,BOMBY
        ADD DI,COUNT 
		
        Bang AH
      			

   POPA
ENDM Explode

   
;;-------------------------------
;; 
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


Shuffle1 MACRO 
  PUSHA
        
		LEA SI,RAND_1

		;; randomize numbers with uniqueness
		RandUnique
		
		Select_UP_1 [SI]
		INC SI

		Select_DOWN_1 [SI]
		INC SI

		Select_LEFT_1 [SI]
		INC SI
		  
		Select_RIGHT_1 [SI]		
		
	    
  POPA	
ENDM Shuffle1


;;--------------------------------------------

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
            MOV UP_ARROW,AL
            JMP END_IT
        
        LEFT_1:
		    MOV AL,LEFT_ARROW_PER
            MOV UP_ARROW,AL
            JMP END_IT
			
		RIGHT_1:
		    MOV AL,RIGHT_ARROW_PER
            MOV UP_ARROW,AL
            JMP END_IT
        
		END_IT:		
                      
   POPA
ENDM Select_UP_1
;;--------------------------------------------

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
            MOV DOWN_ARROW,AL
            JMP END_IT
        
        LEFT_1:
		    MOV AL,LEFT_ARROW_PER
            MOV DOWN_ARROW,AL
            JMP END_IT
			
		RIGHT_1:
		    MOV AL,RIGHT_ARROW_PER
            MOV DOWN_ARROW,AL
            JMP END_IT
        
        END_IT:		
                      
   POPA
ENDM Select_DOWN_1
;;--------------------------------------------

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
            MOV LEFT_ARROW,AL
            JMP END_IT
        
        DOWN_1:
		    MOV AL,DOWN_ARROW_PER
            MOV LEFT_ARROW,AL
            JMP END_IT
			
		RIGHT_1:
		    MOV AL,RIGHT_ARROW_PER
            MOV LEFT_ARROW,AL
            JMP END_IT
        		
        END_IT:        
		
   POPA
ENDM Select_LEFT_1
;;--------------------------------------------

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
            MOV RIGHT_ARROW,AL
            JMP END_IT
        
        DOWN_1:
		    MOV AL,DOWN_ARROW_PER
            MOV RIGHT_ARROW,AL
            JMP END_IT
			
		LEFT_1:
		    MOV AL,LEFT_ARROW_PER
            MOV RIGHT_ARROW,AL
            JMP END_IT
        
        END_IT:		
                      
   POPA
ENDM Select_RIGHT_1


;;--------------------------------------------W->1,2->S,3->A,4->D

Shuffle2 MACRO 
  PUSHA
        
		LEA SI,RAND_1

		;; randomize numbers with uniqueness
		RandUnique
		
		Select_UP_2 [SI]
		INC SI

		Select_DOWN_2 [SI]
		INC SI

		Select_LEFT_2 [SI]
		INC SI
		  
		Select_RIGHT_2 [SI]		
		
	    
  POPA	
ENDM Shuffle2

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
		    MOV AL,S_LETTER_PER
            MOV W_LETTER,AL
            JMP END_IT
        
        LEFT_2:
		    MOV AL,A_LETTER_PER
            MOV W_LETTER,AL
            JMP END_IT
			
		RIGHT_2:
		    MOV AL,D_LETTER_PER
            MOV W_LETTER,AL
            JMP END_IT
        		
        
        END_IT:

		
   POPA
ENDM Select_UP_2
;;--------------------------------------------

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
		    MOV AL,W_LETTER_PER
            MOV S_LETTER,AL
            JMP END_IT
        
        LEFT_2:
		    MOV AL,A_LETTER_PER
            MOV S_LETTER,AL
            JMP END_IT
			
		RIGHT_2:
		    MOV AL,D_LETTER_PER
            MOV S_LETTER,AL
            JMP END_IT
        
        END_IT:		
                      
   POPA
ENDM Select_DOWN_2
;;--------------------------------------------

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
		    MOV AL,W_LETTER_PER
            MOV A_LETTER,AL
            JMP END_IT
        
        DOWN_2:
		    MOV AL,S_LETTER_PER
            MOV A_LETTER,AL
            JMP END_IT
			
		RIGHT_2:
		    MOV AL,D_LETTER_PER
            MOV A_LETTER,AL
            JMP END_IT
        		
				
		END_IT:		
                      
   POPA
ENDM Select_LEFT_2
;;--------------------------------------------

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
		    MOV AL,W_LETTER_PER
            MOV D_LETTER,AL
            JMP END_IT
        
        DOWN_2:
		    MOV AL,S_LETTER_PER
            MOV D_LETTER,AL
            JMP END_IT
			
		LEFT_2:
		    MOV AL,A_LETTER_PER
            MOV D_LETTER,AL
            JMP END_IT
        		
				
		END_IT:		
                      
   POPA
ENDM Select_RIGHT_2


;;--------------------------------------------
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


