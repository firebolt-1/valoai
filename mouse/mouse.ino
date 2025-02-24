#include <hidboot.h>
#include <usbhub.h>
#include <Mouse.h>
#include <hiduniversal.h>
#include <Wire.h>
#include <SPI.h>

#define RPT_LEN  8

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);

class HIDMouseEvents {
  public:
    void OnButtonDn(uint8_t but_id) {
        Mouse.press(but_id);
    }
    void OnButtonUp(uint8_t but_id) {
        Mouse.release(but_id);
    }
    void Move(int8_t xm, int8_t ym, int8_t scr) {
        Mouse.move(xm, ym, scr);
    }
};

class HIDMouseReportParser : public HIDReportParser {
    HIDMouseEvents *mouEvents;
    uint8_t oldButtons;
  public:
    HIDMouseReportParser(HIDMouseEvents *evt) : mouEvents(evt), oldButtons(0) {}
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
        uint8_t buttons = buf[0];
        if (buttons != oldButtons) {
            for (uint8_t but_id = 1; but_id <= 4; but_id <<= 1) {
                if (buttons & but_id) {
                    if (!(oldButtons & but_id)) {
                        mouEvents->OnButtonDn(but_id);
                    }
                } else {
                    if (oldButtons & but_id) {
                        mouEvents->OnButtonUp(but_id);
                    }
                }
            }
            oldButtons = buttons;
        }
        int8_t xm = buf[1];
        int8_t ym = buf[2];
        int8_t scr = buf[3];
        if (xm || ym || scr) {
            mouEvents->Move(xm, ym, scr);
        }
    }
};

HIDMouseEvents MouEvents;
HIDMouseReportParser Mou(&MouEvents);
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);

int rec = 1;
String received_code;
int index1;

void setup() {
  Mouse.begin();
  Serial.begin(9600);
  Serial.setTimeout(1);
  Usb.Init();
  if (!Hid.SetReportParser(0, &Mou)) {
    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1);
  }
}

void loop() {
  Usb.Task();
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '*') {
      index1 = received_code.indexOf(',');
      if (index1 > 0) {
        int x_v = received_code.substring(0, index1).toInt();
        int y_v = received_code.substring(index1 + 1).toInt();
        Mouse.move(x_v, y_v, 0);
        Mouse.click();
      }
      received_code = "";
    } else {
      received_code += c;
    }
  }
}
