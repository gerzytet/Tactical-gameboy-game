;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler 
; Version 4.2.2 #13350 (MINGW64)
;--------------------------------------------------------
	.module tactics
	.optsdcc -msm83
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _copy_window_buffer
	.globl _setup_background_palletes
	.globl _change_text
	.globl _set_sprite_palette
	.globl _set_bkg_palette
	.globl _vmemset
	.globl _set_sprite_data
	.globl _set_bkg_data
	.globl _display_off
	.globl _wait_vbl_done
	.globl _joypad
	.globl _letter_table
	.globl _displayTexts
	.globl _windowBuffer
	.globl _MAP
	.globl _palleteTable
	.globl _colors
	.globl _Letters
	.globl _Tiles
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
G$windowBuffer$0_0$0==.
_windowBuffer::
	.ds 64
Ltactics.change_text$tile$1_1$105==.
_change_text_tile_65537_105:
	.ds 1
Ltactics.main$x$1_2$122==.
_main_x_65538_122:
	.ds 1
Ltactics.main$y$1_2$122==.
_main_y_65538_122:
	.ds 1
Ltactics.main$cursorTimer$1_2$122==.
_main_cursorTimer_65538_122:
	.ds 1
Ltactics.main$joyTimer$1_2$122==.
_main_joyTimer_65538_122:
	.ds 1
Ltactics.main$cameraX$1_2$122==.
_main_cameraX_65538_122:
	.ds 1
Ltactics.main$cameraY$1_2$122==.
_main_cameraY_65538_122:
	.ds 1
Ltactics.main$target_scy$2_4$140==.
_main_target_scy_131076_140:
	.ds 1
Ltactics.main$target_scx$2_5$141==.
_main_target_scx_131077_141:
	.ds 1
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
G$displayTexts$0_0$0==.
_displayTexts::
	.ds 26
G$letter_table$0_0$0==.
_letter_table::
	.ds 26
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
	G$main$0$0	= .
	.globl	G$main$0$0
	C$tactics.c$167$1_2$116	= .
	.globl	C$tactics.c$167$1_2$116
;tactics.c:167: static uchar x = 0;
	ld	hl, #_main_x_65538_122
	ld	(hl), #0x00
	C$tactics.c$168$1_2$116	= .
	.globl	C$tactics.c$168$1_2$116
;tactics.c:168: static uchar y = 0;
	ld	hl, #_main_y_65538_122
	ld	(hl), #0x00
	C$tactics.c$170$1_2$116	= .
	.globl	C$tactics.c$170$1_2$116
;tactics.c:170: static uchar cursorTimer = 0;
	ld	hl, #_main_cursorTimer_65538_122
	ld	(hl), #0x00
	C$tactics.c$171$1_2$116	= .
	.globl	C$tactics.c$171$1_2$116
;tactics.c:171: static uchar joyTimer = 0;
	ld	hl, #_main_joyTimer_65538_122
	ld	(hl), #0x00
	C$tactics.c$173$1_2$116	= .
	.globl	C$tactics.c$173$1_2$116
;tactics.c:173: static uchar cameraX = 0;
	ld	hl, #_main_cameraX_65538_122
	ld	(hl), #0x00
	C$tactics.c$174$1_2$116	= .
	.globl	C$tactics.c$174$1_2$116
;tactics.c:174: static uchar cameraY = 0;
	ld	hl, #_main_cameraY_65538_122
	ld	(hl), #0x00
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	G$change_text$0$0	= .
	.globl	G$change_text$0$0
	C$tactics.c$99$0_0$103	= .
	.globl	C$tactics.c$99$0_0$103
