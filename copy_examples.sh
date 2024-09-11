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
