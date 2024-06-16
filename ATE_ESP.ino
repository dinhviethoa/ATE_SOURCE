#include <stdio.h>
#include <string.h>

#define OUTPUT_CTRL 2
#define CTRL_AC_SOURCE_1 4
#define CTRL_AC_SOURCE_2 16
#define CTRL_AC_SOURCE_3 17
#define CTRL_RELAY_NTC 5
#define CHECK_VBUS_400V 18
#define CHECK_OUTPUT_VOLT 19
#define CHECK_VCC_PFC 21
#define DC_OUTPUT_CURRENT_READ 13
#define VCC_VOLT 12
#define NTC_VOLT 14
#define MCU_VOLT 27
#define FAN_VOLT 26
#define FAN_ON 25
#define FAN_STUCK 33
#define FAN_SHORT 32
#define NTC_PROTECT 35
#define DISCHARGE 34

#define RELAY_NUM 19



int pin_relay[19] = { 2, 4, 16, 17, 5, 18, 19, 21, 13, 12, 14, 27, 26, 25, 33, 32, 35, 34, 15 };

bool lock_on = false;

void check_and_used(char *relay_name, char *state) {
  bool fail = false;
  if (!strcmp(relay_name, "OUTPUT_CTRL")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(OUTPUT_CTRL, true);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(OUTPUT_CTRL, false);
    }
  } else if (!strcmp(relay_name, "CTRL_AC_SOURCE_1")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(CTRL_AC_SOURCE_1, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(CTRL_AC_SOURCE_1, 0);
    }
  } else if (!strcmp(relay_name, "CTRL_AC_SOURCE_2")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(CTRL_AC_SOURCE_2, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(CTRL_AC_SOURCE_2, 0);
    }
  } else if (!strcmp(relay_name, "CTRL_AC_SOURCE_3")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(CTRL_AC_SOURCE_3, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(CTRL_AC_SOURCE_3, 0);
    }
  } else if (!strcmp(relay_name, "CTRL_RELAY_NTC")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(CTRL_RELAY_NTC, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(CTRL_RELAY_NTC, 0);
    }
  } else if (!strcmp(relay_name, "CHECK_VBUS_400V")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(CHECK_VBUS_400V, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(CHECK_VBUS_400V, 0);
    }
  } else if (!strcmp(relay_name, "CHECK_OUTPUT_VOLT")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(CHECK_OUTPUT_VOLT, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(CHECK_OUTPUT_VOLT, 0);
    }
  } else if (!strcmp(relay_name, "CHECK_VCC_PFC")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(CHECK_VCC_PFC, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(CHECK_VCC_PFC, 0);
    }
  } else if (!strcmp(relay_name, "DC_OUTPUT_CURRENT_READ")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(DC_OUTPUT_CURRENT_READ, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(DC_OUTPUT_CURRENT_READ, 0);
    }
  } else if (!strcmp(relay_name, "VCC_VOLT")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(VCC_VOLT, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(VCC_VOLT, 0);
    }
  } else if (!strcmp(relay_name, "NTC_VOLT")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(NTC_VOLT, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(NTC_VOLT, 0);
    }
  } else if (!strcmp(relay_name, "MCU_VOLT")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(MCU_VOLT, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(MCU_VOLT, 0);
    }
  } else if (!strcmp(relay_name, "FAN_VOLT")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(FAN_VOLT, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(FAN_VOLT, 0);
    }
  } else if (!strcmp(relay_name, "FAN_ON")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(FAN_ON, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(FAN_ON, 0);
    }
  } else if (!strcmp(relay_name, "FAN_STUCK")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(FAN_STUCK, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(FAN_STUCK, 0);
    }
  } else if (!strcmp(relay_name, "FAN_SHORT")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(FAN_SHORT, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(FAN_SHORT, 0);
    }
  } else if (!strcmp(relay_name, "NTC_PROTECT")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(NTC_PROTECT, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(NTC_PROTECT, 0);
    }
  } else if (!strcmp(relay_name, "DISCHARGE")) {
    if (!strcmp(state, "ON")) {
      digitalWrite(DISCHARGE, 1);
    } else if (!strcmp(state, "OFF")) {
      digitalWrite(DISCHARGE, 0);
    }
  } else {
    Serial.printf("FAIL: RELAY_NAME OR STATE: relay_name = %s state = %s\n", relay_name, state);
    fail = true;
  }
  if (fail == false) {
    Serial.printf("SUCCESS: %s %s\n", relay_name, state);
  }
}



void action() {
  String command_uart;
  char *command = (char *)malloc(30UL);
  char *relay_name = (char *)malloc(20UL);
  char *state = (char *)malloc(4UL);
  while (Serial.available() == 0) {}
  command_uart = Serial.readString();
  command_uart.toCharArray(command, command_uart.length());
  // strcpy(command, ConvertStringToCharArray(command_uart));
  sscanf(command, "%s %s", relay_name, state);
  if (relay_name != NULL && state != NULL) {
    check_and_used(relay_name, state);
  } else {
    Serial.printf("FAIL COMMAND: RELAY_NAME OR STATE IS NULL: relay_name = %s state = &s\n", relay_name, state);
  }
  free(command);
  free(relay_name);
  free(state);
}


void lock_button_task(void *arg) {
  while (true) {
    if (lock_on == false) {
      if (digitalRead(23) != 0) {
        delay(100);
        if (digitalRead(23) != 0) {
          Serial.println("LOCK ON");
          lock_on = true;
        }
      }
    } else if (lock_on == true) {
      if (digitalRead(23) == 0) {
        delay(100);
        if (digitalRead(23) == 0) {
          Serial.println("LOCK OFF");
          lock_on = false;
        }
      }
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < RELAY_NUM; i++) {
    pinMode(pin_relay[i], OUTPUT);
    digitalWrite(pin_relay[i], 0);
  }
  pinMode(23, INPUT);

  xTaskCreate(lock_button_task, "input", 2048, NULL, 2, NULL);

  digitalWrite(15, 1);

  // pinMode()
}

void loop() {
  // put your main code here, to run repeatedly:
  action();
}
