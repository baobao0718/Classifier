################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BasePoint.cpp \
../src/DDA.cpp \
../src/DataUnit.cpp \
../src/Feature.cpp \
../src/HandWritingRecognize.cpp \
../src/ListTable.cpp \
../src/MyStroke.cpp \
../src/P2DMNClass.cpp \
../src/Recognize.cpp \
../src/Transform.cpp \
../src/VQFileRead.cpp \
../src/distance.cpp \
../src/stdafx.cpp 

OBJS += \
./src/BasePoint.o \
./src/DDA.o \
./src/DataUnit.o \
./src/Feature.o \
./src/HandWritingRecognize.o \
./src/ListTable.o \
./src/MyStroke.o \
./src/P2DMNClass.o \
./src/Recognize.o \
./src/Transform.o \
./src/VQFileRead.o \
./src/distance.o \
./src/stdafx.o 

CPP_DEPS += \
./src/BasePoint.d \
./src/DDA.d \
./src/DataUnit.d \
./src/Feature.d \
./src/HandWritingRecognize.d \
./src/ListTable.d \
./src/MyStroke.d \
./src/P2DMNClass.d \
./src/Recognize.d \
./src/Transform.d \
./src/VQFileRead.d \
./src/distance.d \
./src/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