;tactics.c:99: void change_text(uchar *text) {
;	---------------------------------
; Function change_text
; ---------------------------------
_change_text::
	dec	sp
	ld	c, e
	ld	b, d
	C$tactics.c$100$1_0$103	= .
	.globl	C$tactics.c$100$1_0$103
;tactics.c:100: if (text == NULL) {
	ld	a, b
	or	a, c
	C$tactics.c$101$2_0$104	= .
	.globl	C$tactics.c$101$2_0$104
;tactics.c:101: return;
	jr	Z, 00110$
	C$tactics.c$103$1_1$105	= .
	.globl	C$tactics.c$103$1_1$105
;tactics.c:103: volatile uchar *tilemap = &windowBuffer[0][0];
	C$tactics.c$105$4_1$109	= .
	.globl	C$tactics.c$105$4_1$109
;tactics.c:105: for (uchar i = 0; i < 6; i++) {
	ldhl	sp,	#0
	ld	(hl), #0x00
00108$:
	ldhl	sp,	#0
	ld	a, (hl)
	sub	a, #0x06
	jr	NC, 00110$
	C$tactics.c$106$3_1$107	= .
	.globl	C$tactics.c$106$3_1$107
;tactics.c:106: if (text[i] == ' ') {
	ld	l, (hl)
	ld	h, #0x00
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	a, (de)
	cp	a, #0x20
	jr	NZ, 00104$
	C$tactics.c$107$4_1$108	= .
	.globl	C$tactics.c$107$4_1$108
;tactics.c:107: tile = SPACE_LETTER;
	ld	hl, #_change_text_tile_65537_105
	ld	(hl), #0x2c
	jr	00105$
00104$:
	C$tactics.c$109$4_1$109	= .
	.globl	C$tactics.c$109$4_1$109
;tactics.c:109: tile = letter_table[text[i] - 'A'];
	add	a, #0xbf
	ld	e, a
	rlca
	sbc	a, a
	ld	d, a
	ld	hl, #_letter_table
	add	hl, de
	ld	a, (hl)
	ld	(#_change_text_tile_65537_105),a
00105$:
	C$tactics.c$111$3_1$107	= .
	.globl	C$tactics.c$111$3_1$107
;tactics.c:111: tilemap[i] = tile;
	ld	de, #_windowBuffer
	ldhl	sp,	#0
	ld	l, (hl)
	ld	h, #0x00
	add	hl, de
	ld	e, l
	ld	d, h
	ld	hl, #_change_text_tile_65537_105
	ld	a, (hl)
	ld	(de), a
	C$tactics.c$112$3_1$107	= .
	.globl	C$tactics.c$112$3_1$107
;tactics.c:112: tile++;
	inc	(hl)
	C$tactics.c$113$3_1$107	= .
	.globl	C$tactics.c$113$3_1$107
;tactics.c:113: tilemap[i|32] = tile;
	ldhl	sp,	#0
	ld	a, (hl)
	set	5, a
	add	a, #<(_windowBuffer)
	ld	e, a
	ld	a, #0x00
	adc	a, #>(_windowBuffer)
	ld	d, a
	ld	a, (#_change_text_tile_65537_105)
	ld	(de), a
	C$tactics.c$105$2_1$106	= .
	.globl	C$tactics.c$105$2_1$106
;tactics.c:105: for (uchar i = 0; i < 6; i++) {
	ldhl	sp,	#0
	inc	(hl)
	jr	00108$
00110$:
	C$tactics.c$115$2_1$103	= .
	.globl	C$tactics.c$115$2_1$103
;tactics.c:115: }
	inc	sp
	C$tactics.c$115$2_1$103	= .
	.globl	C$tactics.c$115$2_1$103
	XG$change_text$0$0	= .
	.globl	XG$change_text$0$0
	ret
G$Tiles$0_0$0 == .
_Tiles:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x0f	; 15
	.db #0x0c	; 12
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0c	; 12
	.db #0x3c	; 60
	.db #0x0c	; 12
	.db #0x3c	; 60
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0xf0	; 240
	.db #0x3f	; 63
	.db #0xf0	; 240
	.db #0x3f	; 63
	.db #0xc3	; 195
	.db #0xf3	; 243
	.db #0xc3	; 195
	.db #0xe3	; 227
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x0f	; 15
	.db #0x0c	; 12
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0c	; 12
	.db #0x3c	; 60
	.db #0x0c	; 12
	.db #0x3c	; 60
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xfc	; 252
	.db #0xc0	; 192
	.db #0xfc	; 252
	.db #0x0c	; 12
	.db #0xcc	; 204
	.db #0x4c	; 76	'L'
	.db #0xcc	; 204
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x02	; 2
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x33	; 51	'3'
	.db #0x00	; 0
	.db #0x33	; 51	'3'
	.db #0x03	; 3
	.db #0x3e	; 62
	.db #0x03	; 3
	.db #0x3f	; 63
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x1c	; 28
	.db #0x00	; 0
	.db #0x3c	; 60
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
	.db #0xf8	; 248
	.db #0x00	; 0
	.db #0xd8	; 216
	.db #0xa0	; 160
	.db #0xcc	; 204
	.db #0xf0	; 240
	.db #0xcc	; 204
	.db #0xf0	; 240
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xe0	; 224
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x02	; 2
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0xc3	; 195
	.db #0x00	; 0
	.db #0xc3	; 195
	.db #0x03	; 3
	.db #0x3f	; 63
	.db #0x03	; 3
	.db #0x3f	; 63
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0f	; 15
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x1c	; 28
	.db #0x00	; 0
	.db #0x3c	; 60
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xe0	; 224
	.db #0x00	; 0
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
	.db #0x18	; 24
	.db #0xe0	; 224
	.db #0x18	; 24
	.db #0xe0	; 224
	.db #0x38	; 56	'8'
	.db #0xc0	; 192
	.db #0xfc	; 252
	.db #0x00	; 0
	.db #0xdc	; 220
	.db #0xe0	; 224
	.db #0xcc	; 204
	.db #0xf0	; 240
	.db #0xcc	; 204
	.db #0xf0	; 240
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xe0	; 224
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x0c	; 12
	.db #0x0f	; 15
	.db #0x0c	; 12
	.db #0x0f	; 15
	.db #0x3f	; 63
	.db #0x30	; 48	'0'
	.db #0x3f	; 63
	.db #0x30	; 48	'0'
	.db #0xcf	; 207
	.db #0xf0	; 240
	.db #0xcf	; 207
	.db #0xf0	; 240
	.db #0x0c	; 12
	.db #0x33	; 51	'3'
	.db #0x0c	; 12
	.db #0x33	; 51	'3'
	.db #0x0c	; 12
	.db #0x33	; 51	'3'
	.db #0x0c	; 12
	.db #0x33	; 51	'3'
	.db #0x0c	; 12
	.db #0x33	; 51	'3'
	.db #0x0c	; 12
	.db #0x33	; 51	'3'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0x30	; 48	'0'
	.db #0xf0	; 240
	.db #0x30	; 48	'0'
	.db #0xf0	; 240
	.db #0xfc	; 252
	.db #0x0c	; 12
	.db #0xfc	; 252
	.db #0x0c	; 12
	.db #0xf3	; 243
	.db #0x0f	; 15
	.db #0xf3	; 243
	.db #0x0f	; 15
	.db #0x30	; 48	'0'
	.db #0xcc	; 204
	.db #0x30	; 48	'0'
	.db #0xcc	; 204
	.db #0x30	; 48	'0'
	.db #0xcc	; 204
	.db #0x30	; 48	'0'
	.db #0xcc	; 204
	.db #0x30	; 48	'0'
	.db #0xcc	; 204
	.db #0x30	; 48	'0'
	.db #0xcc	; 204
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x07	; 7
	.db #0x00	; 0
	.db #0x07	; 7
	.db #0x00	; 0
	.db #0x1f	; 31
	.db #0x00	; 0
	.db #0x1f	; 31
	.db #0x01	; 1
	.db #0x7e	; 126
	.db #0x03	; 3
	.db #0x7c	; 124
	.db #0x03	; 3
	.db #0xfc	; 252
	.db #0x07	; 7
	.db #0xfb	; 251
	.db #0x0f	; 15
	.db #0xf3	; 243
	.db #0x0f	; 15
	.db #0xf3	; 243
	.db #0x0f	; 15
	.db #0xf3	; 243
	.db #0x0f	; 15
	.db #0xf3	; 243
	.db #0x0f	; 15
	.db #0xf3	; 243
	.db #0x0f	; 15
	.db #0xf3	; 243
	.db #0x0f	; 15
	.db #0xf3	; 243
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0xfc	; 252
	.db #0x00	; 0
	.db #0xfc	; 252
	.db #0xc0	; 192
	.db #0x3f	; 63
	.db #0xf0	; 240
	.db #0x0f	; 15
	.db #0xf0	; 240
	.db #0xcf	; 207
	.db #0xf8	; 248
	.db #0xc7	; 199
	.db #0xfc	; 252
	.db #0xf3	; 243
	.db #0xfc	; 252
	.db #0xf3	; 243
	.db #0xfc	; 252
	.db #0xf3	; 243
	.db #0xfc	; 252
	.db #0xf3	; 243
	.db #0xfc	; 252
	.db #0xf3	; 243
	.db #0xfc	; 252
	.db #0xf3	; 243
	.db #0xfc	; 252
	.db #0xf3	; 243
	.db #0xfc	; 252
	.db #0xf3	; 243
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x14	; 20
	.db #0x1f	; 31
	.db #0x34	; 52	'4'
	.db #0x3f	; 63
	.db #0x34	; 52	'4'
	.db #0x3f	; 63
	.db #0x34	; 52	'4'
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x1f	; 31
	.db #0x20	; 32
	.db #0x1f	; 31
	.db #0x20	; 32
	.db #0x3c	; 60
	.db #0x3f	; 63
	.db #0x3c	; 60
	.db #0x3f	; 63
	.db #0x30	; 48	'0'
	.db #0x3f	; 63
	.db #0x30	; 48	'0'
	.db #0x3f	; 63
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x28	; 40
	.db #0xf8	; 248
	.db #0x2c	; 44
	.db #0xfc	; 252
	.db #0x2c	; 44
	.db #0xfc	; 252
	.db #0x2c	; 44
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0xf8	; 248
	.db #0x04	; 4
	.db #0xf8	; 248
	.db #0x04	; 4
	.db #0x3c	; 60
	.db #0xfc	; 252
	.db #0x3c	; 60
	.db #0xfc	; 252
	.db #0x0c	; 12
	.db #0xfc	; 252
	.db #0x0c	; 12
	.db #0xfc	; 252
	.db #0x0f	; 15
	.db #0x00	; 0
	.db #0x0d	; 13
	.db #0x02	; 2
	.db #0x3f	; 63
	.db #0x00	; 0
	.db #0x3f	; 63
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xf7	; 247
	.db #0x08	; 8
	.db #0xbf	; 191
	.db #0x40	; 64
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xed	; 237
	.db #0x12	; 18
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0xd0	; 208
	.db #0x20	; 32
	.db #0xfc	; 252
	.db #0x00	; 0
	.db #0x74	; 116	't'
	.db #0x88	; 136
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xdd	; 221
	.db #0x22	; 34
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xf7	; 247
	.db #0x08	; 8
	.db #0xc0	; 192
	.db #0x40	; 64
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x0c	; 12
	.db #0xc3	; 195
	.db #0x0c	; 12
	.db #0xc3	; 195
	.db #0x7d	; 125
	.db #0x82	; 130
	.db #0xef	; 239
	.db #0x10	; 16
	.db #0x20	; 32
	.db #0xc3	; 195
	.db #0x20	; 32
	.db #0xc3	; 195
	.db #0xf7	; 247
	.db #0x08	; 8
	.db #0xbe	; 190
	.db #0x41	; 65	'A'
	.db #0x00	; 0
	.db #0xf3	; 243
	.db #0x00	; 0
	.db #0xf3	; 243
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x0c	; 12
	.db #0x30	; 48	'0'
	.db #0x0c	; 12
	.db #0x30	; 48	'0'
	.db #0xf7	; 247
	.db #0x08	; 8
	.db #0xbe	; 190
	.db #0x41	; 65	'A'
	.db #0x00	; 0
	.db #0x1c	; 28
	.db #0x00	; 0
	.db #0x1c	; 28
	.db #0xdf	; 223
	.db #0x20	; 32
	.db #0xfb	; 251
	.db #0x04	; 4
	.db #0x30	; 48	'0'
	.db #0x0c	; 12
	.db #0x30	; 48	'0'
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x22	; 34
	.db #0x01	; 1
	.db #0x26	; 38
	.db #0x01	; 1
	.db #0x22	; 34
	.db #0x55	; 85	'U'
	.db #0xa2	; 162
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x55	; 85	'U'
	.db #0xaa	; 170
	.db #0x55	; 85	'U'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x11	; 17
	.db #0x2c	; 44
	.db #0x53	; 83	'S'
	.db #0x2c	; 44
	.db #0x53	; 83	'S'
	.db #0xad	; 173
	.db #0x52	; 82	'R'
	.db #0xed	; 237
	.db #0x12	; 18
	.db #0xcd	; 205
	.db #0x32	; 50	'2'
	.db #0xcd	; 205
	.db #0x32	; 50	'2'
	.db #0xcd	; 205
	.db #0x32	; 50	'2'
	.db #0xcd	; 205
	.db #0x32	; 50	'2'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x30	; 48	'0'
	.db #0x30	; 48	'0'
	.db #0x30	; 48	'0'
	.db #0x30	; 48	'0'
	.db #0x00	; 0
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0xf0	; 240
	.db #0x30	; 48	'0'
	.db #0xf0	; 240
	.db #0x30	; 48	'0'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0xc0	; 192
	.db #0xf0	; 240
	.db #0xc0	; 192
	.db #0x03	; 3
	.db #0x33	; 51	'3'
	.db #0x03	; 3
	.db #0x33	; 51	'3'
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0xc0	; 192
	.db #0xf0	; 240
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x01	; 1
	.db #0x08	; 8
	.db #0x07	; 7
	.db #0x00	; 0
	.db #0x1f	; 31
	.db #0x00	; 0
	.db #0x3f	; 63
	.db #0x40	; 64
	.db #0x3f	; 63
	.db #0x80	; 128
	.db #0x7f	; 127
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x80	; 128
	.db #0x7f	; 127
	.db #0x40	; 64
	.db #0x3f	; 63
	.db #0x00	; 0
	.db #0x3f	; 63
	.db #0x00	; 0
	.db #0x1f	; 31
	.db #0x08	; 8
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x03	; 3
	.db #0x40	; 64
	.db #0x80	; 128
	.db #0x10	; 16
	.db #0xe0	; 224
	.db #0x08	; 8
	.db #0xf0	; 240
	.db #0x04	; 4
	.db #0xf8	; 248
	.db #0x02	; 2
	.db #0xfc	; 252
	.db #0x00	; 0
	.db #0xfe	; 254
	.db #0x01	; 1
	.db #0xfe	; 254
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x01	; 1
	.db #0xfe	; 254
	.db #0x01	; 1
	.db #0xfe	; 254
	.db #0x02	; 2
	.db #0xfc	; 252
	.db #0x02	; 2
	.db #0xfc	; 252
	.db #0x00	; 0
	.db #0xfc	; 252
	.db #0x00	; 0
	.db #0xf8	; 248
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
	.db #0x20	; 32
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x30	; 48	'0'
	.db #0x33	; 51	'3'
	.db #0x30	; 48	'0'
	.db #0x31	; 49	'1'
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x4c	; 76	'L'
	.db #0x03	; 3
	.db #0x63	; 99	'c'
	.db #0x03	; 3
	.db #0x73	; 115	's'
	.db #0x03	; 3
	.db #0x73	; 115	's'
	.db #0x03	; 3
	.db #0x63	; 99	'c'
	.db #0x0c	; 12
	.db #0x4c	; 76	'L'
	.db #0x0c	; 12
	.db #0x0c	; 12
	.db #0x30	; 48	'0'
	.db #0x31	; 49	'1'
	.db #0x30	; 48	'0'
	.db #0x33	; 51	'3'
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0xe1	; 225
	.db #0x0c	; 12
	.db #0xcc	; 204
	.db #0x0c	; 12
	.db #0x8c	; 140
	.db #0x30	; 48	'0'
	.db #0x30	; 48	'0'
	.db #0x30	; 48	'0'
	.db #0x32	; 50	'2'
	.db #0xc0	; 192
	.db #0xc6	; 198
	.db #0xc0	; 192
	.db #0xce	; 206
	.db #0xc0	; 192
	.db #0xce	; 206
	.db #0xc0	; 192
	.db #0xc6	; 198
	.db #0x30	; 48	'0'
	.db #0x32	; 50	'2'
	.db #0x30	; 48	'0'
	.db #0x30	; 48	'0'
	.db #0x0c	; 12
	.db #0x8c	; 140
	.db #0x0c	; 12
	.db #0xcc	; 204
	.db #0x00	; 0
	.db #0xe1	; 225
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0xfc	; 252
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x03	; 3
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x3f	; 63
	.db #0x54	; 84	'T'
	.db #0xfc	; 252
	.db #0xa8	; 168
	.db #0xfc	; 252
	.db #0x40	; 64
	.db #0xc0	; 192
	.db #0x80	; 128
	.db #0xc0	; 192
	.db #0x40	; 64
	.db #0xc0	; 192
	.db #0x80	; 128
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x80	; 128
	.db #0xc0	; 192
	.db #0x40	; 64
	.db #0xc0	; 192
	.db #0x80	; 128
	.db #0xc0	; 192
	.db #0x40	; 64
	.db #0xc0	; 192
	.db #0xa8	; 168
	.db #0xfc	; 252
	.db #0x54	; 84	'T'
	.db #0xfc	; 252
	.db #0x2a	; 42
	.db #0x3f	; 63
	.db #0x15	; 21
	.db #0x3f	; 63
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x03	; 3
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x01	; 1
	.db #0x03	; 3
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x03	; 3
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x15	; 21
	.db #0x3f	; 63
	.db #0x2a	; 42
	.db #0x3f	; 63
G$Letters$0_0$0 == .
_Letters:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x0e	; 14
	.db #0x00	; 0
	.db #0x1e	; 30
	.db #0x00	; 0
	.db #0x32	; 50	'2'
	.db #0x00	; 0
	.db #0x32	; 50	'2'
	.db #0x40	; 64
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x6e	; 110	'n'
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x72	; 114	'r'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x46	; 70	'F'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x46	; 70	'F'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x1e	; 30
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x70	; 112	'p'
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x70	; 112	'p'
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x1e	; 30
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x6e	; 110	'n'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x70	; 112	'p'
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x70	; 112	'p'
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x1e	; 30
	.db #0x00	; 0
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x40	; 64
	.db #0x00	; 0
	.db #0x4c	; 76	'L'
	.db #0x00	; 0
	.db #0x4e	; 78	'N'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x3c	; 60
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x6c	; 108	'l'
	.db #0x00	; 0
	.db #0x68	; 104	'h'
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x6c	; 108	'l'
	.db #0x00	; 0
	.db #0x6c	; 108	'l'
	.db #0x00	; 0
	.db #0x6e	; 110	'n'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x72	; 114	'r'
	.db #0x00	; 0
	.db #0x56	; 86	'V'
	.db #0x00	; 0
	.db #0x56	; 86	'V'
	.db #0x00	; 0
	.db #0x5a	; 90	'Z'
	.db #0x00	; 0
	.db #0x5a	; 90	'Z'
	.db #0x00	; 0
	.db #0x4a	; 74	'J'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x46	; 70	'F'
	.db #0x00	; 0
	.db #0x46	; 70	'F'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x72	; 114	'r'
	.db #0x00	; 0
	.db #0x7a	; 122	'z'
	.db #0x10	; 16
	.db #0x6a	; 106	'j'
	.db #0x10	; 16
	.db #0x6a	; 106	'j'
	.db #0x00	; 0
	.db #0x6a	; 106	'j'
	.db #0x00	; 0
	.db #0x6a	; 106	'j'
	.db #0x00	; 0
	.db #0x6a	; 106	'j'
	.db #0x00	; 0
	.db #0x6a	; 106	'j'
	.db #0x04	; 4
	.db #0x62	; 98	'b'
	.db #0x04	; 4
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x3c	; 60
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x3c	; 60
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x6c	; 108	'l'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x70	; 112	'p'
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x60	; 96
	.db #0x00	; 0
	.db #0x30	; 48	'0'
	.db #0x00	; 0
	.db #0x3c	; 60
	.db #0x00	; 0
	.db #0x0e	; 14
	.db #0x00	; 0
	.db #0x06	; 6
	.db #0x00	; 0
	.db #0x0e	; 14
	.db #0x00	; 0
	.db #0x7c	; 124
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x22	; 34
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x14	; 20
	.db #0x00	; 0
	.db #0x08	; 8
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x42	; 66	'B'
	.db #0x00	; 0
	.db #0x52	; 82	'R'
	.db #0x00	; 0
	.db #0x52	; 82	'R'
	.db #0x00	; 0
	.db #0x5a	; 90	'Z'
	.db #0x00	; 0
	.db #0x5a	; 90	'Z'
	.db #0x04	; 4
	.db #0x52	; 82	'R'
	.db #0x00	; 0
	.db #0x34	; 52	'4'
	.db #0x00	; 0
	.db #0x14	; 20
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x62	; 98	'b'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x66	; 102	'f'
	.db #0x00	; 0
	.db #0x26	; 38
	.db #0x00	; 0
	.db #0x3e	; 62
	.db #0x00	; 0
	.db #0x1c	; 28
	.db #0x00	; 0
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x04	; 4
	.db #0x00	; 0
	.db #0x7e	; 126
	.db #0x00	; 0
	.db #0x4c	; 76	'L'
	.db #0x00	; 0
	.db #0x78	; 120	'x'
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
G$colors$0_0$0 == .
_colors:
	.dw #0x7fff
	.dw #0x5294
	.dw #0x294a
	.dw #0x0000
	.dw #0x7fff
	.dw #0x22e7
	.dw #0x19c4
	.dw #0x01b3
	.dw #0x7fff
	.dw #0x4210
	.dw #0x054d
	.dw #0x00d9
	.dw #0x7fff
	.dw #0x15ef
	.dw #0x054d
	.dw #0x14a5
	.dw #0x17bc
	.dw #0x22e7
	.dw #0x19c4
	.dw #0x14e0
	.dw #0x17bc
	.dw #0x22e7
	.dw #0x19c4
	.dw #0x14e0
	.dw #0x17bc
	.dw #0x22e7
	.dw #0x19c4
	.dw #0x14e0
	.dw #0x17bc
	.dw #0x22e7
	.dw #0x19c4
	.dw #0x14e0
G$palleteTable$0_0$0 == .
_palleteTable:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x02	; 2
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x00	; 0
G$MAP$0_0$0 == .
_MAP:
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x05	; 5
	.db #0x08	; 8
	.db #0x04	; 4
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x00	; 0
	.db #0x01	; 1
	.db #0x04	; 4
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x05	; 5
	.db #0x06	; 6
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x04	; 4
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x07	; 7
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x07	; 7
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x07	; 7
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x07	; 7
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x0b	; 11
	.db #0x0c	; 12
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x07	; 7
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x07	; 7
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x07	; 7
	.db #0x07	; 7
	.db #0x04	; 4
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x05	; 5
	.db #0x06	; 6
	.db #0x09	; 9
	.db #0x09	; 9
	.db #0x04	; 4
	.db #0x0a	; 10
	.db #0x02	; 2
	.db #0x03	; 3
	G$setup_background_palletes$0$0	= .
	.globl	G$setup_background_palletes$0$0
	C$tactics.c$125$2_1$110	= .
	.globl	C$tactics.c$125$2_1$110
;tactics.c:125: void setup_background_palletes() {
;	---------------------------------
; Function setup_background_palletes
; ---------------------------------
_setup_background_palletes::
	add	sp, #-6
	C$tactics.c$126$1_0$110	= .
	.globl	C$tactics.c$126$1_0$110
;tactics.c:126: VBK_REG = VBK_BANK_1;
	ld	a, #0x01
	ldh	(_VBK_REG + 0), a
	C$tactics.c$129$5_1$115	= .
	.globl	C$tactics.c$129$5_1$115
;tactics.c:129: for (uchar r = 0; r < HEIGHT * 2; r++) {
	ldhl	sp,	#4
	ld	(hl), #0x00
00107$:
	ldhl	sp,	#4
	ld	a, (hl)
	sub	a, #0x18
	jp	NC, 00102$
	C$tactics.c$130$1_1$110	= .
	.globl	C$tactics.c$130$1_1$110
;tactics.c:130: for (uchar c = 0; c < WIDTH * 2; c++) {
	inc	hl
	ld	(hl), #0x00
00104$:
	ldhl	sp,	#5
	ld	a, (hl)
	sub	a, #0x18
	jp	NC, 00108$
	C$tactics.c$131$5_1$115	= .
	.globl	C$tactics.c$131$5_1$115
;tactics.c:131: uchar tile = MAP[r/2][c/2];
	dec	hl
	ld	a, (hl)
	ldhl	sp,	#0
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl+)
	inc	hl
	ld	(hl-), a
	ld	a, (hl+)
	inc	hl
	ld	(hl-), a
	dec	hl
	bit	7, (hl)
	jr	Z, 00111$
	pop	de
	push	de
	ld	l, e
	ld	h, d
	inc	hl
	push	hl
	ld	a, l
	ldhl	sp,	#4
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#3
	ld	(hl), a
00111$:
	ldhl	sp,#2
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	sra	b
	rr	c
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	bc,#_MAP
	add	hl,bc
	push	hl
	ld	a, l
	ldhl	sp,	#4
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#3
	ld	(hl+), a
	inc	hl
	ld	c, (hl)
	ld	b, #0x00
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	bit	7, b
	jr	Z, 00112$
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
00112$:
	ld	e, l
	ld	d, h
	sra	d
	rr	e
	ldhl	sp,	#2
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	e, l
	ld	d, h
	ld	a, (de)
	ld	e, a
	C$tactics.c$132$5_1$115	= .
	.globl	C$tactics.c$132$5_1$115
;tactics.c:132: uchar pal = palleteTable[tile];
	ld	hl, #_palleteTable
	ld	d, #0x00
	add	hl, de
	ld	e, (hl)
	C$tactics.c$133$5_1$115	= .
	.globl	C$tactics.c$133$5_1$115
;tactics.c:133: tilemap[r*32 + c] = pal;
	ldhl	sp,	#0
	ld	a, (hl+)
	ld	d, (hl)
	add	a, a
	rl	d
	add	a, a
	rl	d
	add	a, a
	rl	d
	add	a, a
	rl	d
	add	a, a
	rl	d
	ld	l, a
	ld	h, d
	add	hl, bc
	ld	bc, #0x9800
	add	hl, bc
	ld	(hl), e
	C$tactics.c$130$4_1$114	= .
	.globl	C$tactics.c$130$4_1$114
;tactics.c:130: for (uchar c = 0; c < WIDTH * 2; c++) {
	ldhl	sp,	#5
	inc	(hl)
	jp	00104$
00108$:
	C$tactics.c$129$2_1$112	= .
	.globl	C$tactics.c$129$2_1$112
;tactics.c:129: for (uchar r = 0; r < HEIGHT * 2; r++) {
	ldhl	sp,	#4
	inc	(hl)
	jp	00107$
00102$:
	C$tactics.c$137$1_1$111	= .
	.globl	C$tactics.c$137$1_1$111
;tactics.c:137: VBK_REG = VBK_BANK_0;
	xor	a, a
	ldh	(_VBK_REG + 0), a
	C$tactics.c$138$1_1$110	= .
	.globl	C$tactics.c$138$1_1$110
;tactics.c:138: }
	add	sp, #6
	C$tactics.c$138$1_1$110	= .
	.globl	C$tactics.c$138$1_1$110
	XG$setup_background_palletes$0$0	= .
	.globl	XG$setup_background_palletes$0$0
	ret
	G$main$0$0	= .
	.globl	G$main$0$0
	C$tactics.c$142$1_1$116	= .
	.globl	C$tactics.c$142$1_1$116
;tactics.c:142: void main() {
;	---------------------------------
; Function main
; ---------------------------------
_main::
	add	sp, #-13
	C$tactics.c$143$1_0$116	= .
	.globl	C$tactics.c$143$1_0$116
;tactics.c:143: wait_vbl_done();
	call	_wait_vbl_done
	C$tactics.c$144$1_0$116	= .
	.globl	C$tactics.c$144$1_0$116
;tactics.c:144: display_off();
	call	_display_off
	C$tactics.c$145$1_0$116	= .
	.globl	C$tactics.c$145$1_0$116
;tactics.c:145: LCDC_REG = 0x00;
	xor	a, a
	ldh	(_LCDC_REG + 0), a
	C$tactics.c$146$1_0$116	= .
	.globl	C$tactics.c$146$1_0$116
;tactics.c:146: set_bkg_data(48, 60, Tiles); //tiles.  15 big tiles, 60 small tiles
	ld	de, #_Tiles
	push	de
	ld	hl, #0x3c30
	push	hl
	call	_set_bkg_data
	add	sp, #4
	C$tactics.c$147$1_0$116	= .
	.globl	C$tactics.c$147$1_0$116
;tactics.c:147: set_bkg_data(0, 46, Letters); //letters. 46 tiles.  23 letters
	ld	de, #_Letters
	push	de
	ld	hl, #0x2e00
	push	hl
	call	_set_bkg_data
	add	sp, #4
	C$tactics.c$150$5_1$121	= .
	.globl	C$tactics.c$150$5_1$121
;tactics.c:150: for (uchar r = 0; r < HEIGHT * 2; r++) {
	ldhl	sp,	#11
	ld	(hl), #0x00
00180$:
	ldhl	sp,	#11
	ld	a, (hl)
	sub	a, #0x18
	jp	NC, 00102$
	C$tactics.c$151$1_2$116	= .
	.globl	C$tactics.c$151$1_2$116
;tactics.c:151: for (uchar c = 0; c < WIDTH * 2; c++) {
	inc	hl
	ld	(hl), #0x00
00177$:
	ldhl	sp,	#12
	ld	a, (hl)
	sub	a, #0x18
	jp	NC, 00181$
	C$tactics.c$152$1_2$116	= .
	.globl	C$tactics.c$152$1_2$116
;tactics.c:152: uchar map = (MAP[r/2][c/2] + FIRST_TILE_OFFSET_2x2)*4;
	dec	hl
	ld	a, (hl)
	ldhl	sp,	#4
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl)
	ldhl	sp,	#9
	ld	(hl), a
	ldhl	sp,	#5
	ld	a, (hl)
	ldhl	sp,	#10
	ld	(hl), a
	ldhl	sp,	#5
	bit	7, (hl)
	jr	Z, 00184$
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	l, e
	ld	h, d
	inc	hl
	push	hl
	ld	a, l
	ldhl	sp,	#11
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#10
	ld	(hl), a
00184$:
	ldhl	sp,#9
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	sra	b
	rr	c
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	bc,#_MAP
	add	hl,bc
	inc	sp
	inc	sp
	push	hl
	ldhl	sp,	#12
	ld	a, (hl)
	ldhl	sp,	#6
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	bit	7, (hl)
	jr	Z, 00185$
	dec	hl
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	inc	bc
00185$:
	ldhl	sp,	#2
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
	sra	(hl)
	dec	hl
	rr	(hl)
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	pop	hl
	push	hl
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#11
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#10
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	a, (de)
	ld	(hl), a
	ld	a, (hl)
	add	a, #0x0c
	add	a, a
	add	a, a
	C$tactics.c$153$5_1$121	= .
	.globl	C$tactics.c$153$5_1$121
;tactics.c:153: uchar value = map + (r&1) + (c&1)*2;
	ld	(hl+), a
	ld	a, (hl-)
	dec	hl
	and	a, #0x01
	ld	(hl+), a
	ld	a, (hl-)
	add	a, (hl)
	dec	hl
	ld	(hl), a
	ldhl	sp,	#12
	ld	a, (hl-)
	dec	hl
	ld	(hl), a
	ld	a, (hl)
	and	a, #0x01
	ld	(hl), a
	sla	(hl)
	ld	a, (hl-)
	dec	hl
	add	a, (hl)
	inc	hl
	inc	hl
	ld	(hl), a
	C$tactics.c$154$5_1$121	= .
	.globl	C$tactics.c$154$5_1$121
;tactics.c:154: tilemap[r*32 + c] = value;
	ldhl	sp,	#4
	ld	a, (hl)
	ldhl	sp,	#8
	ld	(hl), a
	ldhl	sp,	#5
	ld	a, (hl)
	ldhl	sp,	#9
	ld	(hl), a
	ld	a, #0x05
00333$:
	ldhl	sp,	#8
	sla	(hl)
	inc	hl
	rl	(hl)
	dec	a
	jr	NZ, 00333$
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ldhl	sp,	#6
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#6
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#5
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #0x9800
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#10
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#9
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	a, (hl+)
	ld	d, a
	C$tactics.c$151$4_1$120	= .
	.globl	C$tactics.c$151$4_1$120
;tactics.c:151: for (uchar c = 0; c < WIDTH * 2; c++) {
	ld	a, (hl+)
	inc	hl
	ld	(de), a
	inc	(hl)
	jp	00177$
00181$:
	C$tactics.c$150$2_1$118	= .
	.globl	C$tactics.c$150$2_1$118
;tactics.c:150: for (uchar r = 0; r < HEIGHT * 2; r++) {
	ldhl	sp,	#11
	inc	(hl)
	jp	00180$
00102$:
	C$tactics.c$157$1_1$117	= .
	.globl	C$tactics.c$157$1_1$117
;tactics.c:157: set_sprite_data(0, 8, Tiles + (CURSOR1 * 16 * 4));
	ld	de, #(_Tiles + 832)
	push	de
	ld	hl, #0x800
	push	hl
	call	_set_sprite_data
	add	sp, #4
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1602: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 2)
	ld	(hl), #0x00
	ld	hl, #(_shadow_OAM + 6)
	ld	(hl), #0x01
	ld	hl, #(_shadow_OAM + 10)
	ld	(hl), #0x02
	ld	hl, #(_shadow_OAM + 14)
	ld	(hl), #0x03
	C$tactics.c$163$1_1$117	= .
	.globl	C$tactics.c$163$1_1$117
;tactics.c:163: vmemset((uchar *)WIN_TILEMAP_START, SPACE_LETTER, 32*32);
	ld	de, #0x0400
	push	de
	ld	a, #0x2c
	push	af
	inc	sp
	ld	de, #0x9c00
	push	de
	call	_vmemset
	add	sp, #5
	C$tactics.c$165$1_1$117	= .
	.globl	C$tactics.c$165$1_1$117
;tactics.c:165: change_text("FOREST");
	ld	de, #___str_0
	call	_change_text
	C$tactics.c$179$1_2$122	= .
	.globl	C$tactics.c$179$1_2$122
;tactics.c:179: setup_background_palletes();
	call	_setup_background_palletes
	C$tactics.c$181$1_2$122	= .
	.globl	C$tactics.c$181$1_2$122
;tactics.c:181: set_bkg_palette(0, 8, colors);
	ld	de, #_colors
	push	de
	ld	hl, #0x800
	push	hl
	call	_set_bkg_palette
	add	sp, #4
	C$tactics.c$182$1_2$122	= .
	.globl	C$tactics.c$182$1_2$122
;tactics.c:182: set_sprite_palette(0, 1, colors);
	ld	de, #_colors
	push	de
	xor	a, a
	inc	a
	push	af
	call	_set_sprite_palette
	add	sp, #4
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1648: shadow_OAM[nb].prop=prop;
	ld	hl, #(_shadow_OAM + 3)
	ld	(hl), #0x00
	C$tactics.c$185$1_2$122	= .
	.globl	C$tactics.c$185$1_2$122
;tactics.c:185: IE_REG = IEF_VBLANK;
	ld	a, #0x01
	ldh	(_IE_REG + 0), a
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:727: __asm__("ei");
	ei
	C$tactics.c$188$1_2$122	= .
	.globl	C$tactics.c$188$1_2$122
;tactics.c:188: LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00;
	ld	a, #0xc3
	ldh	(_LCDC_REG + 0), a
	C$tactics.c$189$1_2$122	= .
	.globl	C$tactics.c$189$1_2$122
;tactics.c:189: while (1) {
00156$:
	C$tactics.c$191$2_2$123	= .
	.globl	C$tactics.c$191$2_2$123
;tactics.c:191: if (joyTimer > 0) {
	ld	hl, #_main_joyTimer_65538_122
	ld	a, (hl)
	or	a, a
	jr	Z, 00125$
	C$tactics.c$192$3_2$124	= .
	.globl	C$tactics.c$192$3_2$124
;tactics.c:192: joyTimer--;
	dec	(hl)
	jr	00126$
00125$:
	C$tactics.c$194$3_2$125	= .
	.globl	C$tactics.c$194$3_2$125
;tactics.c:194: uchar joy = joypad();
	call	_joypad
	ld	c, a
	C$tactics.c$195$3_2$125	= .
	.globl	C$tactics.c$195$3_2$125
;tactics.c:195: if (joy & J_LEFT) {
	bit	1, c
	jr	Z, 00120$
	C$tactics.c$196$4_2$126	= .
	.globl	C$tactics.c$196$4_2$126
;tactics.c:196: if (x > 0) {
	ld	hl, #_main_x_65538_122
	ld	a, (hl)
	or	a, a
	jr	Z, 00121$
	C$tactics.c$197$5_2$127	= .
	.globl	C$tactics.c$197$5_2$127
;tactics.c:197: x--;
	dec	(hl)
	jr	00121$
00120$:
	C$tactics.c$199$3_2$125	= .
	.globl	C$tactics.c$199$3_2$125
;tactics.c:199: } else if (joy & J_RIGHT) {
	bit	0, c
	jr	Z, 00117$
	C$tactics.c$200$4_2$128	= .
	.globl	C$tactics.c$200$4_2$128
;tactics.c:200: if (x < WIDTH - 1) {
	ld	hl, #_main_x_65538_122
	ld	a, (hl)
	sub	a, #0x0b
	jr	NC, 00121$
	C$tactics.c$201$5_2$129	= .
	.globl	C$tactics.c$201$5_2$129
;tactics.c:201: x++;
	inc	(hl)
	jr	00121$
00117$:
	C$tactics.c$203$3_2$125	= .
	.globl	C$tactics.c$203$3_2$125
;tactics.c:203: } else if (joy & J_UP) {
	bit	2, c
	jr	Z, 00114$
	C$tactics.c$204$4_2$130	= .
	.globl	C$tactics.c$204$4_2$130
;tactics.c:204: if (y > 0) {
	ld	hl, #_main_y_65538_122
	ld	a, (hl)
	or	a, a
	jr	Z, 00121$
	C$tactics.c$205$5_2$131	= .
	.globl	C$tactics.c$205$5_2$131
;tactics.c:205: y--;
	dec	(hl)
	jr	00121$
00114$:
	C$tactics.c$207$3_2$125	= .
	.globl	C$tactics.c$207$3_2$125
;tactics.c:207: } else if (joy & J_DOWN) {
	bit	3, c
	jr	Z, 00121$
	C$tactics.c$208$4_2$132	= .
	.globl	C$tactics.c$208$4_2$132
;tactics.c:208: if (y < HEIGHT - 1) {
	ld	hl, #_main_y_65538_122
	ld	a, (hl)
	sub	a, #0x0b
	jr	NC, 00121$
	C$tactics.c$209$5_2$133	= .
	.globl	C$tactics.c$209$5_2$133
;tactics.c:209: y++;
	inc	(hl)
00121$:
	C$tactics.c$212$3_2$125	= .
	.globl	C$tactics.c$212$3_2$125
;tactics.c:212: if (joy != 0) {
	ld	a, c
	or	a, a
	jr	Z, 00126$
	C$tactics.c$213$4_2$134	= .
	.globl	C$tactics.c$213$4_2$134
;tactics.c:213: joyTimer = 10;
	ld	hl, #_main_joyTimer_65538_122
	ld	(hl), #0x0a
00126$:
	C$tactics.c$217$2_3$135	= .
	.globl	C$tactics.c$217$2_3$135
;tactics.c:217: uchar coord = MAP[y][x];
	ld	hl, #_main_y_65538_122
	ld	c, (hl)
	ld	b, #0x00
	ld	l, c
	ld	h, b
	add	hl, hl
	add	hl, bc
	add	hl, hl
	add	hl, hl
	ld	bc,#_MAP
	add	hl,bc
	ld	c, l
	ld	b, h
	ld	hl, #_main_x_65538_122
	ld	l, (hl)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
	add	hl, bc
	ld	c, (hl)
	C$tactics.c$218$2_3$135	= .
	.globl	C$tactics.c$218$2_3$135
;tactics.c:218: uchar *text = (uchar *)displayTexts[coord];
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ld	l, c
	add	hl, hl
	ld	de, #_displayTexts
	add	hl, de
	ld	a, (hl+)
	ld	c, a
	ld	b, (hl)
	C$tactics.c$219$2_3$135	= .
	.globl	C$tactics.c$219$2_3$135
;tactics.c:219: change_text(text);
	ld	e, c
	ld	d, b
	call	_change_text
	C$tactics.c$221$2_3$135	= .
	.globl	C$tactics.c$221$2_3$135
;tactics.c:221: if (x < cameraX) {
	ld	a, (#_main_x_65538_122)
	ld	hl, #_main_cameraX_65538_122
	sub	a, (hl)
	jr	NC, 00130$
	C$tactics.c$222$3_3$136	= .
	.globl	C$tactics.c$222$3_3$136
;tactics.c:222: cameraX--;
	dec	(hl)
	jr	00131$
00130$:
	C$tactics.c$223$2_3$135	= .
	.globl	C$tactics.c$223$2_3$135
;tactics.c:223: } else if (x >= cameraX + 10) {
	ld	a, (#_main_cameraX_65538_122)
	ld	b, #0x00
	add	a, #0x0a
	ld	c, a
	jr	NC, 00338$
	inc	b
00338$:
	ld	hl, #_main_x_65538_122
	ld	l, (hl)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ld	e, b
	ld	d, h
	ld	a, l
	sub	a, c
	ld	a, h
	sbc	a, b
	bit	7, e
	jr	Z, 00339$
	bit	7, d
	jr	NZ, 00340$
	cp	a, a
	jr	00340$
00339$:
	bit	7, d
	jr	Z, 00340$
	scf
00340$:
	jr	C, 00131$
	C$tactics.c$224$3_3$137	= .
	.globl	C$tactics.c$224$3_3$137
;tactics.c:224: cameraX++;
	ld	hl, #_main_cameraX_65538_122
	inc	(hl)
00131$:
	C$tactics.c$227$2_3$135	= .
	.globl	C$tactics.c$227$2_3$135
;tactics.c:227: if (y < cameraY) {
	ld	a, (#_main_y_65538_122)
	ld	hl, #_main_cameraY_65538_122
	sub	a, (hl)
	jr	NC, 00135$
	C$tactics.c$228$3_3$138	= .
	.globl	C$tactics.c$228$3_3$138
;tactics.c:228: cameraY--;
	dec	(hl)
	jr	00136$
00135$:
	C$tactics.c$229$2_3$135	= .
	.globl	C$tactics.c$229$2_3$135
;tactics.c:229: } else if (y > cameraY + 7) {
	ld	a, (#_main_cameraY_65538_122)
	ld	b, #0x00
	add	a, #0x07
	ld	c, a
	jr	NC, 00341$
	inc	b
00341$:
	ld	hl, #_main_y_65538_122
	ld	l, (hl)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ld	e, h
	ld	d, b
	ld	a, c
	sub	a, l
	ld	a, b
	sbc	a, h
	bit	7, e
	jr	Z, 00342$
	bit	7, d
	jr	NZ, 00343$
	cp	a, a
	jr	00343$
00342$:
	bit	7, d
	jr	Z, 00343$
	scf
00343$:
	jr	NC, 00136$
	C$tactics.c$230$3_3$139	= .
	.globl	C$tactics.c$230$3_3$139
;tactics.c:230: cameraY++;
	ld	hl, #_main_cameraY_65538_122
	inc	(hl)
00136$:
	C$tactics.c$234$2_4$140	= .
	.globl	C$tactics.c$234$2_4$140
;tactics.c:234: target_scy = cameraY * 16;
	ld	a, (#_main_cameraY_65538_122)
	swap	a
	and	a, #0xf0
	ld	(#_main_target_scy_131076_140),a
	C$tactics.c$236$2_5$141	= .
	.globl	C$tactics.c$236$2_5$141
;tactics.c:236: target_scx = cameraX * 16;
	ld	a, (#_main_cameraX_65538_122)
	swap	a
	and	a, #0xf0
	ld	hl, #_main_target_scx_131077_141
	ld	(hl), a
	C$tactics.c$238$2_5$141	= .
	.globl	C$tactics.c$238$2_5$141
;tactics.c:238: __asm__("halt");
	halt
	C$tactics.c$242$2_5$141	= .
	.globl	C$tactics.c$242$2_5$141
;tactics.c:242: if ((uchar)(SCY_REG + 16) < target_scy) {
	ldh	a, (_SCY_REG + 0)
	add	a, #0x10
	ld	c, a
	ldh	a, (_SCY_REG + 0)
	ld	b, a
	ld	a, c
	ld	hl, #_main_target_scy_131076_140
	sub	a, (hl)
	jr	NC, 00140$
	C$tactics.c$243$3_5$142	= .
	.globl	C$tactics.c$243$3_5$142
;tactics.c:243: SCY_REG += 2;
	ld	a, b
	add	a, #0x02
	ldh	(_SCY_REG + 0), a
	jr	00141$
00140$:
	C$tactics.c$244$2_5$141	= .
	.globl	C$tactics.c$244$2_5$141
;tactics.c:244: } else if ((uchar)(SCY_REG + 16) > target_scy) {
	ld	a, b
	add	a, #0x10
	ld	c, a
	ld	a, (#_main_target_scy_131076_140)
	sub	a, c
	jr	NC, 00141$
	C$tactics.c$245$3_5$143	= .
	.globl	C$tactics.c$245$3_5$143
;tactics.c:245: SCY_REG -= 2;
	ldh	a, (_SCY_REG + 0)
	add	a, #0xfe
	ldh	(_SCY_REG + 0), a
00141$:
	C$tactics.c$247$2_5$141	= .
	.globl	C$tactics.c$247$2_5$141
;tactics.c:247: if (SCX_REG < target_scx) {
	ldh	a, (_SCX_REG + 0)
	ld	hl, #_main_target_scx_131077_141
	sub	a, (hl)
	jr	NC, 00145$
	C$tactics.c$248$3_5$144	= .
	.globl	C$tactics.c$248$3_5$144
;tactics.c:248: SCX_REG += 2;
	ldh	a, (_SCX_REG + 0)
	add	a, #0x02
	ldh	(_SCX_REG + 0), a
	jr	00146$
00145$:
	C$tactics.c$249$2_5$141	= .
	.globl	C$tactics.c$249$2_5$141
;tactics.c:249: } else if (SCX_REG > target_scx) {
	ldh	a, (_SCX_REG + 0)
	ld	b, a
	ld	a, (#_main_target_scx_131077_141)
	sub	a, b
	jr	NC, 00146$
	C$tactics.c$250$3_5$145	= .
	.globl	C$tactics.c$250$3_5$145
;tactics.c:250: SCX_REG -= 2;
	ldh	a, (_SCX_REG + 0)
	add	a, #0xfe
	ldh	(_SCX_REG + 0), a
00146$:
;tactics.c:253: move_sprite(0, (x - cameraX)*16 + 8, (y-cameraY)*16 + 32);
	ld	a, (#_main_y_65538_122)
	ld	hl, #_main_cameraY_65538_122
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x20
	ld	c, a
	ld	a, (#_main_x_65538_122)
	ld	hl, #_main_cameraX_65538_122
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x08
	ld	b, a
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1675: OAM_item_t * itm = &shadow_OAM[nb];
	ld	hl, #_shadow_OAM
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1676: itm->y=y, itm->x=x;
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;tactics.c:254: move_sprite(1, (x - cameraX)*16 + 8,  (y-cameraY)*16 + 40);
	ld	a, (#_main_y_65538_122)
	ld	hl, #_main_cameraY_65538_122
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x28
	ld	c, a
	ld	a, (#_main_x_65538_122)
	ld	hl, #_main_cameraX_65538_122
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x08
	ld	b, a
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1675: OAM_item_t * itm = &shadow_OAM[nb];
	ld	hl, #(_shadow_OAM + 4)
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1676: itm->y=y, itm->x=x;
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;tactics.c:255: move_sprite(2, (x - cameraX)*16 + 16, (y-cameraY)*16 + 32);
	ld	a, (#_main_y_65538_122)
	ld	hl, #_main_cameraY_65538_122
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x20
	ld	c, a
	ld	a, (#_main_x_65538_122)
	ld	hl, #_main_cameraX_65538_122
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x10
	ld	b, a
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1675: OAM_item_t * itm = &shadow_OAM[nb];
	ld	hl, #(_shadow_OAM + 8)
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1676: itm->y=y, itm->x=x;
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
;tactics.c:256: move_sprite(3, (x - cameraX)*16 + 16, (y-cameraY)*16 + 40);
	ld	a, (#_main_y_65538_122)
	ld	hl, #_main_cameraY_65538_122
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x28
	ld	c, a
	ld	a, (#_main_x_65538_122)
	ld	hl, #_main_cameraX_65538_122
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x10
	ld	b, a
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1675: OAM_item_t * itm = &shadow_OAM[nb];
	ld	hl, #(_shadow_OAM + 12)
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1676: itm->y=y, itm->x=x;
	ld	a, c
	ld	(hl+), a
	ld	(hl), b
	C$tactics.c$258$2_5$141	= .
	.globl	C$tactics.c$258$2_5$141
;tactics.c:258: cursorTimer++;
	ld	hl, #_main_cursorTimer_65538_122
	inc	(hl)
	C$tactics.c$259$2_5$141	= .
	.globl	C$tactics.c$259$2_5$141
;tactics.c:259: if (cursorTimer == 30) {
	ld	a, (hl)
	sub	a, #0x1e
	jr	NZ, 00150$
	C$tactics.c$260$3_5$146	= .
	.globl	C$tactics.c$260$3_5$146
;tactics.c:260: cursorTimer = 0;
	ld	hl, #_main_cursorTimer_65538_122
	ld	(hl), #0x00
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1602: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 2)
	ld	(hl), #0x00
	ld	hl, #(_shadow_OAM + 6)
	ld	(hl), #0x01
	ld	hl, #(_shadow_OAM + 10)
	ld	(hl), #0x02
	ld	hl, #(_shadow_OAM + 14)
	ld	(hl), #0x03
	C$tactics.c$264$2_5$141	= .
	.globl	C$tactics.c$264$2_5$141
;tactics.c:264: set_sprite_tile(3, 3);
	jr	00151$
00150$:
	C$tactics.c$265$2_5$141	= .
	.globl	C$tactics.c$265$2_5$141
;tactics.c:265: } else if (cursorTimer == 15) {
	ld	a, (#_main_cursorTimer_65538_122)
	sub	a, #0x0f
	jr	NZ, 00151$
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1602: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 2)
	ld	(hl), #0x04
	ld	hl, #(_shadow_OAM + 6)
	ld	(hl), #0x05
	ld	hl, #(_shadow_OAM + 10)
	ld	(hl), #0x06
	ld	hl, #(_shadow_OAM + 14)
	ld	(hl), #0x07
	C$tactics.c$269$2_5$141	= .
	.globl	C$tactics.c$269$2_5$141
;tactics.c:269: set_sprite_tile(3, 7);
00151$:
	C$tactics.c$272$2_5$141	= .
	.globl	C$tactics.c$272$2_5$141
;tactics.c:272: copy_window_buffer();
	call	_copy_window_buffer
	C$tactics.c$274$2_5$141	= .
	.globl	C$tactics.c$274$2_5$141
;tactics.c:274: LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINON;
	ld	a, #0xe3
	ldh	(_LCDC_REG + 0), a
	C$tactics.c$275$2_5$141	= .
	.globl	C$tactics.c$275$2_5$141
;tactics.c:275: while (LY_REG != 16) ;
00152$:
	ldh	a, (_LY_REG + 0)
	sub	a, #0x10
	jr	NZ, 00152$
	C$tactics.c$276$2_5$141	= .
	.globl	C$tactics.c$276$2_5$141
;tactics.c:276: LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINOFF;
	ld	a, #0xc3
	ldh	(_LCDC_REG + 0), a
	jp	00156$
	C$tactics.c$278$1_2$116	= .
	.globl	C$tactics.c$278$1_2$116
;tactics.c:278: }
	add	sp, #13
	C$tactics.c$278$1_2$116	= .
	.globl	C$tactics.c$278$1_2$116
	XG$main$0$0	= .
	.globl	XG$main$0$0
	ret
Ftactics$__str_0$0_0$0 == .
___str_0:
	.ascii "FOREST"
	.db 0x00
	.area _CODE
Ftactics$__str_1$0_0$0 == .
___str_1:
	.ascii "GUY   "
	.db 0x00
Ftactics$__str_2$0_0$0 == .
___str_2:
	.ascii "HOUSE "
	.db 0x00
Ftactics$__str_3$0_0$0 == .
___str_3:
	.ascii "CAVE  "
	.db 0x00
Ftactics$__str_4$0_0$0 == .
___str_4:
	.ascii "CHEST "
	.db 0x00
Ftactics$__str_5$0_0$0 == .
___str_5:
	.ascii "TREE  "
	.db 0x00
Ftactics$__str_6$0_0$0 == .
___str_6:
	.ascii "FENCE "
	.db 0x00
Ftactics$__str_7$0_0$0 == .
___str_7:
	.ascii "GRASS "
	.db 0x00
Ftactics$__str_8$0_0$0 == .
___str_8:
	.ascii "PATH  "
	.db 0x00
Ftactics$__str_9$0_0$0 == .
___str_9:
	.ascii "START "
	.db 0x00
Ftactics$__str_10$0_0$0 == .
___str_10:
	.ascii "END   "
	.db 0x00
	.area _INITIALIZER
Ftactics$__xinit_displayTexts$0_0$0 == .
__xinit__displayTexts:
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_2
	.dw ___str_3
	.dw ___str_4
	.dw ___str_5
	.dw ___str_6
	.dw ___str_7
	.dw ___str_8
	.dw ___str_9
	.dw ___str_10
Ftactics$__xinit_letter_table$0_0$0 == .
__xinit__letter_table:
	.db #0x00	; 0
	.db #0x02	; 2
	.db #0x04	; 4
	.db #0x06	; 6
	.db #0x08	; 8
	.db #0x0a	; 10
	.db #0x0c	; 12
	.db #0x0e	; 14
	.db #0x10	; 16
	.db #0x2c	; 44
	.db #0x12	; 18
	.db #0x14	; 20
	.db #0x16	; 22
	.db #0x18	; 24
	.db #0x1a	; 26
	.db #0x1c	; 28
	.db #0x2c	; 44
	.db #0x1e	; 30
	.db #0x20	; 32
	.db #0x22	; 34
	.db #0x24	; 36
	.db #0x26	; 38
	.db #0x28	; 40
	.db #0x2c	; 44
	.db #0x2a	; 42
	.db #0x2c	; 44
	.area _CABS (ABS)
