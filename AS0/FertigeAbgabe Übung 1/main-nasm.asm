;
;	to compile this code
;	first create an object file
;	nasm -f elf -o main.o main-nasm.asm
;
;	to create an executeable, link it
;	gcc -m32 -o run main.o
;
;	run it:
;	./run

global whileSchleife;
global forSchleife;

forSchleife:
    push ebp
    mov ebp,esp        ; Stackpointer auf Basispointer
    mov esi, [ebp +8]     ; value wird auf esi gelegt ebp+8
    push ebx
    mov ebx, [ebp +12]     ; result wird auf ebx gelegt ebp+12
    mov ecx, esi       ; counter 
    push ecx

loopBedingung:
    cmp ecx,1
    jae loop         ; ecx >= 1  , dann loop
    jb endloop         ; wenn kleiner, dann endloop
    
loop:
    mov edx,0        ; eax null setzen
    mov eax,esi        ; edx auf value setzen
    div ecx
    cmp edx,0
    je ohneRest        ; kein Rest vorhanden
    sub ecx,1        ; counter-1
    jmp loopBedingung

ohneRest:
    sub ecx,1        	;counter -1
    add dword [ebx],1       ;result +1 . An Stelle von ebx Wert um 1 erhöhen. dword : 32 Bit 
    jmp loopBedingung

endloop:             ; Hier wird der Stack wieder geleert.
    pop ecx
    pop ebx
    mov esp,ebp
    pop ebp
    ret
;-------------------------------------------------------------------------------------------------------------------------------------------------

whileSchleife:
	push ebp			;lege Basispointer auf dem Stack
	mov ebp, esp		;speichere den Stackzeiger in Basispointer
	push ebx			; sichere fluechtige Register 
	push 0 				; pusche null, um die Teiler zu zaehlen
	mov ebx, [ebp+8]	; speichere in ebx die Eingabe
	mov ecx, 1			; speichere in ecx 1, um die Teilen anzufangen

loopBedingung2:
	cmp ecx, ebx		; vergleiche die die Conter mit die Eingabe, wenn die beide gleich sind, wird die Schleife terminiert
	jl loop2 			; wenn ecx < ebx springe in loop
	je endloop2			; wenn ecx== ebx d.h. Conter gleich die Eingabe, dann springe in der Ende

loop2:
	mov eax, ebx		; speichere die Eingabe in eax fuer teilen
	mov edx, 0			; initiale edx, um den Rest zu bekommen
	div ecx				; devidiere mit Counter
	cmp edx, 0			; pruefe den Rest, on vorhanden ist
	je ohneRest2			; springe in ohneRest ,wenn es keinen Rest gibt
	jne mitRest2			; springe in mit Rest, wenn es Rest gibt

ohneRest2:
	pop eax             ; hier wird die vorher Null vom Stack in eax gespeichert fur das Inkrementieren, da ein Teiler gefunden wird
	inc eax
	push eax
	inc ecx
	jmp loopBedingung2

mitRest2:
	inc ecx				; hier inkremtiere nur die Counter
	jmp loopBedingung2

endloop2:
	pop eax			; entlerre den Stack
	inc eax 		; inkremtiere die Anzahl der Teiler, damit der Fall Zahl durch sich selbt relasieren.
	pop ebx
	pop ebp
	ret 			; Rueckgabe des Werts von eax
