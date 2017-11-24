#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "SeleneModel.h"

#include "cppitertools/itertools.hpp"

using namespace std;

int main() {
    int option;
    printf("Welcome to Selene Model Checker. Please choose desired option:\n");
    printf("1 - standard formula check\n");
    printf("2 - percentage coverage check\n");
    scanf("%d", &option);
    if(option == 2) {
        struct timespec start, finish;
        double elapsed;
        int noVoters;
        int noBallots;
        int maxCoerced;
        int maxWaitingForVotes;
        int maxWaitingForHelp;

        printf("Number of voters: ");
        scanf("%d", &noVoters);
        printf("Number of candidates: ");
        scanf("%d", &noBallots);
        printf("Maximal coercions: ");
        scanf("%d", &maxCoerced);
        printf("Maximal waiting for votes: ");
        scanf("%d", &maxWaitingForVotes);
        printf("Maximal waiting for help: ");
        scanf("%d", &maxWaitingForHelp);

        string filename = "SeleneModel_" + to_string(noVoters) + "_" + to_string(noBallots) + "_" +
                          to_string(maxCoerced) + "_" + to_string(maxWaitingForVotes) + "_" +
                          to_string(maxWaitingForHelp) + "_percentage_result.txt";

        ofstream resultFile(filename);

        clock_gettime(CLOCK_MONOTONIC, &start);
        SeleneModel seleneModel = SeleneModel(noVoters, noBallots, maxCoerced, maxWaitingForVotes, maxWaitingForHelp);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Generated model in " << elapsed << " s" << endl;
        resultFile << "Number of states: " << seleneModel.states.size() << endl;

        seleneModel.clear();

        clock_gettime(CLOCK_MONOTONIC, &start);
        auto result = seleneModel.getModel().minimumFormulaOneAgentMultipleStatesDisjoint(0,
                                                                                          seleneModel.formula4PercentageWinningStates);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        cout << "Number of result states: " << result.size() << endl;

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Formula 4 imperfect time: " << elapsed << " s" << endl;

        if (result.find(0) != result.end()) {
            resultFile << "Formula 4 imperfect result: true" << endl;
        } else {
            resultFile << "Formula 4 imperfect result: false" << endl;
        }

        int count = 0;
        for (auto s: seleneModel.configurationStates) {
            if (result.find(s) != result.end()) {
                ++count;
            }
        }

        resultFile << "Number of reached configuration states: " << count << endl;
        resultFile << "Number of all configuration states: " << seleneModel.configurationStates.size() << endl;
        resultFile << "Percentage of configuration states: "
                   << (100.0 * (double) count / (double) seleneModel.configurationStates.size()) << "%" << endl;

        resultFile.close();

        printf("Done. Results saved in %s\n", filename.c_str());
    } else {
        struct timespec start, finish;
        double elapsed;
        int noVoters;
        int noBallots;
        int maxCoerced;
        int maxWaitingForVotes;
        int maxWaitingForHelp;

        printf("Number of voters: ");
        scanf("%d", &noVoters);
        printf("Number of candidates: ");
        scanf("%d", &noBallots);
        printf("Maximal coercions: ");
        scanf("%d", &maxCoerced);
        printf("Maximal waiting for votes: ");
        scanf("%d", &maxWaitingForVotes);
        printf("Maximal waiting for help: ");
        scanf("%d", &maxWaitingForHelp);

        string filename = "SeleneModel_" + to_string(noVoters) + "_" + to_string(noBallots) + "_" +
                          to_string(maxCoerced) + "_" + to_string(maxWaitingForVotes) + "_" +
                          to_string(maxWaitingForHelp) + "_result.txt";

        printf("Now testing %d %d %d %d %d\n", noVoters, noBallots, maxCoerced, maxWaitingForVotes, maxWaitingForHelp);

        ofstream resultFile(filename);

        clock_gettime(CLOCK_MONOTONIC, &start);
        SeleneModel seleneModel = SeleneModel(noVoters, noBallots, maxCoerced, maxWaitingForVotes, maxWaitingForHelp);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Generated model in " << elapsed << " s" << endl;
        resultFile << "Number of states: " << seleneModel.states.size() << endl;

        seleneModel.clear();

        clock_gettime(CLOCK_MONOTONIC, &start);
        auto result = seleneModel.getModel().minimumFormulaOneAgentMultipleStatesPerfectInformation(0,
                                                                                                    seleneModel.formula1WinningStates);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Formula 1 perfect time: " << elapsed << " s" << endl;

        if (result.find(0) != result.end()) {
            resultFile << "Formula 1 perfect result: true" << endl;
        } else {
            resultFile << "Formula 1 perfect result: false" << endl;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        result = seleneModel.getModel().minimumFormulaOneAgentMultipleStatesPerfectInformation(0,
                                                                                               seleneModel.formula2WinningStates);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Formula 2 perfect time: " << elapsed << " s" << endl;

        if (result.find(0) != result.end()) {
            resultFile << "Formula 2 perfect result: true" << endl;
        } else {
            resultFile << "Formula 2 perfect result: false" << endl;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        result = seleneModel.getModel().minimumFormulaOneAgentMultipleStatesPerfectInformation(0,
                                                                                               seleneModel.formula3WinningStates);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Formula 3 perfect time: " << elapsed << " s" << endl;

        if (result.find(0) != result.end()) {
            resultFile << "Formula 3 perfect result: true" << endl;
        } else {
            resultFile << "Formula 3 perfect result: false" << endl;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        result = seleneModel.getModel().minimumFormulaOneAgentMultipleStatesPerfectInformation(0,
                                                                                               seleneModel.formula4WinningStates);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Formula 4 perfect time: " << elapsed << " s" << endl;

        if (result.find(0) != result.end()) {
            resultFile << "Formula 4 perfect result: true" << endl;
        } else {
            resultFile << "Formula 4 perfect result: false" << endl;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        result = seleneModel.getModel().minimumFormulaOneAgentMultipleStatesDisjoint(0,
                                                                                     seleneModel.formula1WinningStates);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Formula 1 imperfect time: " << elapsed << " s" << endl;

        if (result.find(0) != result.end()) {
            resultFile << "Formula 1 imperfect result: true" << endl;
        } else {
            resultFile << "Formula 1 imperfect result: false" << endl;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        result = seleneModel.getModel().minimumFormulaOneAgentMultipleStatesDisjoint(0,
                                                                                     seleneModel.formula2WinningStates);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Formula 2 imperfect time: " << elapsed << " s" << endl;

        if (result.find(0) != result.end()) {
            resultFile << "Formula 2 imperfect result: true" << endl;
        } else {
            resultFile << "Formula 2 imperfect result: false" << endl;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        result = seleneModel.getModel().minimumFormulaOneAgentMultipleStatesDisjoint(0,
                                                                                     seleneModel.formula3WinningStates);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Formula 3 imperfect time: " << elapsed << " s" << endl;

        if (result.find(0) != result.end()) {
            resultFile << "Formula 3 imperfect result: true" << endl;
        } else {
            resultFile << "Formula 3 imperfect result: false" << endl;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        result = seleneModel.getModel().minimumFormulaOneAgentMultipleStatesDisjoint(0,
                                                                                     seleneModel.formula4WinningStates);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_sec - start.tv_sec) / 1000000000.0;
        resultFile << "Formula 4 imperfect time: " << elapsed << " s" << endl;

        if (result.find(0) != result.end()) {
            resultFile << "Formula 4 imperfect result: true" << endl;
        } else {
            resultFile << "Formula 4 imperfect result: false" << endl;
        }

        resultFile.close();


        printf("Done. Results saved in %s\n", filename.c_str());
    }




    return 0;
}

