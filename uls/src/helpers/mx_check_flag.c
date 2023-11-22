#include "../../inc/uls.h"

void mx_check_flag(char c, t_flags *opts) {
	switch (c) {
		case '1':
			opts->one = true;
			opts->l = false;
			opts->C = false;
			break;
		case 'A':
			opts->A = true;
			break;
		case 'a':
			opts->A = false;
			opts->a = true;
			break;
		case 'C':
			opts->C = true;
			opts->one = false;
			opts->l = false;
			break;
		case 'F':
			opts->F = true;
			break;
		case 'f':
			opts->f = true;
			opts->a = true;
			break;
		case 'G':
			opts->G = true;
			break;
		case 'i':
			opts->i = true;
		case 'l':
			opts->l = true;
			opts->one = false;
			opts->C = false;
			break;
		case 'm':
			opts->m = true;
			break;
		case 'o':
			opts->o = true;
			break;
		case 'p':
			opts->p = true;
			break;
		case 'r':
			opts->r = true;
			break;
		case 'S':
			opts->S = true;
			opts->t = false;
			break;
		case 's':
			opts->s = true;
			break;
		case 'T':
			opts->T = true;
			break;
		case 't':
			opts->t = true;
			opts->S = false;
			break;
		case 'x':
			opts->x = true;
			opts->C = false;
			opts->one = false;
			opts->l = false;
			break;
		default:
			mx_printerr("uls: illegal option -- ");
			write(2, &c, 1);
			mx_printerr("\n");
			mx_throw_usage();
	}
}

