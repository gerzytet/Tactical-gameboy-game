.globl _copy_window_buffer
;TEXT_OFFSET = 1
;WINDOW_BUFFER = 0x9C00
;void copy_window_buffer() {
;    volatile uchar *tilemap = (uchar *)WIN_TILEMAP_START + TEXT_OFFSET;
;    for (uchar i = 0; i < 6; i++) {
;        tilemap[i] = windowBuffer[0][i];
;        tilemap[i|32] = windowBuffer[1][i];
;    }
;}
_copy_window_buffer:
    ;push af
    ;push bc
    ;push de

    ld hl, #0x9C00 + #1 ;tilemap
    ld de, #_windowBuffer + #1 ;windowBuffer
    ld b, #6
    .copy_window_buffer_loop:
        ld a, (de)
        ld (hl), a

        inc hl
        inc de
        dec b
        jr nz, .copy_window_buffer_loop
    
    ld hl, #0x9C00 + #1 + #32 ;tilemap
    ld de, #_windowBuffer + #1 + #32 ;windowBuffer
    ld b, #6
    .copy_window_buffer_loop2:
        ld a, (de)
        ld (hl), a

        inc hl
        inc de
        dec b
        jr nz, .copy_window_buffer_loop2
    

;TURN COUNTER:
    ld hl, #0x9C00 + #13 ;tilemap
    ld de, #_windowBuffer + #13 ;windowBuffer
    ld b, #6
    .copy_window_buffer_loop3:
        ld a, (de)
        ld (hl), a

        inc hl
        inc de
        dec b
        jr nz, .copy_window_buffer_loop3
    
    ld hl, #0x9C00 + #13 + #32 ;tilemap
    ld de, #_windowBuffer + #13 + #32 ;windowBuffer
    ld b, #6
    .copy_window_buffer_loop4:
        ld a, (de)
        ld (hl), a

        inc hl
        inc de
        dec b
        jr nz, .copy_window_buffer_loop4

;HEALTH BAR: 7 to 12
    ld hl, #0x9C00 + #7 ;tilemap
    ld de, #_windowBuffer + #7 ;windowBuffer
    ld b, #6
    .copy_window_buffer_loop5:
        ld a, (de)
        ld (hl), a

        inc hl
        inc de
        dec b
        jr nz, .copy_window_buffer_loop5
    
    ld hl, #0x9C00 + #7 + #32 ;tilemap
    ld de, #_windowBuffer + #7 + #32 ;windowBuffer
    ld b, #6
    .copy_window_buffer_loop6:
        ld a, (de)
        ld (hl), a

        inc hl
        inc de
        dec b
        jr nz, .copy_window_buffer_loop6

    ;pop de
    ;pop bc
    ;pop af

    ret

;#define internal_display_bigsprite(slot, tile)\
;    set_sprite_tile((slot)*2, (tile)*4);\
;    set_sprite_tile((slot)*2+1, (tile)*4+2);

;#define internal_move_bigsprite(slot, x, y)\
;    move_sprite((slot)*2, (x), (y));\
;    move_sprite((slot)*2+1, (x)+8, (y));

;for (uchar i = 0; i < 20; i++) {
;    internal_display_bigsprite(i, bigsprites[i].sprite);
;    internal_move_bigsprite(i, bigsprites[i].x, bigsprites[i].y);
;}

;SAVES 30 SCANLINES!!!!
.globl _display_bigsprites
_display_bigsprites::
    push hl
    push de
    push af
    push bc

    ld hl, #_shadow_OAM
    ld de, #_bigsprites
    ld b, #20

    .bigsprites_loop:
    ;move_sprite((slot)*2, (x), (y));
        ld a, (de)
        ld (hl), a

        inc hl
        inc de

        ld a, (de)
        ld (hl), a

        inc hl
        inc de

    ;set_sprite_tile((slot)*2, (tile)*4);\

        ld a, (de)
        sla a
        sla a
        ld (hl), a

        inc hl
        inc hl

        dec de
        dec de
    ;move_sprite((slot)*2+1, (x)+8, (y));
        ld a, (de)
        ld (hl), a

        inc hl
        inc de

        ld a, (de)
        add a, #8
        ld (hl), a

        inc hl
        inc de
    ;    set_sprite_tile((slot)*2+1, (tile)*4+2);
        ld a, (de)
        sla a
        inc a
        sla a
        ld (hl), a

        inc hl 
        inc hl
        inc de

        dec b
        jr nz, .bigsprites_loop

    pop bc
    pop af
    pop de
    pop hl
    ret