#include "candidate.h"
#include <vector>

using namespace std;

candidate::candidate(string name_temp = "N/A", int total_votes_temp = 0, bool is_in_race_temp = true, vector<string> ballots_temp = {})
{
    name = name_temp;
    total_vote = total_votes_temp;
    is_in_race = is_in_race_temp;
    ballots = ballots_temp;

}

void candidate::set_name(string temp) { name = temp; }
void candidate::set_total_votes(int temp) { total_vote = temp; }
void candidate::set_is_in_race(bool temp) { is_in_race = temp; }
void candidate::set_ballots(vector<string> temp) { ballots = temp; }
void candidate::update_ballots(string temp) { ballots.push_back(temp); }

string candidate::get_name() { return name; }
int candidate::get_total_votes() { return total_vote; }
bool candidate::get_is_in_race() { return is_in_race; }
vector<string> candidate::get_ballots() { return ballots; }