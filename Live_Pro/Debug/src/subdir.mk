################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ControlJob.cpp \
../src/HttpClient.cpp \
../src/JobBuffer.cpp \
../src/JobPool.cpp \
../src/JobPoster.cpp \
../src/JobThread.cpp \
../src/Live_Pro.cpp \
../src/RtmpInfo.cpp \
../src/RtmpJob.cpp \
../src/WorkQueue.cpp 

OBJS += \
./src/ControlJob.o \
./src/HttpClient.o \
./src/JobBuffer.o \
./src/JobPool.o \
./src/JobPoster.o \
./src/JobThread.o \
./src/Live_Pro.o \
./src/RtmpInfo.o \
./src/RtmpJob.o \
./src/WorkQueue.o 

CPP_DEPS += \
./src/ControlJob.d \
./src/HttpClient.d \
./src/JobBuffer.d \
./src/JobPool.d \
./src/JobPoster.d \
./src/JobThread.d \
./src/Live_Pro.d \
./src/RtmpInfo.d \
./src/RtmpJob.d \
./src/WorkQueue.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/local/ffmpeg/include -I/usr/local/curl/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


