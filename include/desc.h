#ifndef OS_H
#define OS_H

#include "cfg.h"
#include "types.h"

/* --------------- gdt ----------------------------*/

// 大小为8字节
typedef struct _gdt_table_t {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} gdt_table_t OS_ALIGN(8);


/* -------------- irq ---------------------------*/

// 大小为8字节
typedef struct _idt_entry_t {

    uint16_t offset0;
    uint16_t selector;

    uint16_t ist : 3;
    uint16_t : 5;
    /* idt类型 */
    uint16_t type : 4;
    uint16_t : 1;
    /* 特权级 */
    uint16_t dpl : 2;
    /* 1 存在*/
    uint16_t p : 1;

    uint16_t offset1;

} idt_entry_t OS_ALIGN(8);


/* -------------  Page -------------------------- */


#define PDE_P    (1 << 0)
#define PDE_W    (1 << 1)
#define PDE_U    (1 << 2)
#define PDE_PS   (1 << 7)

typedef uint32_t page_table_t;
typedef uint32_t page_dir_t;
typedef uint32_t phys_addr_t;

typedef struct _tss_t {
    uint32_t pre_link;
    uint32_t esp0, ss0, esp1, ss1, esp2, ss2;
    uint32_t cr3;
    uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
    uint32_t es, cs, ss, ds, fs, gs;
    uint32_t ldt;
    uint32_t iomap;
}tss_t;


/* -------------- syscall describe entry -------- */

typedef struct _syscall_des_t {
    uint16_t offset0;
    uint16_t sellector;

    uint16_t param_count: 5;  // 32 parameters
    uint16_t :3;

    uint16_t type:4;
    uint16_t :1;
    /* 特权级 */
    uint16_t dpl : 2;
    /* 1 存在*/
    uint16_t p : 1;

    uint16_t offset1;
} syscall_des_t OS_ALIGN(8);

#endif  // OS_H