# Robotwagentje

Bavo Debraekeleer<br>
Docent: Marc Smets<br>

Smart Systems, major Internet of Things, Elektronica-ICT<br>
AP Hogeschool<br>
Academiejaar 2021-2022

<a href="https://bavodebraekeleer.github.io/bavod-robotwagentje-analyse/#/">Robotwagentje Analyse GitHub Pages</a><br>
<a href="https://ap-it-gh.github.io/ssys-cursus/#/deliverables/analyse">Smart Systems GitHub Pages</a><br>


---

# Probleemstelling

Ontwerp van een schakelingen om een robotwagentje aan te sturen.
Dit opgedeeld in twee deel schakelingen.
Een hoofd PCB met een ESP32, als ook een dochter PCB met een ATMega en sensoren om de sturing te kunnen realiseren.
De vereisten zijn omschreven in de To-Be Situatie.

---

## As-Is Situatie

<img src="./pictures/as-is/robotwagen_as-is_total.jpg" width="100%">

 - Voltage Regulator LM7805 through hole
 - Motord river SN754410 through hole + 2x 2 motor pins: 1A, 1B, 2A, 2B
 - 4x LED's: 1x rood, 2x geel, 1x groen
 - LCD scherm module, I²C pins op PCB: GND, SDA, SCL, 3V3
 - Ultrasoon module aansluiting: 5V, TRIG, ECHO, GND
 - 3 voeding pins: 3V3, 5V, GND
 - 2 pin aansluiting: 3V3, PQ_L
 - 2x 2 GPIO spare pins

---

## To-Be Situatie

### Opdracht doelen

 - Sensoren toepassen in een praktische schakeling.
 - Voldoende materiaal genereren voor gebruik in het eerste jaar.
 - Besturing voorzien.


### Sturingsschakeling vereisten:

Dit is de hoofd PCB.

 - 2x UART connectoren
 - 3x I²C connectoren
 - Voltage regulator LDL1117 SMD
	- 5V
	- 3.3V
 - Polariteitsbeveiliging
 - 2x SMD Motor driver, vb. LA6583MC-AH
	- 7.2V
	- 700mA (Start stroom = 6x nominale stroom)
	- Prijs < €1
	- EMK beveiligingsdiode in tegen polariteit. Misschien reeds aanwezig op IC. Best altijd extra diode bij plaatsen voor de zekerheid.
 - OLED-scherm met I²C-sturing op PCB
 - ESP32 WROOM DevKit module, zie Schematic Checklist in Hardware Design Guidelines
 - Mounting drill holes, voor bevestiging op wagentje
 - Batterij aansluiting (GND, VCC)


### Sensorenschakeling vereisten:

Op dochter PCB bordje.

 - Ultrasoon + IR afstandssensoren
 - 8 channel IR Linetracker


### Besturing

 - Manuele bediening mogelijkheid.
 - Automatisch rijden.
 - Volgens vast patroon rijden.

Er moeten ook een aantal verkeer signalisaties ontwikkeld worden zoals verkeerslichten, slagbomen, enz.<br>
Deze moeten dienen om de software van het wagentje te kunnen testen.

---

## Mindmap

<iframe width="768" height="432" src="https://miro.com/app/embed/uXjVOER2lsE=/?pres=1&frameId=3458764521281290834" frameBorder="0" scrolling="no" allowFullScreen></iframe>
<a href="./pictures/diagrams/mindmap.jpg">Mindmap afbeelding</a>


---

# Hardware Analyse

## Blokschema

<iframe width="768" height="432" src="https://miro.com/app/embed/uXjVOEQMNko=/?pres=1&frameId=3458764521464112345" frameBorder="0" scrolling="no" allowFullScreen></iframe>
<a href="./pictures/diagrams/blokschema_1.jpg">Blokschema afbeelding 1</a><a href="./pictures/diagrams/blokschema_2.jpg">Blokschema afbeelding 2</a>


---

## Specificaties

