	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"file1_prog1.c"
	.text
	.align	2
	.global	factoriel
	.type	factoriel, %function
factoriel:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bge	.L2
	mvn	r3, #0
	b	.L3
.L2:
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bne	.L4
	mov	r3, #0
	b	.L3
.L4:
	ldr	r3, [fp, #-8]
	cmp	r3, #1
	bne	.L5
	mov	r3, #1
	b	.L3
.L5:
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1
	mov	r0, r3
	bl	factoriel
	mov	r3, r0
	ldr	r2, [fp, #-8]
	mul	r3, r2, r3
.L3:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
	.size	factoriel, .-factoriel
	.ident	"GCC: (4.8.2-14ubuntu1+6) 4.8.2"
