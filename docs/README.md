# Robotwagentje

Bavo Debraekeleer<br>
Docent: Marc Smets<br>

Smart Systems, Major Internet of Things, Elektronica-ICT<br>
AP Hogeschool<br>
Academiejaar 2021-2022

<a href="https://bavodebraekeleer.github.io/bavod-robotwagentje-analyse/#/">GitHub Pages</a><br>



---

# Opdracht

Ontwerp van schakelingen om een robot wagentje aan te sturen.

---

## As-Is Situatie

<img src="./pictures/robotwagen_as-is_total.jpg" width="100%">

 - Voltage Regulator LM7805 through hole
 - Motord river SN754410 through hole + 2x 2 motor pins: 1A, 1B, 2A, 2B
 - 4x LED's: 1x rood, 2x geel, 1x groen
 - LCD scherm module, I²C pins op PCB: GND, SDA, SCL, 3V3
 - Ultrasoon module aansluiting: 5V, TRIG, ECHO, GND
 - 3 voeding pins: 3V3, 5V, GND
 - 2 pin aansluiting voor ? : 3V3, PQ_L
 - 2x 2 GPIO spare pins

---

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
 - 2x SMD Motor driver, prijs < €1, vb. LA6583MC-AH
 - OLED-scherm met I2C-sturing op PCB
 - ESP32 WROOM DevKit module, zie Schematic Checklist in Hardware Design Guidelines
 - Mounting drill holes, voor bevestiging op wagentje
 - Batterij aansluiting (GND, VCC)
 - 8line verbinden met ATMega
 
<img src="./pictures/8line_top.jpg" width="50%"> <img src="./pictures/8line_bottom.jpg" width="50%">


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

---

## Mindmap


---

# Hardware Analyse

## Blokschema

<img src="./pictures/" width="100%">

---

## Specificaties

### Microcontroller

<table style="width: 100%">
<colgroup>
    <col span="1" style="width: 15%;">
    <col span="2" style="width: 70%;">
	<col span="3" style="width: 25%;">
</colgroup>
<tr>
    <th>Naam</th>
    <th>Eigenschappen</th>
    <th>Data</th>
</tr>
<tr>
    <td>ESP32-WROOM-32</td>
    <td>
        <ul>
            <li><b>ESP32 WROOM DevKit module</b></li>
			<li>Core: ESP32-D0WD</li>
			<li>SPI flash: 4 MB, 32 Mbits, 3.3V</li>
			<li>Crustal: 40 MHz</li>
            <li>V<sub>cc</sub> = 3.0V - 3.6V</li>
            <li>I<sub>operating</sub> = 80mA</li>
			<li>I<sub>min delivered by power supply</sub> = 500mA</li>
			<li>Module interfaces: SD card, UART, SPI, SDIO, I2C, LED PWM, Motor PWM, I2S, IR, pulse counter, GPIO, capacitive touch sensor, ADC, DAC, TWAI.</li>
			<li>On-chip sensor: Hall sensor</li>
			<li>Operating temperature: -40°C ~ +85°C</li>
			<li><i>Eenheidsprijs: €3,82</i></li>
			<li><i>Lead time: 10 weken</i></li>
        </ul>
    </td>
    <td>
		<a href="./datasheets/esp32_wroom_32d_esp32_wroom_32u_datasheet_en-1365844.pdf">Datasheet Module</a><br>
		<a href="./datasheets/esp32_datasheet_en.pdf">Datasheet ESP32</a><br>
		<a href="./datasheets/esp32_hardware_design_guidelines_en.pdf">Hardware Design Guidelines</a><br>
		<a href="https://www.mouser.be/ProductDetail/Espressif-Systems/ESP32-WROOM-32U-H4?qs=Li%252BoUPsLEnumDLBsCjw4aA%3D%3D">Winkel</a><br>
	</td>
</tr>
</table>

---

### Sturing

<table style="width: 100%">
<colgroup>
    <col span="1" style="width: 15%;">
    <col span="2" style="width: 30%;">
    <col span="3" style="width: 40%;">
	<col span="4" style="width: 25%;">
</colgroup>
<tr>
    <th>Naam</th>
    <th>Eigenschappen</th>
    <th>Argumentatie</th>
    <th>Data</th>
</tr>
<tr>
    <td>LA6583MC-AH</td>
    <td>
        <ul>
            <li><b>Motor driver</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
<tr>
    <td>Naam</td>
    <td>
        <ul>
            <li><b>OLED-scherm</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
<tr>
    <td>8line</td>
    <td>
        <ul>
            <li><b>ATMega verbindingsbordje.</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
</table>

---

### Voeding

<table style="width: 100%">
<colgroup>
    <col span="1" style="width: 15%;">
    <col span="2" style="width: 30%;">
    <col span="3" style="width: 40%;">
	<col span="4" style="width: 25%;">
</colgroup>
<tr>
    <th>Naam</th>
    <th>Eigenschappen</th>
    <th>Argumentatie</th>
    <th>Data</th>
</tr>
<tr>
    <td>Naam</td>
    <td>
        <ul>
            <li><b>Batterij</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
<tr>
    <td>LDL1117 5V</td>
    <td>
        <ul>
            <li><b>SMD Voltage Regulator</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
<tr>
    <td>LDL1117 3.3V</td>
    <td>
        <ul>
            <li><b>SMD Voltage Regulator</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
<tr>
    <td>Naam</td>
    <td>
        <ul>
            <li><b>Polariteitsbeveiliging</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
</table>

---

### Sensoren

<table style="width: 100%">
<colgroup>
    <col span="1" style="width: 15%;">
    <col span="2" style="width: 30%;">
    <col span="3" style="width: 40%;">
	<col span="4" style="width: 25%;">
</colgroup>
<tr>
    <th>Naam</th>
    <th>Eigenschappen</th>
    <th>Argumentatie</th>
    <th>Data</th>
</tr>
<tr>
    <td>Naam</td>
    <td>
        <ul>
            <li><b>Linetracker</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
<tr>
    <td>Naam</td>
    <td>
        <ul>
            <li><b>IR-afstandssensor</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
<tr>
    <td>Naam</td>
    <td>
        <ul>
            <li><b>Ultrasoon afstandssensor</b></li>
            <li>V<sub>cc</sub> = V - V</li>
            <li>I<sub>max</sub> = mA</li>
			<li><i>Eenheidsprijs vanaf 10 stuks: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Argumentatie.
	</td>
    <td>
		<a href="./datasheet/">Datasheet</a><br>
		<a href="url">Winkel</a><br>
	</td>
</tr>
</table>

---

## Elektrisch Schema

<img src="./pictures/" width="100%"><br>
<a href="./elektrisch_schema.sch">Schematic File</a><br>

---

# Software Analyse

## Statediagram

---

## Flowcharts


---

# Planning

## Epics

---

## Technical Stories

---

## Sprints

---