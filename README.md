# ST Wireless Remote Controller

Open Source Wireless remote for Raymarine Seatalk ST1000/ST2000 autopilots as well as ST60 speed timer. Allows controlling of autopilot and various raymarine displays using 433mhz remote as well as mobile/tablet using built in WIFI Access Point. 

Aside from the remote functionality the connection to the seatalk bus allows us to read signals and decode other instrument data such as wind, speed , depth etc . Currently developing Seatalk -> NMEA 183 TCPIP transposer to allow Open CPN (and other such applications) to use the seatalk data , this would be done again over the wireless connection. This is currently under development . Other ideas for the future include a man over board mode where it'll set the heading nose to wind . These will be documented once completed on the main https://www.nauti-control.com website.

# Software
The code is written in C++ using platform IO . I use Visual Code as my editor . The firmware uses soft serial with the parity bit acting at the 9th bit that seatalk protocol uses.  The seatalk datagrams I have been using an excellent technical guide by Thomas Knauf http://thomasknauf.de/rap/seatalk2.htm . There is two parts to the code 1. The main firmware 2. A mini web application for settings the button mapping settings as well as allowing the device to be controlled from a mobile device . This is written to the esp32 spiffs. These get built and uploaded to the ESP32 seperately from with the platform IO extension in Visual Code.

# Hardware
You can purchase a fully hand built Wireless Controller from our online store which will help support ongoing development and new features <br/>
https://nauti-control.com/product/st-wireless-controller-fully-built-with-4-button-remote/<br/>
This includes a remote , 3d printed case and fully built PCB with latest firmware pre-installed , just plug into your seatalk system and go.<br/>

Bill Of Materials with links that will support on going development through affiliation or direct purchase.

1 x PCB - https://nauti-control.com/product/st-wireless-remote-controller-pcb/<br/>
1 x ESP32 - https://s.click.aliexpress.com/e/_DD5c10v <br />
1 x RXB6 433Mhz Superheterodyne Receiver - https://s.click.aliexpress.com/e/_DCJstw9 <br />
1 x 4 Button Remote https://nauti-control.com/product/4-button-wireless-remote-for-st-wireless-remote-controller/<br />
1 x 7805 Voltage REgulator - https://s.click.aliexpress.com/e/_DBNSCGH <br />
1 x BC547 Transister - https://s.click.aliexpress.com/e/_DCKfQwp <br />
2 x 270ohm 1/4W Resistor - https://s.click.aliexpress.com/e/_DkgFIJ7 <br />
1 x 1kohm 1/4 Resistor - https://s.click.aliexpress.com/e/_DkgFIJ7 <br />
1 x 3.9kohm 1/4 Resistor -https://s.click.aliexpress.com/e/_DkgFIJ7 <br />
3 x 10kohm 1/4 Resistor - https://s.click.aliexpress.com/e/_DkgFIJ7 <br />
2 x PC817 Optocoupler -https://s.click.aliexpress.com/e/_DEU20qv <br />
1 x PCB Terminal Block 5.00mm pitch - https://s.click.aliexpress.com/e/_DFGZrcp <br />

Donate to support on going development and features.
https://nauti-control.com/donate/

