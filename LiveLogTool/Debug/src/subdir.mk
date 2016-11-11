################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CvFileReader.cpp \
../src/CvImageDeal.cpp \
../src/CvLogImage.cpp \
../src/CvLogTotal.cpp \
../src/main.cpp 

OBJS += \
./src/CvFileReader.o \
./src/CvImageDeal.o \
./src/CvLogImage.o \
./src/CvLogTotal.o \
./src/main.o 

CPP_DEPS += \
./src/CvFileReader.d \
./src/CvImageDeal.d \
./src/CvLogImage.d \
./src/CvLogTotal.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/json/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


