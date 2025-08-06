#ifndef MOOD_ANALYZER_H
#define MOOD_ANALYZER_H

#include <string>
#include <vector>
#include "Storage.h"

class MoodAnalyzer {
private:
    // Helper methods
    bool containsKeyword(const std::string& text, const std::vector<std::string>& keywords);
    std::string getRandomMessage(const std::vector<std::string>& messages);
    
    // NEW: Keyword extraction and sentiment analysis
    std::vector<std::string> extractKeywords(const std::string& text);
    double calculateSentimentScore(const std::string& text);
    std::vector<std::string> getPositiveKeywords();
    std::vector<std::string> getNegativeKeywords();
    std::vector<std::string> getEnergyKeywords();

public:
    MoodAnalyzer() = default;
    
    // Main method to generate supportive response
    std::string generateSupportiveMessage(const MoodEntry& entry);
    
    // Generate task suggestions based on mood
    std::string generateTaskSuggestion(MoodLevel mood, int completedTasks, int totalTasks);
    
    // Analyze mood patterns
    std::string analyzeMoodTrend(const std::vector<MoodEntry>& recentEntries);
    
    // NEW: Enhanced mood analysis
    void analyzeMoodEntry(MoodEntry& entry);
    std::string generateDetailedInsights(const MoodEntry& entry);
};

#endif // MOOD_ANALYZER_H 