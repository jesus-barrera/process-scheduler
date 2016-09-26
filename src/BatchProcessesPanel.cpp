#include <sstream>
#include <iomanip>

#include "../include/BatchProcessesPanel.h"

BatchProcessesPanel::BatchProcessesPanel(
    WINDOW *parent,
    int nlines, int ncols,
    int begin_x, int begin_y)

    : ProcessesListPanel(parent, "Lote actual", nlines, ncols, begin_x, begin_y) {

    std::stringstream heading;

    // set column heading
    heading << setw(2) << "ID" << " | "
            << setw(2) << "TE" << " | "
            << setw(2) << "TR";

    columns_heading = heading.str();
}

void BatchProcessesPanel::printProcess(Process *process) {
    wprintw(
        inner_win,
        "%-2lu | %-2lu | %-2lu",
        process->program_number,
        process->estimated_time,
        process->getTimeLeft()
    );
}