Reference websites:
 - <a href="https://be.farnell.com/">Farnell</a>
 - <a href="https://www.mouser.be/">Mouser</a>
 - <a href="https://www.tinytronics.nl/shop/nl">TinyTronics</a>
 - <a href="https://www.allaboutcircuits.com/electronic-components">All About Circuits</a>


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
    <td>ESP32-WROOM-32 Dev. Board</td>
    <td>
        <ul>
            <li><b>ESP32 WROOM DevKit module</b></li>
			<li>Core: ESP32-D0WD</li>
			<li>SPI flash: 4 MB, 32 Mbits, 3.3 V</li>
			<li>Crustal: 40 MHz</li>
            <li>V<sub>cc</sub> = 3.0 - 3.6 V</li>
            <li>I<sub>operating</sub> = 80 mA</li>
			<li>I<sub>min delivered by power supply</sub> = 500 mA</li>
			<li>Module interfaces: SD card, UART, SPI, SDIO, I2C, LED PWM, Motor PWM, I2S, IR, pulse counter, GPIO, capacitive touch sensor, ADC, DAC, TWAI.</li>
			<li>On-chip sensor: Hall sensor</li>
			<li>Operating temperature: -40°C ~ +85°C</li>
			<li><i>Eenheidsprijs: €11,98</i></li>
			<li><i>Lead time: 10 weken (op voorraad)</i></li>
        </ul>
    </td>
    <td>
		<a href="./datasheets/esp32_wroom_32d_esp32_wroom_32u_datasheet_en-1365844.pdf">Datasheet Module</a><br>
		<a href="./datasheets/esp32_datasheet_en.pdf">Datasheet ESP32</a><br>
		<a href="./datasheets/esp32_hardware_design_guidelines_en.pdf">Hardware Design Guidelines</a><br>
		<a href="https://www.bol.com/be/nl/p/esp-wroom-32-ontwikkelbord/9200000114634593/?Referrer=ADVNLGOO002013-G-137016892532-S-1080766724149-9200000114634593&gclid=CjwKCAjwoduRBhA4EiwACL5RP3gmvcCjgniShMIKJF6Tj-c8ILHCnZigB3Wc8GkKKFBQUkc2TnLEZBoC6nkQAvD_BwE">Winkel</a><br>
		
		<a href="https://www.elektor.nl/wemos-lolin-esp32-oled-display-module-for-arduino"Alternatief met OLED</a>
		
		<a href="https://www.espressif.com/en/products/devkits">Alternatieve DevKits</a>
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
			<li>Single Phase Driver With Hall Sensor Method (no Speed Control)</li>
			<li>SMD IC</li>
			<li>Output Configuration: Half Bridge, 2 outputs</li>
            <li>V<sub>cc</sub> = 2.8 - 14 V</li>
			<li>V<sub>cc max</sub> = 15 V
			<li>I<sub>cc drive</sub> = 4 - 6 - 9 mA
            <li>I<sub>OUT max</sub> = 800 mA</li>
			<li><i>Eenheidsprijs: 0,526€</i></li>
			<li><i>Lead time: onbekend (op voorraad)</i></li>
        </ul>
    </td>
    <td>
		Deze Motor Driver heeft twee outputs en wordt gebruikt om één motor aan te sturen in twee richtingen.
		Voor twee motors zijn er dus twee nodig in de schakeling.
		Een enkele IC om de twee motors aan te sturen komt veel duurder uit of zijn niet op voorraad.
		
		<a href="https://www.mouser.be/ProductDetail/Toshiba/TB6612FNGC8EL?qs=rsevcuukUAy2UalRuv4E%2FQ%3D%3D">Alternatief: TB6612FNG</a>
	</td>
    <td>
		<a href="./datasheets/LA6583MC-AH.pdf">Datasheet</a><br>
		<a href="https://be.farnell.com/on-semiconductor/la6583mc-ah/mtr-drvr-sngl-phase-fan-motor/dp/2728202?st=LA6583MC-AH">Winkel</a><br>
	</td>
