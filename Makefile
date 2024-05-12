# Copyright (C) 2024  Kristoffer A. Wright

# Makefile

BUILD_DIR				:=	.build
OBJ_DIR					:=	${BUILD_DIR}/obj
BIN_DIR					:=	${BUILD_DIR}/bin
SRC_DIR					:=	src

OBJS					:=	${OBJ_DIR}/err.o		\
							${OBJ_DIR}/lnbuf.o		\

FLAGS					:=	-Isrc/include			\
							-Wall					\
							-g						\
							-fno-diagnostics-color

${BIN_DIR}/prpr: ${SRC_DIR}/main.c ${OBJS}
	@echo 'Building binary $@'
	@mkdir -p ${BUILD_DIR}
	@mkdir -p ${BIN_DIR}
	@gcc ${FLAGS} ${OBJS} ${SRC_DIR}/main.c -o $@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@echo 'Building object file $@'
	@mkdir -p ${BUILD_DIR}
	@mkdir -p ${OBJ_DIR}
	@gcc ${FLAGS} -c $< -o $@

.PHONY: all
all: ${BIN_DIR}/prpr
	@echo Done!

.PHONE: clean
clean:
	@echo Cleaning build artifacts
	@rm -rf ${BUILD_DIR}
	@echo Done!
