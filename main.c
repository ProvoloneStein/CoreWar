#include "assem.h"
#include "stdlib.h"
#include "stdio.h"
/*
t_pars *parser_init()
{
	t_pars *pars;

	pars = (t_pars*)malloc(sizeof(t_pars));
	pars->comment = NULL;
	pars->name = NULL;
	pars->line = 0;
	pars->column = 0;
	pars->token = NULL;
	return(pars);
}

void move(t_pars *pars)
{
	pars->token = pars->token->next->next;
}

int main(int ac, char **av)
{
	t_pars *pars;

	pars = parser_init();
	pars->token = (t_token*)malloc(sizeof(t_token));
	pars->token->content = "kek";
	pars->token->next = (t_token*)malloc(sizeof(t_token));
	pars->token->next->content = "kok";
	pars->token->next->next = (t_token*)malloc(sizeof(t_token));
	pars->token->next->next->content = "kak";
	printf("%s", pars->token->content);
	move(pars);
	printf("%s", pars->token->content);
	return(0);
}*/
}