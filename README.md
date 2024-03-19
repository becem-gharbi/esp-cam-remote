# ESP Cam Remote

This project permits remote camera streaming from `ESP32-Cam` board. It's built with [ESP Admin](https://esp-admin.tn/) which is a web-based platform for remote management of ESP32 microcontrollers. The **firmware** takes camera frames as jpeg images and publish them to the MQTT broker registered on ESP Admin. The frontend **app** subscribes to the stream topic and renders the incoming frames on an image element. The result is a video stream with a frame rate that depends on image quality and network latency.

## Requirements
- Node.js +v18
- PlatformIO
- ESP32-Cam board
  
## Setup

1. Create an account on [ESP Admin Cloud](https://app.esp-admin.tn/).
2. Register your MQTT broker on Settings page. It's recommended to use [HiveMQ Cloud](https://www.hivemq.com).
3. Create a new project with the following commands.
   - `Viewer_Count` | `{"viewer":"count"}`
   - `Viewer_Reset` | `{"viewer":"reset"}`
4. Create a new device and link it to the project.
5. Clone this repository.
6. On firmware, rename `example.credentials.h` to `credentials.h` and set secrets.
7. Build and flash the firmware to `ESP32-CAM` board.
8. On app, rename `example.env` to `.env` and set secrets.
9. Install dependencies and run `dev` script.

## License

[MIT License](./LICENSE)
