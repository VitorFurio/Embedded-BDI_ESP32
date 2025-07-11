---
## Example
This example illustrates an agent called `sensor2`, which collaborates with other agents on fire detection. Upon detecting a condition indicating the presence of fire in its area, the agent enters an alert state and exchanges information with other agents in the region to determine if the event is a fire or an isolated incident that could be mistaken for one (e.g., a temperature increase due to a heat source like a stove, heater, etc.). In this example, a fire is considered present when at least two sensors detect fire, at which point the agent triggers an emergency alarm.

### Docker-based execution (recommended)
If the ESP32 board is connected to the /dev/ttyUSB0 serial port, type
```
docker run --device=/dev/ttyUSB0 -it --rm maiquelb/embedded-bdi:latest /bin/bash -c "cd /Embedded-BDI_ESP32 && . ~/esp/esp-idf/export.sh && make fire_sensors"
```

If the ESP32 board is connected to a different serial port:
- Acess the container via shell (replace `[SERIAL PORT]` with the proper value):
  ```
  docker run --device=[SERIAL PORT] -it --rm maiquelb/embedded-bdi:latest bash
  ```
- Set the proper serial port in the line 2 of the `Makefile`
  ```
  nano /Embedded-BDI_ESP32/Makefile
  ```
- Run the example
  ```
  make -C /Embedded-BDI_ESP32 fire_sensors
  ```
