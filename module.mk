CC := g++

DIR := ..
SRC_DIR := ../src
WIN_DIR := .
BUILD_DIR := build
INCLUDE_DIR := ../include
STD := c++14

.PHONY: clean

build_dir:
	mkdir -p ${BUILD_DIR}

compile: build_dir \
		${BUILD_DIR}/main.o \
		${BUILD_DIR}/application.o \
		${BUILD_DIR}/json.o \
		${BUILD_DIR}/glad.o \
		${BUILD_DIR}/shader.o \
		${BUILD_DIR}/triangle.o \
		${BUILD_DIR}/render.o \
		${BUILD_DIR}/command.o \
		${BUILD_DIR}/vram.o \
		${BUILD_DIR}/asset_manager.o \
		${BUILD_DIR}/texture.o 

${BUILD_DIR}/json.o: ${DIR}/libjson/json.cpp ${DIR}/libjson/json.hpp
	${CC} -std=${STD} -c ${DIR}/libjson/json.cpp -o ${BUILD_DIR}/json.o

${BUILD_DIR}/application.o: ${SRC_DIR}/application.hpp ${SRC_DIR}/application.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/application.cpp -o ${BUILD_DIR}/application.o -I ${INCLUDE_DIR} -I ${SRC_DIR}

${BUILD_DIR}/glad.o:${SRC_DIR}/render/glad.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/glad.cpp -o ${BUILD_DIR}/glad.o -I ${INCLUDE_DIR}

${BUILD_DIR}/shader.o:${SRC_DIR}/render/shader.cpp ${SRC_DIR}/render/shader.hpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/shader.cpp -o ${BUILD_DIR}/shader.o -I ${INCLUDE_DIR} -I ${SRC_DIR}

${BUILD_DIR}/command.o:${SRC_DIR}/render/command.cpp ${SRC_DIR}/render/command.hpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/command.cpp -o ${BUILD_DIR}/command.o -I ${INCLUDE_DIR} -I ${SRC_DIR}

${BUILD_DIR}/triangle.o:${SRC_DIR}/render/triangle.cpp ${SRC_DIR}/render/triangle.hpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/triangle.cpp -o ${BUILD_DIR}/triangle.o -I ${INCLUDE_DIR} -I ${SRC_DIR} 

${BUILD_DIR}/vram.o:${SRC_DIR}/render/vram.cpp ${SRC_DIR}/render/vram.hpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/vram.cpp -o ${BUILD_DIR}/vram.o -I ${INCLUDE_DIR} -I ${SRC_DIR}

${BUILD_DIR}/render.o:${SRC_DIR}/render/render.cpp ${SRC_DIR}/render/render.hpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/render.cpp -o ${BUILD_DIR}/render.o -I ${INCLUDE_DIR} -I ${SRC_DIR} 

${BUILD_DIR}/texture.o:${SRC_DIR}/render/texture.cpp ${SRC_DIR}/render/texture.hpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/texture.cpp -o ${BUILD_DIR}/texture.o -I ${INCLUDE_DIR} -I ${SRC_DIR}

${BUILD_DIR}/asset_manager.o:${SRC_DIR}/resource/asset_manager.cpp ${SRC_DIR}/resource/asset_manager.hpp
	${CC} -std=${STD} -c ${SRC_DIR}/resource/asset_manager.cpp -o ${BUILD_DIR}/asset_manager.o -I ${INCLUDE_DIR} -I ${SRC_DIR}