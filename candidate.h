#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
#include <vector>

struct candidate
{
    public:

    candidate(std::string name, int total_votes, bool is_in_race, std::vector<std::string> ballots);

    void set_name(std::string name);
    void set_total_votes(int total_vote);
    void set_is_in_race(bool is_in_race);
    void set_ballots(std::vector<std::string> ballots);
    void update_ballots(std::string ballot);

    std::string get_name();
    int get_total_votes();
    bool get_is_in_race();
    std::vector<std::string> get_ballots();


    private:
    std::string name;
    int total_vote;
    bool is_in_race;
    std::vector<std::string> ballots;
};

#endif