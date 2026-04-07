# 🚀 Travel Booking System (C Project)

## 📌 Project Description

This project is a **menu-driven travel booking application** built using the C programming language. It allows users to reserve tickets for bus or train journeys, calculate travel costs, and manage bookings efficiently.

All booking and feedback data are stored using **file handling**, making the system persistent across multiple runs.

---

## 🎯 Key Functionalities

* ✔️ Book tickets for bus or train
* ✔️ Automatic generation of unique ticket numbers
* ✔️ Fare calculation based on passenger age and travel mode
* ✔️ Save booking details to a file
* ✔️ Display all existing bookings
* ✔️ Cancel bookings using ticket ID
* ✔️ Provide helpline information and policies
* ✔️ Collect and store user feedback

---

## 🧠 Concepts Implemented

* Structures for organizing booking data
* File operations for data storage and retrieval
* Conditional statements for validation and fare logic
* String manipulation functions
* Random number generation for ticket IDs

---

## 🛠️ Technologies Used

* Programming Language: C
* Compiler: GCC
* Execution Mode: Command Line Interface

---

## ▶️ Execution Steps

### Compile the program

```bash id="c1a2b3"
gcc travel_booking_system.c -o booking
```

### Run the program

```bash id="d4e5f6"
./booking
```

---

## 📋 Application Flow

1. User selects an option from the main menu
2. For booking, user enters personal and travel details
3. System validates input and calculates fare
4. Booking is confirmed and saved to file
5. User can view, cancel bookings, or give feedback

---

## 💰 Fare Calculation Logic

* Children below 5 years → No charge
* Senior citizens (60+) → 50% discount
* Others → Standard fare
* Bus travel → Lower base fare
* Train travel → Higher base fare

---

## 📂 Output Files

* `bookings.txt` → Contains all booking records
* `feedback.txt` → Stores user feedback

---

## ⚠️ Current Limitations

* Runs only in terminal (no graphical interface)
* Limited to basic booking functionality
* Does not include online payment or authentication

---

## 🔮 Possible Enhancements

* Add graphical user interface
* Integrate database instead of text files
* Implement seat selection system
* Add login and user accounts
* Extend to flight and hotel booking

---

## 👨‍💻 Developer

Pruthviraj Patil

---

## ⭐ Summary

This project showcases how fundamental C programming concepts can be applied to design a simple yet functional booking system with real-world relevance.
