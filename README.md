# MooDoo
ADHD Planner and Journal - A Mental Health-Aware Task Management System

## Project Overview
MooDoo is a planner and journal application designed specifically for people with ADHD and mental health considerations. It allows users to:
- Write about how they're feeling and adjust their todo list accordingly
- Receive mood-based suggestions and motivational support
- Get reassurance when they're not as productive
- Leverage positive moods for enhanced productivity

## Core Features (MVP)
- Create, update, and delete daily tasks
- Journal mood entries (e.g. "Feeling tired today...")
- Mood-based suggestions (e.g. "Let's take it slow today")
- Daily encouragement/motivation messages
- Persist user data (local file storage)
- Clean CLI interface
- **Task difficulty levels** (Easy/Medium/Hard)
- **Mood-based task recommendations**
- **Daily mood summary & progress tracking**
- **Weekly mood & productivity patterns**
- **Gentle reminders (ADHD-friendly)**

## Current Feature Set

### Task Management
- **Smart Task Creation**: Add tasks with priority and difficulty levels
- **Mood-Aware Suggestions**: Get task recommendations based on current energy level
- **Progress Tracking**: See completion rates and daily progress
- **Gentle Reminders**: ADHD-friendly task suggestions without pressure

### Mood & Mental Health
- **Daily Mood Logging**: Track how you're feeling throughout the day
- **Mood Analysis**: Get insights about your emotional patterns
- **Weekly Patterns**: See correlations between mood and productivity
- **Supportive Messages**: Encouraging responses based on your current state

### ADHD-Specific Features
- **Non-Judgmental Approach**: Never shames for low productivity days
- **Energy-Level Matching**: Suggests tasks that fit your current capacity
- **Pattern Recognition**: Helps identify what helps/hurts your productivity
- **Gentle Encouragement**: Soft reminders and supportive messaging

##  System Architecture
The application is built with a modular, object-oriented design:

| Component | Responsibility | C++ Class |
|-----------|----------------|-----------|
| TaskManager | Create/update/delete tasks | `class TaskManager` |
| JournalManager | Log mood entries and fetch past logs | `class JournalManager` |
| MoodEngine | Respond to moods with suggestions/motivation | `class MoodEngine` |
| Storage | Save/load tasks and journal entries | `class Storage` |
| UI | Handle input/output (CLI) | `class App` |

## Project Structure
```
MooDoo/
├── src/
│   ├── main.cpp
│   ├── TaskManager.cpp / .h
│   ├── JournalManager.cpp / .h
│   ├── MoodEngine.cpp / .h
│   ├── Storage.cpp / .h
├── data/
│   ├── tasks.txt
│   ├── journal.txt
├── docs/
│   └── plan.md
├── README.md
├── Makefile
```

## Getting Started

### Prerequisites
- C++17 compatible compiler (g++ recommended)
- Make (for build automation)

### Building
```bash
# Build the project
make

# Run the application
make run

# Clean build files
make clean
```

### Development
```bash
# Format code (requires clang-format)
make format

# Static analysis (requires cppcheck)
make check
```

##  Development Roadmap

### Phase 1: Core Implementation
- [x] Project structure setup
- [x] TaskManager implementation
- [x] JournalManager implementation
- [x] MoodEngine implementation
- [x] Storage system
- [x] Basic CLI interface

### Phase 2: Enhancement (In Progress)
- [x] Enhanced mood analysis (keyword extraction, sentiment analysis)
- [x] Statistics and insights (daily/weekly patterns)
- [x] Smart mood pattern recognition
- [x] Productivity correlation insights
- [ ] AI integration for smart responses
- [ ] JSON data format

### Phase 3: Advanced Features
- [ ] GUI interface (Raylib/Qt/ImGui)
- [ ] Cloud sync capabilities
- [ ] Calendar integration
- [ ] User authentication

## Contributing
This project is currently in development. All rights reserved.

## License
This project is licensed under a proprietary license. All rights reserved.

You may not copy, modify, distribute, or use any part of this codebase without explicit written permission from the author.
