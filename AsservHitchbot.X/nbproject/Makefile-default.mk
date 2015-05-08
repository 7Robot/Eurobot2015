#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/AsservHitchbot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/AsservHitchbot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=lib_asserv/private/asserv.c lib_asserv/private/debug.c lib_asserv/private/motion.c lib_asserv/private/odo.c lib_asserv/private/pid.c lib_asserv/private/tools.c user.c interrupts.c main.c motor.c ax12.c actions_ax12.c communication.c sick.c ultrason.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/lib_asserv/private/asserv.o ${OBJECTDIR}/lib_asserv/private/debug.o ${OBJECTDIR}/lib_asserv/private/motion.o ${OBJECTDIR}/lib_asserv/private/odo.o ${OBJECTDIR}/lib_asserv/private/pid.o ${OBJECTDIR}/lib_asserv/private/tools.o ${OBJECTDIR}/user.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/motor.o ${OBJECTDIR}/ax12.o ${OBJECTDIR}/actions_ax12.o ${OBJECTDIR}/communication.o ${OBJECTDIR}/sick.o ${OBJECTDIR}/ultrason.o
POSSIBLE_DEPFILES=${OBJECTDIR}/lib_asserv/private/asserv.o.d ${OBJECTDIR}/lib_asserv/private/debug.o.d ${OBJECTDIR}/lib_asserv/private/motion.o.d ${OBJECTDIR}/lib_asserv/private/odo.o.d ${OBJECTDIR}/lib_asserv/private/pid.o.d ${OBJECTDIR}/lib_asserv/private/tools.o.d ${OBJECTDIR}/user.o.d ${OBJECTDIR}/interrupts.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/motor.o.d ${OBJECTDIR}/ax12.o.d ${OBJECTDIR}/actions_ax12.o.d ${OBJECTDIR}/communication.o.d ${OBJECTDIR}/sick.o.d ${OBJECTDIR}/ultrason.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/lib_asserv/private/asserv.o ${OBJECTDIR}/lib_asserv/private/debug.o ${OBJECTDIR}/lib_asserv/private/motion.o ${OBJECTDIR}/lib_asserv/private/odo.o ${OBJECTDIR}/lib_asserv/private/pid.o ${OBJECTDIR}/lib_asserv/private/tools.o ${OBJECTDIR}/user.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/motor.o ${OBJECTDIR}/ax12.o ${OBJECTDIR}/actions_ax12.o ${OBJECTDIR}/communication.o ${OBJECTDIR}/sick.o ${OBJECTDIR}/ultrason.o

