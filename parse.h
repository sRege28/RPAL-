#ifndef PARSE_H
#define PARSE_H


void buildTree(Tree t, int count);

void parse();

void read(string value);


void expect(tokenQueue L_Q, string type, string value);


token peek(tokenQueue L_Q);



void parseE();
void parseEw();
void parseD();
void parseDa();
void parseDb();
void parseDr();
void parseR();
void parseRn();
void parseVb();
void parseVl();
void parseT();
void parseTa();
void parseTc();
void parseB();
void parseBt();
void parseBs();
void parseBp();
void parseA();
void parseAt();
void parseAf();
void parseAp();


void testParse();


#endif
