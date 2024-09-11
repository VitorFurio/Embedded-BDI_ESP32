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
  
        
agent-bdi: set-target translate build flash monitor

set-target: clean-build
	idf.py set-target esp32

build:
	idf.py build

flash:
	idf.py -p $(interface) flash

monitor:
	idf.py monitor

clean-build:
	rm -rf build/

######################## DEFAULT IDF MAKEFILE #################################

alice:
	./copy_examples.sh alice
	make agent-bdi
	
PROJECT_NAME := agent-loop




