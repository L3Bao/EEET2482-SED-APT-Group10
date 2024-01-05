#include "Rating.h"
#include "Member.h"
#include "Booking.h"
#include <iostream> 
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;


    void Rating::InputRatingDetails() {
        if (relatedBooking && relatedBooking->isCompleted()) {
            std::cout << "Enter skill rating: ";
            std::cin >> skillRating;

            std::cout << "Enter supporter rating: ";
            std::cin >> supporterRating;

            std::cout << "Enter host rating: ";
            std::cin >> hostRating;

            std::cout << "Enter comments: ";
            std::cin.ignore(); // To clear the newline character in the buffer
            std::getline(std::cin, comments);

            std::cout << "Rating submitted for booking ID: " << relatedBooking->GetBookingId() << std::endl;
        } else {
            std::cout << "Rating cannot be submitted. Booking is not completed or does not exist." << std::endl;
        }
    }

    void Rating::SaveRatingToFile(const std::string& filename) {
        std::ofstream file(filename, std::ios::app); // Open in append mode
        if (file.is_open()) {
            file << "Rating ID: " << ratingId << "\n"
                 << "Skill Rating: " << skillRating << "\n"
                 << "Supporter Rating: " << supporterRating << "\n"
                 << "Host Rating: " << hostRating << "\n"
                 << "Comments: " << comments << "\n"
                 << "Related Booking ID: " << (relatedBooking ? relatedBooking->GetBookingId() : "N/A") << "\n\n";
            file.close();
            std::cout << "Rating saved to file: " << filename << std::endl;
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }


void Rating::SubmitRating(float skillRating, float supporterRating, float hostRating, const std::string& comments, Member* memberSubmittingRating) {
    // Check if the booking is associated and if the member is the same as the booking member
    if (relatedBooking && (relatedBooking->GetBookingMember() == memberSubmittingRating || relatedBooking->GetOfferingMember() == memberSubmittingRating)) {
        this->skillRating = skillRating;
        this->supporterRating = supporterRating;
        this->hostRating = hostRating;
        this->comments = comments;      
        std::cout << "Rating submitted for member " << ratedMember->getUsername() << std::endl;
    } else {
        std::cout << "You are not authorized to rate this service." << std::endl;
    }
};

    

