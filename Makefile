CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/main.cpp \
      src/User.cpp \
      src/Administrator.cpp \
      src/BookingAgent.cpp \
      src/Passenger.cpp \
      src/Flight.cpp \
      src/Aircraft.cpp \
      src/Reservation.cpp \
      src/Payment.cpp \
      src/Pilot.cpp \
      src/FlightAttendant.cpp \
      src/FlightService.cpp \
      src/ReservationService.cpp \
      src/CheckInService.cpp \
      src/PaymentService.cpp \
      src/UserManagementService.cpp \
      src/FlightManagementService.cpp \
      src/ReportService.cpp

TARGET = airline

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)
