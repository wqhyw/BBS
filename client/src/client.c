//
// Created by leo on 2017/12/25.
//

#include "client.h"

static WINDOW *OUTWIN;
static int CURRENT_LINE = 1;
static int LINE_NUM = 1;
static int BACK_GROUD_PID;
static int CLIENT_QUIT = 0;

WINDOW *create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);

    box(local_win, 0, 0);

    wrefresh(local_win);

    return local_win;
}

void destroy_win(WINDOW *local_win) {
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(local_win);

    delwin(local_win);
}

void ui() {
    WINDOW *input_win;
    PANEL *my_panels[2];

    initscr();
    cbreak();
    noecho();
    curs_set(2);


    mvprintw(0, (int) ((COLS - strlen("Welcome!")) / 2), "Welcome!");

    OUTWIN = create_newwin(LINES - 4, COLS, 1, 0);
    input_win = create_newwin(3, COLS, LINES - 3, 0);
    keypad(input_win, TRUE);

    my_panels[0] = new_panel(OUTWIN);
    my_panels[1] = new_panel(input_win);

    update_panels();
    doupdate();

    char *prompt = "command>";
    int len_prompt = (int) strlen(prompt);

    while (1) {
        char buf[MAX_BUF_LEN];
        int input_len;
        int ch;

        mvwprintw(input_win, 1, 1, prompt);

        for (input_len = 0;;) {
            if (input_len < COLS * 0.75) {
                ch = wgetch(input_win);
                if (ch == KEY_DC || ch == KEY_DL || ch == KEY_BACKSPACE || ch == 127) {
                    if (input_len > 0) {
                        mvwprintw(input_win, 1, input_len + len_prompt, " ");
                        wmove(input_win, 1, input_len-- + len_prompt);
                    }
                } else if (ch != '\n' && ch != EOF) {
                    buf[input_len++] = (char) ch;
                    wprintw(input_win, "%c", ch);
                } else {
                    buf[input_len] = '\0';
                    run_cmd(parse_msg(buf, COLS));

                    break;
                }

            } else {
                LOG(ERROR_LOG, "INPUT IS TOO LONG!!");
                break;
            }
        }

        if (CLIENT_QUIT) {
            LOG(INFO_LOG, "Waiting backgroud quit...");
            wait(NULL);
            LOG(INFO_LOG, "Background quited. I am leaving.");
            break;
        }

        wclrtoeol(OUTWIN);
        wrefresh(OUTWIN);

        if (++CURRENT_LINE >= LINES - 5) {
            wclear(OUTWIN);
            CURRENT_LINE = 1;
        }

        box(OUTWIN, 0, 0);

        wclear(input_win);
        box(input_win, 0, 0);

    }

    LOG(INFO_LOG, "Byebye!");

    endwin();

    destroy_win(OUTWIN);
    destroy_win(input_win);
}

void listener() {

}

void run_cmd(MSG *msg) {
    switch (msg->opercode) {
        case OPER_REGISTER:
        case OPER_LOGIN:
        case OPER_SEND:
        case OPER_LOGOUT:
            async_sender(msg, SERVER_IP, SERVER_PORT);
            break;
        case OPER_QUIT:
            async_sender(init_msg(OPER_QUIT, "", 5), SERVER_IP, SERVER_PORT);
            quit();
        default:
            LOG(ERROR_LOG, "INPUT NOT COMMAND!");
    }
}

void quit() {
    LOG(INFO_LOG, "do some cleanning.");
    kill(BACK_GROUD_PID, SIGQUIT);
    CLIENT_QUIT = 1;
}

void LOG(const char *prompt, const char *s) {
    mvwprintw(OUTWIN, CURRENT_LINE, 1, "[line %2d] %s %s", LINE_NUM++, prompt, s);

    if (CURRENT_LINE >= LINES - 5) {
        wclear(OUTWIN);
        box(OUTWIN, 0, 0);
        CURRENT_LINE = 1;
    }

    wrefresh(OUTWIN);
}

static void ouch(int sig) {
    LOG(INFO_LOG, "I am listener. I am aksed to quit. Bye!");
    exit(0);
}