</tr>
<tr>
    <td>Seeed Studio Grove 104020208</td>
    <td>
        <ul>
            <li><b>0.96" OLED Display 128x64</b></li>
            <li>V<sub>cc</sub> = 3.3 - 5 V</li>
            <li>I<sub>cc</sub> = 9 - 15 mA</li>
			<li>Controller: SSD1315</li>
			<li>Comm protocol: I²C</li>
			<li>Connector: JST 4P</li>
			<li><i>Eenheidsprijs: €4,60 - €7,00</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Zeer goedkope OLED van gemiddelde grote die zowel op 3.3 V als op 5 V werkt.
		De JST connector maakt verbinden gemakkelijk. Deze zit echter wel aan de bovenkant, wat niet de meest praktische plaats is.
		De toepassing is hier echter voor gebruik door studenten waarbij het een voordeel is dat alles goed zichtbaar is.
		
		Er wordt hier gekozen voor een module omdat losse OLED displays moeilijk vindbaar zijn en/of duurder uitkomen, en meer werk zijn.
		
		Enkele merkloze alternatieven van TinyTronics met PIN connectors:
		 - <a href="https://www.tinytronics.nl/shop/nl/displays/oled/0.96-inch-oled-display-128*64-pixels-wit-i2c">0.96" 128x64 SSD1306 voor €7,00</a>
		 - <a href="https://www.tinytronics.nl/shop/nl/displays/oled/1.3-inch-oled-display-128*64-pixels-wit-i2c">1.3" 128x64 SSH1106 voor €8,00</a>
		 - <a href="https://www.tinytronics.nl/shop/nl/displays/oled/1.5-inch-oled-display-128*128-pixels-wit-i2c">1.5" 128x128 SSD1327 voor €10,00</a>
		 
		<a href="https://www.tinytronics.nl/shop/nl/kabels-en-connectoren/kabels-en-adapters/jst-compatible/wemos-i2c-kabel-sh1.0-4p-10cm">JST 4P kabel I²C</a>
		<a href="https://www.tinytronics.nl/shop/nl/kabels-en-connectoren/connectoren/jst-compatible/jst-xh-krimpstekker-en-behuizing-set>JST-HX stekkers set</a>
	</td>
    <td>
		<a href="https://wiki.seeedstudio.com/Grove-OLED-Display-0.96-SSD1315/">Fabrikant product info</a>
		<a href="./datasheets/OEL_Display_Module_SJY-2864KSWPG01.pdf">OLED Module Datasheet</a><br>
		<a href="https://www.distrelec.biz/en/ssd1315-grove-96-128-64-monochrome-oled-display-seeed-studio-104020208/p/30164993?utm_source=octoX&utm_medium=cse&utm_campaign=octo-feed&ext_cid=ceoctaqzzen-na">Winkel Distrelec</a><br>
		<a href="https://www.tinytronics.nl/shop/nl/displays/oled/seeed-studio-grove-oled-display-0.96-inch-128*64-pixels-wit-ssd1315">Winkel TinyTronics</a><br>
		<a href="https://www.digikey.be/en/products/detail/104020208/1597-104020208-ND/10667534?utm_campaign=allaboutcircuits&utm_medium=aggregator&curr=usd&utm_source=octopart">Winkel Digi-Key</a><br>
		<a href="https://github.com/olikraus/u8g2">Bibliotheek: U8g2</a><br>
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
    <td>MJKDZ MIR-3.0Y</td>
    <td>
        <ul>
            <li><b>8x IR Line Tracking Module</b></li>
            <li>V<sub>cc</sub> = 3 - 5 V</li>
            <li>I<sub>max</sub> = ? mA</li>
			<li>Bereik (max. bij 5V) = 40 mm
			<li>Afmetingen LxB: 17 x 67 mm
			<li><i>Eenheidsprijs: €6,00</i></li>
			<li><i>Lead time: onbekend (op voorraad)</i></li>
        </ul>
    </td>
    <td>
		Gegeven in de opgave.
	</td>
    <td>
		<a href="http://www.mjkdz.com/mjkdz/products/18365968.html">Fabrikant website</a><br>
		<a href="https://www.tinytronics.nl/shop/nl/sensoren/optisch/infrarood/8x-ir-lijn-tracking-module-40mm-bereik">Winkel TinyTronics</a><br>
	</td>
