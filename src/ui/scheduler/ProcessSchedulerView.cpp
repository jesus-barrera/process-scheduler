#include "ui/scheduler/ProcessSchedulerView.h"
#include "ui/screen.h"
#include "ui/GridLayout.h"
#include "ProcessScheduler.h"

ProcessSchedulerView::ProcessSchedulerView(ProcessScheduler *scheduler) {
    this->scheduler = scheduler;

    new_processes_counter = new Counter(content, "Procesos nuevos: ", 0, 0);
    total_time_counter = new Counter(content, "Tiempo total: ", 1, 0);

    panels_win = derwin(content, CONTENT_LINES - 2, COLS, 2, 0);
    syncok(panels_win, TRUE);

    initPanels();
}

ProcessSchedulerView::~ProcessSchedulerView() {
    delete(new_processes_counter);
    delete(total_time_counter);

    delete(ready_panel);
    delete(blocked_panel);
    delete(process_panel);
    delete(terminated_panel);

    delwin(panels_win);
}

/**
 * Writes all elements to screen.
 */
void ProcessSchedulerView::post() {
    // show counters
    new_processes_counter->post();
    total_time_counter->post();

    // show panels
    ready_panel->post();
    blocked_panel->post();
    process_panel->post();
    terminated_panel->post();

    update();
}

/**
 * Updates panels with the current data.
 */
void ProcessSchedulerView::update() {
    new_processes_counter->setValue(scheduler->new_processes.size());
    total_time_counter->setValue(scheduler->timer.getSeconds());

    process_panel->display(scheduler->running_process);
    ready_panel->setProcesses(scheduler->ready_processes);
    blocked_panel->setProcesses(scheduler->blocked_processes);
    terminated_panel->setProcesses(scheduler->terminated_processes);
}

void ProcessSchedulerView::initPanels() {
    GridLayout grid(panels_win, 2, 4); // 2x4 layout over panels_win

    grid.add(1, 1, 0, 0); // ready panel
    grid.add(1, 1, 0, 1); // blocked panel
    grid.add(1, 2, 1, 0); // process panel
    grid.add(2, 2, 0, 2); // terminated panel

    ready_panel = new ReadyProcessesPanel(
        panels_win,
        grid[READY_PANEL].height,
        grid[READY_PANEL].width,
        grid[READY_PANEL].y,
        grid[READY_PANEL].x
    );

    blocked_panel = new BlockedProcessesPanel(
        panels_win,
        grid[BLOCKED_PANEL].height,
        grid[BLOCKED_PANEL].width,
        grid[BLOCKED_PANEL].y,
        grid[BLOCKED_PANEL].x
    );

    process_panel = new ProcessPanel(
        panels_win,
        grid[PROCESS_PANEL].height,
        grid[PROCESS_PANEL].width,
        grid[PROCESS_PANEL].y,
        grid[PROCESS_PANEL].x
    );

    terminated_panel = new FinishedProcessesPanel(
        panels_win,
        grid[TERMINATED_PANEL].height,
        grid[TERMINATED_PANEL].width,
        grid[TERMINATED_PANEL].y,
        grid[TERMINATED_PANEL].x
    );
}