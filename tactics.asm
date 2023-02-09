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
	.globl _change_text
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
Ltactics.main$x$1_2$120==.
_main_x_65538_120:
	.ds 1
Ltactics.main$y$1_2$120==.
_main_y_65538_120:
	.ds 1
Ltactics.main$cursorTimer$1_2$120==.
_main_cursorTimer_65538_120:
	.ds 1
Ltactics.main$joyTimer$1_2$120==.
_main_joyTimer_65538_120:
	.ds 1
Ltactics.main$cameraX$1_2$120==.
_main_cameraX_65538_120:
	.ds 1
Ltactics.main$cameraY$1_2$120==.
_main_cameraY_65538_120:
	.ds 1
Ltactics.main$target_scy$2_4$138==.
_main_target_scy_131076_138:
	.ds 1
Ltactics.main$target_scx$2_5$139==.
_main_target_scx_131077_139:
	.ds 1
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
G$displayTexts$0_0$0==.
_displayTexts::
	.ds 50
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
	C$tactics.c$152$1_2$110	= .
	.globl	C$tactics.c$152$1_2$110
;tactics.c:152: static uchar x = 0;
	ld	hl, #_main_x_65538_120
	ld	(hl), #0x00
	C$tactics.c$153$1_2$110	= .
	.globl	C$tactics.c$153$1_2$110
;tactics.c:153: static uchar y = 0;
	ld	hl, #_main_y_65538_120
	ld	(hl), #0x00
	C$tactics.c$155$1_2$110	= .
	.globl	C$tactics.c$155$1_2$110
;tactics.c:155: static uchar cursorTimer = 0;
	ld	hl, #_main_cursorTimer_65538_120
	ld	(hl), #0x00
	C$tactics.c$156$1_2$110	= .
	.globl	C$tactics.c$156$1_2$110
;tactics.c:156: static uchar joyTimer = 0;
	ld	hl, #_main_joyTimer_65538_120
	ld	(hl), #0x00
	C$tactics.c$158$1_2$110	= .
	.globl	C$tactics.c$158$1_2$110
;tactics.c:158: static uchar cameraX = 0;
	ld	hl, #_main_cameraX_65538_120
	ld	(hl), #0x00
	C$tactics.c$159$1_2$110	= .
	.globl	C$tactics.c$159$1_2$110
;tactics.c:159: static uchar cameraY = 0;
	ld	hl, #_main_cameraY_65538_120
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
	C$tactics.c$94$0_0$103	= .
	.globl	C$tactics.c$94$0_0$103