</tr>
<tr>
    <td>PCF8574</td>
    <td>
        <ul>
            <li><b>Remote 8-bit I/O Expander I²C</b></li>
            <li>V<sub>cc</sub> = 2.5 - 6 V</li>
            <li>I<sub>cc Operating</sub> = 40 - 100 μA</li>
			<li>I<sub>cc Standby</sub> = 2.5 - 10 μA</li>
			<li><i>Eenheidsprijs: €</i></li>
			<li><i>Lead time: </i></li>
        </ul>
    </td>
    <td>
		Bovenstaande Line Tracker heeft op zich al 9 pins nodig. Bovenop de andere vereisten is dit te veel voor de hoeveelheid GPIO pins de ESP32 heeft.
		Er is dus nood aan een IO uitbreiding zoals deze. Deze kan de D1-D8 outputs van de IR sensors opvangen en via I²C doorsturen waardoor de de vereiste GPIO pins op de ESP32 herleid worden naar 3.
	</td>
    <td>
		<a href="./datasheet/PCF8574_IOExpander_TI.pdf">Datasheet TI</a><br>
		<a href="./datasheet/PCF8574_IOExpander_NXP.pdf">Datasheet NXP</a><br>
		<a href="https://www.mouser.be/ProductDetail/Texas-Instruments/PCF8574DGVR?qs=wgAEGBTxy7kn%2FU04Mebwcg%3D%3D">Winkel Mouser PCF8574DGVR</a><br>
		<a href="https://be.farnell.com/nxp/pcf8574t-3-512/i-o-expander-8bit-remote-so-16/dp/1506644?st=pcf8574">Winkel Farnell PCF8574T/3,512</a><br>
	</td>
</tr>
<tr>
    <td>Sharp GP2Y0A21YK0F</td>
    <td>
        <ul>
            <li><b>IR-afstandssensor</b></li>
            <li>V<sub>cc</sub> = 4.5 - 5.5 V</li>
            <li>I<sub>typ</sub> = 30 mA</li>
			<li>Bereik: 100 - 800 mm
			<li>Afmetingen: 29.5 x 13 x 13.5 mm
			<li><i>Eenheidsprijs: €5,50 - 12,06</i></li>
			<li><i>Lead time: 16 weken (op voorraad)</i></li>
        </ul>
    </td>
    <td>
		Op voorraad in het labo.
	</td>
    <td>
		<a href="./datasheets/Sharp_GP2Y0A21YK0F.pdf">Datasheet</a><br>
		<a href="https://www.tinytronics.nl/shop/nl/sensoren/afstand/sharp-optische-afstandsensor-gp2y0a21yk0f">Winkel TinyTronics</a><br>
		<a href="https://be.farnell.com/sharp/gp2y0a21yk0f/sensor-distance-analogue/dp/1243869?ost=gp2y0a21yk0f">Winkel Farnell</a><br>
		<a href="https://www.mouser.be/ProductDetail/Sharp-Microelectronics/GP2Y0A21YK0F?qs=5S%2F4hkdqNNcI0gpWLEuQ8w%3D%3D">Winkel Mouser</a><br>
	</td>
