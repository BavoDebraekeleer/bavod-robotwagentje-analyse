# Robotwagentje

Bavo Debraekeleer<br>
Docent: Marc Smets<br>

Smart Systems, Major Internet of Things, Elektronica-ICT<br>
AP Hogeschool<br>
Academiejaar 2021-2022

<a href="https://bavodebraekeleer.github.io/bavod-robotwagentje-analyse/#/">GitHub Pages</a><br>





# Probleemstelling


## Opdracht

Ontwerp van schakelingen om een robot wagentje aan te sturen.


## As-Is Situatie

<img src="./pictures/robotwagen_as-is_total.jpg" width="100%">

 - Voltage Regulator LM7805 through hole
 - Motordriver SN754410 through hole + 2x 2 motor pins: 1A, 1B, 2A, 2B
 - 4x LED's: 1x rood, 2x geel, 1x groen
 - LCD scherm module, I²C pins op PCB: GND, SDA, SCL, 3V3
 - Ultrasoon module aansluiting: 5V, TRIG, ECHO, GND
 - 3 voeding pins: 3V3, 5V, GND
 - 2 pin aansluiting voor ? : 3V3, PQ_L
 - 2x 2 GPIO spare pins
 
 
## To-Be Situatie

### Doelen

 - Sensoren toepassen in een praktische schakeling.
 - Voldoende materiaal genereren voor gebruik in het eerste jaar.
 - Besturing voorzien.


### Sturingschakeling vereisten:

Dit is de hoofd PCB.

 - 2x UART connectoren
 - 3x I²C connectoren
 - Voltage regulator LDL1117 van 5V en 3.3V SMD
 - Polariteitsbeveiliging
 - 2x SMD Motordriver, prijs < €1, vb. LA6583MC-AH
 - OLED-scherm met I2C-sturing op PCB
 - ESP32 WROOM module, zie Schematic Checklist in Hardware Design Guidelines
 - 8line verbinden met ATMega
 - Mounting drill holes, voor bevestiging op wagentje
 - Batterij aansluiting (GND, VCC)
 
 <img src="./pictures/8line_top.jpg" width="50%">
 <img src="./pictures/8line_bottom.jpg" width="50%">


### Sensorschakelingen vereisten:

Op aparte PCB bordjes.

 - Linetracker (dringend)
 - IR-afstandssensoren 
 - Ultrasoon afstandssensoren
 - …


### Besturing

 - Manuele bediening mogelijkheid.
 - Automatisch rijden.
 - Volgens vast patroon rijden.

Er moeten ook een aantal verkeerssignalisaties ontwikkeld worden zoals verkeerslichten, slagbomen, enz.<br>
Deze moeten dienen om de software van het wagentje te kunnen testen.


## Mindmap



# Hardware Analyse

## Blokschema

## Onderdelen



# Software Analyse

## Statediagram

## Flowcharts


# Planning

## Epics

## Technical Stories

## Sprints