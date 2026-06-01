# 🎬 Cinema Seat Reservation System

A fully functional **C++ GUI application** built with SFML for managing cinema ticket reservations with a complete booking workflow.

## ✨ Features

- **Movie Selection**: Browse and select from available movies
- **Seat Booking**: Choose between VIP and regular seats with visual seat map
- **Concessions**: Add drinks and popcorn to your order
- **Payment System**: Pay by cash or card (16-digit validation)
- **Auto-Billing**: Automatic bill generation with itemized breakdown
- **Click-Based UI**: Intuitive graphical interface for seamless navigation
- **Multi-Screen Navigation**: Smooth transitions between booking stages
- **Data Persistence**: Saves all reservations to movie-wise files
- **Real-time Updates**: Seat availability updates instantly

## 🛠️ Tech Stack

- **Language**: C++
- **GUI Framework**: SFML (Simple and Fast Multimedia Library)
- **Architecture**: Object-Oriented Programming (OOP)
- **Storage**: File-based (text files)

## 📋 Prerequisites

- C++ compiler (C++11 or higher)
- SFML library installed
- CMake (optional, for build management)

## 🚀 Installation

```bash
# Clone the repository
git clone https://github.com/Talha925-hub/Cinema-seat-reservation-System-c-sfml-.git
cd Cinema-seat-reservation-System-c-sfml-

# Compile with SFML
g++ -c main.cpp -o main.o
g++ main.o -o cinema_booking -lsfml-graphics -lsfml-window -lsfml-system

# Run the application
./cinema_booking
```

## 📖 Usage

1. **Launch** the application
2. **Select a Movie** from the available options
3. **Choose Seats** - click on available seats to select (VIP or Regular)
4. **Add Concessions** - select drinks and popcorn (optional)
5. **Review Bill** - check the itemized breakdown
6. **Make Payment** - pay by cash or card
7. **Confirmation** - receive booking confirmation with reservation details

## 🎯 Project Structure

```
Cinema-seat-reservation-System-c-sfml-/
├── main.cpp                 # Main application logic
├── movie.h / movie.cpp      # Movie management
├── seat.h / seat.cpp        # Seat booking system
├── payment.h / payment.cpp  # Payment processing
├── bill.h / bill.cpp        # Billing generation
├── reservations/            # Stored reservation files
└── README.md
```

## 💡 Key Algorithms

- **Seat Availability**: Real-time seat status tracking
- **Payment Validation**: 16-digit card validation
- **Bill Generation**: Automatic calculation with tax/discounts
- **File I/O**: Persistent storage across sessions

## 📝 Sample Data Format

Reservations are stored as:
```
Movie: Inception
Seats: A1, A2, B3
Concessions: 2x Popcorn, 1x Coke
Total: PKR 2,500
Date: 2026-02-02
```

## 🔧 Customization

- Add more movies to the database
- Modify seat layout and pricing
- Customize payment methods
- Add discount/promo code functionality
- Implement email confirmations

## 🐛 Known Issues

- No critical issues at the moment

## 📈 Future Enhancements

- [ ] Database integration (MySQL/SQLite)
- [ ] Online payment gateway
- [ ] Mobile app version
- [ ] Email/SMS notifications
- [ ] Admin dashboard
- [ ] QR code generation for tickets
- [ ] Multi-language support
- [ ] Loyalty rewards program
- [ ] Group booking discounts

## 📄 License

This project is open source and available under the MIT License.

## 👨‍💻 Author

**Talha925-hub** - Full-stack developer with expertise in C++ and system design

## 📞 Contact & Support

- GitHub: [@Talha925-hub](https://github.com/Talha925-hub)
- Report issues or suggest features via [Issues](https://github.com/Talha925-hub/Cinema-seat-reservation-System-c-sfml-/issues)

---

⭐ **If you found this helpful, please consider starring the repository!**
