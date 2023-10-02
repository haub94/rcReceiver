# rcReceiver
**RC-receiver (based on Arduino nano and NRF24-L01) which can used for an aircraft model.**
<br>
<br>
The code based on a [tutorial](https://electronoobs.com/eng_robotica_tut4_4.php) from ELECTRONOOBS - thank you for this great work! <br>
I created the code to control a 3D printed airplane but you can use it for anything you want to control per 2.4 GHz. The hardware used is an Arduino nano and the NRF24-L01 radio module. Below is the pinout of the radio module and the microcontroller:
 
 ## 🔌 Controller-pinout
| Connection | PinL | PinR | Connection       |
|------------|:----:|:----:|------------------|
|            |  VIN |  TX1 |                  |
|            |  GND |  RX0 |                  |
|            |  RST |  RST |                  |
|            |  +5V |  GND |                  |
|            |  A7  |  D2  |                  |
|            |  A6  |  D3  | Rudder RD        |
|            |  A5  |  D4  |                  |
|            |  A4  |  D5  | Aileron right AR |
|            |  A3  |  D6  | Aileron left AL  |
|            |  A2  |  D7  | NRF24/CE         |
|            |  A1  |  D8  | NRF24/CNS        |
|            |  A0  |  D9  | Propeller PR     |
|            | AREF |  D10 | Elevator EL      |
|            |  3V3 |  D11 | NRF24/MOSI       |
| NRF24/SCK  |  D13 |  D12 | NRF24/MISO       |


## 🔌 NRF24-L01 connectiontable
| controller | - | NRF24-L01 |
|:----------:|:-:|:---------:|
|     GND    | - |    GND    |
|    DI 7    | - |     CE    |
|    DI 13   | - |    SCK    |
|    DI 12   | - |    MISO   |
|     3V3    | - |    VCC    |
|    DI 8    | - |    CNS    |
|    DI 11   | - |    MOSI   |
|      /     | - |    IRQ    |

## ❗Important Notes❗
Please consider it as a prototype. Currently there is no failsafe function: in case of signal loss the model will go straight ahead in the last indicated direction until the battery is empty. It is on my list...
## PlatformIO
Note that i use VS Code with the Plugin **PlatformIO** (ID: platformio.platformio-ide). I can highly recomand this Plugin, so maybe you should check it out 😊. Otherwise you should delete the file: platformio.ini.