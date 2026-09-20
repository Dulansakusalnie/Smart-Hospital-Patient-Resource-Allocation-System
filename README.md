# Smart Hospital & Resource Allocation System

A console-based application written in C, designed to simulate daily hospital operations. This system helps hospital administrators efficiently manage patient records, prioritize treatments based on emergency severity, allocate hospital beds, and generate accurate patient bills.

## Project Overview
This project was developed as an individual assignment for the **CSC 1012 Introduction to Computer Programming** module at the **University of Sri Jayewardenepura**. The primary goal was to apply fundamental programming concepts—including parallel arrays, custom functions, loops, conditionals, and file handling—to solve a practical, real-world problem.

## Key Features
*   **Patient Intake:** Collects patient details, triage level (Normal, Urgent, Critical), and specialty selection.
*   **Bed Allocation:** Uses a 2D array to track bed availability across four hospital wards, automatically assigning beds and preventing overbooking.
*   **Automated Billing:** Calculates base consultation fees, emergency surcharges (based on triage level), ward stay costs, and applies a 15% age subsidy for patients under 5 or over 65.
*   **Priority Sorting:** Implements a Bubble Sort algorithm to display patients in priority order (Critical > Urgent > Normal) and then by registration order.
*   **Performance Reports:** Generates hospital analytics, including total revenue, total discounts, bed occupancy percentages, and the highest-paying patient.
*   **File Handling:** Saves and loads bed occupancy states to `beds_status.txt` and appends patient billing logs to `patient_records.txt` to maintain records across program runs.

## Technologies Used
*   **Language:** C
*   **Concepts:** Parallel Arrays, 2D Arrays, Modular Functions, File I/O, Bubble Sort.
*   **Tools:** Code::Blocks IDE, Git, GitHub.

## How to Compile and Run
1. Clone the repository to your local machine.
2. Open the `main.c` file in your preferred C IDE (e.g., Code::Blocks).
3. Compile and run the program.
4. Follow the on-screen menu to register patients, view bed statuses, and generate reports.

## Repository Structure
```text
Smart-Hospital-Patient-Resource-Allocation-System/
│
├── main.c                  # The complete source code
├── README.md               # Project documentation
├── .gitignore              # Prevents generated files from being tracked
└── [Your_Report.pdf]       # (Optional) The project report
