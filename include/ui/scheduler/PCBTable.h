#ifndef _BCP_TABLE_INCLUDED_
#define _BCP_TABLE_INCLUDED_

#include <string>
#include <ncurses.h>

#include "ui/Table.h"
#include "Process.h"

typedef Table<Process *> ProcessesTable;

using namespace std;

class PCBTable: public ProcessesTable {
public:
    static const string SEPARATOR;
    static const char str_states[];

    PCBTable(WINDOW *window);
    void post();

protected:
    void printRow(Process *process);

private:
    WINDOW *window;

    string formatTime(int time_value, int width);
    string formatOperation(Process *process);
};

#endif
