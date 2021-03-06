#ifndef ATLFORMULACHECKER_ATLMODEL_H
#define ATLFORMULACHECKER_ATLMODEL_H

#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <cstdio>
#include <iterator>
#include <algorithm>
#include "DisjointUnion.h"

class AtlModel {
public:
    struct Transition {
        Transition();

        int nextState;
        std::vector<std::string> actions;

        Transition(int nextState, const std::vector<std::string> &actions);

        bool operator<(const Transition &rhs) const;

        bool operator>(const Transition &rhs) const;

        bool operator<=(const Transition &rhs) const;

        bool operator>=(const Transition &rhs) const;
    };

private:
    int numberOfAgents;
    int numberOfStates;
    int numberOfTransitions;
    std::vector<std::set<Transition> > transitions;
    std::vector<std::set<int> > preStates;
    std::vector<std::vector<std::string> > agentsActions;
    std::vector<std::vector<int> > epistemicClassMembership;
    std::vector<DisjointUnion> epistemicClassDisjoint;
    std::vector<std::vector<std::map<std::string, std::set<int> > > > canGoThere;
    std::set<int> winningStates;
    unsigned long beginningStatesCount;
public:

    unsigned long getBeginningStatesCount() const;

    void setBeginningStatesCount(unsigned long beginningStatesCount);

public:
    std::vector<std::vector<std::set<int> > > imperfectInformation;

    AtlModel(int numberOfAgents, int numberOfStates);

    AtlModel();

    void addAction(int agentNumber, std::string action);

    void addTransition(int from, int to, std::vector<std::string> actions);

    void addEpistemicClass(int agentNumber, std::set<int> epistemicClass);

    void finishEpistemicClasses(int agentNumber);

    void findWhereCanGo(std::set<int> epistemicClass, int epistemicClassNumber, int agentNumber);

    bool isReachableByAgentDisjoint(std::string action, int fromState, int agentNumber, int firstWinning,
                                    DisjointUnion winningStates);

    bool isReachableByAgent(std::string action, int fromState, bool isWinningState[], int agentNumber);

    bool isReachableByAgentInSet(std::string action, int fromState, std::set<int> winningStates, int agentNumber);

    std::pair<std::set<int>, bool>
    basicFormulaOneAgentMultipleStatesDisjoint(int agentNumber, std::set<int> currentStates, int firstWinning,
                                               DisjointUnion &winningStatesDisjoint,
                                               std::vector<std::map<std::string, std::set<int> > > &customCanGoThere);

    std::set<int> basicFormulaOneAgentMultipleStatesPerfectInformation(int agentNumber, std::set<int> currentStates,
                                                                       std::vector<bool> &isWinningState);

    std::set<int> minimumFormulaOneAgentMultipleStatesDisjoint(int agentNumber, const std::set<int> &winningStates);

    std::set<int> minimumFormulaOneAgentMultipleStatesPerfectInformation(int agentNumber, std::set<int> winningStates);

    void setNumberOfStates(int numberOfStates);

    void saveToFile(std::ofstream &file);

    void loadFromFile(std::ifstream &file, bool imperfect = true);

    void clearTransitions();

    const std::set<int> &getWinningStates() const;

    void setWinningStates(const std::set<int> &winningStates);

    std::set<Transition> getTransitions(int stateNumber);
};


#endif //ATLFORMULACHECKER_ATLMODEL_H
