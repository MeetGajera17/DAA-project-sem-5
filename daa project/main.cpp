#include <iostream>
#include <vector>
#include <algorithm>

class Event {
public:
    std::string name;
    int start_time; // Start time in hours (0-23)
    int end_time;   // End time in hours (0-23)

    Event(std::string name, int start, int end) : name(name), start_time(start), end_time(end) {}

    // Overload the < operator for sorting events by end time
    bool operator<(const Event &other) const {
        return end_time < other.end_time;
    }
};

class EventScheduler {
private:
    std::vector<Event> events;

public:
    void addEvent(const Event &event) {
        // Check for overlap with existing events
        for (const auto &existing_event : events) {
            if (event.start_time < existing_event.end_time && event.end_time > existing_event.start_time) {
                std::cout << "Cannot add event '" << event.name << "': Time conflict with '"
                          << existing_event.name << "'" << std::endl;
                return;
            }
        }
        events.push_back(event);
        
        std::cout << "Event '" << event.name << "' added successfully." << std::endl;
    }

    void displaySchedule() {
        std::cout << "\nScheduled Events:\n";
        for (const auto &event : events) {
            std::cout << "Event: " << event.name 
                      << ", Start Time: " << event.start_time 
                      << ", End Time: " << event.end_time << std::endl;
        }
    }

    void selectNonOverlappingEvents() {
        // Sort events by end time
        std::sort(events.begin(), events.end());

        std::cout << "\nSelected Non-Overlapping Events:\n";
        if (events.empty()) {
            std::cout << "No events scheduled." << std::endl;
            return;
        }

        // Select the first event
        Event last_selected_event = events[0];
        std::cout << last_selected_event.name << std::endl;

        // Iterate through the sorted events and select non-overlapping events
        for (size_t i = 1; i < events.size(); i++) {
            if (events[i].start_time >= last_selected_event.end_time) {
                std::cout << events[i].name << std::endl;
                last_selected_event = events[i];
            }
        }
    }
};

int main() {
    EventScheduler scheduler;
    int numberOfEvents;

    std::cout << "Enter the number of events you want to schedule: ";
    std::cin >> numberOfEvents;

    for (int i = 0; i < numberOfEvents; i++) {
        std::string name;
        int start_time, end_time;

        std::cout << "Enter name for event " << (i + 1) << ": ";
        std::cin >> name;
        std::cout << "Enter start time (0-23) for event " << (i + 1) << ": ";
        std::cin >> start_time;
        std::cout << "Enter end time (0-23) for event " << (i + 1) << ": ";
        std::cin >> end_time;

        // Create a new event and add it to the scheduler
        Event newEvent(name, start_time, end_time);
        scheduler.addEvent(newEvent);
    }

    // Display the schedule
    scheduler.displaySchedule();

    // Select and display non-overlapping events
    scheduler.selectNonOverlappingEvents();

    return 0;
}