</tr>
<tr>
    <td>HC-SR04</td>
    <td>
        <ul>
            <li><b>Ultrasoon afstandssensor</b></li>
            <li>V<sub>cc</sub> = 5 V</li>
            <li>I<sub>cc</sub> = <2 - 15 mA</li>
			<li>Bereik: 20 - 4500 mm
			<li>Resolutie: 3 mm
			<li>Sensor hoek: <15°
			<li>Ultrasone freq.: 40 kHz
			<li><i>Eenheidsprijs: €3,00 - 7,21</i></li>
			<li><i>Lead time: 16 weken (op voorraad)</i></li>
        </ul>
    </td>
    <td>
		Op voorraad in het labo.
		Wat variatie in technische gegevens tussen leveranciers. Goed nakijken of het 3 V of 5 V logica betreft.
	</td>
    <td>
		<a href="./datasheets/distance_measurement_ultrasound_hcsr04-2489278.pdf">Datasheet</a><br>
		<a href="./datasheets/HC-SR04_Adafruit_Product_Overview_3942.pdf">Data and application notes.</a><br>
		<a href="https://www.tinytronics.nl/shop/nl/sensoren/afstand/ultrasonische-sensor-hc-sr04">Winkel TinyTronics</a><br>
		<a href="https://www.mouser.be/ProductDetail/Adafruit/3942?qs=byeeYqUIh0OD1hDPcrj%252BAQ%3D%3D">Winkel Mouser (Adafruit)</a><br>
		<a href="https://www.mouser.be/ProductDetail/OSEPP-Electronics/HC-SR04?qs=wNBL%252BABd93PqZEhuhHkuOw%3D%3D">Winkel Mouser (SEPP)</a><br>
		<a href="https://www.osepp.com/downloads/HCSR04_Library.zip">OSEPP Library</a>
		<a href="https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6">Arduino tutorial</a>
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
    <td>Zelfde als in As-Is</td>
    <td>
        <ul>
            <li><b>LiPo softcase accupack</b></li>
            <li>V<sub>nomonaal</sub> = 7.4 V</li>
            <li>I<sub>nominaal</sub> =  1200 mAh</li>
			<li>Aantal cellen: 2</li>
			<li>Belastbaarheid: 20 C</li>
			<li>Aansluiting: XT60, XH-balancer</li>
			<li>Afmetingen: 112 x 35 x 19 mm
			<li><i>Eenheidsprijs: €16,49</i></li>
			<li><i>Lead time: onbekend (op voorraad)</i></li>
        </ul>
    </td>
    <td>
		Zelfde batterij als in de As-Is situatie blijft behouden.
	</td>
    <td>
		<a href="./datasheets/accu.pdf">Datasheet</a>
		<a href="https://www.conrad.be/nl/p/conrad-energy-lipo-accupack-7-4-v-2400-mah-aantal-cellen-2-20-c-softcase-xt60-1344133.html?t=1&utm_source=google&utm_medium=surfaces&utm_term=1344133&utm_content=free-google-shopping-clicks&utm_campaign=shopping-feed&vat=true&gclid=CjwKCAjwxOCRBhA8EiwA0X8hi6Dpvaew0u-kTnIyrUmKE2RRHzkksSaw41QoJ36AmjOCY1n-dP7VnRoC240QAvD_BwE&gclsrc=aw.ds&tid=13894944235_122657379817_pla-301443522443_pla-1344133&WT.srch=1">Winkel Conrad</a><br>
	</td>
</tr>
<tr>
    <td>LDL1117S50R</td>
    <td>
        <ul>
            <li><b>Voltage Regulator 5 V</b></li>
			<li>Package: SOT223 SMD</li>
			<li>V<sub>output</sub> = 5 V
            <li>V<sub>input</sub> = 2.5 - 18 V</li>
            <li>I<sub>output</sub> = 1.2 A</li>
			<li><i>Eenheidsprijs: €0,56</i></li>
			<li><i>Lead time: 52 weken (lage voorraad)</i></li>
        </ul>
    </td>
    <td>
		Eenvoudige en goedkope LDO regulator.
		Alternatieven die 3.3 en 5 V in één package doen hebben een lage I<sub>output</sub>.
		Alternatief voorbeeld: <a href="https://www.mouser.be/ProductDetail/Microchip-Technology-Micrel/MIC5211-LXYM6-TR?qs=U6T8BxXiZAWZW72McTiFRQ%3D%3D>MIC5211-LXYM6-TR</a>
	</td>
    <td>
		<a href="./datasheets/LDL1117_algemeen.pdf">Datasheet algemeen</a><br>
		<a href="./datasheets/LDL1117_SOT223_specific.pdf">Datasheet SOT223</a><br>
		<a href="https://www.mouser.be/ProductDetail/STMicroelectronics/LDL1117S50R?qs=AQlKX63v8RsuN9BQFiVf%2Fg%3D%3D">Winkel Mouser</a><br>
		<a href="https://www.avnet.com/shop/us/products/stmicroelectronics/ldl1117s50r-3074457345642528941?CMP=EMA_Octopart_inventoryfeed_VSE>Winkel AVNET (op voorraad)</a><br>
	</td>
