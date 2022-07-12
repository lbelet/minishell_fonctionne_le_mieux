#include "minishell.h"

void    display_prompt(int num)
{
    num++;
    write(1, "\n", 1);
	rl_on_new_line();
//	rl_replace_line("", 0);
	rl_redisplay();
}
    
void    define_input_signals(void)
{
    signal(SIGINT, display_prompt);//CTRL+C
    signal(SIGQUIT, SIG_IGN);//CTRL+"\"
}