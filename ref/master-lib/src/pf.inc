;BFILE�\����
BFILE   	struc
	b_hdl	dw	?	; int		�t�@�C���n���h��
	b_left	dw	?	; unsigned	�o�b�t�@���̎c��f�[�^��
	b_pos	dw	?	; unsigned	���݂̃o�b�t�@��|�C���^
	b_siz	dw	?	; unsigned	�o�b�t�@�T�C�Y
	b_buff	db	?	; unsigned char[1] �ꊇ�ǂݍ��ݗp�o�b�t�@
BFILE	    	ends


;	�G���[�ԍ�
;	pferr	enum	{		; �G���[���
	PFEZERO = 0		; 0 �����l
	PFENOTOPEN = 1		; 1 �t�@�C�����I�[�v���ł��Ȃ�
	PFENOTFOUND= 2		; 2 �t�@�C�����p�b�N�t�@�C�����ɂȂ�
	PFENOMEM = 3		; 3 ���������m�ۂł��Ȃ�
	PFERESERVE0 = 4		; 4 �\��
	PFEUNKNOWN = 5		; 5 ���k�^�C�v���s��
	PFEILPFILE = 6 		; 6 �p�b�N�t�@�C����par�`���łȂ�
	PFEILEXE = 7		; 7 EXE�t�@�C�����s��
	PFEINTERNAL = 0ffh	; 255 �����G���[
;	}

; �o�b�t�@�T�C�Y�f�t�H���g�l
	BBUFSIZE equ	512

	CR	equ	0dh
	LF	equ	0ah
	EOF	equ	-1

;	�e��}�N��

	clr	macro	reg
		xor	reg, reg
		endm

	chk	macro	reg
		or	reg, reg
		endm

;----------------------------------------------------------------------------
;	for MS-DOS function call
;----------------------------------------------------------------------------

msdos	macro	req, param	; call msdos function
	ifnb	<param>
		mov	ax, req * 256 + param
	else
		mov	ah, req
	endif
		int	21h
	endm

DisplayChar		equ	02h	; �����̃X�N���[���o��
DisplayString		equ	09h	; �X�g�����O�̃X�N���[���o��
SetInterruptVector	equ	25h	; ���荞�݃x�N�^�̃Z�b�g
GetDate			equ	2ah	; ���t�𓾂�
KeepProcess		equ	31h	; �L�[�v�v���Z�X
GetInterruptVector	equ	35h	; ���荞�݃x�N�^�𓾂�
GetSetSwitch		equ	37h	; �X�C�b�`�L�����N�^�𓾂�/�Z�b�g����
CreateHandle		equ	3ch	; �n���h���̍쐬
OpenHandle		equ	3dh	; �n���h���̃I�[�v��
CloseHandle		equ	3eh	; �n���h���̃N���[�Y
ReadHandle		equ	3fh	; ���[�h�n���h��
WriteHandle		equ	40h	; ���C�g�n���h��
MoveFilePointer		equ	42h	; �t�@�C���|�C���^�̈ړ�
IOCTL			equ	44h	; IOCTL
DuplicateFileHandle	equ	45h	; �t�@�C���n���h���̓�d��
ForceDuplicateFileHandle equ	46h	; �t�@�C���n���h���̋�����d��
AllocateMemory		equ	48h	; �������̊��蓖��
FreeMemory		equ	49h	; ���蓖�Ă�ꂽ�������̉��
SetBlock		equ	4ah	; ���蓖�Ă�ꂽ�������u���b�N�̕ύX
EndProcess		equ	4ch	; �v���Z�X�̏I��
SetPSP			equ	50h	; PSP�A�h���X�̃Z�b�g
GetDOSarea		equ	52h	; �����ϐ��̈�̃A�h���X�̎擾
CopyPSP			equ	55h	; PSP�̕���
GetSetDateTimeofFile	equ	57h	; �t�@�C���̓��t/�����𓾂�/�Z�b�g����
LockUnlock		equ	5ch	; �t�@�C���A�N�Z�X�̃��b�N/�A�����b�N
GetPSP			equ	62h	; PSP���擾


;	PFILE�\����

PFILE   	struc
	pf_bf	dw	?	; BFILE�\���̂̃Z�O�����g
	pf_getc	dw	?	; int (near *)(pf_t) pfgetc()�p�֐�
	pf_getx	dw	?	; int (near *)(pf_t) getc�֐�
	pf_size	dd	?	; unsigned long		�p�b�N�T�C�Y
	pf_read	dd	?	; unsigned long		�Ǎ��񂾃o�C�g��(����)
	pf_home	dd	?	; unsigned long		�t�@�C���擪
	pf_loc	dd	?	; unsigned long		���P�[�V����(�_��)
	pf_osize dd	?	; unsigned long		�I���W�i���T�C�Y
;	pf_time	dd	?	; unsigned long		�^�C���X�^���v ��
	pf_cnt	dw	?	; int			�W�J�p���[�N
	pf_ch	dw	?	; int			�V
	pf_key	db	?	; unsigned char		�������p���[�N
				;			�������g�p
PFILE	    	ends