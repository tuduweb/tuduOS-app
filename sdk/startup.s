; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
                PRESERVE8
                THUMB


;Reset_Handler   PROC
;                EXPORT  Reset_Handler                       [WEAK]
;                IMPORT  __main
                ;IMPORT  SystemInit
                ;LDR     R0, =SystemInit
                ;BLX     R0
;                ENDP

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, CODE, READONLY
                IMPORT  |Region$$Table$$Limit|

                LDR     R0, app_entry_addr
                ADR     R1, app_entry_addr
                ADD     R0, R1
                BX      R0

;__Vectors
				IMPORT |Image$$text$$RO$$Length|
				IMPORT |Image$$text$$RW$$Length|
				IMPORT |Image$$bss$$RW$$Length|
				IMPORT |Image$$bss$$ZI$$Length|
				IMPORT |Image$$data$$RW$$Length|
				IMPORT |Image$$data$$ZI$$Length|

				IMPORT |Image$$bss$$Limit|
				IMPORT |Image$$bss$$Base|
    
                IMPORT  |Region$$Table$$Base|
                IMPORT  |Region$$Table$$Limit|
                IMPORT  |Region$$Table$$Length|



                IMPORT  |Image$$bss$$Length|
                IMPORT  |Image$$text$$Length|

                DCB     "LWP.b200819"
                

data_addr       DCD     |Image$$text$$RO$$Length|;RO Length;DCD     |Region$$Table$$Limit| - . + .		
                DCD     |Image$$text$$RW$$Length|


                DCD     |Image$$bss$$RW$$Length|
                DCD     |Image$$bss$$ZI$$Length|
                DCD     |Image$$data$$RW$$Length|
                DCD     |Image$$data$$ZI$$Length|

                DCD     |Image$$bss$$Limit| - .
                DCD     |Image$$bss$$Base| - .


                DCD     1,2,3,4,5,6,7,8,8,7,6,5,4,3,2,1

                DCD     |Image$$text$$Length|       ;code+RO
                DCD     |Image$$bss$$ZI$$Length|    ;ZI
                DCD     |Image$$data$$RW$$Length|   ;RW
                DCD     |Image$$bss$$ZI$$Length| + |Image$$data$$RW$$Length|

                DCD     1,2,3,4,5,6,7,8,8,7,6,5,4,3,2,1


;__Vectors_End
                IMPORT  __main
app_entry_addr  DCD     __main - .


main_entry      PROC
                LDR     R0, main_entry_addr
                ADR     R1, main_entry_addr
                ADD     R0, R1
                BX      R0
                ENDP
main_entry_addr      DCD     __main - .

                AREA    RESET, CODE, READONLY


;__Vectors_Size  EQU  0x2;__Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY
                
                ALIGN





                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                IF      :DEF:__MICROLIB
            
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
            
                ELSE
            
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
                
;R0 heap_base | R1 stack_base | R2 heap_limit | R3 stack_limit
;R2 >= R0 R1 > R3
;stack 栈 栈顶地址 < 栈底
;heap 堆 堆底 < 堆顶
;stack(limit) stack+size (sp) heap heap+size(limit)
__user_initial_stackheap
                IMPORT |HEAP$$Base|
                IMPORT |STACK$$Base|
                IMPORT |HEAP$$Length|
                IMPORT |STACK$$Length|
                IMPORT |Region$$Table$$Limit|
                IMPORT |HEAP$$Limit|
                IMPORT |STACK$$Limit|

                ;以下为绝对地址.相对于0x00
                ;要改成相对于|Region$$Table$$Limit|
                ;然后加上SB的值
                ; addr - T_limit + R9
                ; addr + (R9 - T_limit)

                LDR     R0, table_limit
                ADR     R1, table_limit
                ADD     R0, R1
                SUB     R1, R9, R1;rw_addr_offset
                
                LDR     R0, heap_base;data
				ADR		R2,	heap_base;heap
                ADD     R0, R2;heap_base
                ADD     R0, R1;heap_base + addr_offset

                LDR     R3, stack_limit
                ADR     R2, stack_limit
                ADD     R3, R2
                ADD     R3, R1

                LDR     R2, heap_length
                ADD     R2, R0

                LDR     R1, stack_length
                ADD     R1, R3

                BX      LR

                ;LDR     R0, heap_base;data
				;ADR		R1,	heap_base;heap
                ;ADD     R0, R0, R1;heap_base

				;LDR		R1, stack_base;RW base + offset
                ;ADR     R2, stack_base
                ;ADD     R1, R2

                ;LDR     R2, heap_limit
                ;ADR     R3, heap_limit
                ;ADD     R2, R3

                ;LDR     R3, stack_limit
                ;ADR     R4, stack_limit
                ;ADD     R3, R4
                ;BX      LR


table_limit     DCD |Region$$Table$$Limit| - .
stack_limit     DCD |STACK$$Base| - .
stack_base      DCD |STACK$$Limit| - .
heap_base       DCD |HEAP$$Base| - .
heap_limit      DCD |HEAP$$Limit| - .
heap_length     DCD |HEAP$$Length|
stack_length    DCD |STACK$$Length|

                ALIGN

                ENDIF



    END