</tr>
<tr>
    <td>LDL1117S33R</td>
    <td>
        <ul>
            <li><b>Voltage Regulator</b></li>
			<li>Package: SOT-223 SMD</li>
			<li>V<sub>output</sub> = 5 V
            <li>V<sub>input</sub> = 2.5 - 18 V</li>
            <li>I<sub>output</sub> = 1.2 A</li>
			<li><i>Eenheidsprijs: €0,56</i></li>
			<li><i>Lead time: 52 weken (op voorraad)</i></li>
        </ul>
    </td>
    <td>
		Eenvoudige en goedkope LDO regulator.
		Alternatieven die 3.3 en 5 V in één package doen hebben een lage I<sub>output</sub>.
	</td>
    <td>
		<a href="./datasheets/LDL1117_algemeen.pdf">Datasheet algemeen</a><br>
		<a href="./datasheets/LDL1117_SOT223_specific.pdf">Datasheet SOT223</a><br>
		<a href="https://www.mouser.be/ProductDetail/STMicroelectronics/LDL1117S33R?qs=AQlKX63v8Rt9Bf6AWSrbFg%3D%3D">Winkel Mouser</a><br>
		<a href="https://uk.farnell.com/stmicroelectronics/ldl1117s33r/ldo-fixed-3-3v-1-2a-sot-223-3/dp/2729708?st=ldl1117s33r">Winkel Farnell</a><br>
	</td>
</tr>
<tr>
    <td>DMG3414U</td>
    <td>
        <ul>
            <li><b>Polariteitsbeveiliging N-channel MOSFET</b></li>
			<li>Package: SOT-23 SMD</li>
            <li>V<sub>ds</sub> = 20 V</li>
            <li>I<sub>d</sub> = 4.2 A</li>
			<li>R<sub>ds(on)</sub> = 0.019 ohm</a>
			<li>V<sub>gs(th)</sub> = 500 mV</li>
			<li>P<sub>d</sub> = 780 mW</li>
			<li><i>Eenheidsprijs: 0,72€</i></li>
			<li><i>Lead time: 52 weken (op voorraad)</i></li>
        </ul>
    </td>
    <td>
		Een N-channel MOSFET met lage R<sub>ds(on)</sub> op de negatieve voedingslijn geeft de beste batterij levensduur volgens onderzoek.
		De DMG3414U heeft een lage threshold spanning zodat deze ook geleid bij lage spanningen, en een V<sub>ds</sub> en I<sub>d</sub> die hoog genoeg zijn zodat de MOSFET niet stuk gaat in deze schakeling met 7.2 V batterij.
		
		<a href="./datasheets/Polariteitsbeveiliging_dt94-8.pdf">Polariteitsbeveiliging onderzoek</a>
		<a href="http://www.irf.com/technical-info/designtp/dt94-8.pdf">Web download (bron)</a>
		<a href="https://www.elektormagazine.nl/magazine/elektor-199907/39665>Uitleg.</a>
		<a href="https://www.circuitsonline.net/forum/view/50988>Uitleg.</a>
	</td>
    <td>
		<a href="./datasheets/DMG3414U_N-MOSFET.pdf">Datasheet</a><br>
		<a href="https://nl.farnell.com/diodes-inc/dmg3414u/mosfet-n-ch-w-diode-20v-4-2a-sot23/dp/2061404?st=mosfet%20n%20smd">Winkel Farnell</a><br>
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