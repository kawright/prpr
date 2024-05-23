# Copyright (C) 2024  Kristoffer A. Wright

# Makefile

BUILD_DIR				:=	.build
OBJ_DIR					:=	${BUILD_DIR}/obj
BIN_DIR					:=	${BUILD_DIR}/bin
SRC_DIR					:=	src
ASSET_DIR				:=	asset
INSTALL_BIN_DIR			:= /usr/local/bin
INSTALL_MAN_DIR			:= /usr/local/share/man/man1


OBJS					:=	${OBJ_DIR}/err.o						\
							${OBJ_DIR}/lnbuf.o						\
							${OBJ_DIR}/cmdbuf.o						\
							${OBJ_DIR}/cmd.o						\
							${OBJ_DIR}/chmat.o						\
							${OBJ_DIR}/graphic.o					\
							${OBJ_DIR}/asset.o						\
							${OBJ_DIR}/fdback.o						\
							${OBJ_DIR}/argvp.o						\
							${OBJ_DIR}/ati_9x14.ttf.o				\
							${OBJ_DIR}/ibm_iso8.ttf.o				\
							${OBJ_DIR}/help.txt.o					\
							${OBJ_DIR}/version.txt.o				\
							${OBJ_DIR}/plex.ttf.o

LIBS					:=	-lSDL2					\
							-lSDL2_image			\
							-lSDL2_ttf

FLAGS					:=	-Isrc/include			\
							-Wall					\
							-g						\
							-fno-diagnostics-color

${BIN_DIR}/prpr: ${SRC_DIR}/main.c ${OBJS}
	@echo 'Building binary $@'
	@mkdir -p ${BUILD_DIR}
	@mkdir -p ${BIN_DIR}
	@gcc ${FLAGS} ${OBJS} ${SRC_DIR}/main.c ${LIBS} -o $@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@echo 'Building object file $@'
	@mkdir -p ${BUILD_DIR}
	@mkdir -p ${OBJ_DIR}
	@gcc ${FLAGS} -c $< ${LIBS} -o $@

$(OBJ_DIR)/%.o: $(ASSET_DIR)/%
	@echo 'Linking asset $@'
	@ld -r -b binary -o $@ $<

.PHONY: all
all: ${BIN_DIR}/prpr
	@echo Done!

.PHONY: clean
clean:
	@echo Cleaning build artifacts
	@rm -rf ${BUILD_DIR}
	@echo Done!

.PHONY: install
install: ${BIN_DIR}/prpr man.groff
	@echo Installing prpr
	@cp ${BIN_DIR}/prpr ${INSTALL_BIN_DIR}/prpr
	@cp man.groff ${INSTALL_MAN_DIR}/prpr.1
	@gzip ${INSTALL_MAN_DIR}/prpr.1
	@echo Done!

.PHONY: uninstall
uninstall:
	@echo Uninstalling prpr
	@rm -f ${INSTALL_BIN_DIR}/prpr
	@rm -f ${INSTALL_MAN_DIR}/prpr
	@echo Done! 
