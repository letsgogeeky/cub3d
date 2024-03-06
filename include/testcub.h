#ifndef TESTCUB_H
#define TESTCUB_H
# include "cube.h"

t_map	*mock_map_shifted_section_valid();
t_map	*mock_base_map_valid();
t_map	*mock_passage_map_valid();
t_map	*mock_deep_passage_map_valid();

t_map	*mock_map_shifted_section_invalid();
t_map	*mock_map_with_spaces_invalid();
t_map	*mock_passage_map_invalid();
t_map	*mock_deep_passage_map_invalid();

#endif