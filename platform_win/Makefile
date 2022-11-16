CC := g++

DIR := ..
SRC_DIR := ../src
WIN_DIR := .
BUILD_DIR := build
INCLUDE_DIR := ../include
STD := c++14

build_dir:
	mkdir -p ${BUILD_DIR}

compile: build_dir \
		${BUILD_DIR}/main.o \
		${BUILD_DIR}/application.o \
		${BUILD_DIR}/json.o \
		${BUILD_DIR}/glad.o \
		${BUILD_DIR}/shader.o \
		${BUILD_DIR}/triangle.o

${BUILD_DIR}/json.o:
	${CC} -std=${STD} -c ${DIR}/libjson/json.cpp -o ${BUILD_DIR}/json.o

${BUILD_DIR}/application.o:
	${CC} -std=${STD} -c ${SRC_DIR}/application.cpp -o ${BUILD_DIR}/application.o -I ${INCLUDE_DIR} -I ${SRC_DIR}

${BUILD_DIR}/glad.o:${SRC_DIR}/render/glad.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/glad.cpp -o ${BUILD_DIR}/glad.o -I ${INCLUDE_DIR}

${BUILD_DIR}/shader.o:${SRC_DIR}/render/shader.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/shader.cpp -o ${BUILD_DIR}/shader.o -I ${INCLUDE_DIR} -I ${SRC_DIR}

${BUILD_DIR}/triangle.o:${SRC_DIR}/render/triangle.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/render/triangle.cpp -o ${BUILD_DIR}/triangle.o -I ${INCLUDE_DIR} -I ${SRC_DIR} 

${BUILD_DIR}/main.o:main.cpp
	${CC} -std=${STD} -c main.cpp -o ${BUILD_DIR}/main.o -I ${INCLUDE_DIR} -I ../ -I ${SRC_DIR}
	
link:compile
	${CC} ${BUILD_DIR}/*.o -o ${BUILD_DIR}/main.exe -Llib -lglfw3dll
	
run:link
	${BUILD_DIR}/main

clean:
	rm -f ${BUILD_DIR}/*.o 
	rm -f ${BUILD_DIR}/main.exe