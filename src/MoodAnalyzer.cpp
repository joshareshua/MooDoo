#include "MoodAnalyzer.h"
#include <algorithm>
#include <random>
#include <ctime>

bool MoodAnalyzer::containsKeyword(const std::string& text, const std::vector<std::string>& keywords) {
    std::string lowerText = text;
    std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
    
    for (const auto& keyword : keywords) {
        if (lowerText.find(keyword) != std::string::npos) {
            return true;
        }
    }
    return false;
}

std::string MoodAnalyzer::getRandomMessage(const std::vector<std::string>& messages) {
    if (messages.empty()) return "";
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, messages.size() - 1);
    
    return messages[dis(gen)];
}

std::string MoodAnalyzer::generateSupportiveMessage(const MoodEntry& entry) {
    std::string response = "\n💙 MooDoo's Supportive Message:\n";
    
    // Analyze mood level and content
    switch (entry.mood) {
        case MoodLevel::VERY_LOW:
        case MoodLevel::LOW: {
            std::vector<std::string> lowMoodMessages = {
                "I can see you're having a tough day. That's completely okay - we all have them! 💙",
                "It's okay to not be okay. Remember, you don't have to be productive every single day.",
                "I understand this feels hard right now. Let's take it one small step at a time.",
                "You're doing better than you think. Even getting out of bed is an achievement on hard days."
            };
            
            // Add specific responses based on keywords
            if (containsKeyword(entry.content, {"overwhelmed", "stress", "anxiety", "pressure"})) {
                response += "I notice you're feeling overwhelmed. Let's break things down together.\n";
                response += "What's one tiny thing you could do that would make you feel even slightly better?\n";
            } else if (containsKeyword(entry.content, {"tired", "exhausted", "drained", "fatigue"})) {
                response += "It sounds like you're really tired. Rest is productive too!\n";
                response += "Maybe today is a day for gentle self-care instead of pushing yourself.\n";
            } else {
                response += getRandomMessage(lowMoodMessages) + "\n";
            }
            break;
        }
        
        case MoodLevel::NEUTRAL: {
            std::vector<std::string> neutralMessages = {
                "You're in a balanced place today. That's actually really good!",
                "Neutral is totally fine. Sometimes steady progress is the best kind.",
                "How about we check in on your tasks and see what feels right for today?",
                "You're doing great. Let's find something that feels good to work on."
            };
            response += getRandomMessage(neutralMessages) + "\n";
            break;
        }
        
        case MoodLevel::GOOD:
        case MoodLevel::EXCELLENT: {
            std::vector<std::string> goodMoodMessages = {
                "You're feeling great! This is a perfect time to tackle those important tasks! ✨",
                "Your positive energy is wonderful! Let's channel that into something productive.",
                "You're in a great headspace today. What would you like to accomplish?",
                "This is your moment! You've got the energy and motivation - let's make the most of it!"
            };
            
            if (containsKeyword(entry.content, {"energized", "motivated", "excited", "happy"})) {
                response += "I love your energy! You're clearly in a great place to get things done.\n";
                response += "This is the perfect time to tackle those challenging tasks you've been putting off!\n";
            } else {
                response += getRandomMessage(goodMoodMessages) + "\n";
            }
            break;
        }
    }
    
    // Add a general supportive closing
    response += "\nRemember: You're doing great, and it's okay to adjust your plans based on how you're feeling. 💙\n";
    
    return response;
}

std::string MoodAnalyzer::generateTaskSuggestion(MoodLevel mood, int completedTasks, int totalTasks) {
    if (totalTasks == 0) {
        return "You don't have any tasks yet. How about adding one small thing you'd like to accomplish today?";
    }
    
    double completionRate = totalTasks > 0 ? (double)completedTasks / totalTasks : 0.0;
    
    switch (mood) {
        case MoodLevel::VERY_LOW:
        case MoodLevel::LOW:
            if (completionRate < 0.3) {
                return "💡 Suggestion: You're having a low-energy day. Maybe pick just ONE small, easy task? Even something like 'drink water' or 'make your bed' counts as a win!";
            } else {
                return "💡 Suggestion: You've already made some progress today! That's amazing. Maybe just one more small thing?";
            }
            
        case MoodLevel::NEUTRAL:
            return "💡 Suggestion: You're in a good place to tackle some medium-priority tasks. What feels most important right now?";
            
        case MoodLevel::GOOD:
        case MoodLevel::EXCELLENT:
            if (completionRate < 0.5) {
                return "💡 Suggestion: You're feeling great! This is perfect energy for tackling those high-priority tasks. Go for it! ✨";
            } else {
                return "💡 Suggestion: You're on fire today! Keep that momentum going with another task!";
            }
    }
    
    return "💡 Suggestion: Check your task list and pick something that feels right for your energy level today.";
}

std::string MoodAnalyzer::analyzeMoodTrend(const std::vector<MoodEntry>& recentEntries) {
    if (recentEntries.size() < 2) {
        return "Keep logging your mood to see patterns over time!";
    }
    
    // Simple trend analysis
    int lowMoodCount = 0;
    int highMoodCount = 0;
    
    for (const auto& entry : recentEntries) {
        if (entry.mood == MoodLevel::VERY_LOW || entry.mood == MoodLevel::LOW) {
            lowMoodCount++;
        } else if (entry.mood == MoodLevel::GOOD || entry.mood == MoodLevel::EXCELLENT) {
            highMoodCount++;
        }
    }
    
    if (lowMoodCount > highMoodCount) {
        return "📊 Mood Insight: You've been having more challenging days lately. Remember, this is temporary and you're doing great just by showing up.";
    } else if (highMoodCount > lowMoodCount) {
        return "📊 Mood Insight: You've been in a really good place lately! Keep up whatever's working for you.";
    } else {
        return "📊 Mood Insight: Your mood has been pretty balanced lately. That's actually really healthy!";
    }
} 