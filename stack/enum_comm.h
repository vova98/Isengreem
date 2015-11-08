
//PUS_CMD(push, 1, 2, assembly_push(i, buffer, j, commandBuff, val); break;)
//POP_CMD(pop,  2, 1, (*i) += 1; if (buffer[(*i)] != 'a') commandBuff[(*j)++] = 2; else commandBuff[(*j)++] = 18; (*i)++; break;)
DEF_CMD(add, 3, 1)
DEF_CMD(sub, 4, 1)
DEF_CMD(mul, 5, 1)
DEF_CMD(divi,6, 1)
DEF_CMD(end, 7, 1)
DEF_CMD(err, 28,1)
//DEF_CMD(out, 8, 1)
DEF_CMD(sqr, 9, 1)
DEF_CMD(root, 27, 1)
JMP_CMD(ja,  11,2)
JMP_CMD(jae, 12, 2)
JMP_CMD(jb, 13, 2)
JMP_CMD(jbe, 14, 2)
JMP_CMD(je, 15, 2)
JMP_CMD(jne, 16, 2)
//JMP_CMD(jmp, 17, 2)

//enum commands {
//	tmp, push = 1, pop = 2, add = 3, sub = 4, mul = 5, divi = 6, end = 7,
//	out = 8, sqr = 9, push_ax = 10, ja = 11, jae = 12, jb = 13, jbe = 14, je = 15, jne = 16, jmp = 17
//};