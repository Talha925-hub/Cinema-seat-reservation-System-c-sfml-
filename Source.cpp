#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

#define TOTAL_SEATS 50
#define VIP_SEATS 20
#define VIP_COST 2000
#define NORMAL_COST 1000
#define BEVERAGE_COST 200
#define POPCORN_SMALL_COST 100
#define POPCORN_MEDIUM_COST 250
#define POPCORN_LARGE_COST 350

enum Screen { MOVIE_SELECTION, SEAT_SELECTION, BEVERAGE_SELECTION, PAYMENT_SELECTION };

string getMovieFileName(const string& movieName) {
    return movieName + "_reservations.txt";
}

void saveReservations(const string& movieName, const vector<int>& reservedSeats, int totalBill, const string& beverages, const string& popcorn, const string& paymentMethod) {
    string fileName = getMovieFileName(movieName);
    ofstream outFile(fileName, ios::app);

    if (outFile.is_open()) {
        outFile << "Reserved Seats: ";
        for (int seatNum : reservedSeats) {
            outFile << seatNum << " ";
        }
        outFile << "\nTotal Bill: " << totalBill << " PKR\n";
        outFile << "Beverages: " << beverages << "\n";
        outFile << "Popcorn: " << popcorn << "\n";
        outFile << "Payment Method: " << paymentMethod << "\n\n";
        outFile.close();
    }
    else {
        cout << "Unable to open file: " << fileName << endl;
    }
}

