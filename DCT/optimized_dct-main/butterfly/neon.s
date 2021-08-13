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
	.file	"neon.c"
	.text
	.align	2
	.global	neon
	.type	neon, %function
neon:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 320
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	fstmfdd	sp!, {d8, d9, d10, d11}
	sub	sp, sp, #320
	add	r2, sp, #64
	add	r3, sp, #96
	str	r2, [sp, #44]
	str	r1, [sp, #20]
	str	r3, [sp, #4]
	mov	fp, r0
	mov	r9, r2
	vmov.i32	q4, #181  @ v4si
	vldr	d0, .L8
	vldr	d1, .L8+8
	vldr	d2, .L8+16
	vldr	d3, .L8+24
	vldr	d4, .L8+32
	vldr	d5, .L8+40
	vldr	d6, .L8+48
	vldr	d7, .L8+56
	vldr	d30, .L8+64
	vldr	d31, .L8+72
	vldr	d28, .L8+80
	vldr	d29, .L8+88
	vldr	d26, .L8+96
	vldr	d27, .L8+104
.L2:
	ldr	r0, [fp, #28]
	ldmia	fp, {r1, r2, r3}	@ phole ldm
	ldr	sl, [fp, #24]
	ldr	ip, [fp, #20]
	add	r5, fp, #16
	ldmda	r5, {r4, r5}
	add	r4, r5, r4
	add	r1, r0, r1
	add	sl, sl, r2
	add	ip, ip, r3
	str	r1, [sp, #48]
	str	sl, [sp, #52]
	str	ip, [sp, #56]
	str	r4, [sp, #60]
	vldr	d16, [sp, #48]
	vldr	d17, [sp, #56]
	vmul.i32	q11, q8, q2
	vmul.i32	q9, q8, q4
	vmul.i32	q10, q8, q0
	vmul.i32	q8, q8, q1
	vpaddl.s32	q9, q9
	vpaddl.s32	q10, q10
	vpaddl.s32	q8, q8
	vpaddl.s32	q11, q11
	vmovn.i64	d18, q9
	vmovn.i64	d20, q10
	vmovn.i64	d16, q8
	vmovn.i64	d22, q11
	vpaddl.s32	d24, d18
	vpaddl.s32	d25, d20
	vpaddl.s32	d18, d16
	vpaddl.s32	d19, d22
	vmov	r5, r6, d18  @ di
	str	r4, [sp, #28]
	str	r1, [sp, #24]
	vmov	r3, r4, d24  @ di
	vmov	r1, r2, d25  @ di
	vmov	r7, r8, d19  @ di
	str	r5, [r9, #128]
	str	r7, [r9, #192]
	str	r3, [r9, #0]
	str	r1, [r9, #64]
	ldr	r3, [fp, #28]
	ldr	r4, [sp, #24]
	add	r0, fp, #16
	ldmia	r0, {r0, r1, r2}	@ phole ldm
	ldr	r5, [sp, #28]
	sub	r3, r4, r3, asl #1
	str	r3, [sp, #48]
	sub	sl, sl, r2, asl #1
	sub	r3, r5, r0, asl #1
	sub	ip, ip, r1, asl #1
	str	sl, [sp, #52]
	str	r3, [sp, #60]
	str	ip, [sp, #56]
	vldr	d16, [sp, #48]
	vldr	d17, [sp, #56]
	vmul.i32	q11, q8, q13
	vmul.i32	q9, q8, q3
	vmul.i32	q10, q8, q15
	vmul.i32	q8, q8, q14
	vpaddl.s32	q9, q9
	vpaddl.s32	q10, q10
	vpaddl.s32	q8, q8
	vpaddl.s32	q11, q11
	vmovn.i64	d18, q9
	vmovn.i64	d20, q10
	vmovn.i64	d16, q8
	vmovn.i64	d22, q11
	vpaddl.s32	d24, d18
	vpaddl.s32	d25, d20
	vpaddl.s32	d18, d16
	vpaddl.s32	d19, d22
	vmov	r3, r4, d24  @ di
	vmov	r1, r2, d25  @ di
	vmov	r5, r6, d18  @ di
	vmov	r7, r8, d19  @ di
	str	r3, [r9, #32]
	str	r1, [r9, #96]
	str	r5, [r9, #160]
	str	r7, [r9, #224]
	ldr	sl, [sp, #4]
	add	r9, r9, #4
	cmp	r9, sl
	add	fp, fp, #32
	bne	.L2
	ldr	fp, [sp, #20]
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
	ldr	ip, [sp, #44]
	ldr	r0, [ip, #24]
	ldr	r3, [sp, #44]
	str	r0, [sp, #8]
	ldr	sl, [ip, #28]
	ldr	r2, [ip, #20]
	ldr	r0, [ip, #0]
	ldr	r7, [r3, #8]
	ldr	ip, [ip, #4]
	ldr	r5, [sp, #8]
	add	r4, r3, #16
	ldmda	r4, {r4, r8}
	add	r8, r8, r4
	add	r0, sl, r0
	add	ip, r5, ip
	add	r7, r2, r7
	ldr	r9, [r3, #16]
	str	r0, [sp, #48]
	str	ip, [sp, #52]
	str	r7, [sp, #56]
	str	r8, [sp, #60]
	vldr	d22, [sp, #48]
	vldr	d23, [sp, #56]
	vmul.i32	q10, q11, q1
	vmul.i32	q8, q11, q4
	vmul.i32	q9, q11, q0
	vpaddl.s32	q8, q8
	vpaddl.s32	q9, q9
	vpaddl.s32	q10, q10
	sub	r0, r0, sl, asl #1
	ldr	sl, [sp, #8]
	str	r2, [sp, #12]
	str	r9, [sp, #16]
	vmovn.i64	d16, q8
	vmovn.i64	d18, q9
	vmovn.i64	d20, q10
	vpaddl.s32	d24, d16
	vpaddl.s32	d25, d18
	vpaddl.s32	d16, d20
	sub	ip, ip, sl, asl #1
	add	r9, sp, #12
	ldmia	r9, {r9, sl}	@ phole ldm
	vmov	r3, r4, d24  @ di
	vmov	r1, r2, d25  @ di
	vmov	r5, r6, d16  @ di
	sub	r7, r7, r9, asl #1
	sub	r8, r8, sl, asl #1
	mov	r3, r3, asr #18
	mov	r1, r1, asr #18
	mov	r5, r5, asr #18
	str	r3, [fp, #8]
	str	r1, [fp, #16]
	str	r5, [fp, #24]
	str	ip, [sp, #52]
	str	r7, [sp, #56]
	str	r8, [sp, #60]
	str	r0, [sp, #48]
	vldr	d16, [sp, #48]
	vldr	d17, [sp, #56]
	vmul.i32	q12, q8, q14
	vmul.i32	q9, q8, q2
	vpaddl.s32	q12, q12
	vmul.i32	q10, q8, q3
	vpaddl.s32	q9, q9
	vmul.i32	q11, q11, q5
	vmul.i32	q8, q8, q15
	vmovn.i64	d24, q12
	vmovn.i64	d18, q9
	vpaddl.s32	q11, q11
	vpaddl.s32	q10, q10
	vpaddl.s32	q8, q8
	vpaddl.s32	d19, d24
	vmovn.i64	d22, q11
	vmov	r9, sl, d19  @ di
	vmovn.i64	d20, q10
	ldr	sl, [sp, #44]
	vmovn.i64	d16, q8
	vpaddl.s32	d26, d22
	vpaddl.s32	d27, d18
	vpaddl.s32	d22, d20
	vpaddl.s32	d18, d16
	vmov	r1, r2, d27  @ di
	add	sl, sl, #32
	vmov	r3, r4, d26  @ di
	vmov	r5, r6, d22  @ di
	vmov	r7, r8, d18  @ di
	add	ip, sp, #320
	mov	r3, r3, asr #18
	mov	r1, r1, asr #18
	mov	r5, r5, asr #18
	mov	r7, r7, asr #18
	mov	r2, r9, asr #18
	cmp	sl, ip
	str	sl, [sp, #44]
	str	r3, [fp, #0]
	str	r1, [fp, #4]
	str	r5, [fp, #12]
	str	r7, [fp, #20]
	str	r2, [fp, #28]
	add	fp, fp, #32
	bne	.L3
	add	sp, sp, #320
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
	.size	neon, .-neon
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