;tactics.c:94: void change_text(uchar *text) {
;	---------------------------------
; Function change_text
; ---------------------------------
_change_text::
	dec	sp
	ld	c, e
	ld	b, d
	C$tactics.c$95$1_0$103	= .
	.globl	C$tactics.c$95$1_0$103
;tactics.c:95: if (text == NULL) {
	ld	a, b
	or	a, c
	C$tactics.c$96$2_0$104	= .
	.globl	C$tactics.c$96$2_0$104
;tactics.c:96: return;
	jr	Z, 00110$
	C$tactics.c$98$1_1$105	= .
	.globl	C$tactics.c$98$1_1$105
;tactics.c:98: volatile uchar *tilemap = &windowBuffer[0][0];
	C$tactics.c$100$4_1$109	= .
	.globl	C$tactics.c$100$4_1$109
;tactics.c:100: for (uchar i = 0; i < 6; i++) {
	ldhl	sp,	#0
	ld	(hl), #0x00
00108$:
	ldhl	sp,	#0
	ld	a, (hl)
	sub	a, #0x06
	jr	NC, 00110$
	C$tactics.c$101$3_1$107	= .
	.globl	C$tactics.c$101$3_1$107
;tactics.c:101: if (text[i] == ' ') {
	ld	l, (hl)
	ld	h, #0x00
	add	hl, bc
	ld	e, l
	ld	d, h
	ld	a, (de)
	cp	a, #0x20
	jr	NZ, 00104$
	C$tactics.c$102$4_1$108	= .
	.globl	C$tactics.c$102$4_1$108
;tactics.c:102: tile = SPACE_LETTER;
	ld	hl, #_change_text_tile_65537_105
	ld	(hl), #0x2c
	jr	00105$
00104$:
	C$tactics.c$104$4_1$109	= .
	.globl	C$tactics.c$104$4_1$109
;tactics.c:104: tile = letter_table[text[i] - 'A'];
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
	C$tactics.c$106$3_1$107	= .
	.globl	C$tactics.c$106$3_1$107
;tactics.c:106: tilemap[i] = tile;
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
	C$tactics.c$107$3_1$107	= .
	.globl	C$tactics.c$107$3_1$107
;tactics.c:107: tile++;
	inc	(hl)
	C$tactics.c$108$3_1$107	= .
	.globl	C$tactics.c$108$3_1$107
;tactics.c:108: tilemap[i|32] = tile;
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
	C$tactics.c$100$2_1$106	= .
	.globl	C$tactics.c$100$2_1$106
;tactics.c:100: for (uchar i = 0; i < 6; i++) {
	ldhl	sp,	#0
	inc	(hl)
	jr	00108$
00110$:
	C$tactics.c$110$2_1$103	= .
	.globl	C$tactics.c$110$2_1$103
;tactics.c:110: }
	inc	sp
	C$tactics.c$110$2_1$103	= .
	.globl	C$tactics.c$110$2_1$103
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
	.db #0x0f	; 15
	.db #0x02	; 2
	.db #0x3f	; 63
	.db #0x00	; 0
	.db #0x3f	; 63
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x08	; 8
	.db #0xff	; 255
	.db #0x40	; 64
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x12	; 18
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0xf0	; 240
	.db #0x00	; 0
	.db #0xf0	; 240
	.db #0x20	; 32
	.db #0xfc	; 252
	.db #0x00	; 0
	.db #0xfc	; 252
	.db #0x88	; 136
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x22	; 34
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0xff	; 255
	.db #0x08	; 8
	.db #0x80	; 128
	.db #0x40	; 64
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
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
	.db #0xff	; 255
	.db #0xef	; 239
	.db #0xff	; 255
	.db #0x20	; 32
	.db #0xc3	; 195
	.db #0x20	; 32
	.db #0xc3	; 195
	.db #0xf7	; 247
	.db #0xff	; 255
	.db #0xbe	; 190
	.db #0xff	; 255
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
	.db #0xff	; 255
	.db #0xbe	; 190
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0x1c	; 28
	.db #0x00	; 0
	.db #0x1c	; 28
	.db #0xdf	; 223
	.db #0xff	; 255
	.db #0xfb	; 251
	.db #0xff	; 255
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
	.db #0x00	; 0
	.db #0x30	; 48	'0'
	.db #0x00	; 0
	.db #0x30	; 48	'0'
	.db #0x00	; 0
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0x0c	; 12
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0xc0	; 192
	.db #0xc0	; 192
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
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
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
	.db #0x00	; 0
	.db #0x33	; 51	'3'
	.db #0x00	; 0
	.db #0x33	; 51	'3'
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x03	; 3
	.db #0x00	; 0
	.db #0x30	; 48	'0'
	.db #0xc0	; 192
	.db #0x30	; 48	'0'
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
G$MAP$0_0$0 == .
_MAP:
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x11	; 17
	.db #0x14	; 20
	.db #0x10	; 16
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x0c	; 12
	.db #0x0d	; 13
	.db #0x10	; 16
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x11	; 17
	.db #0x12	; 18
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x0e	; 14
	.db #0x0f	; 15
	.db #0x10	; 16
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x13	; 19
	.db #0x13	; 19
	.db #0x10	; 16
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x13	; 19
	.db #0x13	; 19
	.db #0x10	; 16
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x13	; 19
	.db #0x13	; 19
	.db #0x10	; 16
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x13	; 19
	.db #0x13	; 19
	.db #0x10	; 16
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x17	; 23
	.db #0x18	; 24
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x13	; 19
	.db #0x13	; 19
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x13	; 19
	.db #0x13	; 19
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x13	; 19
	.db #0x13	; 19
	.db #0x10	; 16
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x11	; 17
	.db #0x12	; 18
	.db #0x15	; 21
	.db #0x15	; 21
	.db #0x10	; 16
	.db #0x16	; 22
	.db #0x0e	; 14
	.db #0x0f	; 15
	G$main$0$0	= .
	.globl	G$main$0$0
	C$tactics.c$122$2_1$110	= .
	.globl	C$tactics.c$122$2_1$110
;tactics.c:122: void main() {
;	---------------------------------
; Function main
; ---------------------------------
_main::
	add	sp, #-9
	C$tactics.c$123$1_0$110	= .
	.globl	C$tactics.c$123$1_0$110
;tactics.c:123: wait_vbl_done();
	call	_wait_vbl_done
	C$tactics.c$124$1_0$110	= .
	.globl	C$tactics.c$124$1_0$110
;tactics.c:124: display_off();
	call	_display_off
	C$tactics.c$125$1_0$110	= .
	.globl	C$tactics.c$125$1_0$110
;tactics.c:125: LCDC_REG = 0x00;
	xor	a, a
	ldh	(_LCDC_REG + 0), a
	C$tactics.c$126$1_0$110	= .
	.globl	C$tactics.c$126$1_0$110
;tactics.c:126: set_bkg_data(48, 60, Tiles); //tiles.  15 big tiles, 60 small tiles
	ld	de, #_Tiles
	push	de
	ld	hl, #0x3c30
	push	hl
	call	_set_bkg_data
	add	sp, #4
	C$tactics.c$127$1_0$110	= .
	.globl	C$tactics.c$127$1_0$110
;tactics.c:127: set_bkg_data(0, 46, Letters); //letters. 46 tiles.  23 letters
	ld	de, #_Letters
	push	de
	ld	hl, #0x2e00
	push	hl
	call	_set_bkg_data
	add	sp, #4
	C$tactics.c$130$5_1$115	= .
	.globl	C$tactics.c$130$5_1$115
;tactics.c:130: for (uchar r = 0; r < HEIGHT * 2; r++) {
	ld	c, #0x00
00181$:
	ld	a, c
	sub	a, #0x18
	jp	NC, 00102$
	C$tactics.c$131$1_2$110	= .
	.globl	C$tactics.c$131$1_2$110
;tactics.c:131: for (uchar c = 0; c < WIDTH * 2; c++) {
	ldhl	sp,	#8
	ld	(hl), #0x00
00178$:
	ldhl	sp,	#8
	ld	a, (hl)
	sub	a, #0x18
	jp	NC, 00182$
	C$tactics.c$132$1_2$110	= .
	.globl	C$tactics.c$132$1_2$110
;tactics.c:132: uchar map = MAP[r/2][c/2]*4;
	ldhl	sp,	#0
	ld	a, c
	ld	(hl+), a
	xor	a, a
	ld	(hl-), a
	ld	a, (hl)
	ldhl	sp,	#6
	ld	(hl), a
	ldhl	sp,	#1
	ld	a, (hl)
	ldhl	sp,	#7
	ld	(hl), a
	ldhl	sp,	#1
	bit	7, (hl)
	jr	Z, 00191$
	pop	de
	push	de
	ld	l, e
	ld	h, d
	inc	hl
	push	hl
	ld	a, l
	ldhl	sp,	#8
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#7
	ld	(hl), a
00191$:
	ldhl	sp,	#7
	sra	(hl)
	dec	hl
	rr	(hl)
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	l, e
	ld	h, d
	add	hl, hl
	add	hl, de
	add	hl, hl
	add	hl, hl
	push	hl
	ld	a, l
	ldhl	sp,	#8
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#7
	ld	(hl-), a
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	hl, #_MAP
	add	hl, de
	push	hl
	ld	a, l
	ldhl	sp,	#4
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#3
	ld	(hl), a
	ldhl	sp,	#8
	ld	a, (hl)
	ldhl	sp,	#4
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
	jr	Z, 00192$
	dec	hl
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
	ld	l, e
	ld	h, d
	inc	hl
	push	hl
	ld	a, l
	ldhl	sp,	#8
	ld	(hl), a
	pop	hl
	ld	a, h
	ldhl	sp,	#7
	ld	(hl), a
00192$:
	ldhl	sp,#6
	ld	a, (hl+)
	ld	e, a
	ld	d, (hl)
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
	add	a, a
	add	a, a
	ld	e, a
	C$tactics.c$133$5_1$115	= .
	.globl	C$tactics.c$133$5_1$115
;tactics.c:133: uchar value = map + (r&1) + (c&1)*2;
	ld	a, c
	and	a, #0x01
	add	a, e
	ld	e, a
	ldhl	sp,	#8
	ld	a, (hl-)
	and	a, #0x01
	add	a, a
	add	a, e
	ld	(hl), a
	C$tactics.c$134$5_1$115	= .
	.globl	C$tactics.c$134$5_1$115
;tactics.c:134: tilemap[r*32 + c + 64] = value;
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
	ld	e, a
	ldhl	sp,	#4
	ld	a,	(hl+)
	ld	h, (hl)
	ld	l, a
	add	hl, de
	ld	e, l
	ld	d, h
	ld	hl, #0x0040
	add	hl, de
	ld	e, l
	ld	a, h
	add	a, #0x98
	ld	d, a
	ldhl	sp,	#7
	C$tactics.c$131$4_1$114	= .
	.globl	C$tactics.c$131$4_1$114
;tactics.c:131: for (uchar c = 0; c < WIDTH * 2; c++) {
	ld	a, (hl+)
	ld	(de), a
	inc	(hl)
	jp	00178$
00182$:
	C$tactics.c$130$2_1$112	= .
	.globl	C$tactics.c$130$2_1$112
;tactics.c:130: for (uchar r = 0; r < HEIGHT * 2; r++) {
	inc	c
	jp	00181$
00102$:
	C$tactics.c$137$1_2$110	= .
	.globl	C$tactics.c$137$1_2$110
;tactics.c:137: for (uchar r = 0; r < 2; r++) {
	ldhl	sp,	#8
	ld	(hl), #0x00
00187$:
	ldhl	sp,	#8
	ld	a, (hl)
	sub	a, #0x02
	jr	NC, 00104$
	C$tactics.c$138$1_2$110	= .
	.globl	C$tactics.c$138$1_2$110
;tactics.c:138: for (uchar c = 0; c < WIDTH * 2; c++) {
	ld	c, #0x00
00184$:
	ld	a, c
	sub	a, #0x18
	jr	NC, 00188$
	C$tactics.c$139$5_1$119	= .
	.globl	C$tactics.c$139$5_1$119
;tactics.c:139: tilemap[r*32 + c] = SPACE_LETTER;
	ldhl	sp,	#8
	ld	l, (hl)
	ld	h, #0x00
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	e, c
	ld	d, #0x00
	add	hl, de
	ld	a, h
	add	a, #0x98
	ld	h, a
	ld	(hl), #0x2c
	C$tactics.c$138$4_1$118	= .
	.globl	C$tactics.c$138$4_1$118
;tactics.c:138: for (uchar c = 0; c < WIDTH * 2; c++) {
	inc	c
	jr	00184$
00188$:
	C$tactics.c$137$2_1$116	= .
	.globl	C$tactics.c$137$2_1$116
;tactics.c:137: for (uchar r = 0; r < 2; r++) {
	ldhl	sp,	#8
	inc	(hl)
	jr	00187$
00104$:
	C$tactics.c$142$1_1$111	= .
	.globl	C$tactics.c$142$1_1$111
;tactics.c:142: set_sprite_data(0, 8, Tiles + ((CURSOR1 - FIRST_TILE) * 16 * 4));
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
	C$tactics.c$148$1_1$111	= .
	.globl	C$tactics.c$148$1_1$111
;tactics.c:148: vmemset((uchar *)WIN_TILEMAP_START, SPACE_LETTER, 32*32);
	ld	de, #0x0400
	push	de
	ld	a, #0x2c
	push	af
	inc	sp
	ld	de, #0x9c00
	push	de
	call	_vmemset
	add	sp, #5
	C$tactics.c$150$1_1$111	= .
	.globl	C$tactics.c$150$1_1$111
;tactics.c:150: change_text("FOREST");
	ld	de, #___str_0
	call	_change_text
	C$tactics.c$164$1_2$120	= .
	.globl	C$tactics.c$164$1_2$120
;tactics.c:164: IE_REG = IEF_VBLANK;
	ld	a, #0x01
	ldh	(_IE_REG + 0), a
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:727: __asm__("ei");
	ei
	C$tactics.c$167$1_2$120	= .
	.globl	C$tactics.c$167$1_2$120
;tactics.c:167: LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00;
	ld	a, #0xc3
	ldh	(_LCDC_REG + 0), a
	C$tactics.c$168$1_2$120	= .
	.globl	C$tactics.c$168$1_2$120
;tactics.c:168: while (1) {
00158$:
	C$tactics.c$170$2_2$121	= .
	.globl	C$tactics.c$170$2_2$121
;tactics.c:170: if (joyTimer > 0) {
	ld	hl, #_main_joyTimer_65538_120
	ld	a, (hl)
	or	a, a
	jr	Z, 00127$
	C$tactics.c$171$3_2$122	= .
	.globl	C$tactics.c$171$3_2$122
;tactics.c:171: joyTimer--;
	dec	(hl)
	jr	00128$
00127$:
	C$tactics.c$173$3_2$123	= .
	.globl	C$tactics.c$173$3_2$123
;tactics.c:173: uchar joy = joypad();
	call	_joypad
	ld	c, a
	C$tactics.c$174$3_2$123	= .
	.globl	C$tactics.c$174$3_2$123
;tactics.c:174: if (joy & J_LEFT) {
	bit	1, c
	jr	Z, 00122$
	C$tactics.c$175$4_2$124	= .
	.globl	C$tactics.c$175$4_2$124
;tactics.c:175: if (x > 0) {
	ld	hl, #_main_x_65538_120
	ld	a, (hl)
	or	a, a
	jr	Z, 00123$
	C$tactics.c$176$5_2$125	= .
	.globl	C$tactics.c$176$5_2$125
;tactics.c:176: x--;
	dec	(hl)
	jr	00123$
00122$:
	C$tactics.c$178$3_2$123	= .
	.globl	C$tactics.c$178$3_2$123
;tactics.c:178: } else if (joy & J_RIGHT) {
	bit	0, c
	jr	Z, 00119$
	C$tactics.c$179$4_2$126	= .
	.globl	C$tactics.c$179$4_2$126
;tactics.c:179: if (x < WIDTH - 1) {
	ld	hl, #_main_x_65538_120
	ld	a, (hl)
	sub	a, #0x0b
	jr	NC, 00123$
	C$tactics.c$180$5_2$127	= .
	.globl	C$tactics.c$180$5_2$127
;tactics.c:180: x++;
	inc	(hl)
	jr	00123$
00119$:
	C$tactics.c$182$3_2$123	= .
	.globl	C$tactics.c$182$3_2$123
;tactics.c:182: } else if (joy & J_UP) {
	bit	2, c
	jr	Z, 00116$
	C$tactics.c$183$4_2$128	= .
	.globl	C$tactics.c$183$4_2$128
;tactics.c:183: if (y > 0) {
	ld	hl, #_main_y_65538_120
	ld	a, (hl)
	or	a, a
	jr	Z, 00123$
	C$tactics.c$184$5_2$129	= .
	.globl	C$tactics.c$184$5_2$129
;tactics.c:184: y--;
	dec	(hl)
	jr	00123$
00116$:
	C$tactics.c$186$3_2$123	= .
	.globl	C$tactics.c$186$3_2$123
;tactics.c:186: } else if (joy & J_DOWN) {
	bit	3, c
	jr	Z, 00123$
	C$tactics.c$187$4_2$130	= .
	.globl	C$tactics.c$187$4_2$130
;tactics.c:187: if (y < HEIGHT - 1) {
	ld	hl, #_main_y_65538_120
	ld	a, (hl)
	sub	a, #0x0b
	jr	NC, 00123$
	C$tactics.c$188$5_2$131	= .
	.globl	C$tactics.c$188$5_2$131
;tactics.c:188: y++;
	inc	(hl)
00123$:
	C$tactics.c$191$3_2$123	= .
	.globl	C$tactics.c$191$3_2$123
;tactics.c:191: if (joy != 0) {
	ld	a, c
	or	a, a
	jr	Z, 00128$
	C$tactics.c$192$4_2$132	= .
	.globl	C$tactics.c$192$4_2$132
;tactics.c:192: joyTimer = 10;
	ld	hl, #_main_joyTimer_65538_120
	ld	(hl), #0x0a
00128$:
	C$tactics.c$196$2_3$133	= .
	.globl	C$tactics.c$196$2_3$133
;tactics.c:196: uchar coord = MAP[y][x];
	ld	hl, #_main_y_65538_120
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
	ld	hl, #_main_x_65538_120
	ld	l, (hl)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
	add	hl, bc
	ld	c, (hl)
	C$tactics.c$197$2_3$133	= .
	.globl	C$tactics.c$197$2_3$133
;tactics.c:197: uchar *text = (uchar *)displayTexts[coord];
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
	C$tactics.c$198$2_3$133	= .
	.globl	C$tactics.c$198$2_3$133
;tactics.c:198: change_text(text);
	ld	e, c
	ld	d, b
	call	_change_text
	C$tactics.c$200$2_3$133	= .
	.globl	C$tactics.c$200$2_3$133
;tactics.c:200: if (x < cameraX) {
	ld	a, (#_main_x_65538_120)
	ld	hl, #_main_cameraX_65538_120
	sub	a, (hl)
	jr	NC, 00132$
	C$tactics.c$201$3_3$134	= .
	.globl	C$tactics.c$201$3_3$134
;tactics.c:201: cameraX--;
	dec	(hl)
	jr	00133$
00132$:
	C$tactics.c$202$2_3$133	= .
	.globl	C$tactics.c$202$2_3$133
;tactics.c:202: } else if (x >= cameraX + 10) {
	ld	a, (#_main_cameraX_65538_120)
	ld	b, #0x00
	add	a, #0x0a
	ld	c, a
	jr	NC, 00367$
	inc	b
00367$:
	ld	hl, #_main_x_65538_120
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
	jr	Z, 00368$
	bit	7, d
	jr	NZ, 00369$
	cp	a, a
	jr	00369$
00368$:
	bit	7, d
	jr	Z, 00369$
	scf
00369$:
	jr	C, 00133$
	C$tactics.c$203$3_3$135	= .
	.globl	C$tactics.c$203$3_3$135
;tactics.c:203: cameraX++;
	ld	hl, #_main_cameraX_65538_120
	inc	(hl)
00133$:
	C$tactics.c$206$2_3$133	= .
	.globl	C$tactics.c$206$2_3$133
;tactics.c:206: if (y < cameraY) {
	ld	a, (#_main_y_65538_120)
	ld	hl, #_main_cameraY_65538_120
	sub	a, (hl)
	jr	NC, 00137$
	C$tactics.c$207$3_3$136	= .
	.globl	C$tactics.c$207$3_3$136
;tactics.c:207: cameraY--;
	dec	(hl)
	jr	00138$
00137$:
	C$tactics.c$208$2_3$133	= .
	.globl	C$tactics.c$208$2_3$133
;tactics.c:208: } else if (y > cameraY + 7) {
	ld	a, (#_main_cameraY_65538_120)
	ld	b, #0x00
	add	a, #0x07
	ld	c, a
	jr	NC, 00370$
	inc	b
00370$:
	ld	hl, #_main_y_65538_120
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
	jr	Z, 00371$
	bit	7, d
	jr	NZ, 00372$
	cp	a, a
	jr	00372$
00371$:
	bit	7, d
	jr	Z, 00372$
	scf
00372$:
	jr	NC, 00138$
	C$tactics.c$209$3_3$137	= .
	.globl	C$tactics.c$209$3_3$137
;tactics.c:209: cameraY++;
	ld	hl, #_main_cameraY_65538_120
	inc	(hl)
00138$:
	C$tactics.c$213$2_4$138	= .
	.globl	C$tactics.c$213$2_4$138
;tactics.c:213: target_scy = cameraY * 16;
	ld	a, (#_main_cameraY_65538_120)
	swap	a
	and	a, #0xf0
	ld	(#_main_target_scy_131076_138),a
	C$tactics.c$215$2_5$139	= .
	.globl	C$tactics.c$215$2_5$139
;tactics.c:215: target_scx = cameraX * 16;
	ld	a, (#_main_cameraX_65538_120)
	swap	a
	and	a, #0xf0
	ld	hl, #_main_target_scx_131077_139
	ld	(hl), a
	C$tactics.c$217$2_5$139	= .
	.globl	C$tactics.c$217$2_5$139
;tactics.c:217: __asm__("halt");
	halt
	C$tactics.c$221$2_5$139	= .
	.globl	C$tactics.c$221$2_5$139
;tactics.c:221: if (SCY_REG < target_scy) {
	ldh	a, (_SCY_REG + 0)
	ld	hl, #_main_target_scy_131076_138
	sub	a, (hl)
	jr	NC, 00142$
	C$tactics.c$222$3_5$140	= .
	.globl	C$tactics.c$222$3_5$140
;tactics.c:222: SCY_REG += 2;
	ldh	a, (_SCY_REG + 0)
	add	a, #0x02
	ldh	(_SCY_REG + 0), a
	jr	00143$
00142$:
	C$tactics.c$223$2_5$139	= .
	.globl	C$tactics.c$223$2_5$139
;tactics.c:223: } else if (SCY_REG > target_scy) {
	ldh	a, (_SCY_REG + 0)
	ld	b, a
	ld	a, (#_main_target_scy_131076_138)
	sub	a, b
	jr	NC, 00143$
	C$tactics.c$224$3_5$141	= .
	.globl	C$tactics.c$224$3_5$141
;tactics.c:224: SCY_REG -= 2;
	ldh	a, (_SCY_REG + 0)
	add	a, #0xfe
	ldh	(_SCY_REG + 0), a
00143$:
	C$tactics.c$226$2_5$139	= .
	.globl	C$tactics.c$226$2_5$139
;tactics.c:226: if (SCX_REG < target_scx) {
	ldh	a, (_SCX_REG + 0)
	ld	hl, #_main_target_scx_131077_139
	sub	a, (hl)
	jr	NC, 00147$
	C$tactics.c$227$3_5$142	= .
	.globl	C$tactics.c$227$3_5$142
;tactics.c:227: SCX_REG += 2;
	ldh	a, (_SCX_REG + 0)
	add	a, #0x02
	ldh	(_SCX_REG + 0), a
	jr	00148$
00147$:
	C$tactics.c$228$2_5$139	= .
	.globl	C$tactics.c$228$2_5$139
;tactics.c:228: } else if (SCX_REG > target_scx) {
	ldh	a, (_SCX_REG + 0)
	ld	b, a
	ld	a, (#_main_target_scx_131077_139)
	sub	a, b
	jr	NC, 00148$
	C$tactics.c$229$3_5$143	= .
	.globl	C$tactics.c$229$3_5$143
;tactics.c:229: SCX_REG -= 2;
	ldh	a, (_SCX_REG + 0)
	add	a, #0xfe
	ldh	(_SCX_REG + 0), a
00148$:
;tactics.c:232: move_sprite(0, (x - cameraX)*16 + 8, (y-cameraY)*16 + 32);
	ld	a, (#_main_y_65538_120)
	ld	hl, #_main_cameraY_65538_120
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x20
	ld	c, a
	ld	a, (#_main_x_65538_120)
	ld	hl, #_main_cameraX_65538_120
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
;tactics.c:233: move_sprite(1, (x - cameraX)*16 + 8,  (y-cameraY)*16 + 40);
	ld	a, (#_main_y_65538_120)
	ld	hl, #_main_cameraY_65538_120
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x28
	ld	c, a
	ld	a, (#_main_x_65538_120)
	ld	hl, #_main_cameraX_65538_120
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
;tactics.c:234: move_sprite(2, (x - cameraX)*16 + 16, (y-cameraY)*16 + 32);
	ld	a, (#_main_y_65538_120)
	ld	hl, #_main_cameraY_65538_120
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x20
	ld	c, a
	ld	a, (#_main_x_65538_120)
	ld	hl, #_main_cameraX_65538_120
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
;tactics.c:235: move_sprite(3, (x - cameraX)*16 + 16, (y-cameraY)*16 + 40);
	ld	a, (#_main_y_65538_120)
	ld	hl, #_main_cameraY_65538_120
	sub	a, (hl)
	swap	a
	and	a, #0xf0
	add	a, #0x28
	ld	c, a
	ld	a, (#_main_x_65538_120)
	ld	hl, #_main_cameraX_65538_120
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
	C$tactics.c$237$2_5$139	= .
	.globl	C$tactics.c$237$2_5$139
;tactics.c:237: cursorTimer++;
	ld	hl, #_main_cursorTimer_65538_120
	inc	(hl)
	C$tactics.c$238$2_5$139	= .
	.globl	C$tactics.c$238$2_5$139
;tactics.c:238: if (cursorTimer == 30) {
	ld	a, (hl)
	sub	a, #0x1e
	jr	NZ, 00152$
	C$tactics.c$239$3_5$144	= .
	.globl	C$tactics.c$239$3_5$144
;tactics.c:239: cursorTimer = 0;
	ld	hl, #_main_cursorTimer_65538_120
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
	C$tactics.c$243$2_5$139	= .
	.globl	C$tactics.c$243$2_5$139
;tactics.c:243: set_sprite_tile(3, 3);
	jr	00153$
00152$:
	C$tactics.c$244$2_5$139	= .
	.globl	C$tactics.c$244$2_5$139
;tactics.c:244: } else if (cursorTimer == 15) {
	ld	a, (#_main_cursorTimer_65538_120)
	sub	a, #0x0f
	jr	NZ, 00153$
;C:/Users/gerzy/OneDrive - Florida Polytechnic University/Documents/Merpcraft Stuff/codeforces/gmamer_boy/gbdk/include/gb/gb.h:1602: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 2)
	ld	(hl), #0x04
	ld	hl, #(_shadow_OAM + 6)
	ld	(hl), #0x05
	ld	hl, #(_shadow_OAM + 10)
	ld	(hl), #0x06
	ld	hl, #(_shadow_OAM + 14)
	ld	(hl), #0x07
	C$tactics.c$248$2_5$139	= .
	.globl	C$tactics.c$248$2_5$139
;tactics.c:248: set_sprite_tile(3, 7);
00153$:
	C$tactics.c$251$2_5$139	= .
	.globl	C$tactics.c$251$2_5$139
;tactics.c:251: copy_window_buffer();
	call	_copy_window_buffer
	C$tactics.c$253$2_5$139	= .
	.globl	C$tactics.c$253$2_5$139
;tactics.c:253: LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINON;
	ld	a, #0xe3
	ldh	(_LCDC_REG + 0), a
	C$tactics.c$254$2_5$139	= .
	.globl	C$tactics.c$254$2_5$139
;tactics.c:254: while (LY_REG != 16) ;
00154$:
	ldh	a, (_LY_REG + 0)
	sub	a, #0x10
	jr	NZ, 00154$
	C$tactics.c$255$2_5$139	= .
	.globl	C$tactics.c$255$2_5$139
;tactics.c:255: LCDC_REG = LCDCF_BGON | LCDCF_ON | LCDCF_BG8800 | LCDCF_OBJON | LCDCF_WIN9C00 | LCDCF_WINOFF;
	ld	a, #0xc3
	ldh	(_LCDC_REG + 0), a
	jp	00158$
	C$tactics.c$257$1_2$110	= .
	.globl	C$tactics.c$257$1_2$110
;tactics.c:257: }
	add	sp, #9
	C$tactics.c$257$1_2$110	= .
	.globl	C$tactics.c$257$1_2$110
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
	.ascii "      "
	.db 0x00
Ftactics$__str_2$0_0$0 == .
___str_2:
	.ascii "GUY   "
	.db 0x00
Ftactics$__str_3$0_0$0 == .
___str_3:
	.ascii "HOUSE "
	.db 0x00
Ftactics$__str_4$0_0$0 == .
___str_4:
	.ascii "CAVE  "
	.db 0x00
Ftactics$__str_5$0_0$0 == .
___str_5:
	.ascii "CHEST "
	.db 0x00
Ftactics$__str_6$0_0$0 == .
___str_6:
	.ascii "TREE  "
	.db 0x00
Ftactics$__str_7$0_0$0 == .
___str_7:
	.ascii "FENCE "
	.db 0x00
Ftactics$__str_8$0_0$0 == .
___str_8:
	.ascii "GRASS "
	.db 0x00
Ftactics$__str_9$0_0$0 == .
___str_9:
	.ascii "PATH  "
	.db 0x00
Ftactics$__str_10$0_0$0 == .
___str_10:
	.ascii "START "
	.db 0x00
Ftactics$__str_11$0_0$0 == .
___str_11:
	.ascii "END   "
	.db 0x00
	.area _INITIALIZER
Ftactics$__xinit_displayTexts$0_0$0 == .
__xinit__displayTexts:
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_1
	.dw ___str_2
	.dw ___str_2
	.dw ___str_2
	.dw ___str_2
	.dw ___str_2
	.dw ___str_2
	.dw ___str_3
	.dw ___str_4
	.dw ___str_5
	.dw ___str_6
	.dw ___str_7
	.dw ___str_8
	.dw ___str_9
	.dw ___str_10
	.dw ___str_11
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
