#ifndef TEXT_GENERATOR_H
#define TEXT_GENERATOR_H

#include "frequency_table.h"

void loadFrequencyTableFromCSV(const char *filename, WordRelation **wordRelations);
void generateRandomText(WordRelation *wordRelations, int wordCount);

#endif // TEXT_GENERATOR_H
