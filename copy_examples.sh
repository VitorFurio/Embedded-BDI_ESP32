#!/bin/bash

if [ $# -eq 0 ]; then
  echo "No arguments supplied"
  exit 1
fi

if [ "$#" -ne 1 ]; then
  echo "Illegal number of parameters"
  exit 1
fi

if [[ "$1" == "alice" ]];
then
  rm -rf main/data/*
  rm -rf main/src/config/*
  rm -rf main/src/agent*
  rm -rf main/CMakeLists.txt
  cp examples/alice/agentspeak.asl main/data/
  cp examples/alice/functions.* main/data/
  cp examples/alice/agent_loop.cpp main/src/
  cp examples/alice/CMakeLists.txt main/
  cp examples/alice/agent.config .
fi

if [[ "$1" == "sensor" ]];
then
  rm -rf main/data/*
  rm -rf main/src/config/*
  rm -rf main/src/agent*
  rm -rf main/CMakeLists.txt
  cp examples/fire_sensors/agentspeak.asl main/data/
  cp examples/fire_sensors/functions.* main/data/
  cp examples/fire_sensors/agent_loop.cpp main/src/
  cp examples/fire_sensors/CMakeLists.txt main/
  cp examples/fire_sensors/agent.config .
fi


