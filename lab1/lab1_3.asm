#make_COM#

; COM file is loaded at CS:0100h
ORG 100h

mov ah,09
mov dx, offset msg
int 21h

xor cx,cx      
nxt:
mov ah,01h
int 21h 
cmp cx,const  
je error         
cmp al,0dh             
je ent                 
push ax
inc cx
jmp nxt

ent:                   
push cx
mov ah,3               ;??????? ????????? ???????
int 10h
mov ah,2               ;??????? ?? ??. ??????
inc dh
xor dl,dl
int 10h
pop cx
mov ah,09
mov dx, offset msg2
int 21h
mov ah,02h
 
nx: 
	pop dx
	int 21h
	loop nx
jmp ed	
error:
	mov ah,3               ;??????? ????????? ???????
	int 10h
	mov ah,2               ;??????? ?? ??. ??????
	inc dh
	xor dl,dl
	int 10h
	mov ah,09
	mov dx, offset msge
	int 21h
ed:	
int 20h         ; terminate


msg     db 'Enter string  : $'
msg2    db 'Reverse string: $'
msge    db 'Error! Stack is full $'
const 	equ 7

end