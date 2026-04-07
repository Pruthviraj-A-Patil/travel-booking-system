#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 100
#define MAX_CONTACT 20

struct Booking {
    char name[MAX_NAME];
    int age;
    char contact[MAX_CONTACT];
    char gender[10];
    char mode[10];
    int departureDate;
    int returnDate;
    int ticketID;
    float fare;
};

int generateTicketID() {
    return 10000 + rand() % 90000;
}

float calculateFare(struct Booking b) {
    float baseFare = strcmp(b.mode, "bus") == 0 ? 200.0 : 500.0;
    if (b.age < 5)
        return 0.0;
    else if (b.age >= 60)
        return baseFare / 2;
    else
        return baseFare;
}

void saveBookingToFile(struct Booking b) {
    FILE *fp = fopen("bookings.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(fp, "%d|%s|%d|%s|%s|%s|%d|%d|%.2f\n",
            b.ticketID, b.name, b.age, b.gender, b.mode, b.contact,
            b.departureDate, b.returnDate, b.fare);
    fclose(fp);
}

void saveFeedbackToFile(char feedback[]) {
    FILE *fp = fopen("feedback.txt", "a");
    if (fp == NULL) {
        printf("Error opening feedback file.\n");
        return;
    }
    fprintf(fp, "Feedback: %s\n", feedback);
    fclose(fp);
}

void showHelplines() {
    printf("\n--- Luggage Helpline Contacts ---\n");
    printf("1. Bus Luggage Help: 1800-111-222\n");
    printf("2. Train Luggage Help: 1800-333-444\n");
}

void showCancellationPolicy() {
    printf("\n--- Cancellation & Refund Policy ---\n");
    printf("- Full refund if cancelled 24 hrs before departure\n");
    printf("- 50%% refund if cancelled 12 hrs before departure\n");
    printf("- No refund for last-minute cancellations\n");
}

void displayConfirmation(struct Booking b) {
    printf("\n--- TICKET CONFIRMATION ---\n");
    printf("Ticket ID     : %d\n", b.ticketID);
    printf("Name          : %s\n", b.name);
    printf("Age           : %d\n", b.age);
    printf("Gender        : %s\n", b.gender);
    printf("Transport     : %s\n", b.mode);
    printf("Contact       : %s\n", b.contact);
    printf("Departure     : %d\n", b.departureDate);
    printf("Return        : %d\n", b.returnDate);
    printf("\u20B9");
    printf("Fare          : %.2f\n", b.fare); // Using the Rupee symbol
    printf("Confirmation  : Sent to %s\n", b.contact);
}

void collectDetails(struct Booking *b) {
    printf("Enter your name: ");
    scanf(" %[^\n]", b->name);

    printf("Enter your age: ");
    scanf("%d", &b->age);

    printf("Enter contact number: ");
    scanf(" %s", b->contact);

    printf("Enter gender (M/F): ");
    scanf(" %s", b->gender);

    printf("Enter departure date (DDMM): ");
    scanf("%d", &b->departureDate);

    printf("Enter return date (DDMM): ");
    scanf("%d", &b->returnDate);
}

int validate(struct Booking b) {
    if (strlen(b.name) == 0 || strlen(b.contact) == 0 || b.age <= 0) {
        printf("Error: All fields are mandatory and must be valid.\n");
        return 0;
    }
    if (b.returnDate < b.departureDate) {
        printf("Error: Return date cannot be before departure date.\n");
        return 0;
    }
    return 1;
}

void bookBus(struct Booking *b) {
    printf("\n--- BUS BOOKING ---\n");
    printf("Luggage Limit: 20kg per person\n");
    if (strcmp(b->gender, "F") == 0)
        printf("You will be seated in the Women's Only section.\n");

    b->fare = calculateFare(*b);
    b->ticketID = generateTicketID();
    displayConfirmation(*b);
    saveBookingToFile(*b);
}

void bookTrain(struct Booking *b) {
    printf("\n--- TRAIN BOOKING ---\n");
    printf("Pets are allowed with documentation.\n");
    if (strcmp(b->gender, "F") == 0)
        printf("You will be seated in the Women's Only carriage.\n");

    b->fare = calculateFare(*b);
    b->ticketID = generateTicketID();
    displayConfirmation(*b);
    saveBookingToFile(*b);
}

void viewAllBookings() {
    FILE *fp = fopen("bookings.txt", "r");
    if (fp == NULL) {
        printf("No bookings found.\n");
        return;
    }

    char ch;
    printf("\n--- All Bookings ---\n");
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);
    fclose(fp);
}

void getFeedback() {
    char feedback[300];
    printf("\nWe value your feedback. Enter your comments:\n");
    scanf(" %[^\n]", feedback);
    saveFeedbackToFile(feedback);
    printf("Thank you for your feedback!\n");
}

void cancelBookingByID(int cancelID) {
    FILE *fp = fopen("bookings.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int found = 0;

    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), fp)) {
        int ticketID;
        sscanf(line, "%d|", &ticketID);

        if (ticketID == cancelID) {
            found = 1;
            continue;
        }
        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if (found)
        printf("Booking with Ticket ID %d has been cancelled.\n", cancelID);
    else
        printf("Booking ID not found.\n");
}

int main() {
    struct Booking booking;
    char again;
    int choice;

    srand(time(NULL));

    do {
        printf("\n=========== Travel Booking System ===========\n");
        printf("1. Book Ticket\n");
        printf("2. View Luggage Helplines\n");
        printf("3. View Cancellation Policy\n");
        printf("4. View All Bookings\n");
        printf("5. Give Feedback\n");
        printf("6. Cancel Booking by Ticket ID\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter mode of transport (bus/train): ");
            scanf(" %s", booking.mode);
            if (strcmp(booking.mode, "bus") != 0 && strcmp(booking.mode, "train") != 0) {
                printf("Only bus/train bookings are supported.\n");
                break;
            }

            collectDetails(&booking);
            if (validate(booking)==0) {
                printf("Booking failed. Please try again.\n");
                break;
            }

            if (strcmp(booking.mode, "bus") == 0)
                bookBus(&booking);
            else
                bookTrain(&booking);
            break;

        case 2:
            showHelplines();
            break;

        case 3:
            showCancellationPolicy();
            break;

        case 4:
            viewAllBookings();
            break;

        case 5:
            getFeedback();
            break;

        case 6:
            printf("Enter Ticket ID to cancel: ");
            int cancelID;
            scanf("%d", &cancelID);
            cancelBookingByID(cancelID);
            break;

        case 7:
            printf("Thank you for using the Travel Booking System!\n");
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }

        printf("\nDo you want to perform another action? (Y/N): ");
        scanf(" %c", &again);
    } while (again == 'Y' || again == 'y');

    return 0;
}
