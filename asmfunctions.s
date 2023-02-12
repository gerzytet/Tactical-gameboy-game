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
    ld de, #_windowBuffer ;windowBuffer
    ld b, #6
    .copy_window_buffer_loop:
        ld a, (de)
        ld (hl), a

        inc hl
        inc de
        dec b
        jr nz, .copy_window_buffer_loop
    
    ld hl, #0x9C00 + #1 + #32 ;tilemap
    ld de, #_windowBuffer + #32 ;windowBuffer
    ld b, #6
    .copy_window_buffer_loop2:
        ld a, (de)
        ld (hl), a

        inc hl
        inc de
        dec b
        jr nz, .copy_window_buffer_loop2

    ;pop de
    ;pop bc
    ;pop af

    ret