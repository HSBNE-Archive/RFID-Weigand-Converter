# RFID Weigand Converter
This little firmware sits on a microcontroller between a weigand compatible RFID reader. It allows you to get the tag ID and control the LED/buzzer via a simple serial protocol. This is designed to work with HSBNE's suite of access control software and hardware. See our [GitHub](https://github.com/hsbne) for more information and resources.

# Usage
Flash onto any arduino or compatible board and hook up wires as defined in the arduino code. Everytime a weigand message is received, it converts it to text and sends it over the serial connection. (9600 baud)

# Commands

`flash` - start rapidly flashing. Designed to indicate checking the card details, etc. Times out after 30s.
`slowflash` - call after `flash` for a slow 500ms flash. Good to indicate an OTA update etc.
`fastflash` - will reset to the normal flashing speed (also does if you just call `flash` again).
`approved` - buzzes and indiciates LED for a so solid length of time to indicate a successful swipe.
`denied` - a couple of fast flashes/buzzes to indicate a rejected swipe.
`stop` - will turn off both the LED and buzzer.
