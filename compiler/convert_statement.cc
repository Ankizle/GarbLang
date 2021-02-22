#include <map>
#include <functional>
#include <stdio.h>
#include "convert_statement.h"

std::map<std::string, std::function<void(FILE *f, char **operands, size_t len)>> converters = {
	{"var", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "%s = (long long*)calloc(1, 1);", operands[0]);
	 }},
	{"mov", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "memcpy(%s, %s);", operands[0], operands[1]);
	 }},
	{"alc", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "%s = (long long*)realloc(%s, %s);", operands[0], operands[0], operands[1]);
	 }},
	{"free", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "gfree(%s);", operands[0]);
	 }},
	{"bind", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "gbind(%s, %s);", operands[0], operands[1]);
	 }},
	{"ret", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "return (long long *)%s;", operands[0]);
	 }},
	{"add", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s+=*%s;", operands[0], operands[1]);
	 }},
	{"sub", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s-=*%s;", operands[0], operands[1]);
	 }},
	{"mul", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s*=*%s;", operands[0], operands[1]);
	 }},
	{"div", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s/=*%s;", operands[0], operands[1]);
	 }},
	{"mod", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s%=*%s;", operands[0], operands[1]);
	 }},
	{"and", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s&&=*%s;", operands[0], operands[1]);
	 }},
	{"or", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s||=*%s;", operands[0], operands[1]);
	 }},
	{"not", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s=!(*%s);", operands[0], operands[0]);
	 }},
	{"band", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s&=*%s;", operands[0], operands[1]);
	 }},
	{"bor", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s|=*%s;", operands[0], operands[1]);
	 }},
	{"bnot", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s~=(*%s);", operands[0], operands[1]);
	 }},
	{"xor", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s^=*%s;", operands[0], operands[1]);
	 }},
	{"cmp", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "*%s=(*%s)-(*%s);", operands[2], operands[0], operands[1]);
	 }},
	{"jmpeq", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "if (*%s == 0) goto %s;", operands[0], operands[1]);
	 }},
	{"jmpls", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "if (*%s < 0) goto %s;", operands[0], operands[1]);
	 }},
	{"jmpgt", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "if (*%s > 0) goto %s;", operands[0], operands[1]);
	 }},
	{"cal", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "%s = %s();", operands[1], operands[0]);
	 }},
	{"calp", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "%s = ((genf)%s)();", operands[1], operands[0]);
	 }},
	{"lbl", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "%s:;", operands[0]);
	 }},
	{"set", [](FILE *f, char **operands, size_t len) {
		 fprintf(f, "%s[%s] = %s;", operands[0], operands[1], operands[2]);
	 }},
};

void write_statement(FILE *f, char *lbl, char **operands, size_t len)
{
	converters[lbl](f, operands, len);
}