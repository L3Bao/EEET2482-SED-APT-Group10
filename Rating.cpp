#include "Rating.h"
#include <iostream>



void Rating::SubmitRating(float skill, float supporter, float host, const std::string& comment) {
    skillRating = skill;
    supporterRating = supporter;
    hostRating = host;
    comments = comment;
    std::cout << "Rating submitted for member " << ratedMember->GetName() << std::endl;
}
    void Rating::PrintRatingDetails() const {
    std::cout << "Rating ID: " << ratingId << std::endl;
    if (ratedMember != nullptr) {
        std::cout << "Rated Member: " << ratedMember->GetName() << std::endl;
    } else {
        std::cout << "Rated Member: Not available" << std::endl;
    }
    std::cout << "Skill Rating: " << skillRating << std::endl;
    std::cout << "Supporter Rating: " << supporterRating << std::endl;
    std::cout << "Host Rating: " << hostRating << std::endl;
    std::cout << "Comments: " << comments << std::endl;
}

