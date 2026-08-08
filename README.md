# Screen-Free Assistive Home Routine Assistant

A simple, screen-free voice guidance prototype for autistic kids to help them navigate daily routines at home without sensory overload or app distractions.

Built with **C++** and **Arduino Nano** on [Wokwi Simulator](https://wokwi.com/projects/471798447475227649).

---

### Why Screen-Free?
Most routine apps for neurodivergent kids rely on smartphones or tablets. But screen notifications and bright displays can easily cause sensory overload or become a distraction. Physical buttons and voice prompts create a much calmer, predictable setup for managing daily tasks like study time, quiet breaks, and activity transitions.

---

### How it Works

1. **Room Entry (PIR Motion Sensor):** Triggers a calm voice prompt as soon as the child enters their desk or room area.
2. **🔴 Red Button:** Request a short, quiet break when feeling overwhelmed.
3. **🔵 Blue Button:** Mark an activity complete and hear positive reinforcement.
4. **🟡 Yellow Button:** Call a parent or caregiver for assistance.
5. **🟢 Green Button:** Repeat the last voice instruction if missed.

---

### Live Simulation

🔗 **Live Wokwi Project:** [Screen-Free Home Routine Assistant Prototype](https://wokwi.com/projects/471798447475227649)

---

### Components Used

* Arduino Nano
* PIR Motion Sensor (HC-SR501)
* DFPlayer Mini MP3 Module
* 3W Speaker / Piezo Buzzer (Buzzer used in simulation)
* 4x Pushbuttons (Red, Blue, Yellow, Green)

---

### Running in Wokwi

1. Open the [Wokwi Simulation Link](https://wokwi.com/projects/471798447475227649).
2. Make sure `DFRobotDFPlayerMini` is added in the **Library Manager** (`libraries.txt`).
3. Hit **Play** and check the Serial Monitor logs while testing the buttons and motion sensor.

---

### Code Highlights
* **Debounced Buttons:** Uses internal `INPUT_PULLUP` resistors to stop random button triggers and floating pins.
* **Edge Detection:** Ensures the PIR sensor triggers the welcome sequence only once per room entry.
* **Hardware-Ready:** Includes commented blocks with 30s sensor warm-up and actual MP3 playback timing for physical assembly.

---

### Planned Enhancements

* **Smart Stagnation Detection (PIR Timeout):** If the PIR sensor detects the child is still present long after a prompt finishes without pressing "Task Complete" or "Break", the system will trigger a soft re-engagement prompt or alert parents via a local buzzer/LED indicator that the child might be stuck or overwhelmed.
* **Parent Companion Dashboard:** Adding a low-power ESP32 or Wi-Fi module to silently log routine completions and button presses to a parent's phone without adding any screens to the child's environment.
* **Custom Family Voice Recordings:** Allowing parents/therapists to record personalized voice prompts directly onto the SD card.