# Source Files
SOURCEFILES=lib_asserv/private/asserv.c lib_asserv/private/debug.c lib_asserv/private/motion.c lib_asserv/private/odo.c lib_asserv/private/pid.c lib_asserv/private/tools.c user.c interrupts.c main.c motor.c ax12.c actions_ax12.c communication.c sick.c ultrason.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/AsservHitchbot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/lib_asserv/private/asserv.o: lib_asserv/private/asserv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/asserv.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/asserv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/asserv.c  -o ${OBJECTDIR}/lib_asserv/private/asserv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/asserv.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/asserv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/debug.o: lib_asserv/private/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/debug.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/debug.c  -o ${OBJECTDIR}/lib_asserv/private/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/debug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/motion.o: lib_asserv/private/motion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/motion.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/motion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/motion.c  -o ${OBJECTDIR}/lib_asserv/private/motion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/motion.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/motion.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/odo.o: lib_asserv/private/odo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/odo.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/odo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/odo.c  -o ${OBJECTDIR}/lib_asserv/private/odo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/odo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/odo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/pid.o: lib_asserv/private/pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/pid.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/pid.c  -o ${OBJECTDIR}/lib_asserv/private/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/pid.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/pid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/tools.o: lib_asserv/private/tools.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/tools.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/tools.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/tools.c  -o ${OBJECTDIR}/lib_asserv/private/tools.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/tools.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/tools.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/user.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interrupts.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor.o: motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motor.o.d 
	@${RM} ${OBJECTDIR}/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor.c  -o ${OBJECTDIR}/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ax12.o: ax12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ax12.o.d 
	@${RM} ${OBJECTDIR}/ax12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ax12.c  -o ${OBJECTDIR}/ax12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ax12.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ax12.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/actions_ax12.o: actions_ax12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/actions_ax12.o.d 
	@${RM} ${OBJECTDIR}/actions_ax12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  actions_ax12.c  -o ${OBJECTDIR}/actions_ax12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/actions_ax12.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/actions_ax12.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/communication.o: communication.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/communication.o.d 
	@${RM} ${OBJECTDIR}/communication.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  communication.c  -o ${OBJECTDIR}/communication.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/communication.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/communication.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sick.o: sick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sick.o.d 
	@${RM} ${OBJECTDIR}/sick.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sick.c  -o ${OBJECTDIR}/sick.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sick.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sick.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ultrason.o: ultrason.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ultrason.o.d 
	@${RM} ${OBJECTDIR}/ultrason.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ultrason.c  -o ${OBJECTDIR}/ultrason.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ultrason.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ultrason.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/lib_asserv/private/asserv.o: lib_asserv/private/asserv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/asserv.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/asserv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/asserv.c  -o ${OBJECTDIR}/lib_asserv/private/asserv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/asserv.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/asserv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/debug.o: lib_asserv/private/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/debug.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/debug.c  -o ${OBJECTDIR}/lib_asserv/private/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/debug.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/motion.o: lib_asserv/private/motion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/motion.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/motion.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/motion.c  -o ${OBJECTDIR}/lib_asserv/private/motion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/motion.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/motion.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/odo.o: lib_asserv/private/odo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/odo.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/odo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/odo.c  -o ${OBJECTDIR}/lib_asserv/private/odo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/odo.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/odo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/pid.o: lib_asserv/private/pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/pid.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/pid.c  -o ${OBJECTDIR}/lib_asserv/private/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/pid.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/pid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib_asserv/private/tools.o: lib_asserv/private/tools.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/lib_asserv/private" 
	@${RM} ${OBJECTDIR}/lib_asserv/private/tools.o.d 
	@${RM} ${OBJECTDIR}/lib_asserv/private/tools.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_asserv/private/tools.c  -o ${OBJECTDIR}/lib_asserv/private/tools.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib_asserv/private/tools.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib_asserv/private/tools.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/user.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interrupts.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor.o: motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motor.o.d 
	@${RM} ${OBJECTDIR}/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor.c  -o ${OBJECTDIR}/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ax12.o: ax12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ax12.o.d 
	@${RM} ${OBJECTDIR}/ax12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ax12.c  -o ${OBJECTDIR}/ax12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ax12.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ax12.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/actions_ax12.o: actions_ax12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/actions_ax12.o.d 
	@${RM} ${OBJECTDIR}/actions_ax12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  actions_ax12.c  -o ${OBJECTDIR}/actions_ax12.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/actions_ax12.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/actions_ax12.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/communication.o: communication.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/communication.o.d 
	@${RM} ${OBJECTDIR}/communication.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  communication.c  -o ${OBJECTDIR}/communication.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/communication.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/communication.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sick.o: sick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sick.o.d 
	@${RM} ${OBJECTDIR}/sick.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sick.c  -o ${OBJECTDIR}/sick.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sick.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sick.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ultrason.o: ultrason.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ultrason.o.d 
	@${RM} ${OBJECTDIR}/ultrason.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ultrason.c  -o ${OBJECTDIR}/ultrason.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ultrason.o.d"        -g -omf=elf -mlarge-code -mlarge-data -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ultrason.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/AsservHitchbot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/AsservHitchbot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/AsservHitchbot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/AsservHitchbot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/AsservHitchbot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
