# Event-Ease 🎫

A modern console-based event management system written in C that provides a complete solution for event booking, user management, and administrative control.

## 🌟 Overview

Event-Ease is a comprehensive event management application designed for simplicity and efficiency. Whether you're a user looking to book seats for events or an administrator managing the entire system, Event-Ease provides an intuitive interface with robust functionality.

## ✨ Key Features

### 🎭 User Features
- **Smart Registration**: Automatic unique 4-digit ticket code generation (0000-9999)
- **Secure Login**: Name and ticket code authentication system
- **Event Discovery**: Browse detailed event information with venue, date, and time
- **Seamless Booking**: One-click seat booking with automatic user recognition
- **Booking Management**: View and cancel personal bookings
- **Event Names Display**: See actual event names instead of confusing IDs

### 🔧 Admin Features
- **Complete Event Management**: Add, edit, and delete events
- **User Analytics**: View all registered users and their information
- **Booking Overview**: Monitor all bookings across the system with event names
- **Real-time Data**: Live updates of booking and user statistics

### 🎨 Technical Excellence
- **Unified UI System**: Consistent alignment and professional presentation
- **Smart Input Handling**: Automatic logged-in user recognition (no repeated name entry)
- **Data Persistence**: Reliable file-based storage system
- **Cross-Platform**: Windows-optimized with console enhancements

## 🚀 Quick Start

### Prerequisites
- **Compiler**: GCC (MinGW for Windows)
- **OS**: Windows (uses Windows console API)
- **Memory**: Minimal system requirements

### Installation & Setup

1. **Clone the Repository**
   ```bash
   git clone https://github.com/fahimshahriar24/Event-Ease.git
   cd Event-Ease
   ```

2. **Compile the Application**
   ```bash
   gcc Event_Ease.c -o Event_Ease.exe
   ```

3. **Run Event-Ease**
   ```bash
   ./Event_Ease.exe
   ```

## 🎯 Core Functionality

### Authentication System
- **New Users**: Register once, get a unique ticket code, immediate access
- **Existing Users**: Login with name + ticket code
- **Administrators**: Secure admin panel access (`admin` / `password`)

### Smart Booking Flow
1. **User logs in** → System remembers user identity
2. **Browse events** → View detailed event information
3. **Book seats** → No need to re-enter name (automatic user recognition)
4. **View bookings** → See event names, not just IDs

### Admin Control Panel
- **Event Management**: Complete CRUD operations
- **User Monitoring**: Track registrations and activity
- **System Analytics**: Comprehensive booking overview

## 📁 Project Structure

```
Event-Ease/
├── Event_Ease.c           # Main source code
├── Event_Ease.exe         # Compiled executable
├── README.md              # Project documentation
├── user_manual.md         # Detailed user guide
├── events.txt             # Event database
├── user_info.txt          # User registration data
└── bookings.txt           # Booking records
```

## 🔒 Security Features

- **Input Validation**: Comprehensive sanitization of all user inputs
- **Unique ID Generation**: Collision-resistant ticket code system
- **Data Integrity**: Proper file handling with error checking
- **Access Control**: Role-based authentication system

## 💾 Data Management

### File Formats
- **User Info**: `ticket,name` (CSV format)
- **Events**: `name|venue|date|time|capacity` (pipe-delimited)
- **Bookings**: `eventID username` (space-delimited)

### Data Features
- **Automatic Persistence**: All changes saved immediately
- **Data Validation**: Format verification on read/write operations
- **Backup Friendly**: Human-readable text file formats

## 🎨 User Experience

### Visual Design
- **Centered Layout**: Professional console presentation
- **Unified Alignment**: Consistent UI across all screens
- **Color Coding**: Visual feedback for different operations
- **Clear Navigation**: Intuitive menu systems

### Smart Features
- **Auto-complete User Info**: Logged-in users don't re-enter details
- **Event Name Display**: Meaningful names instead of numeric IDs
- **Streamlined Booking**: Direct booking from event details
- **Confirmation Messages**: Clear feedback for all actions

## 🛠️ Development

### Code Architecture
- **Modular Design**: Separate functions for each feature
- **Clean Comments**: Enhanced readability and maintenance
- **Error Handling**: Comprehensive error checking
- **Cross-Platform Ready**: Designed for easy porting

### Recent Improvements
- ✅ Automatic user recognition in booking system
- ✅ Event names in booking displays
- ✅ Enhanced comment clarity
- ✅ Fixed Windows compatibility issues
- ✅ Unified UI positioning system
- ✅ Comprehensive code audit and optimization

## 📖 Documentation

- **[User Manual](user_manual.md)**: Complete step-by-step guide
- **Code Documentation**: Inline comments and function descriptions
- **API Reference**: Function signatures and usage examples

## 🤝 Contributing

We welcome contributions! Please see our contribution guidelines:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Built with modern C programming practices
- Designed for educational and practical use
- Community-driven development approach

---

**Event-Ease** - Making event management simple, efficient, and enjoyable! 🎉
