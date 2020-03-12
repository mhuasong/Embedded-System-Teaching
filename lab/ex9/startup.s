.global _Start
.global cmsg
.global clen

.data
msg:
        .ascii  "Hello, ARM!\n"
len = . - msg

cmsg:
        .ascii  "Test jump into c entry!\r\n"
clen = . - cmsg


.text

_Start:
        /*Syscall write(int fd, const void *buf, size_t count)*/
        mov %r0, $1     /*输出到stdout，stdout的设备描述符为1*/
        ldr %r1, =msg   /*buf=msg*/
        ldr %r2, =len   /*count=len*/
        mov %r7, $4     /*syscall 4*/
        swi $0          /*invoke syscall*/

	BL c_entry

        /*Syscall exit*/
        mov %r0, $0
        mov %r7, $1
        swi $0
.end
