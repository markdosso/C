CFLAGS=-D${ALGO} -Wall -static -O3
DEPS=./src/main.c ./src/dct.c

ifdef S # generate assembly instead of executable, dev only
	OUTPUT=-S
endif
ifndef S
	OUTPUT=-o dct.exe
endif

ifdef G # compile with debugging option, dev only
	CLFAGS+=-g
endif

ifeq (${ALGO}, NAIVE) # make <arm> ALGO=NAIVE
	DEPS+=./src/naive.c
endif

ifeq (${ALGO}, UNOPTIMIZED) # make <arm> ALGO=UNOPTIMIZED
	DEPS+=./src/unoptimized.c
endif

ifeq (${ALGO}, UNROLLED) # make <arm> ALGO=UNROLLED
	CFLAGS+=-DTRANSPOSE
	DEPS+=./src/unrolled.c
endif

ifeq (${ALGO}, PIPELINED) # make <arm> ALGO=PIPELINED
	CFLAGS+=-DTRANSPOSE
	DEPS+=./src/pipelined.c
endif

ifeq (${ALGO}, NEON) # make arm ALGO=NEON
	CFLAGS+=-DTRANSPOSE -mfloat-abi=softfp -mfpu=neon
	DEPS+=./src/neon.c
endif

dct: ${DEPS}
	gcc $(CFLAGS) $^ $(OUTPUT)

arm: ${DEPS}
	arm-linux-gcc $(CFLAGS) $^ $(OUTPUT)

testbench: ./src/testbench.c ./src/neon.c ./src/naive.c # arm only, tests NAIVE vs. NEON
	arm-linux-gcc -Wall -static -mfloat-abi=softfp -mfpu=neon ./src/testbench.c ./src/neon.c ./src/naive.c -o testbench.exe

.PHONY clean:
clean:
	-rm -rf ./**/*.o ./*.exe
