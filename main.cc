#include <iostream>
#include <fstream>
#include <vector>
#include "candidate.h"

using namespace std;

int main (int argc, char const *argv[])
{
    int winner_location = -1;
    int round = 2;
    int loser_location = -1;
    int smallest_vote = 10000000;
    int total_votes = 0;
    bool winner = false;
    string input = "";
    string temp = "";
    string current_ballot = "";
    vector<string> ballots;
    vector<candidate> candidates;

    ///loading with file
    if (argc == 2)
    {
        fstream file(argv[1]);

        if (!file.is_open()) { cout << "Error, file did not open" << endl; }
        ///getting candidate names
        getline(file, input);
        while (input.length() != 0)
        {
        temp = input;
        temp = temp.substr(0, temp.find(','));
        candidate temp_candidate(temp, 0, true, {});
        candidates.push_back(temp_candidate);
        if (temp.length() + 1 < input.length()) { input = input.substr(temp.length() + 1); }
        else { input = ""; }
        }
        ///input ballots
        while (getline(file,input))
        {
            ballots.push_back(input);
        }     
        file.close();
    }
    else/// manual enter
    {
        cout << "Enter the name of all candidates followed by a ',' example 'John, Lynda': ";
        getline(cin, input);
        
        while (input.length() != 0)
        {
            temp = input;
            temp = temp.substr(0, temp.find(','));
            candidate temp_candidate(temp, 0, true, {});
            candidates.push_back(temp_candidate);
            if (temp.length() + 1 < input.length()) { input = input.substr(temp.length() + 1); }
            else { input = ""; }
        }
        
        cout << "Input all ballots: ";
        cin >> input;

        while(input != "q" && input != "Q")
        {
            ballots.push_back(input);
            cout << "Enter Ballot or type q to end entry: ";
            cin >> input;
        }
    }

    ///first round 
    ///putting all ballots in the right pile for counting
    for (size_t i = 0; i < ballots.size(); i++)
    {
        temp = ballots.at(i);
        for (size_t j = 0; j < temp.length(); j++)
        {///finding the location of the 1 and putting it in the right location
            if (temp.at(j) == '1')
            {
                candidates.at(j / 2).update_ballots(temp);
            }
        }
    }

    cout << candidates.at(3).get_ballots().size() << endl;

    ///setting the total number of votes
    for (size_t i = 0; i < candidates.size(); i++)
    {
        cout << i << endl;
        candidates.at(i).set_total_votes(candidates.at(i).get_ballots().size());
        cout << "hi" << endl;
    }
    
    cout << "bye" << endl;

    total_votes = ballots.size();

    cout << "wee" << endl;
    cout << total_votes;
    
    while (!winner)
    {///checking if any candidate has won the election
        for (size_t i = 0; i < candidates.size(); i++)
        {
            if(candidates.at(i).get_total_votes() > (total_votes / 2) && candidates.at(i).get_is_in_race()) 
            {
                winner = true; 
                winner_location = i;
            }            
        }///recounting votes
        if (!winner)
        {
            smallest_vote = candidates.at(0).get_total_votes();
            loser_location = 0;
            for (size_t i = 0; i < candidates.size(); i++)
            {///checking for the smallest number of votes
                if (smallest_vote > candidates.at(i).get_total_votes() && candidates.at(i).get_is_in_race())
                {
                    smallest_vote = candidates.at(i).get_total_votes();
                    loser_location = i;
                }/// STILL NEED TO ADD IN CASE OF TIE
            }

            char next_rank = '9';
            cout << next_rank;

            ///recounting ballots
            candidates.at(loser_location).set_is_in_race(false);
            for (size_t i = 0; i < candidates.at(loser_location).get_ballots().size(); i++)
            {///finding the location of the highest candidate still in and the ballot in the right spot it in the right location
                temp = candidates.at(loser_location).get_ballots().at(i);

                for (size_t j = 0; j < temp.length(); j++)
                {
                    if (next_rank > temp.at(j) && candidates.at((j + 1) / 2).get_is_in_race() && temp.at(j) != ',')
                    {
                        next_rank = temp.at(j);
                    }
                }
                ///finding the next highest ranked candidate
                int location = -1;
                location = temp.find(next_rank);
                candidates.at((location / 2)).update_ballots(temp);
            }
            candidates.at(loser_location).set_ballots({});

            for (size_t i = 0; i < candidates.size(); i++)
            {
                candidates.at(i).set_total_votes(candidates.at(i).get_ballots().size());
            }
            
            round++;
        }
    }
    
    cout << "the winner: " << candidates.at(winner_location).get_name() << endl;


    ///printing
    for (size_t i = 0; i < candidates.size(); i++)
    {
        cout << candidates.at(i).get_name() << " ";
        for (size_t j = 0; j < candidates.at(i).get_ballots().size(); j++)
        {
            cout << candidates.at(i).get_ballots().at(j) << " ";
        }
        cout << endl;
    }
    
}