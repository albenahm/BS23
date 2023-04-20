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

whileSchleife:
	push ebp			;lege Basispointer auf dem Stack
	mov ebp, esp		;speichere den Stackzeiger in Basispointer
	push ebx			; sichere fluechtige Register 
	push 0 				; pusche null, um die Teiler zu zaehlen
	mov ebx, [ebp+8]	; speichere in ebx die Eingabe
	mov ecx, 1			; speichere in ecx 1, um die Teilen anzufangen

loopBedingung:
	cmp ecx, ebx		; vergleiche die die Conter mit die Eingabe, wenn die beide gleich sind, wird die Schleife terminiert
	jl loop 			; wenn ecx < ebx springe in loop
	je endloop			; wenn ecx== ebx d.h. Conter gleich die Eingabe, dann springe in der Ende

loop:
	mov eax, ebx		; speichere die Eingabe in eax fuer teilen
	mov edx, 0			; initiale edx, um den Rest zu bekommen
	div ecx				; devidiere mit Counter
	cmp edx, 0			; pruefe den Rest, on vorhanden ist
	je ohneRest			; springe in ohneRest ,wenn es keinen Rest gibt
	jne mitRest			; springe in mit Rest, wenn es Rest gibt

ohneRest:
	pop eax             ; hier wird die vorher Null vom Stack in eax gespeichert fur das Inkrementieren, da ein Teiler gefunden wird
	inc eax
	push eax
	inc ecx
	jmp loopBedingung

mitRest:
	inc ecx				; hier inkremtiere nur die Counter
	jmp loopBedingung

endloop:
	pop eax			; entlerre den Stack
	inc eax 		; inkremtiere die Anzahl der Teiler, damit der Fall Zahl durch sich selbt relasieren.
	pop ebx
	pop ebp
	ret 			; Rueckgabe des Werts von eax