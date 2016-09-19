.386
PUBLIC @Bin@8
.model flat
.code
Print proto C
@Bin@8 proc
cld
			xor ah, ah 			
			mov edi, ecx
			mov al,','
			mov ecx, edx
			jmp met2
met:
		mov al, ','
		cmp byte ptr [edi],0
		je _end
			repne scasb
			jne _end
met2:			
			cmp byte ptr [edi],','
			je met
			cmp byte ptr [edi],0
			je met
			push ecx
			push edi
			mov ebx,edi
			repne scasb
			cmp ecx,0
			jne vari
			add edi,1
			vari:				
			push ebx
			push ecx
			push edi
			push ebx
			call Check
			pop ecx
			pop ebx			
			cmp eax,0
			je _next
			push edi
			push ebx
			call Print
			pop ebx 
			pop edi
_next:
			pop edi
			pop ecx			
			jmp met
_end:
ret
@Bin@8 endp

Check proc stdcall, a: dword, b: dword
local flag:dword
mov edx,a

mov al,byte ptr '0'
mov ah,byte ptr [edx]
cmp al,ah
jne _next
add edx,1

mov al,byte ptr 'b'
mov ah,byte ptr [edx]
cmp al,ah
jne _next
add edx,1

mov ecx,b
sub ecx,2
mov flag,1
cycle1:

cmp edx,ecx
jge _end

mov al,byte ptr '0'
mov ah,byte ptr [ecx]
cmp al,ah
jne _next1

mov al,byte ptr '0'
mov ah,byte ptr [edx]
cmp al,ah
jne _next2
_this:
sub ecx,1
add edx,1
jmp cycle1

_next1:
mov al,byte ptr '1'
mov ah,byte ptr [ecx]
cmp al,ah
je _this
mov flag,0

_next2:
mov al,byte ptr '1'
mov ah,byte ptr [edx]
cmp al,ah
je _this
mov flag,0

_next:
mov flag,0

_end:
mov eax,flag

ret
Check endp
end