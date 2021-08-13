	.arch armv4t
	.eabi_attribute 27, 3
	.fpu neon
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 18, 4
	.file	"neonButterflyUpdated.c"
	.text
	.align	2
	.global	neonButterflyUpdated
	.type	neonButterflyUpdated, %function
neonButterflyUpdated:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	mov	fp, r0
	sub	sp, sp, #24
	mov	sl, r0
	add	r0, r0, #256
	stmia	sp, {r0, r1}	@ phole stm
.L2:
	ldr	r8, [sl, #0]
	ldr	r5, [sl, #28]
	mov	r2, #1
#APP
@ 25 "neonButterflyUpdated.c" 1
	btrfly	r3, r8, r5

@ 0 "" 2
	mov	r7, #2
	ldr	r6, [sl, #4]
	ldr	r1, [sl, #24]
#APP
@ 30 "neonButterflyUpdated.c" 1
	btrfly	r3, r6, r1

@ 0 "" 2
	mov	ip, #3
	ldr	r4, [sl, #8]
	ldr	r9, [sl, #20]
#APP
@ 35 "neonButterflyUpdated.c" 1
	btrfly	r2, r4, r9

@ 0 "" 2
	add	r0, sl, #12
	ldmia	r0, {r0, ip}	@ phole ldm
	add	r7, r7, r7
#APP
@ 40 "neonButterflyUpdated.c" 1
	btrfly	r2, r0, ip

@ 0 "" 2
	mov	r9, #6
#APP
@ 61 "neonButterflyUpdated.c" 1
	btrfly	r2, r8, r5

@ 0 "" 2
@ 66 "neonButterflyUpdated.c" 1
	btrfly	r2, r6, r1

@ 0 "" 2
	ldr	r7, [sl, #20]
	add	r9, r9, #1
#APP
@ 71 "neonButterflyUpdated.c" 1
	btrfly	r2, r4, r7

@ 0 "" 2
	mov	r7, #8
#APP
@ 76 "neonButterflyUpdated.c" 1
	btrfly	r2, r0, ip

@ 0 "" 2
	add	r9, r9, #2
#APP
@ 94 "neonButterflyUpdated.c" 1
	btrfly	r2, r8, r5 r9

@ 0 "" 2
	add	r7, r7, #2
#APP
@ 99 "neonButterflyUpdated.c" 1
	btrfly	r2, r6, r1 r7

@ 0 "" 2
	mov	r3, #11
	ldr	r9, [sl, #20]
#APP
@ 104 "neonButterflyUpdated.c" 1
	btrfly	r2, r4, r9 r3

@ 0 "" 2
	mov	r2, #12
#APP
@ 109 "neonButterflyUpdated.c" 1
	btrfly	r2, r0, ip r2

@ 0 "" 2
	mov	r3, #13
#APP
@ 127 "neonButterflyUpdated.c" 1
	btrfly	r8, r8, r5 r3

@ 0 "" 2
	mov	r2, #14
#APP
@ 132 "neonButterflyUpdated.c" 1
	btrfly	r6, r6, r1 r2

@ 0 "" 2
	add	r3, r3, #2
	ldr	r2, [sl, #20]
#APP
@ 137 "neonButterflyUpdated.c" 1
	btrfly	r4, r4, r2 r3

@ 0 "" 2
	mov	r2, #16
#APP
@ 142 "neonButterflyUpdated.c" 1
	btrfly	r0, r0, ip r2

@ 0 "" 2
	ldr	r3, [sp, #0]
	add	sl, sl, #32
	cmp	sl, r3
	str	r8, [sp, #8]
	str	r6, [sp, #12]
	str	r4, [sp, #16]
	str	r0, [sp, #20]
	bne	.L2
	ldr	ip, [sp, #4]
.L3:
	ldr	r8, [fp, #0]
	ldr	r3, [fp, #28]
	mov	r7, #1
#APP
@ 163 "neonButterflyUpdated.c" 1
	btrfly	r8, r8, r3 r7

@ 0 "" 2
	mov	r0, #2
	ldr	r6, [fp, #4]
	ldr	r3, [fp, #24]
#APP
@ 168 "neonButterflyUpdated.c" 1
	btrfly	r6, r6, r3 r0

@ 0 "" 2
	mov	r2, #3
	ldr	r4, [fp, #8]
	ldr	r3, [fp, #20]
#APP
@ 173 "neonButterflyUpdated.c" 1
	btrfly	r4, r4, r3 r2

@ 0 "" 2
	add	r1, fp, #12
	ldmia	r1, {r1, r3}	@ phole ldm
	add	r0, r0, r0
#APP
@ 178 "neonButterflyUpdated.c" 1
	btrfly	r1, r1, r3 r0

@ 0 "" 2
	str	r2, [sp, #20]
	str	r9, [sp, #8]
	str	r7, [sp, #12]
	str	r5, [sp, #16]
	vldr	d18, [sp, #8]
	vldr	d19, [sp, #16]
	str	r4, [sp, #16]
	str	r1, [sp, #20]
	str	r8, [sp, #8]
	str	r6, [sp, #12]
	vldr	d16, [sp, #8]
	vldr	d17, [sp, #16]
	vpaddl.s32	q9, q9
	vpaddl.s32	q8, q8
	vmovn.i64	d18, q9
	vmovn.i64	d16, q8
	vpaddl.s32	d20, d18
	vpaddl.s32	d21, d16
	vmov	r1, r2, d21  @ di
	vmov	r3, r4, d20  @ di
	mov	r3, r3, asr #18
	mov	r1, r1, asr #18
	str	r3, [ip, #0]
	str	r1, [ip, #4]
	ldr	r8, [fp, #0]
	ldr	r3, [fp, #28]
	mov	r2, #5
#APP
@ 196 "neonButterflyUpdated.c" 1
	btrfly	r8, r8, r3 r2

@ 0 "" 2
	ldr	r6, [fp, #4]
	ldr	r3, [fp, #24]
	add	r0, r0, #2
#APP
@ 201 "neonButterflyUpdated.c" 1
	btrfly	r6, r6, r3 r0

@ 0 "" 2
	ldr	r4, [fp, #8]
	ldr	r3, [fp, #20]
	add	r2, r2, #2
#APP
@ 206 "neonButterflyUpdated.c" 1
	btrfly	r4, r4, r3 r2

@ 0 "" 2
	add	r1, fp, #12
	ldmia	r1, {r1, r3}	@ phole ldm
	add	r0, r0, #2
#APP
@ 211 "neonButterflyUpdated.c" 1
	btrfly	r1, r1, r3 r0

@ 0 "" 2
	str	r2, [sp, #20]
	str	r9, [sp, #8]
	str	r7, [sp, #12]
	str	r5, [sp, #16]
	vldr	d18, [sp, #8]
	vldr	d19, [sp, #16]
	str	r4, [sp, #16]
	str	r1, [sp, #20]
	str	r8, [sp, #8]
	str	r6, [sp, #12]
	vldr	d16, [sp, #8]
	vldr	d17, [sp, #16]
	vpaddl.s32	q9, q9
	vpaddl.s32	q8, q8
	vmovn.i64	d18, q9
	vmovn.i64	d16, q8
	vpaddl.s32	d20, d18
	vpaddl.s32	d21, d16
	vmov	r1, r2, d21  @ di
	vmov	r3, r4, d20  @ di
	mov	r3, r3, asr #18
	mov	r1, r1, asr #18
	str	r3, [ip, #8]
	str	r1, [ip, #12]
	ldr	r8, [fp, #0]
	ldr	r3, [fp, #28]
	mov	r2, #9
#APP
@ 229 "neonButterflyUpdated.c" 1
	btrfly	r8, r8, r3 r2

@ 0 "" 2
	mov	r3, #10
	ldr	r6, [fp, #4]
	ldr	r2, [fp, #24]
#APP
@ 234 "neonButterflyUpdated.c" 1
	btrfly	r6, r6, r2 r3

@ 0 "" 2
	ldr	r4, [fp, #8]
	ldr	r0, [fp, #20]
	add	r3, r3, #1
#APP
@ 239 "neonButterflyUpdated.c" 1
	btrfly	r4, r4, r0 r3

@ 0 "" 2
	ldr	r1, [fp, #12]
	ldr	r0, [fp, #16]
	add	r3, r3, #1
#APP
@ 244 "neonButterflyUpdated.c" 1
	btrfly	r1, r1, r0 r3

@ 0 "" 2
	str	r2, [sp, #20]
	str	r9, [sp, #8]
	str	r7, [sp, #12]
	str	r5, [sp, #16]
	vldr	d18, [sp, #8]
	vldr	d19, [sp, #16]
	str	r4, [sp, #16]
	str	r1, [sp, #20]
	str	r8, [sp, #8]
	str	r6, [sp, #12]
	vldr	d16, [sp, #8]
	vldr	d17, [sp, #16]
	vpaddl.s32	q9, q9
	vpaddl.s32	q8, q8
	vmovn.i64	d18, q9
	vmovn.i64	d16, q8
	vpaddl.s32	d20, d18
	vpaddl.s32	d21, d16
	vmov	r1, r2, d21  @ di
	vmov	r3, r4, d20  @ di
	mov	r3, r3, asr #18
	mov	r1, r1, asr #18
	str	r3, [ip, #16]
	str	r1, [ip, #20]
	ldr	r8, [fp, #0]
	ldr	r2, [fp, #28]
	mov	r3, #13
#APP
@ 262 "neonButterflyUpdated.c" 1
	btrfly	r8, r8, r2 r3

@ 0 "" 2
	ldr	r6, [fp, #4]
	ldr	r2, [fp, #24]
	add	r3, r3, #1
#APP
@ 267 "neonButterflyUpdated.c" 1
	btrfly	r6, r6, r2 r3

@ 0 "" 2
	ldr	r4, [fp, #8]
	ldr	r0, [fp, #20]
	add	r3, r3, #1
#APP
@ 272 "neonButterflyUpdated.c" 1
	btrfly	r4, r4, r0 r3

@ 0 "" 2
	ldr	r1, [fp, #12]
	ldr	r0, [fp, #16]
	add	r3, r3, #1
#APP
@ 277 "neonButterflyUpdated.c" 1
	btrfly	r1, r1, r0 r3

@ 0 "" 2
	str	r2, [sp, #20]
	str	r9, [sp, #8]
	str	r7, [sp, #12]
	str	r5, [sp, #16]
	vldr	d18, [sp, #8]
	vldr	d19, [sp, #16]
	str	r4, [sp, #16]
	str	r1, [sp, #20]
	str	r8, [sp, #8]
	str	r6, [sp, #12]
	vldr	d16, [sp, #8]
	vldr	d17, [sp, #16]
	vpaddl.s32	q9, q9
	vpaddl.s32	q8, q8
	vmovn.i64	d18, q9
	vmovn.i64	d16, q8
	vpaddl.s32	d20, d18
	vpaddl.s32	d21, d16
	vmov	r3, r4, d20  @ di
	vmov	r1, r2, d21  @ di
	add	fp, fp, #32
	mov	r3, r3, asr #18
	mov	r1, r1, asr #18
	cmp	fp, sl
	str	r3, [ip, #24]
	str	r1, [ip, #28]
	add	ip, ip, #32
	bne	.L3
	add	sp, sp, #24
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	bx	lr
	.size	neonButterflyUpdated, .-neonButterflyUpdated
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
