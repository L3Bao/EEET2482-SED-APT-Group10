#ifndef Rating_H
#define Rating_H

#include "Member.h"
#include <string>




class Rating {
private:
    std::string ratingId;
    Member* ratedMember;
    float skillRating;
    float supporterRating;
    float hostRating;
    std::string comments;
    Booking* relatedBooking;

public:
    // Constructors
     Rating(const std::string& id, Member* member, Booking* booking)
        : ratingId(id), ratedMember(member), relatedBooking(booking),
          skillRating(0.0f), supporterRating(0.0f), hostRating(0.0f) {}

    
    // Getters and Setters
    std::string GetRatingId() const { return ratingId; }
    void SetRatingId(const std::string& id) { ratingId = id; }

   Member* GetRatedMember() const { return ratedMember; }
    void SetRatedMember(Member* member) { ratedMember = member; }

    float GetSkillRating() const { return skillRating; }
    void SetSkillRating(float rating) { skillRating = rating; }

    float GetSupporterRating() const { return supporterRating; }
    void SetSupporterRating(float rating) { supporterRating = rating; }

    float GetHostRating() const { return hostRating; }
    void SetHostRating(float rating) { hostRating = rating; }

    std::string GetComments() const { return comments; }
    void SetComments(const std::string& comments) { this->comments = comments; }

    Booking* GetRelatedBooking() const { return relatedBooking; }
    void SetRelatedBooking(Booking* booking) { relatedBooking = booking; }

    void InputRatingDetails();
    void SaveRatingToFile(const std::string& filename);
    void SubmitRating(float skillRating, float supporterRating, float hostRating, const std::string& comments, Member* memberSubmittingRating);

};
#endif // Rating_H