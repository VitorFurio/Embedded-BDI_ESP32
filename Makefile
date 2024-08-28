# Definir a interface serial, ajuste conforme necessário
interface=/dev/ttyUSB0

include agent.config

translate:
	javac -cp embedded-bdi/lib/parser/lib/jason-2.6.jar                       \
        embedded-bdi/lib/parser/src/translator/As2Json.java                   \
        embedded-bdi/lib/parser/src/translator/PlanSkeleton.java              \
        embedded-bdi/lib/parser/src/translator/BodyInstruction.java           \
        embedded-bdi/lib/parser/src/translator/EventOperatorType.java         \
        embedded-bdi/lib/parser/src/translator/HeaderCreator.java

	java -cp                                                                  \
	    embedded-bdi/lib/parser/lib/jason-2.6.jar:embedded-bdi/lib/parser/src \
        translator.As2Json                                                    \
        main/data/agentspeak.asl                                              \
        main/data/functions.h                                                 \
        main/src/config/configuration.h                                       \
        $(EVENT_BASE_SIZE) $(INTENTION_BASE_SIZE) $(INTENTION_STACK_SIZE)
        
agent-bdi: set-target translate
	idf.py -p $(interface) flash monitor

agent-trad: set-target
	idf.py -p $(interface) flash monitor

set-target:
	idf.py set-target esp32

######################## DEFAULT IDF MAKEFILE #################################

PROJECT_NAME := agent-loop
# include $(IDF_PATH)/make/project.mk




