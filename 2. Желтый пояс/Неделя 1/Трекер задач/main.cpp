#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

TaskStatus Next(TaskStatus task_status) {
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    const TasksInfo &GetPersonTasksInfo(const string &person) const;

    void AddNewTask(const string &person);

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count);

private:
    map<string, TasksInfo> person_tasks_;
};

const TasksInfo &TeamTasks::GetPersonTasksInfo(const string &person) const {
    return person_tasks_.at(person);
}

void TeamTasks::AddNewTask(const string &person) {
    ++person_tasks_[person][TaskStatus::NEW];
}

void RemoveZeros(TasksInfo &tasks_info) {
    vector<TaskStatus> statuses_to_remove;
    for (const auto &task_item : tasks_info) {
        if (task_item.second == 0) {
            statuses_to_remove.push_back(task_item.first);
        }
    }
    for (const TaskStatus status : statuses_to_remove) {
        tasks_info.erase(status);
    }
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string &person, int task_count) {
    TasksInfo updated_tasks, untouched_tasks;
    TasksInfo &tasks = person_tasks_[person];
    for (TaskStatus status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status)) {
        updated_tasks[Next(status)] = min(task_count, tasks[status]);
        task_count -= updated_tasks[Next(status)];
    }
    for (TaskStatus status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status)) {
        untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
        tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
    }
    tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];
    RemoveZeros(updated_tasks);
    RemoveZeros(untouched_tasks);
    RemoveZeros(person_tasks_.at(person));
    return {updated_tasks, untouched_tasks};
}