string getCardNumber() {
    string cardNumber;
    cout << "Enter Card Number (16 digits): ";
    cin >> cardNumber;
    return cardNumber;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Cinema Reservation System");
    Screen currentScreen = MOVIE_SELECTION;

    sf::Texture movieSelectionBgTexture;
    if (!movieSelectionBgTexture.loadFromFile("polll.jpg")) {
        cout << "Error loading movie selection background image" << endl;
        return -1;
    }
    sf::Sprite movieSelectionBgSprite(movieSelectionBgTexture);
    movieSelectionBgSprite.setScale(
        window.getSize().x / movieSelectionBgSprite.getLocalBounds().width,
        window.getSize().y / movieSelectionBgSprite.getLocalBounds().height);

    sf::Texture seatSelectionBgTexture;
    if (!seatSelectionBgTexture.loadFromFile("seat_background.jpg")) {
        cout << "Error loading seat selection background image" << endl;
        return -1;
    }
    sf::Sprite seatSelectionBgSprite(seatSelectionBgTexture);
    seatSelectionBgSprite.setScale(
        window.getSize().x / seatSelectionBgSprite.getLocalBounds().width,
        window.getSize().y / seatSelectionBgSprite.getLocalBounds().height);

    sf::Texture beverageSelectionBgTexture;
    if (!beverageSelectionBgTexture.loadFromFile("beverage_background.jpg")) {
        cout << "Error loading beverage selection background image" << endl;
        return -1;
    }
    sf::Sprite beverageSelectionBgSprite(beverageSelectionBgTexture);
    beverageSelectionBgSprite.setScale(
        window.getSize().x / beverageSelectionBgSprite.getLocalBounds().width,
        window.getSize().y / beverageSelectionBgSprite.getLocalBounds().height);

    sf::Texture paymentSelectionBgTexture;
    if (!paymentSelectionBgTexture.loadFromFile("payment_background.jpg")) {
        cout << "Error loading payment selection background image" << endl;
        return -1;
    }
    sf::Sprite paymentSelectionBgSprite(paymentSelectionBgTexture);
    paymentSelectionBgSprite.setScale(
        window.getSize().x / paymentSelectionBgSprite.getLocalBounds().width,
        window.getSize().y / paymentSelectionBgSprite.getLocalBounds().height);


    sf::Vector2f targetSize(150.0f, 150.0f);
    int spacing = 30;
    float totalWidth = 4 * targetSize.x + 3 * spacing;
    float xOffset = (window.getSize().x - totalWidth) / 2;

    sf::Texture movieTextures[8];
    string movieNames[8] = { "It", "Eyes in the sky", "Fast and Furious", "Venom", "Pursuit of Happiness", "Avengers Endgame", "John Wick", "Inception" };

    for (int i = 0; i < 8; ++i) {
        if (!movieTextures[i].loadFromFile(movieNames[i] + ".png")) {
            cout << "Error loading image for " << movieNames[i] << endl;
            return -1;
        }
    }

    sf::Sprite movieSprites[8];
    for (int i = 0; i < 8; ++i) {
        movieSprites[i] = sf::Sprite(movieTextures[i]);
        movieSprites[i].setScale(targetSize.x / movieSprites[i].getLocalBounds().width, targetSize.y / movieSprites[i].getLocalBounds().height);
        movieSprites[i].setPosition(xOffset + (i % 4) * (targetSize.x + spacing), 200 + (i / 4) * (targetSize.y + spacing));
    }

    sf::Texture beverageTextures[4];
    string beverageNames[4] = { "cocaCola", "sprite", "fanta", "pepsi" };
    int beverageCount[4] = { 0 };

    for (int i = 0; i < 4; ++i) {
        if (!beverageTextures[i].loadFromFile(beverageNames[i] + ".png")) {
            cout << "Error loading image for " << beverageNames[i] << endl;
            return -1;
        }
    }

    sf::Sprite beverageSprites[4];
    for (int i = 0; i < 4; ++i) {
        beverageSprites[i] = sf::Sprite(beverageTextures[i]);
        beverageSprites[i].setScale(targetSize.x / beverageSprites[i].getLocalBounds().width, targetSize.y / beverageSprites[i].getLocalBounds().height);
        beverageSprites[i].setPosition(xOffset + (i % 4) * (targetSize.x + spacing), 105 + (i / 4) * (targetSize.y + spacing));
    }

    string popcornSizes[3] = { "Small", "Medium", "Large" };
    int popcornCosts[3] = { POPCORN_SMALL_COST, POPCORN_MEDIUM_COST, POPCORN_LARGE_COST };
    int popcornCount[3] = { 0 };

    sf::Font font;
    if (!font.loadFromFile("Cinzel-Regular.ttf")) {
        cout << "Error loading font" << endl;
        return -1;
    }
    sf::Text cinemaName("FLICK RESERVE", font, 65);
    cinemaName.setFillColor(sf::Color::White);
    cinemaName.setStyle(sf::Text::Underlined);
    cinemaName.setPosition(
        (window.getSize().x / 2) - (cinemaName.getLocalBounds().width / 2), 50);

    sf::Text refreshmentHeading("REFRESHMENT", font, 50);
    refreshmentHeading.setFillColor(sf::Color::Black);
    refreshmentHeading.setStyle(sf::Text::Underlined);
    refreshmentHeading.setPosition((window.getSize().x / 2) - (refreshmentHeading.getLocalBounds().width / 2), 30);

    sf::Text popcornHeading("POPCORN:", font, 28);
    popcornHeading.setFillColor(sf::Color::Black);
    popcornHeading.setStyle(sf::Text::Underlined);
    popcornHeading.setPosition((window.getSize().x / 10) - (popcornHeading.getLocalBounds().width / 10), 295);

    sf::Text popcornText[3];
    for (int i = 0; i < 3; ++i) {
        popcornText[i].setFont(font);
        popcornText[i].setString("• " + popcornSizes[i] + " - " + to_string(popcornCosts[i]) + " PKR");
        popcornText[i].setCharacterSize(30);
        popcornText[i].setFillColor(sf::Color::Black);
        popcornText[i].setPosition(70, 350 + (i * 40));
    }

    int seats[TOTAL_SEATS] = { 0 };
    vector<int> reservedSeats;

    sf::RectangleShape seatShapes[TOTAL_SEATS];
    sf::Text seatNumbers[TOTAL_SEATS];

    for (int i = 0; i < TOTAL_SEATS; ++i) {
        seatShapes[i].setSize(sf::Vector2f(50, 50));
        seatShapes[i].setPosition(50 + (i % 10) * 60, 100 + (i / 10) * 60);

        if (i < VIP_SEATS) {
            seatShapes[i].setFillColor(sf::Color::Red);
        }
        else {
            seatShapes[i].setFillColor(sf::Color::Green);
        }

        seatNumbers[i].setFont(font);
        seatNumbers[i].setString(to_string(i + 1));
        seatNumbers[i].setCharacterSize(20);
        seatNumbers[i].setFillColor(sf::Color::Black);
        seatNumbers[i].setPosition(
            seatShapes[i].getPosition().x + 15,
            seatShapes[i].getPosition().y + 10);
    }

    int totalBill = 0;
    sf::Text billText;
    billText.setFont(font);
    billText.setCharacterSize(30);
    billText.setFillColor(sf::Color::White);
    billText.setPosition(50, 500);

    string selectedMovie;
    string selectedBeverages = "";
    string selectedPopcorn = "";
    string paymentMethod = "";


    sf::Text paymentHeading;
    paymentHeading.setFont(font);
    paymentHeading.setString("SELECT PAYMENT METHOD");
    paymentHeading.setCharacterSize(40);
    paymentHeading.setFillColor(sf::Color::Black);
    paymentHeading.setStyle(sf::Text::Underlined);
    paymentHeading.setPosition(
        (window.getSize().x / 2) - (paymentHeading.getLocalBounds().width / 2), 100);

    sf::Text cashPaymentText;
    cashPaymentText.setFont(font);
    cashPaymentText.setString("• CASH PAYMENT");
    cashPaymentText.setCharacterSize(30);
    cashPaymentText.setFillColor(sf::Color::Black);
    cashPaymentText.setPosition(window.getSize().x / 2 - 100, 250);

    sf::Text cardPaymentText;
    cardPaymentText.setFont(font);
    cardPaymentText.setString("• CARD PAYMENT");
    cardPaymentText.setCharacterSize(30);
    cardPaymentText.setFillColor(sf::Color::Black);
    cardPaymentText.setPosition(window.getSize().x / 2 - 100, 350);

    sf::Text cardNumberText;
    cardNumberText.setFont(font);
    cardNumberText.setCharacterSize(24);
    cardNumberText.setFillColor(sf::Color::Black);
    cardNumberText.setPosition(window.getSize().x / 2 - 100, 400);
    string cardNumber = "";

    sf::Text submitButtonText;
    submitButtonText.setFont(font);
    submitButtonText.setString("Submit");
    submitButtonText.setCharacterSize(24);
    submitButtonText.setFillColor(sf::Color::Black);
    submitButtonText.setPosition(window.getSize().x / 2 - 50, 450);

    sf::Text paymentBillText;
    paymentBillText.setFont(font);
    paymentBillText.setCharacterSize(30);
    paymentBillText.setFillColor(sf::Color::Black); // Changed to black
    paymentBillText.setPosition(50, 500);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentScreen == MOVIE_SELECTION) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    for (int i = 0; i < 8; ++i) {
                        if (movieSprites[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            cout << "You selected '" << movieNames[i] << "'" << endl;
                            selectedMovie = movieNames[i];
                            currentScreen = SEAT_SELECTION;
                            break;
                        }
                    }
                }
            }
            else if (currentScreen == SEAT_SELECTION) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    for (int i = 0; i < TOTAL_SEATS; ++i) {
                        if (seatShapes[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && seats[i] == 0) {
                            seats[i] = 1;
                            reservedSeats.push_back(i + 1);

                            if (i < VIP_SEATS) {
                                totalBill += VIP_COST;
                            }
                            else {
                                totalBill += NORMAL_COST;
                            }

                            seatShapes[i].setFillColor(sf::Color::White);
                        }
                    }
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        currentScreen = BEVERAGE_SELECTION;
                    }
                }
            }
            else if (currentScreen == BEVERAGE_SELECTION) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    for (int i = 0; i < 4; ++i) {
                        if (beverageSprites[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            beverageCount[i]++;
                            totalBill += BEVERAGE_COST;
                            selectedBeverages += beverageNames[i] + " (1) ";
                        }
                    }

                    for (int i = 0; i < 3; ++i) {
                        if (event.type == sf::Event::MouseButtonPressed) {
                            if (popcornText[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                                popcornCount[i]++;
                                totalBill += popcornCosts[i];
                                selectedPopcorn += popcornSizes[i] + " (" + to_string(popcornCount[i]) + ") ";
                            }
                        }
                    }
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        currentScreen = PAYMENT_SELECTION;
                    }
                }
            }
            else if (currentScreen == PAYMENT_SELECTION) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (cashPaymentText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        paymentMethod = "Cash";
                        cout << "Payment Method: " << paymentMethod << endl;
                        cout << "Summary:\n";
                        cout << "Movie: " << selectedMovie << endl;
                        cout << "Reserved Seats: ";
                        for (int seatNum : reservedSeats) {
                            cout << seatNum << " ";
                        }
                        cout << "\nBeverages: " << selectedBeverages << "\n";
                        cout << "Popcorn: " << selectedPopcorn << "\n";
                        cout << "Total Bill: " << totalBill << " PKR\n";
                        saveReservations(selectedMovie, reservedSeats, totalBill, selectedBeverages, selectedPopcorn, paymentMethod);
                        window.close();
                    }
                    else if (cardPaymentText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        //Card Payment selected, now handle card number input
                        currentScreen = PAYMENT_SELECTION; //Stay on payment screen
                    }
                    else if (submitButtonText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        //Submit button pressed
                        if (cardNumber.length() == 16) {
                            paymentMethod = "Card";
                            cout << "Payment Method: " << paymentMethod << std::endl;
                            cout << "Card Number: " << cardNumber << std::endl;
                            cout << "Summary:\n";
                            cout << "Movie: " << selectedMovie << std::endl;
                            cout << "Reserved Seats: ";
                            for (int seatNum : reservedSeats) {
                                cout << seatNum << " ";
                            }
                            cout << "\nBeverages: " << selectedBeverages << "\n";
                            cout << "Popcorn: " << selectedPopcorn << "\n";
                            cout << "Total Bill: " << totalBill << " PKR\n";
                            saveReservations(selectedMovie, reservedSeats, totalBill, selectedBeverages, selectedPopcorn, paymentMethod);
                            window.close();
                        }
                        else {
                            cout << "Invalid card number. Please enter 16 digits.\n";
                            cardNumber = ""; //Clear the input
                        }
                    }
                }
                else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9' && cardNumber.length() < 16) {
                        cardNumber += static_cast<char>(event.text.unicode);
                        cardNumberText.setString("Card Number: " + cardNumber);
                    }
                    else if (event.text.unicode == '\b' && !cardNumber.empty()) {
                        cardNumber.pop_back();
                        cardNumberText.setString("Card Number: " + cardNumber);
                    }
                }
            }
        }

        window.clear();

        if (currentScreen == MOVIE_SELECTION) {
            window.draw(movieSelectionBgSprite);
            for (int i = 0; i < 8; ++i) {
                window.draw(movieSprites[i]);
            }
            window.draw(cinemaName);
        }
        else if (currentScreen == SEAT_SELECTION) {
            window.draw(seatSelectionBgSprite);
            for (int i = 0; i < TOTAL_SEATS; ++i) {
                window.draw(seatShapes[i]);
                window.draw(seatNumbers[i]);
            }

            billText.setString("Total Bill: " + to_string(totalBill) + " PKR");
            window.draw(billText);
        }
        else if (currentScreen == BEVERAGE_SELECTION) {
            window.draw(beverageSelectionBgSprite);
            for (int i = 0; i < 4; ++i) {
                window.draw(beverageSprites[i]);
            }

            window.draw(refreshmentHeading);
            window.draw(popcornHeading);
            for (int i = 0; i < 3; ++i) {
                window.draw(popcornText[i]);
            }

            billText.setString("Total Bill: " + to_string(totalBill) + " PKR");
            window.draw(billText);
        }
        else if (currentScreen == PAYMENT_SELECTION) {
            window.draw(paymentSelectionBgSprite);
            window.draw(paymentHeading);
            window.draw(cashPaymentText);
            window.draw(cardPaymentText);
            window.draw(cardNumberText);
            window.draw(submitButtonText);
            paymentBillText.setString("Total Bill: " + to_string(totalBill) + " PKR"); //Use paymentBillText here
            paymentBillText.setFillColor(sf::Color::Black); //Set color to black
            window.draw(paymentBillText); //Draw paymentBillText
        }

        window.display();
    }

    return 0;
}