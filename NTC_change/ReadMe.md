# NTC Change

To change the thermistor of the print bed, research was done to work out what the values of the thermistor circuit for the bed are. Likely the method can be used for the print head(s).

Plugging the information from the [SteelCity's page](https://steelcityelectronics.com/da-vinci-3d-printer/da-vinci-print-bed-thermistor/) on the topic, and hours of playing with values in a [spreadsheet](./Bed_Thermistor.ods) and Python results in...

**The values of the original Bed NTC circuit appear to be:**
* Voltage divider static/top resistance: 33k ohm
* Original NTC likely 370k ohm, β=3450

A modified [Dv10-E3Dv6-ThermistorTable.py](../Dv10-E3Dv6-ThermistorTable.py) ([ThermistorTable.py](./ThermistorTable.py)) was used to plug values in to the spreadsheet and finally the **configuration.h** file.

### Configuration.h notes & changes:
* Bed thermistor is ``USER_THERMISTORTABLE1`` (unchanged; logic cleanup for bed thermiistor so only 1 copy of the array definition)
* Print head thermistor ``USER_THERMISTORTABLE0``
* Configation is for DaVinci AIO, but change the values accordingly

## Background
My DaVinci AIO was acquired in late 2023 after it had been sitting in a room at work for years (assuming customer returned and been through service multiple times).
In essence an almost free printer.

The printer was in service making parts, tools, gadgets and decorative items until a hot summer day (southern Africa) midway through an engine repair (needed a specific tool to hold the flywheel; orderig online would be weeks) the bed NTC just died and the glass build plate had also started pitting.
Luckily I had also acquired a bunch of DaVici Jnr's a few months later to make a full working printer for a friend and an office/team play toy, so the [flywheel holding] tool was built with that.

Months pass (not making the partner happy as it was in a common/guest visible area) and a new bed, but of course nothing matches up nor do I want to order even more stuff from another continent.

Hoping to have a shortcut, while givig a lift, I asked the supervisor who used to lead the team servicing/repairing the printers, if he had any known values to work against: XYZ didn't share schematics or details. The spare parts were also flushed during a cleaup -- oh well, guess it'll be the hard way then.

While I could have taken the board out and traced the circuit, doing this at night would mean being in my workshop and not being a warm body in bed comforting... so resarcch, math, programming and trying to be quiet.

Recycle, reuse, adapt & be better.

## Shoutouts
* The amazing work of all the people that have shared their work with the rest of us.
