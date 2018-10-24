#make_COM#

; COM file is loaded at CS:0100h
ORG 100h

mov ah,09
mov dx, offset msg
int 21h
mov ax,0h
mov ss,ax
mov ax,200h
mov sp,ax     
nxt:              
pusha
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
	
int 20h         ; terminate


msg     db 'Enter string  :  '
msg2    db 'Reverse string:  '

end