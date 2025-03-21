---
## Example

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
