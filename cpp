#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class for a person
class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

    string getName() const {
        return name;
    }
};

// Class representing a voter
class Voter : public Person {
private:
    bool hasVoted;

public:
    Voter(string n, int a) : Person(n, a), hasVoted(false) {}

    bool getHasVoted() const {
        return hasVoted;
    }

    void setHasVoted(bool voted) {
        hasVoted = voted;
    }
};

// Class representing a candidate
class Candidate : public Person {
private:
    int votesReceived;

public:
    Candidate(string n, int a) : Person(n, a), votesReceived(0) {}

    int getVotesReceived() const {
        return votesReceived;
    }

    void addVote() {
        votesReceived++;
    }
};

// Class representing the voting machine
class VotingMachine {
private:
    vector<Voter> voters;
    vector<Candidate> candidates;

public:
    void registerVoter(const string& name, int age) {
        voters.push_back(Voter(name, age));
    }

    void addCandidate(const string& name, int age) {
        candidates.push_back(Candidate(name, age));
    }

    void castVote(const string& voterName, const string& candidateName) {
        for (auto voter : voters) {
            if (voter.getName() == voterName && !voter.getHasVoted()) {
                for (Candidate& candidate : candidates) {
                    if (candidate.getName() == candidateName) {
                        candidate.addVote();
                        voter.setHasVoted(true);
                        cout << "Vote cast successfully.\n";
                        return;
                    }
                }
                cout << "Candidate not found.\n";
                return;
            }
        }
        cout << "Voter not found or has already voted.\n";
    }

    void displayResults() {
        cout << "Election Results:\n";
        for (const Candidate& candidate : candidates) {
            cout << candidate.getName() << ": " << candidate.getVotesReceived() << " votes\n";
        }
    }
};

int main() {
    VotingMachine votingMachine;
    // Register voters
    votingMachine.registerVoter("Alice", 30);
    votingMachine.registerVoter("Bob", 25);
    // Add candidates
    votingMachine.addCandidate("Candidate A", 45);
    votingMachine.addCandidate("Candidate B", 50);
    // Cast votes
    votingMachine.castVote("Alice", "Candidate A");
    votingMachine.castVote("Bob", "Candidate B");
    votingMachine.castVote("Alice", "Candidate B"); // Attempt to vote again

    // Display results
    votingMachine.displayResults();

    return 0;
}
