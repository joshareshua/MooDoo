# MooDoo Development Plan

## Project Vision
MooDoo is a mental health-aware planner that adapts to the user's emotional state, providing personalized support for people with ADHD and mental health considerations.

## Core Concept
- **Mood-Aware Planning**: Adjust task suggestions based on current emotional state
- **Supportive Environment**: Provide encouragement and understanding when productivity is low
- **Motivation Leverage**: Harness positive moods for enhanced productivity
- **Non-Judgmental**: Never shame users for low productivity days

## System Design

### Component Responsibilities

#### 1. TaskManager
- **Purpose**: Handle CRUD operations for tasks
- **Key Features**:
  - Create new tasks with priority levels
  - Mark tasks as complete/incomplete
  - Adjust task difficulty based on mood
  - Suggest task modifications for low-energy days

#### 2. JournalManager
- **Purpose**: Handle mood logging and emotional tracking
- **Key Features**:
  - Log daily mood entries with timestamps
  - Analyze mood patterns over time
  - Extract emotional keywords from entries
  - Provide mood history for insights

#### 3. MoodEngine
- **Purpose**: Generate contextual responses based on mood
- **Key Features**:
  - Analyze journal entries for emotional content
  - Generate supportive messages for difficult days
  - Suggest task modifications based on energy levels
  - Provide motivational content for positive moods

#### 4. Storage
- **Purpose**: Persist data between sessions
- **Key Features**:
  - Save tasks and journal entries to files
  - Load historical data on startup
  - Backup and restore functionality
  - Data validation and integrity checks

## Implementation Phases

### Phase 1: Foundation (Current)
1. **Project Setup** ✅
   - Directory structure
   - Build system (Makefile)
   - Basic documentation

2. **TaskManager Implementation** ✅
   - Task data structure
   - CRUD operations
   - Priority system
   - Task status tracking
   - **NEW: Task difficulty levels**
   - **NEW: Mood-based task recommendations**

3. **JournalManager Implementation** ✅
   - Mood entry data structure
   - Timestamp handling
   - Basic text analysis
   - Entry retrieval

4. **Storage System** ✅
   - File I/O operations
   - Data serialization
   - Error handling
   - Data validation

5. **Basic CLI Interface** ✅
   - Menu system
   - User input handling
   - Basic output formatting
   - **NEW: Daily mood summary & progress tracking**
   - **NEW: Weekly mood & productivity patterns**
   - **NEW: Mood-based task recommendations**
   - **NEW: Gentle reminders (ADHD-friendly)**

### Phase 2: Intelligence
1. **MoodEngine Enhancement** ✅
   - Keyword extraction ✅
   - Sentiment analysis ✅
   - Response generation ✅
   - Context awareness ✅
   - **NEW: Weekly mood pattern recognition**
   - **NEW: Productivity correlation insights**

2. **AI Integration** (Future)
   - OpenAI API integration
   - Custom response generation
   - Advanced mood analysis
   - Personalized suggestions

### Phase 3: Polish
1. **Enhanced UI/UX**
   - Better formatting
   - Color coding
   - Progress indicators
   - Interactive elements

2. **Advanced Features**
   - Statistics and insights
   - Goal tracking
   - Habit formation
   - Export capabilities

## User Experience Flow

### Daily Interaction
1. **Morning Check-in**
   - User opens app
   - Logs current mood/energy level
   - Receives personalized greeting

2. **Task Review**
   - View existing tasks
   - Receive mood-based suggestions
   - Adjust task priorities if needed

3. **Throughout the Day**
   - Update task status
   - Log mood changes
   - Receive encouragement

4. **Evening Reflection**
   - Review completed tasks
   - Log final mood
   - Receive supportive summary

## Technical Considerations

### Data Structures
```cpp
struct Task {
    int id;
    string title;
    string description;
    Priority priority;
    bool completed;
    time_t created;
    time_t completed_time;
};

struct MoodEntry {
    int id;
    string content;
    MoodLevel mood;
    time_t timestamp;
    vector<string> keywords;
};
```

### File Formats
- **Tasks**: Simple text format with delimiters
- **Journal**: Timestamped entries
- **Future**: JSON for more complex data

### Error Handling
- File I/O errors
- Invalid user input
- Data corruption
- Graceful degradation

## Success Metrics
- User engagement (daily usage)
- Task completion rates
- Mood improvement over time
- User feedback and satisfaction

## Future Enhancements
- Mobile app version
- Cloud synchronization
- Social features (anonymous support groups)
- Integration with health apps
- Professional therapist dashboard
