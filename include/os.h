#ifndef OS_H
#define OS_H

#include "cfg.h"
#include "types.h"

/* --------------- gdt ----------------------------*/

// 大小为8字节
typedef struct _gdt_table_t {

    uint16_t limit_l;
    uint16_t base_l;
    uint16_t basehl_attr;
    uint16_t base_limit;

} gdt_table_t OS_ALIGN(8);

// struct _segment_desc_t {
//     uint16_t            limit15_0;
//     uint16_t            base15_0;
//     uint8_t             base23_16;
//     uint16_t            attr;
//     uint8_t             base31_24;
// };

/* -------------- irq ---------------------------*/

// 大小为8字节
typedef struct _idt_table_t {

    uint16_t offset_l;
    uint16_t selector;
    uint16_t attr;
    uint16_t offset_h;

} idt_table_t OS_ALIGN(8);


/* -------------  Page --------------------------*/


#define PDE_P    (1 << 0)
#define PDE_W    (1 << 1)
#define PDE_U    (1 << 2)
#define PDE_PS   (1 << 7)

typedef uint32_t page_table_t;
typedef uint32_t page_dir_t;


typedef struct _tss_t {
    uint32_t pre_link;
    uint32_t esp0, ss0, esp1, ss1, esp2, ss2;
    uint32_t cr3;
    uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
    uint32_t es, cs, ss, ds, fs, gs;
    uint32_t ldt;
    uint32_t iomap;
}tss_t;


#endif  // OS_H