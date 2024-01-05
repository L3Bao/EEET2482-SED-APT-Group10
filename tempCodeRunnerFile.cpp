oking("123", bookingTime, &member1, &member2);
  Rating rating("456", &member1, 4.5, 4.2, 4.8, "Great experience!", &booking);

  booking.CreateBooking();
  booking.CompleteBooking();
  rating.SubmitRating();

  return 0;
}