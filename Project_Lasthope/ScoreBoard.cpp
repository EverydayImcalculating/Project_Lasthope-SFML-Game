#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
    m_font.loadFromFile(Utils::GetResourceDirectory() + "/media/Fonts/arial.ttf");
}

bool ScoreBoard::sortDes(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b)
{
    return (a > b);
}

void ScoreBoard::clearScore()
{
    for (int i = 0; i < 5; i++)
    {
        scorePair.erase(scorePair.begin());
    }
}

void ScoreBoard::readFile()
{
    
    fp = fopen("./Assets/media/Score/score.txt", "r");
    if (!fp)
    {
        std::cout << "!Cannot Read score.txt" << std::endl;
    }
    for (int i = 0; i < 5; i++)
    {
        fscanf(fp, "%s %d\n", &temp, &score[i]);
        name[i] = temp;
        scorePair.push_back(make_pair(score[i], name[i]));
    }
    std::sort(scorePair.begin(), scorePair.end(), sortDes);
    fclose(fp);
}

void ScoreBoard::writeFile(std::string playerName, int playerScore)
{
    readFile();
    scorePair.push_back(make_pair(playerScore, playerName));
    std::sort(scorePair.begin(), scorePair.end(), sortDes);

    fp = fopen("./Assets/media/Score/score.txt", "w");

    for (int i = 0; i < 5; i++)
    {
        strcpy(temp, scorePair[i].second.c_str());
        fprintf(fp, "%s %d\n", temp, scorePair[i].first);
    }

    fclose(fp);
}