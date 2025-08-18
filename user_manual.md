# Event‑Ease User Manual

Welcome to Event‑Ease — a simple, colorful Windows console app to browse events, register/login with a ticket code, book seats, and manage records as an admin.

This guide explains each screen and how to navigate the program using your keyboard.

## Quick Start

- Run the program to see the welcome art and the main menu.
- Use the number keys for menu options, then press Enter.
- Text input is case‑insensitive where noted; 4‑digit ticket codes accept 0000–9999.

## Main Menu (Landing Page)

You’ll see boxes with these options:

1. New User Registration
2. Existing User Login
3. Admin Login
4. Exit

Use the number for the action you want. If you enter something invalid, you’ll see a warning box and can try again.

## New User Registration

1. Enter your name (non‑empty, not only spaces).
2. The system generates a unique 4‑digit Ticket Code.
3. You’ll see a success message showing your code. Save it.
4. Press any key to proceed to the User Dashboard.

Tip: Each name must be unique in the system. If a name already exists, pick a slightly different one (e.g., “Alex M”).

## Existing User Login

1. Enter your name (must match how you registered).
2. Enter your 4‑digit Ticket Code (0000–9999).
3. On success, you’ll see a confirmation and then the User Dashboard.
4. On failure, you’ll see an error with a prompt to try again.

## User Dashboard

Options:

1. View Event Details
2. Book Seat
3. Cancel Booking
4. View All Bookings
5. Logout
6. Exit

Navigation notes:

- All lists are shown in cyan framed boxes; informational/success/error notices appear in colored message boxes.
- When a prompt says “Press Enter to continue…”, just press Enter (no text needed).

### 1) View Event Details

- Shows a list of all events by name.
- Enter an event number to view its details (Name, Venue, Date, Time, Seat Capacity).
- Press Enter to go back to the list; choosing the final “Return to dashboard” item takes you back to the dashboard.

### 2) Book Seat

- Displays all events; input the event number you want to book.
- After booking, you’ll see a “Booking Confirmation” notice with the event info.
- Press Enter to return.

Notes:

- You must be logged in to book.
- Bookings are recorded in `bookings.txt` as “EventID Name”.

### 3) Cancel Booking

- Shows only your current bookings with Event ID and Event Name.
- Enter the Event ID to cancel your booking for that event.
- Success and not‑found messages are shown accordingly.

### 4) View All Bookings (User)

- Shows all your bookings in a list.
- Press Enter to return.

### 5) Logout

- Logs you out and returns to the main menu.

### 6) Exit

- Shows a friendly exit message and closes the program after you press a key.

## Admin Login

- Username: `admin`
- Password: `strongpassword`

On success, you’ll enter the Admin Panel.

## Admin Panel

Options:

1. View all bookings
2. Add Event
3. View All Events
4. View All Users
5. Logout
6. Exit

### 1) View all bookings (Admin)

- Shows every booking (User Name – Event Name).
- Press Enter to return.

### 2) Add Event

- You’ll be prompted for: Event Name, Venue, Date (DD‑MM‑YYYY), Time (HH:MM), Seat Capacity.
- On success, a confirmation appears and you’ll return to the panel.

### 3) View All Events (Admin)

- Shows the list of events. Select an event number to view details.
- Actions menu per event:
  1. Edit Event — Update fields; press Enter to keep current values. Seat capacity: enter a positive number or 0 to keep existing.
  2. Delete Event — Removes the selected event from the list.
  3. Return — Go back without changes.

### 4) View All Users

- Lists all registered users as “TicketCode | Name”.
- Press Enter to return.

### 5) Logout and 6) Exit

- Logout returns to the main menu; Exit closes the app after a confirmation prompt.

## Files Used

- `events.txt` — Event records: `Name|Venue|Date|Time|SeatCapacity`
- `user_info.txt` — Registered users: `TicketCode,Name`
- `bookings.txt` — Bookings: `EventID Name`
- `temp.txt` — Temporary file for safe updates (e.g., during booking cancellation)

## Tips & Troubleshooting

- If text appears misaligned, resize your console window wider; Event‑Ease centers content based on your current console width.
- The program uses UTF‑8 and Unicode line graphics for a nicer look; on older consoles, boxes may degrade to plain text.
- If you forget your Ticket Code, ask an admin to check `user_info.txt` for your name and ticket.
- If you can’t log in: verify exact name spelling and that your ticket code is 4 digits.

## Keyboard Basics

- Numbers + Enter to select menu items.
- Type text and press Enter to submit.
- Press any key when a notice says “Press any key…”.

Enjoy using Event‑Ease! If you have ideas or issues, feel free to update this manual.
