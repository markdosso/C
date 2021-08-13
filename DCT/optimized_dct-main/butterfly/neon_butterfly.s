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
	.file	"neon_butterfly.c"
	.text
	.align	2
	.global	neonButterfly
	.type	neonButterfly, %function
neonButterfly:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	fstmfdd	sp!, {d8, d9, d10, d11}
	mov	r9, r0
	sub	sp, sp, #32
	mov	r5, r1
	mov	sl, r0
	add	r4, r0, #256
.L2:
	ldr	ip, [sl, #0]
	ldr	r3, [sl, #28]
#APP
@ 34 "neon_butterfly.c" 1
	btrfly	ip, ip, r3

@ 0 "" 2
	ldr	r0, [sl, #4]
	ldr	r3, [sl, #24]
#APP
@ 39 "neon_butterfly.c" 1
	btrfly	r0, r0, r3

@ 0 "" 2
	ldr	r1, [sl, #8]
	ldr	r3, [sl, #20]
#APP
@ 44 "neon_butterfly.c" 1
	btrfly	r1, r1, r3

@ 0 "" 2
	add	r2, sl, #12
	ldmia	r2, {r2, r3}	@ phole ldm
#APP
@ 49 "neon_butterfly.c" 1
	btrfly	r2, r2, r3

@ 0 "" 2
	mov	ip, ip, asl #16
	mov	r0, r0, asl #16
	mov	r1, r1, asl #16
	mov	r2, r2, asl #16
	add	sl, sl, #32
	mov	ip, ip, lsr #16
	mov	r0, r0, lsr #16
	mov	r1, r1, lsr #16
	mov	r2, r2, lsr #16
	cmp	sl, r4
	str	ip, [sp, #16]
	str	r0, [sp, #20]
	str	r1, [sp, #24]
	str	r2, [sp, #28]
	bne	.L2
	mov	fp, r5
	vmov.i32	q5, #181  @ v4si
	vldr	d8, .L8
	vldr	d9, .L8+8
	vldr	d0, .L8+16
	vldr	d1, .L8+24
	vldr	d2, .L8+32
	vldr	d3, .L8+40
	vldr	d4, .L8+48
	vldr	d5, .L8+56
	vldr	d6, .L8+64
	vldr	d7, .L8+72
	vldr	d30, .L8+80
	vldr	d31, .L8+88
	vldr	d28, .L8+96
	vldr	d29, .L8+104
.L3:
	ldr	r8, [r9, #0]
	ldr	r3, [r9, #28]
#APP
@ 118 "neon_butterfly.c" 1
	btrfly	r8, r8, r3

@ 0 "" 2
	ldr	r7, [r9, #4]
	ldr	r3, [r9, #24]
#APP
@ 123 "neon_butterfly.c" 1
	btrfly	r7, r7, r3

@ 0 "" 2
	ldr	ip, [r9, #8]
	ldr	r3, [r9, #20]
#APP
@ 128 "neon_butterfly.c" 1
	btrfly	ip, ip, r3

@ 0 "" 2
	add	r0, r9, #12
	ldmia	r0, {r0, r3}	@ phole ldm
#APP
@ 133 "neon_butterfly.c" 1
	btrfly	r0, r0, r3

@ 0 "" 2
	mov	r2, r8, asr #16
	mov	r3, r7, asr #16
	mov	r1, ip, asr #16
	mov	r4, r0, asr #16
	str	r2, [sp, #16]
	str	r3, [sp, #20]
	str	r1, [sp, #24]
	str	r4, [sp, #28]
	vldr	d22, [sp, #16]
	vldr	d23, [sp, #24]
	vmul.i32	q10, q11, q1
	vmul.i32	q8, q11, q4
	vmul.i32	q9, q11, q0
	vpaddl.s32	q8, q8
	vpaddl.s32	q9, q9
	vpaddl.s32	q10, q10
	vmovn.i64	d16, q8
	vmovn.i64	d18, q9
	vmovn.i64	d20, q10
	vpaddl.s32	d24, d16
	vpaddl.s32	d25, d18
	vpaddl.s32	d16, d20
	vmov	r3, r4, d24  @ di
	vmov	r1, r2, d25  @ di
	vmov	r5, r6, d16  @ di
	mov	r8, r8, asl #16
	mov	r7, r7, asl #16
	mov	ip, ip, asl #16
	mov	r0, r0, asl #16
	mov	r3, r3, asr #18
	mov	r1, r1, asr #18
	mov	r5, r5, asr #18
	mov	r8, r8, lsr #16
	mov	r7, r7, lsr #16
	mov	r0, r0, lsr #16
	mov	ip, ip, lsr #16
	str	r3, [fp, #8]
	str	r1, [fp, #16]
	str	r5, [fp, #24]
	str	r8, [sp, #16]
	str	r7, [sp, #20]
	str	r0, [sp, #28]
	str	ip, [sp, #24]
	vldr	d16, [sp, #16]
	vldr	d17, [sp, #24]
	vmul.i32	q11, q11, q5
	vmul.i32	q12, q8, q14
	vpaddl.s32	q11, q11
	vmul.i32	q9, q8, q2
	vmovn.i64	d22, q11
	vpaddl.s32	q12, q12
	vpaddl.s32	q9, q9
	vpaddl.s32	d26, d22
	vmovn.i64	d24, q12
	vmovn.i64	d18, q9
	vmov	r2, r3, d26  @ di
	vmul.i32	q10, q8, q3
	vpaddl.s32	d19, d24
	vmul.i32	q8, q8, q15
	stmia	sp, {r2-r3}
	vpaddl.s32	q10, q10
	vmov	r3, r4, d19  @ di
	vpaddl.s32	q8, q8
	str	r3, [sp, #8]
	str	r4, [sp, #12]
	vmovn.i64	d20, q10
	vmovn.i64	d16, q8
	vpaddl.s32	d27, d18
	vpaddl.s32	d22, d20
	vpaddl.s32	d18, d16
	ldr	r4, [sp, #0]
	ldr	r0, [sp, #8]
	vmov	r1, r2, d27  @ di
	vmov	r5, r6, d22  @ di
	vmov	r7, r8, d18  @ di
	add	r9, r9, #32
	mov	r3, r4, asr #18
	mov	r1, r1, asr #18
	mov	r5, r5, asr #18
	mov	r7, r7, asr #18
	mov	r0, r0, asr #18
	cmp	r9, sl
	str	r0, [fp, #28]
	str	r3, [fp, #0]
	str	r1, [fp, #4]
	str	r5, [fp, #12]
	str	r7, [fp, #20]
	add	fp, fp, #32
	bne	.L3
	add	sp, sp, #32
	fldmfdd	sp!, {d8, d9, d10, d11}
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	bx	lr
.L9:
	.align	3
.L8:
	.word	237
	.word	98
	.word	-98
	.word	-237
	.word	181
	.word	-181
	.word	-181
	.word	181
	.word	98
	.word	-237
	.word	237
	.word	-98
	.word	251
	.word	213
	.word	142
	.word	50
	.word	213
	.word	-50
	.word	-251
	.word	-142
	.word	142
	.word	-251
	.word	50
	.word	213
	.word	50
	.word	-142
	.word	213
	.word	-251
	.size	neonButterfly, .-neonButterfly
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
