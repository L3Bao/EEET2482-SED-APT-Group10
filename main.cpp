#include "Rating.h"
#include "Member.h"
#include "DATETIME.h"
#include <iostream>
#include <vector>

int main() {
    // Create a vector to hold Rating objects
    std::vector<Rating*> ratings;

    
    Member* member1 = new Member("John Doe", 1);
    Member* member2 = new Member("Jane Smith", 2);
    DateTime bookingTime1(2023, 1, 1, 12, 0, 0); 
    DateTime bookingTime2(2023, 1, 2, 13, 0, 0); 
    Booking* booking1 = new Booking("B123", bookingTime1, member1, member2);
    Booking* booking2 = new Booking("B124", bookingTime2, member2, member1);

    // Create Rating objects and add to the vector
    ratings.push_back(new Rating("R001", member1, booking1));
    ratings.push_back(new Rating("R002", member2, booking2));

    // Submit ratings (example values used here)
    ratings[0]->SubmitRating(4.0, 3.5, 4.5, "Good service");
    ratings[1]->SubmitRating(4.5, 4.0, 4.0, "Excellent experience");

    // Iterate through the vector and print details of each rating
    for (Rating* rating : ratings) {
        rating->PrintRatingDetails();
    }

    // Clean up
    for (Rating* rating : ratings) {
        delete rating; // Delete each Rating object
    }
    delete member1;
    delete member2;
    delete booking1;
    delete booking2;

    return 0;
}
// to run the program add (cd "h:\Booking &Rating class\" ; if ($?) { g++ main.cpp Rating.cpp -o main } ; if ($?) { .\main })