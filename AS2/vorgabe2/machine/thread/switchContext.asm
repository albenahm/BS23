%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym switchContext

[GLOBAL switchContext]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; switchContext: Der Coroutinenwechsel
;
; C-Prototyp:
;
;     void switchContext (void*& from, void*& to);
;

switchContext:
;	fuegt hier Euren Code ein!
push ebp 		; setze Bsasispointer
mov ebp,esp  	;speicher den Stackzeiger in Bsasispointer

;lege die fluechtige Register auf dem Stack
push ebx
push edi
push esi

;speichere die Parameter from und to
mov eax, [ebp+8] ; from Adresse in eax speichern
mov [eax],esp ; transfiere Wert Stackpointer stack 1 in adresse von eax
mov eax, [ebp+12]; to  adresse in eax speichern
mov esp,[eax] ; speichere die adresse von eax in esp 

pop esi
pop edi
pop ebx
pop ebp

ret

	ret		; Ruecksprung zum Aufrufer

