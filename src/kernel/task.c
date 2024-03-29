
#include "types.h"
#include "desc.h"
#include "cpu.h"

extern int printf(const char *fmt, ...);


extern gdt_table_t * gdt_table;
extern page_dir_t * page_dir; 

uint32_t task_0_stack_dpl1[1024];
uint32_t task_0_stack_dpl3[1024];

uint32_t task_1_stack_dpl1[1024];
uint32_t task_1_stack_dpl3[1024];

void task_0_entry() {
    uint8_t color = 0xff;
    while(1) {
        printf("this is --------");
    }
}

void task_1_entry() {
    uint8_t color = 0x0;
    while(1) {
        printf("this is ++++++++");
    }
}

void task_sched() {
    static int task_tss = TASK_0_TSS;
    task_tss = (task_tss == TASK_0_TSS) ? TASK_1_TSS : TASK_0_TSS;
    ljmp(task_tss);
}

uint32_t task0_tss[] = {
    // prelink, esp0,ss0, esp1,ss1, esp2,ss2
    0, (uint32_t)task_0_stack_dpl1+4096, KERNEL_DATA_SEG, 0x0, 0x0, 0x0, 0x0,
    // cr3, eip, eflags,  eax, ecx, edx, ebx, 
    (uint32_t)(0xA000), (uint32_t)task_0_entry, 0x202, 0xa, 0xc, 0xd, 0xb,
    // esp, ebp, esi, edi,
    (uint32_t)task_0_stack_dpl3+4096, 0x1, 0x2, 0x3,
    // es, cs, ss, ds, fs, gs, ldt, iomap
    APP_DATA_SEG, APP_CODE_SEG, APP_DATA_SEG, APP_DATA_SEG, APP_DATA_SEG, APP_DATA_SEG, 0x0, 0x0,
};

uint32_t task1_tss[] = {
    // prelink, esp0,ss0, esp1,ss1, esp2,ss2
    0, (uint32_t)task_1_stack_dpl1+4096, KERNEL_DATA_SEG, 0x0, 0x0, 0x0, 0x0,
    // cr3, eip, eflags,  eax, ecx, edx, ebx, 
    (uint32_t)(0xA000), (uint32_t)task_1_entry, 0x202, 0xa, 0xc, 0xd, 0xb, 
    // esp, ebp, esi, edi,
    (uint32_t)task_1_stack_dpl3+4096, 0x1, 0x2, 0x3,
    // es, cs, ss, ds, fs, gs, ldt, iomap
    APP_DATA_SEG, APP_CODE_SEG, APP_DATA_SEG, APP_DATA_SEG, APP_DATA_SEG, APP_DATA_SEG, 0x0, 0x0,
};

uint32_t kernel_tss[] = {
    // prelink, esp0,ss0, esp1,ss1, esp2,ss2
    0, (uint32_t)0x7c00, KERNEL_DATA_SEG, 0x0, 0x0, 0x0, 0x0,
    // cr3, eip, eflags,  eax, ecx, edx, ebx, 
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
    // esp, ebp, esi, edi,
    0x0, 0x0, 0x0, 0x0,
    // es, cs, ss, ds, fs, gs, ldt, iomap
    0x0, KERNEL_CODE_SEG, KERNEL_DATA_SEG, 0x0, 0x0, 0x0, 0x0, 0x0,
};

uint32_t kernel_tss2[] = {
    // prelink, esp0,ss0, esp1,ss1, esp2,ss2
    0, (uint32_t)0x6c00, KERNEL_DATA_SEG, 0x0, 0x0, 0x0, 0x0,
    // cr3, eip, eflags,  eax, ecx, edx, ebx, 
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
    // esp, ebp, esi, edi,
    0x0, 0x0, 0x0, 0x0,
    // es, cs, ss, ds, fs, gs, ldt, iomap
    0x0, KERNEL_CODE_SEG, KERNEL_DATA_SEG, 0x0, 0x0, 0x0, 0x0, 0x0,
};

void task_init () {

    gdt_table[5].limit_low = 0x86; //task 0 tss  TASK_0_TSS
    gdt_table[5].base_low = (uint32_t)task0_tss & 0xffff;  // 低16

    gdt_table[5].base_middle = ((uint32_t)task0_tss >> 16) & 0xff;
    gdt_table[5].access = 0xe9;
    gdt_table[5].granularity = 0x0; 
    gdt_table[5].base_high =  ((uint32_t)task0_tss >> 24) & 0xff;
    

    gdt_table[6].limit_low = 0x86; //task 0 tss  TASK_0_TSS
    gdt_table[6].base_low = (uint32_t)task1_tss & 0xffff;  // 低16

    gdt_table[6].base_middle = ((uint32_t)task1_tss >> 16) & 0xff;
    gdt_table[6].access = 0xe9;
    gdt_table[6].granularity = 0x0; 
    gdt_table[6].base_high = ((uint32_t)task1_tss >> 24) & 0xff;


    // 内核 任务
    gdt_table[16].limit_low = 0xffff; 
    gdt_table[16].base_low = (uint32_t)kernel_tss & 0xffff;  // 低16

    gdt_table[16].base_middle = ((uint32_t)kernel_tss >> 16) & 0xff;
    gdt_table[16].access = 0b10001001;  //dpl = 0
    gdt_table[16].granularity = 0x0; 
    gdt_table[16].base_high = ((uint32_t)kernel_tss >> 24) & 0xff;

}